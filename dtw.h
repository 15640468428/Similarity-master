#pragma once
#ifndef dtw_h
#define dtw_h

#include <vector>
#include <iostream>
#include "tool.h"
#include "point.h"
using namespace std;

#define infinity INT_MAX

class DTW {
public:
	vector<pair<int,int>> path;
	
	/*
	* DTW with trajectories data set
	*/
	double DTWDistance(vector<Point*> a,vector<Point*> b,double dis(Point* x,Point* y)) {
		int len1 = a.size();
		int len2 = b.size();
		int i, j;
		vector<vector<GridItem*>> dtw(len1 + 1, vector<GridItem*>(len2 + 1));;
		dtw[0][0] = new GridItem(0, -1, -1);
		for (i = 1; i <= len2; ++i) {
			dtw[0][i] = new GridItem(infinity, 0, i - 1);
		}
		for (i = 1; i <= len1; ++i) {
			dtw[i][0] = new GridItem(infinity, i - 1, 0);
		}
		for (i = 1;i <= len1;i++) {
			for (j = 1;j <= len2;j++) {
				int tmp1, tmp2;
				if (dtw[i - 1][j - 1]->value <= dtw[i - 1][j]->value) {
					tmp1 = i - 1; tmp2 = j - 1;
				}else {
					tmp1 = i - 1; tmp2 = j;
				}
				if (dtw[tmp1][tmp2]->value > dtw[i][j - 1]->value) {
					tmp1 = i; tmp2 = j - 1;
				}
				dtw[i][j] = new GridItem(dis(a[i - 1], b[j - 1]) + dtw[tmp1][tmp2]->value,tmp1,tmp2);
			}
		}
		if (IS_DEBUG) {
			for (i = 0;i <= len1;i++) {
				for (j = 0;j <= len2;j++) {
					printf("%5.0lf ", dtw[i][j]->value);
				}
				cout << endl;
			}
		}
		if (IS_FIND_PATH) {
			path = getPath(dtw, len1, len2);
			for (i = path.size() - 1;i >= 0;i--) {
				cout << "(" << path[i].first << "," << path[i].second << ")" << " ";
			}
			cout << endl;
		}
		return dtw[len1][len2]->value;
	}
	double FastDTW(vector<Point*> a, vector<Point*> b, int radius, double dis(Point* x, Point* y)) {
		int min_time_size = radius + 2;
		if (a.size() < min_time_size || b.size() < min_time_size) {
			return DTWDistance(a, b, dis);
		}
		vector<Point*> x_shrinked = __reduce_by_half(a);
		vector<Point*> y_shrinked = __reduce_by_half(b);
		FastDTW(x_shrinked, y_shrinked,radius, dis);
		vector<pair<int, int>> window = __expand_window(path,a.size(),b.size(),radius);
		if (window.size() == 0) {
			return DTWDistance(a, b, dis);
		}
		return DTWDistance(a, b, window, dis);
	}

