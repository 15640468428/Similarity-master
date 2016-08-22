#pragma once
#ifndef  edr_h
#define edr_h
#include <iostream>
#include <vector>
#include "tool.h"
#include "point.h"
using namespace std;

class EDR {
public:
	vector<pair<int,int>> path;

	double minDistance(string word1, string word2,int md,int dc(char,char)) {
		int i, j;
		int len1 = word1.length();
		int len2 = word2.length();
		if (len1 == 0)
			return len2;
		if (len2 == 0)
			return len1;
		vector<vector<GridItem*> > dp(len1 + 1, vector<GridItem*>(len2 + 1));
		dp[0][0] = new GridItem(0,-1,-1);
		for (i = 1; i <= len1; ++i)
			dp[i][0] = new GridItem(i,i-1,0);
		for (j = 1; j <= len2; ++j)
			dp[0][j] = new GridItem(j, 0, j-1);
		int cost;
		for (i = 1; i <= len1; ++i) {
			for (j = 1; j <= len2; ++j) {
				cost = dc(word1[i-1],word2[j-1])<=md ? 0 : 1;
				int tmp1, tmp2;
				double minV = 0;
				if (dp[i - 1][j - 1]->value + cost < dp[i][j - 1]->value + 1) {
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
	int EDRComputation(vector<Point*> a, vector<Point*> b, double threshold, vector<queue<int>*> IntersectionList) {
		int i, j;
		int len1 = a.size();
		int len2 = b.size();
		vector<int> matches(2*len2 + 1);
		matches[0] = 0;
		for (i = 1;i <= 2 * len2;i++)
			matches[i] = len1 + 1;
		int max = 0;
		for (j = 0;j < len2;j++) {
			int c = 0;
			int temp = matches[0];
			int temp2 = matches[0];
			queue<int>* tQ = IntersectionList[j];
			while (!tQ->empty()) {
				int k = tQ->front();
				tQ->pop();
				if (temp < k) {
					while (matches[c] < k) {
						if (temp < matches[c] - 1 && temp < len1 - 1) {
							temp2 = matches[c];
							matches[c] = temp + 1;
							temp = temp2;
						}
						else temp = matches[c];
						c++;
					}
					temp2 = matches[c];
					matches[c] = temp + 1;
					temp = matches[c+1];
					if (matches[c + 1] > k) matches[c + 1] = k;
					if (max < c + 1) max = c + 1;
					c += 2;
				}else if(temp2<k&&k<matches[c]){
					temp2 = temp;
					temp = matches[c];
					matches[c] = k;
					if (max < c) max = c;
					c++;
				}
			}
			for (j = c;j <= max + 1;j++) {
				if (temp < matches[j] - 1 && temp < len1 - 1) {
					temp2 = matches[j];
					matches[j] = temp + 1;
					temp = temp2;
					if (max < j) max = j;
				}else temp = matches[j];
			}
		}
		return max - len1 - len2;
	}

};

#endif // ! edr_h