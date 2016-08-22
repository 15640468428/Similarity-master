#pragma once
#ifndef point_h
#define point_h
#include <iostream>
#include <vector>
using namespace std;

class Point {
public:
	Point() {}
	Point(int time,double lat,double lng) {
		this->time = time;
		this->latitude = lat;
		this->longitude = lng;
	}
	void display() {
		cout << "Time: " << time << " , " << "latitude: " << latitude << " , " << "longitude: " << longitude << endl;
	}
	/*
	* Time, Latitude and Longitude
	*/
	int time;
	double latitude;
	double longitude;
};

class GridItem {
public:
	GridItem() {}
	GridItem(double value,int i,int j) {
		this->value = value;
		this->i = i;
		this->j = j;
	}
	void display() {
		cout << "i=" << i << ",j=" << j << ",value=" << value << endl;
	}
	double value;
	int i, j;
};

#endif