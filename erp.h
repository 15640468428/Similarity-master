#pragma once
#ifndef  erp_h
#define erp_h

#include <iostream>
#include <vector>
#include "tool.h"
using namespace std;

class ERP {
public:
	vector<pair<int,int>> path;
	double minDistance(string a,string b,char gap,int dis(char,char)) {
		int i, j;
		if (a.size() == 0) {
			double result = 0;
			for (i = 0;i < b.size();i++)
				result += dis(b[i],gap);
			return result;
		}
		if (b.size() == 0) {
			double result = 0;
			for (i = 0;i < a.size();i++)
				result += dis(a[i], gap);
			return result;
		}
		int len1 = a.length();
		int len2 = b.length();
		vector<vector<GridItem*> > dp(len1 + 1, vector<GridItem*>(len2 + 1));
		dp[0][0] = new GridItem(0,-1,-1);
		for (i = 1; i <= len1; ++i)
			dp[i][0] = new GridItem(dp[i-1][0]->value+ dis(a[i-1],gap),i-1,0);
		for (j = 1; j <= len2; ++j)
			dp[0][j] = new GridItem(dp[0][j-1]->value + dis(b[j-1], gap),0,j-1);
		for (i = 1; i <= len1; ++i) {
			for (j = 1; j <= len2; ++j) {
				double minV;
				int tmp1, tmp2;
				if (dp[i - 1][j - 1]->value + dis(a[i - 1], b[j - 1]) <= dp[i][j - 1]->value + dis(b[j - 1], gap)) {
					tmp1 = i - 1; tmp2 = j - 1; minV = dp[i - 1][j - 1]->value + dis(a[i - 1], b[j - 1]);
				}else {
					tmp1 = i; tmp2 = j - 1; minV = dp[i][j - 1]->value + dis(b[j - 1], gap);
				}
				if (dp[tmp1][tmp2]->value > dp[i - 1][j]->value + dis(a[i - 1], gap)) {
					tmp1 = i - 1; tmp2 = j; minV = dp[i - 1][j]->value + dis(a[i - 1], gap);
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

#endif // ! erp_h