	double DTWDistance(vector<Point*> a, vector<Point*> b, vector<pair<int, int>> window, double dis(Point* x, Point* y)) {
		int i, j;
		int len_x = a.size();
		int len_y = b.size();
		vector<vector<GridItem*>> dtw(len_x + 1, vector<GridItem*>(len_y + 1));;
		dtw[0][0] = new GridItem(0, -1, -1);
		for (i = 1; i <= len_y; ++i) {
			dtw[0][i] = new GridItem(infinity, 0, i - 1);
		}
		for (i = 1; i <= len_x; ++i) {
			dtw[i][0] = new GridItem(infinity, i - 1, 0);
		}
		for (i = 1; i <= len_x; ++i) {
			for (j = 1;j <= len_y;j++) {
				dtw[i][j]= new GridItem(infinity, i - 1, j-1);
			}
		}
		for (i = 0;i < window.size();i++) {
			int aP = window[i].first+1;
			int bP = window[i].second+1;
			double dt = dis(a[aP-1],b[bP-1]);
			int tmp1, tmp2;
			if (dtw[aP - 1][bP - 1]->value <= dtw[aP - 1][bP]->value) {
				tmp1 = aP - 1; tmp2 = bP - 1;
			}else {
				tmp1 = aP - 1; tmp2 = bP;
			}
			if (dtw[tmp1][tmp2]->value > dtw[aP][bP - 1]->value) {
				tmp1 = aP; tmp2 = bP - 1;
			}
			dtw[aP][bP] = new GridItem(dt + dtw[tmp1][tmp2]->value, tmp1, tmp2);
		}
		if (IS_DEBUG) {
			for (i = 0;i <= len_x;i++) {
				for (j = 0;j <= len_y;j++) {
					printf("%5.0lf ", dtw[i][j]->value);
				}
				cout << endl;
			}
		}
		if (IS_FIND_PATH) {
			path = getPath(dtw, len_x, len_y);
			for (i = path.size() - 1;i >= 0;i--) {
				cout << "(" << path[i].first << "," << path[i].second << ")" << " ";
			}
			cout << endl;
		}
		return dtw[len_x][len_y]->value;
	}
	vector<pair<int, int>> __expand_window(vector<pair<int,int>> path,int len_x,int len_y,int radius) {
		vector<pair<int, int>> path_;
		int i, j,a,b;
		for (i = 0;i < path.size();i++) {
			for (a = -radius;a < radius + 1;a++) {
				for (b = -radius;b < radius + 1;b++) {
					path_.push_back(make_pair(path[i].first-1+a,path[i].second-1+b));
				}
			}
		}
		vector<pair<int, int>> window_;
		for (i = 0;i < path.size();i++) {
			int a = path[i].first-1;
			int b = path[i].second-1;
			window_.push_back(make_pair(a*2,b*2));
			window_.push_back(make_pair(a * 2, b * 2+1));
			window_.push_back(make_pair(a * 2+1, b * 2));
			window_.push_back(make_pair(a * 2+1, b * 2+1));
		}
		vector<pair<int, int>> window;
		int start_j = 0;
		for (i = 0;i < len_x;i++) {
			int new_start_j = -1;
			for (j = start_j;j < len_y;j++) {
				vector<pair<int,int>>::iterator it;
				pair<int, int> value = make_pair(i,j);
				it = find(window_.begin(), window_.end(), value);
				if (it != window_.end()) {
					window.push_back(make_pair(i,j));
					if (new_start_j == -1)
						new_start_j = j;
				}else if(new_start_j!=-1){
					break;
				}
			}
			start_j = new_start_j;
		}
		return window;
	}
	vector<Point*> __reduce_by_half(vector<Point*> x) {
		vector<Point*> result;
		int i;
		for (i = 0;i < x.size() - x.size() % 2;i += 2) {
			result.push_back(new Point((x[i]->time + x[i + 1]->time) / 2, (x[i]->latitude + x[i + 1]->latitude) / 2, (x[i]->longitude + x[i + 1]->longitude) / 2));
		}
		return result;
	}

