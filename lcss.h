#pragma once
#ifndef  lcss_h
#define lcss_h

#include <iostream>
#include <vector>
#include "tool.h"
#include "point.h"
#include "grid.h"
using namespace std;

class LCSS {
public:
	vector<pair<int,int>> path;
	/*
	* LCSS with string
	*/
	int LcssScore(string a,string b,int v,int dis(char, char)) {
		int i, j;
		if (a.size() == 0 || b.size() == 0) return 0;
		vector<vector<GridItem*>> lcss(a.size() + 1, vector<GridItem*>(b.size() + 1));;
		lcss[0][0] = new GridItem(0, -1, -1);
		for (i = 1; i <= a.size(); ++i) {
			lcss[i][0] = new GridItem(0, i - 1, 0);
		}for (j = 1;j <= b.size();j++) {
			lcss[0][j] = new GridItem(0, 0, j - 1);
		}
		for (i = 1;i <= a.size();i++) {
			for (j = 1;j <= b.size();j++) {
				if (dis(a[i - 1],b[j - 1]) <= v) {
					lcss[i][j] = new GridItem(lcss[i-1][j-1]->value+1,i-1,j-1);
				}
				else if(lcss[i - 1][j]->value>lcss[i][j - 1]->value){
					lcss[i][j] = new GridItem(lcss[i - 1][j]->value,i-1,j);
				}else lcss[i][j] = new GridItem(lcss[i][j - 1]->value, i, j-1);
			}
		}
		if (IS_DEBUG) {
			for (int i = 0; i <= a.size(); ++i) {
				for (int j = 0; j <= b.size(); ++j)
					cout << lcss[i][j]->value << " ";
				cout << endl;
			}
		}
		if (IS_FIND_PATH) {
			path = getPath(lcss, a.size(), b.size());
			for (i = path.size() - 1;i >= 0;i--) {
				cout << "(" << path[i].first << "," << path[i].second << ")" << " ";
			}
			cout << endl;
		}
		return lcss[a.size()][b.size()]->value;
	}
	
	/*
	* LCSS with Trajectories data set
	* S1  |  FTSE
	*/
	int LcssScore(vector<Point*> a, vector<Point*> b, double ddThreshold,int timeThreshold,double dis(double,double)) {
		int i, j;
		if (a.size() == 0 || b.size() == 0) return 0;
		vector<vector<GridItem*>> lcss(a.size() + 1, vector<GridItem*>(b.size() + 1));;
		lcss[0][0] = new GridItem(0,-1,-1);
		for (i = 1; i <= a.size(); ++i)
			lcss[i][0] = new GridItem(0,i-1,0);
		for (j = 1; j <= b.size(); ++j)
			lcss[0][j] = new GridItem(0,0, j-1);
		for (i = 1;i <= a.size();i++) {
			for (j = 1;j <= b.size();j++) {
				if (dis(a[i - 1]->latitude , b[j - 1]->latitude)<= ddThreshold&&dis(a[i - 1]->longitude , b[j - 1]->longitude)<= ddThreshold&&mabs(a[i - 1]->time - b[j - 1]->time) <= timeThreshold) {
					lcss[i][j] = new GridItem(lcss[i - 1][j - 1]->value + 1, i-1, j - 1);
				}else if(lcss[i - 1][j]->value< lcss[i][j - 1]->value){
					lcss[i][j] = new GridItem(lcss[i][j - 1]->value, i, j - 1);
				}else {
					lcss[i][j] = new GridItem(lcss[i-1][j]->value, i-1, j);
				}
			}
		}
		if (IS_DEBUG) {
			for (int i = 1; i <= a.size(); ++i) {
				for (int j = 1; j <= b.size(); ++j)
					cout << lcss[i][j]->value << " ";
				cout << endl;
			}
		}
		if (IS_FIND_PATH) {
			path = getPath(lcss, a.size(), b.size());
			for (int i = path.size() - 1;i >= 0;i--) {
				cout << "(" << path[i].first << "," << path[i].second << ")" << " ";
			}
			cout << endl;
		}
		return lcss[a.size()][b.size()]->value;
	}
	int S1(vector<Point*> a, vector<Point*> b, double d, int v,double dis(double,double)) {
		int len1 = a.size();
		int len2 = b.size();
		return LcssScore(a,b,d,v,dis)/mmin(len1,len2);
	}

	int LCSSComputation(vector<Point*> a, vector<Point*> b, double threshold,vector<queue<int>*> IntersectionList) {
		int i, j;
		int max=0;
		int len1 = a.size();
		int len2 = b.size();
		vector<int> matches(len2+1);
		matches[0] = 0;
		for (i = 1;i <= len2;i++)
			matches[i] = len1 + 1;
		for (j = 0;j < len2;j++) {
			int c = 0;
			int temp = matches[0];
			queue<int>* tQ = IntersectionList[j];
			while (!tQ->empty()) {
				int k = tQ->front();
				tQ->pop();
				if (temp < k) {
					while (matches[c] < k) {
						c++;
					}
					temp = matches[c];
					matches[c] = k;
					if (c > max) max = c;
				}
			}
		}
		return max;
	}
};

#endif // ! lcss_h