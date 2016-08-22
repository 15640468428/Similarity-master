#pragma once
#ifndef grid_h
#define grid_h
#include <iostream>
#include <vector>
#include <queue>
#include "point.h"
#include "tool.h"
using namespace std;

class Grid {
public:
	Grid(double a) {
		this->threshold = a;
		latD = -9999999;
		lngD = -9999999;
		latU = 9999999;
		lngU = 9999999;
	}
	Grid() {
		this->threshold = 1;
		latD = 9999999;
		lngD = 9999999;
		latU = -9999999;
		lngU = -9999999;
	}
	void initGrid(vector<Point*> a) {
		for (int i = 0;i < a.size();i++) {
			if (a[i]->latitude > latU) {
				latU = a[i]->latitude;
			}
			if (a[i]->longitude > lngU) {
				lngU = a[i]->longitude;
			}
			if (a[i]->latitude < latD) {
				latD = a[i]->latitude;
			}
			if (a[i]->longitude < lngD) {
				lngD = a[i]->longitude;
			}
		}
	}
	void makePartition(double a) {
		lngU += 0.1;
		latU += 0.1;
		latD -= 0.1;
		lngD -= 0.1;
		this->threshold = a;
		this->oN = (int)((lngU-lngD)/threshold+0.5);
		this->vN = (int)((latU-latD)/threshold+0.5);
		for (int i = 0;i < vN;i++) {
			vector<queue<pair<Point*, int>>*> tmp;
			for (int j = 0;j < oN;j++) {
				queue<pair<Point*, int>>* tQ = new queue<pair<Point*, int>>();
				tmp.push_back(tQ);
			}
			grid.push_back(tmp);
		}
	}
	void insert(Point* a,int value) {
		int oNT = (int)((a->longitude-lngD)/threshold);
		int vNT = (int)((a->latitude - latD) / threshold);
		grid[vNT][oNT]->push(make_pair(a,value));
		if(vNT+1<vN) grid[vNT+1][oNT]->push(make_pair(a, value));
		if(oNT+1<oN) grid[vNT][oNT+1]->push(make_pair(a, value));
		if(vNT-1>=0) grid[vNT-1][oNT]->push(make_pair(a, value));
		if(oNT-1>=0) grid[vNT][oNT-1]->push(make_pair(a, value));
		if (vNT + 1<vN&&oNT + 1<oN) grid[vNT + 1][oNT+1]->push(make_pair(a, value));
		if (vNT - 1 >= 0&& oNT - 1 >= 0) grid[vNT - 1][oNT-1]->push(make_pair(a, value));
		if (vNT + 1<vN&&oNT - 1>=0) grid[vNT + 1][oNT - 1]->push(make_pair(a, value));
		if (vNT - 1 >= 0 && oNT + 1<oN) grid[vNT - 1][oNT + 1]->push(make_pair(a, value));
	}
	void buildList(Point* a,double dis(double,double)) {
		queue<int>* result=new queue<int>();
		int oNT = (int)((a->longitude - lngD) / threshold);
		int vNT = (int)((a->latitude - latD) / threshold);
		queue<pair<Point*, int>>* tmp=grid[vNT][oNT];
		while (!tmp->empty()) {
			pair<Point*, int> ttmp = tmp->front();
			tmp->pop();
			if (dis(ttmp.first->latitude,a->latitude)<= threshold&&dis(ttmp.first->longitude , a->longitude) <= threshold) {
				result->push(ttmp.second);
			}
		}
		IntersectionList.push_back(result);
	}
	double threshold;
	double latD, latU;
	double lngD, lngU;
	int oN, vN;
	vector<vector<queue<pair<Point*,int>>*>> grid;
	vector<queue<int>*> IntersectionList;
};

#endif