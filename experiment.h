#pragma once
#ifndef  experiment_h
#define experiment_h
#include "config.h"
#include <iostream>
#include <vector>
#include "point.h"
#include "tool.h"
#include "lcss.h"
#include "erp.h"
#include "edr.h"
#include "dtw.h"
#include "editdistance.h"
#include "grid.h"
#include "swale.h"
using namespace std;

class Experiment{
public:
	Grid grid;
	void LCSS_String() {
		LCSS *lcss = new LCSS();
		string a = "aaaaabaaaaa";
		string b = "aaaaacaaqaa";
		cout << "The Lcss's score is: " << lcss->LcssScore(a, b, 0,dc) << endl;
	}
	void LCSS_Tra(){
		LCSS *lcss = new LCSS();
		vector<Point*> a;
		vector<Point*> b;
		FileReader *reader1 = new FileReader("D://yangkai/plt/dataset/singapore/20/10.txt", false);
		FileReader *reader2 = new FileReader("D://yangkai/plt/dataset/singapore/20/11.txt", false);
		while (1) {
			int t = reader1->GetNextInt();
			if (t == EOF) break;
			reader1->GetNextChar();
			double lat = reader1->GetNextDouble();
			reader1->GetNextChar();
			double lng = reader1->GetNextDouble();
			a.push_back(new Point(t, lat, lng));
			if (a.size() == 20) break;
		}
		while (1) {
			int t = reader2->GetNextInt();
			if (t == EOF) break;
			reader2->GetNextChar();
			double lat = reader2->GetNextDouble();
			reader2->GetNextChar();
			double lng = reader2->GetNextDouble();
			b.push_back(new Point(t, lat, lng));
			if (b.size() == 20) break;
		}
		cout << "The Lcss's score is: " << lcss->LcssScore(a, b, 1000,1000000,dd) << endl;
	}
	void LCSS_Tra_S1() {
		LCSS *lcss = new LCSS();
		vector<Point*> a;
		vector<Point*> b;
		FileReader *reader1 = new FileReader("D://yangkai/plt/dataset/singapore/20/10.txt", false);
		FileReader *reader2 = new FileReader("D://yangkai/plt/dataset/singapore/20/11.txt", false);
		while (1) {
			int t = reader1->GetNextInt();
			if (t == EOF) break;
			reader1->GetNextChar();
			double lat = reader1->GetNextDouble();
			reader1->GetNextChar();
			double lng = reader1->GetNextDouble();
			a.push_back(new Point(t, lat, lng));
		}
		while (1) {
			int t = reader2->GetNextInt();
			if (t == EOF) break;
			reader2->GetNextChar();
			double lat = reader2->GetNextDouble();
			reader2->GetNextChar();
			double lng = reader2->GetNextDouble();
			b.push_back(new Point(t, lat, lng));
		}
		//a,b,ddThreshold,timeThreshold,disFunction
		cout << "The Lcss's score is: " << lcss->S1(a, b, 10, 100,dd) << endl;
	}
	void LCSS_Tra_FTSE() {
		LCSS *lcss = new LCSS();
		vector<Point*> a;
		vector<Point*> b;
		FileReader *reader1 = new FileReader("D://yangkai/plt/dataset/singapore/20/10.txt", false);
		FileReader *reader2 = new FileReader("D://yangkai/plt/dataset/singapore/20/11.txt", false);
		while (1) {
			int t = reader1->GetNextInt();
			if (t == EOF) break;
			reader1->GetNextChar();
			double lat = reader1->GetNextDouble();
			reader1->GetNextChar();
			double lng = reader1->GetNextDouble();
			a.push_back(new Point(t, lat, lng));
		}
		while (1) {
			int t = reader2->GetNextInt();
			if (t == EOF) break;
			reader2->GetNextChar();
			double lat = reader2->GetNextDouble();
			reader2->GetNextChar();
			double lng = reader2->GetNextDouble();
			b.push_back(new Point(t, lat, lng));
		}
		getIntersectionList();
		cout << "The Lcss's score is: " << lcss->LCSSComputation(a, b, grid.threshold, grid.IntersectionList) << endl;
	}
	void ERP_String() {
		ERP* erp = new ERP();
		string a = "aaaaabcdefghi";
		string b = "zzzaaaaazzzzzzzzzzbcdefghi";
		cout << erp->minDistance(a, b, 0,dc) << endl;
	}
	void EDR_String() {
		EDR* edr = new EDR();
		string a = "aaaaabaaaaa";
		string b = "aaaaacaabaa";
		cout << edr->minDistance(a, b,10,dc) << endl;
	}
	void EDR_Tra_FTSE() {
		EDR *edr = new EDR();
		vector<Point*> a;
		vector<Point*> b;
		FileReader *reader1 = new FileReader("D://yangkai/plt/dataset/singapore/20/10.txt", false);
		FileReader *reader2 = new FileReader("D://yangkai/plt/dataset/singapore/20/11.txt", false);
		while (1) {
			int t = reader1->GetNextInt();
			if (t == EOF) break;
			reader1->GetNextChar();
			double lat = reader1->GetNextDouble();
			reader1->GetNextChar();
			double lng = reader1->GetNextDouble();
			a.push_back(new Point(t, lat, lng));
		}
		while (1) {
			int t = reader2->GetNextInt();
			if (t == EOF) break;
			reader2->GetNextChar();
			double lat = reader2->GetNextDouble();
			reader2->GetNextChar();
			double lng = reader2->GetNextDouble();
			b.push_back(new Point(t, lat, lng));
		}
		getIntersectionList();
		cout << "The EDR's score is: " << edr->EDRComputation(a, b, grid.threshold, grid.IntersectionList) << endl;
	}
	void DTW_String() {
		DTW* mydtw = new DTW();
		string a = "aaaaabaaaaa";
		string b = "aaaaacaabaa";
		cout << mydtw->DTWDistance(a, b) << endl;
	}
	void DTW_Tra() {
		DTW *dtw = new DTW();
		vector<Point*> a;
		vector<Point*> b;
		FileReader *reader1 = new FileReader("D://yangkai/plt/dataset/singapore/20/10.txt", false);
		FileReader *reader2 = new FileReader("D://yangkai/plt/dataset/singapore/20/11.txt", false);
		while (1) {
			int t = reader1->GetNextInt();
			if (t == EOF) break;
			reader1->GetNextChar();
			double lat = reader1->GetNextDouble();
			reader1->GetNextChar();
			double lng = reader1->GetNextDouble();
			a.push_back(new Point(t, lat, lng));
			if (a.size() == 20) break;
		}
		while (1) {
			int t = reader2->GetNextInt();
			if (t == EOF) break;
			reader2->GetNextChar();
			double lat = reader2->GetNextDouble();
			reader2->GetNextChar();
			double lng = reader2->GetNextDouble();
			b.push_back(new Point(t, lat, lng));
			if (b.size() == 20) break;
		}
		cout << "The DTW's score is: " << dtw->DTWDistance(a, b,L2) << endl;
	}
	void FastDTW_Tra() {
		DTW *dtw = new DTW();
		vector<Point*> a;
		vector<Point*> b;
		FileReader *reader1 = new FileReader("D://yangkai/plt/dataset/singapore/20/10.txt", false);
		FileReader *reader2 = new FileReader("D://yangkai/plt/dataset/singapore/20/11.txt", false);
		while (1) {
			int t = reader1->GetNextInt();
			if (t == EOF) break;
			reader1->GetNextChar();
			double lat = reader1->GetNextDouble();
			reader1->GetNextChar();
			double lng = reader1->GetNextDouble();
			a.push_back(new Point(t, lat, lng));
			if (a.size() == 20) break;
		}
		while (1) {
			int t = reader2->GetNextInt();
			if (t == EOF) break;
			reader2->GetNextChar();
			double lat = reader2->GetNextDouble();
			reader2->GetNextChar();
			double lng = reader2->GetNextDouble();
			b.push_back(new Point(t, lat, lng));
			if (b.size() == 20) break;
		}
		cout << "The fastDTW's score is: " << dtw->FastDTW(a, b, 2,L2) << endl;
	}
	void DTWWithConstraint_String() {
		DTW* mydtw = new DTW();
		string a = "aaaaabaaaaa";
		string b = "aaaaacaabaa";
		cout << mydtw->DTWDistance(a, b,2) << endl;
	}
	void PrunedDTW_String() {
		DTW* mydtw = new DTW();
		string a = "000030";
		string b = "000004";
		cout << mydtw->PrunedDTW(a, b, 3, 1000) << endl;
	}
	void EditDistance_String() {
		EditDistance* edit = new EditDistance();
		string a = "aaaaabaaaaa";
		string b = "aaaaacaabaa";
		cout << edit->minDistance(a, b) << endl;
	}
	void getIntersectionList() {
		int i;
		vector<Point*> a;
		vector<Point*> b;
		FileReader *reader1 = new FileReader("D://yangkai/plt/dataset/singapore/20/10.txt", false);
		FileReader *reader2 = new FileReader("D://yangkai/plt/dataset/singapore/20/11.txt", false);
		while (1) {
			int t = reader1->GetNextInt();
			if (t == EOF) break;
			reader1->GetNextChar();
			double lat = reader1->GetNextDouble();
			reader1->GetNextChar();
			double lng = reader1->GetNextDouble();
			a.push_back(new Point(t, lat, lng));
		}
		while (1) {
			int t = reader2->GetNextInt();
			if (t == EOF) break;
			reader2->GetNextChar();
			double lat = reader2->GetNextDouble();
			reader2->GetNextChar();
			double lng = reader2->GetNextDouble();
			b.push_back(new Point(t, lat, lng));
		}
		grid.initGrid(a);
		grid.initGrid(b);
		grid.makePartition(0.01);
		for (i = 0;i < a.size();i++) {
			grid.insert(a[i],i);
		}
		for (i = 0;i < b.size();i++) {
			grid.buildList(b[i],dd);
		}
		/*
		for (i = 0;i < grid.IntersectionList.size();i++) {
			queue<int>* t = grid.IntersectionList[i];
			while (!t->empty()) {
				cout << t->front() << " ";
				t->pop();
			}
			cout << endl;
		}
		*/
	}
	void Swale_Tra() {
		Swale *swale = new Swale();
		vector<Point*> a;
		vector<Point*> b;
		FileReader *reader1 = new FileReader("D://yangkai/plt/dataset/singapore/20/10.txt", false);
		FileReader *reader2 = new FileReader("D://yangkai/plt/dataset/singapore/20/11.txt", false);
		while (1) {
			int t = reader1->GetNextInt();
			if (t == EOF) break;
			reader1->GetNextChar();
			double lat = reader1->GetNextDouble();
			reader1->GetNextChar();
			double lng = reader1->GetNextDouble();
			a.push_back(new Point(t, lat, lng));
			if (a.size() == 20) break;
		}
		while (1) {
			int t = reader2->GetNextInt();
			if (t == EOF) break;
			reader2->GetNextChar();
			double lat = reader2->GetNextDouble();
			reader2->GetNextChar();
			double lng = reader2->GetNextDouble();
			b.push_back(new Point(t, lat, lng));
			if (b.size() == 20) break;
		}
		cout << "The Swale's score is: " << swale->getSwaleScore(a, b, -1, 1,0.5,dd,false) << endl;
	}
};

#endif // ! experiment_h