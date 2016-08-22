#pragma once
#ifndef  editdistance_h
#define editdistance_h
#include <iostream>
#include <vector>
#include "tool.h"
#include "point.h"
using namespace std;
#define NDEBUG true

class EditDistance {
public:
	vector<pair<int,int>> path;
	double minDistance(string word1, string word2) {
		int i, j;
         int len1 = word1.length();
         int len2 = word2.length();
         if (len1 == 0) 
			 return len2;
         if (len2 == 0) 
			 return len1;
         vector<vector<GridItem*> > dp(len1 + 1, vector<GridItem*>(len2 + 1));
		 dp[0][0] = new GridItem(0, -1, -1);
		 for (i = 1; i <= word1.size(); ++i) {
			 dp[i][0] = new GridItem(i, i - 1, 0);
		 }for (j = 1;j <= word2.size();j++) {
			 dp[0][j] = new GridItem(j, 0, j - 1);
		 }
         int cost;
         for (int i = 1; i <= len1; ++i) {
             for (int j = 1; j <= len2; ++j) {
				cost = (word1[i - 1] == word2[j - 1]) ? 0 : 1;
				double minV;
				int tmp1, tmp2;
				if (dp[i - 1][j - 1]->value + cost <= dp[i][j - 1]->value + 1) {
					tmp1 = i - 1; tmp2 = j - 1; minV = dp[i - 1][j - 1]->value + cost;
				}else {
					tmp1 = i; tmp2 = j - 1; minV = dp[i][j - 1]->value + 1;
				}
				if (minV > dp[i - 1][j]->value + 1) {
					tmp1 = i - 1; tmp2 = j; minV = dp[i - 1][j]->value + 1;
				}
				dp[i][j] = new GridItem(minV,tmp1,tmp2);
			}
		}
		if (IS_DEBUG) {
			for (i = 1; i <= len1; ++i) {
				for (j = 1; j <= len2; ++j)
					cout << dp[i][j]->value << " ";
				cout << endl;
			}
		}
		if (IS_FIND_PATH) {
			path = getPath(dp, len1, len2);
			for (i = path.size() - 1;i >= 0;i--) {
				cout << "(" << path[i].first << "," << path[i].second << ")" << " ";
			}
			cout << endl;
		}
		return dp[len1][len2]->value;
	}
};

#endif // ! editdistance_h