	/*
	* DTW with string
	* General  |  With window constraint  |  PrunedDTW
	*/
	double DTWDistance(string s, string t){
		if (s.size() == 0 && t.size()== 0) return 0;
		if (s.size() == 0 || t.size() == 0) return infinity;
		int i,j;
		vector<vector<GridItem*>> dtw(s.size()+1, vector<GridItem*>(t.size() + 1));;
		dtw[0][0] = new GridItem(0,-1,-1);
		for (i = 1; i <=s.size(); ++i) {
			dtw[i][0] = new GridItem(infinity,i-1,0);
		}for (j = 1;j <= t.size();j++) {
			dtw[0][j] = new GridItem(infinity,0,j-1);
		}
		for (i = 1;i <= s.size();i++) {
			for (j = 1;j <= t.size() ;j++) {
				int cost = dc(s[i-1],t[j-1]);
				int tmp1, tmp2;
				if (dtw[i - 1][j]->value < dtw[i][j - 1]->value) {
					tmp1 = i - 1; tmp2 = j; 
				}else {
					tmp1 = i; tmp2 = j - 1;
				}
				if (dtw[tmp1][tmp2]->value >= dtw[i - 1][j - 1]->value) {
					tmp1 = i - 1; tmp2 = j - 1;
				}
				dtw[i][j] = new GridItem(cost + dtw[tmp1][tmp2]->value,tmp1,tmp2);
			}
		}
		if (IS_DEBUG) {
			for (int i = 0; i <= s.size(); ++i) {
				for (int j = 0; j <= t.size(); ++j)
					cout << dtw[i][j]->value << " ";
				cout << endl;
			}
		}
		if (IS_FIND_PATH) {
			path = getPath(dtw, s.size(), t.size());
			for (i = path.size() - 1;i >= 0;i--) {
				cout << "(" << path[i].first << "," << path[i].second << ")" << " ";
			}
			cout << endl;
		}
		return dtw[s.size()][t.size()]->value;
	}
	double DTWDistance(string s, string t,int w) {
		if (s.size() == 0 && t.size() == 0) return 0;
		if (s.size() == 0 || t.size() == 0) return infinity;
		int i, j;
		int dis = dc(s.size()-1, t.size()-1);
		w = w < dis ? dis : w;
		vector<vector<GridItem*>> dtw(s.size()+1, vector<GridItem*>(t.size() + 1));;
		dtw[0][0] = new GridItem(0, -1, -1);
		for (i = 1; i <= s.size(); ++i) {
			dtw[i][0] = new GridItem(infinity, i - 1, 0);
		}for (j = 1;j <= t.size();j++) {
			dtw[0][j] = new GridItem(infinity, 0, j - 1);
		}
		for (i = 1;i <= s.size();i++) {
			for (j = 1;j <= t.size();j++) {
				dtw[i][j] = new GridItem(infinity,i-1,j-1);
			}
		}
		for (i = 1;i <= s.size();i++) {
			for (j = (1 > i - w ? 1 : i - w);j <= (t.size() < i + w ? t.size() : i + w);j++) {
				int cost = dc(s[i-1], t[j-1]);
				int tmp1, tmp2;
				if (dtw[i - 1][j]->value < dtw[i][j - 1]->value) {
					tmp1 = i - 1; tmp2 = j;
				}
				else {
					tmp1 = i; tmp2 = j - 1;
				}
				if (dtw[tmp1][tmp2]->value >= dtw[i - 1][j - 1]->value) {
					tmp1 = i - 1; tmp2 = j - 1;
				}
				dtw[i][j] = new GridItem(cost + dtw[tmp1][tmp2]->value, tmp1, tmp2);
			}
		}
		if (IS_DEBUG) {
			for (int i = 0; i <= s.size(); ++i) {
				for (int j = 0; j <= t.size(); ++j)
					cout << dtw[i][j]->value << " ";
				cout << endl;
			}
		}
		if (IS_FIND_PATH) {
			path = getPath(dtw, s.size(), t.size());
			for (i = path.size() - 1;i >= 0;i--) {
				cout << "(" << path[i].first << "," << path[i].second << ")" << " ";
			}
			cout << endl;
		}
		return dtw[s.size()][t.size()]->value;
	}
	int PrunedDTW(string x,string y,int ws,int UB) {
		if (x.size() == 0 && y.size() == 0) return 0;
		if (x.size() == 0 || y.size() == 0) return infinity;
		int i, j, ec_next;
		int sc = 1;
		int ec = 1;
		vector<vector<GridItem*>> dtw(x.size() + 1, vector<GridItem*>(y.size() + 1));;
		dtw[0][0] = new GridItem(0, -1, -1);
		for (i = 1; i <= x.size(); ++i) {
			dtw[i][0] = new GridItem(infinity, i - 1, 0);
		}for (j = 1;j <= y.size();j++) {
			dtw[0][j] = new GridItem(infinity, 0, j - 1);
		}
		for (i = 1;i <= x.size();i++) {
			for (j = 1;j <= y.size();j++) {
				dtw[i][j] = new GridItem(infinity, i - 1, j - 1);
			}
		}
		for (i = 1;i <= x.size();i++) {
			int beg = mmax(sc,i-ws);
			int end = mmin(i+ws,y.size());
			bool smaller_found = false;
			for (j = beg;j <= end;j++) {
				int tmp1, tmp2;
				if (dtw[i - 1][j]->value < dtw[i][j - 1]->value) {
					tmp1 = i - 1; tmp2 = j;
				}
				else {
					tmp1 = i; tmp2 = j - 1;
				}
				if (dtw[tmp1][tmp2]->value >= dtw[i - 1][j - 1]->value) {
					tmp1 = i - 1; tmp2 = j - 1;
				}
				dtw[i][j] = new GridItem(sqED(x[i-1],y[j-1])+ dtw[tmp1][tmp2]->value,tmp1,tmp2);
				if (dtw[i][j]->value > UB) {
					if (!smaller_found) {
						sc = j + 1;
					}
					if (j >= ec) {
						break;
					}
				}else {
					smaller_found = true;
					ec_next = j + 1;
				}
			}
			ec = ec_next;
		}
		if (IS_DEBUG) {
			for (int i = 0; i <= x.size(); ++i) {
				for (int j = 0; j <= y.size(); ++j)
					cout << dtw[i][j]->value << " ";
				cout << endl;
			}
		}
		if (IS_FIND_PATH) {
			path = getPath(dtw, x.size(), y.size());
			for (i = path.size() - 1;i >= 0;i--) {
				cout << "(" << path[i].first << "," << path[i].second << ")" << " ";
			}
			cout << endl;
		}
		return dtw[x.size()][y.size()]->value;
	}
};

#endif // !DTW