#pragma once
#ifndef  swale_h
#define swale_h
#include <iostream>
#include "tool.h"
#include "point.h"
#include <vector>
using namespace std;

class Swale {
public:
	vector<pair<int,int>> path;
	double getSwaleScore(vector<Point*> a,vector<Point*> b,int gap,int reward,double threshold,double dis(double,double),bool reverse=true) {
		int i, j;
		int len1 = a.size();
		int len2 = b.size();
		if (len1 == 0) return len2*gap;
		if (len2 == 0) return len1*gap;
		vector<vector<GridItem*>> swale(len1 + 1, vector<GridItem*>(len2 + 1));;
		swale[0][0] = new GridItem(0, -1, -1);
		for (i = 1; i <= len2; ++i) {
			swale[0][i] = new GridItem(i*gap,0,i-1);
		}
		for (i = 1; i <= len1; ++i) {
			swale[i][0] = new GridItem(i*gap, i-1, 0);
		}
		for (i = 1;i <= len1;i++) {
			for (j = 1;j <= len2;j++) {
				if (dis(a[i-1]->latitude,b[j-1]->latitude) <= threshold&&dis(a[i-1]->longitude,b[j-1]->longitude) <= threshold) {
					swale[i][j] = new GridItem(reward + swale[i - 1][j - 1]->value, i-1, j-1);
				}else if (gap + swale[i - 1][j]->value>gap + swale[i][j - 1]->value) {
					swale[i][j] = new GridItem(gap + swale[i - 1][j]->value,i-1,j);
				}else{
					swale[i][j] = new GridItem(gap + swale[i][j - 1]->value, i, j-1);
				}
			}
		}
		if (IS_DEBUG) {
			for (i = 0;i < swale.size();i++) {
				for (j = 0;j < swale[i].size();j++) {
					printf("%5.0lf ", swale[i][j]->value);
				}
				cout << endl;
			}
		}
		if (IS_FIND_PATH) {
			path = getPath(swale, len1, len2);
			for (i = path.size() - 1;i >= 0;i--) {
				cout << "(" << path[i].first << "," << path[i].second << ")" << " ";
			}
			cout << endl;
		}
		return swale[len1][len2]->value;
	}
};

#endif // ! swale_h