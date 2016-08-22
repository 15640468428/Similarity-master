#pragma once
#ifndef  tool_h
#define tool_h
#include <iostream>
using namespace std;

vector<pair<int, int>> getPath(vector<vector<GridItem*>> grid,int or,int col) {
	vector<pair<int, int>> result;
	GridItem* tmp = grid[or ][col];
	int i=or, j=col;
	while (i!=0&&j!=0) {
		result.push_back(make_pair(i,j));
		i = grid[i][j]->i;
		j = grid[i][j]->j;
	}
	while (i != 0) {
		result.push_back(make_pair(i, 0));
		i = grid[i][0]->i;
	}
	while (j != 0) {
		result.push_back(make_pair(0, j));
		j = grid[0][j]->j;
	}
	return result;
}

/**
* min max and abs
*/
int mmin(int a, int b) {
	return a < b ? a : b;
}

int mmin(int a, int b, int c) {
	a = a < c ? a : c;
	return a < b ? a : b;
}

int mmax(int a, int b) {
	return a > b ? a : b;
}
int mmax(int a, int b, int c) {
	a = a > c ? a : c;
	return a > b ? a : b;
}

int mabs(int a) {
	return a > 0 ? a : -a;
}
double mmin(double a, double b) {
	return a < b ? a : b;
}

double mmin(double a, double b, double c) {
	a = a < c ? a : c;
	return a < b ? a : b;
}

double mmax(double a, double b) {
	return a > b ? a : b;
}
double mmax(double a, double b, double c) {
	a = a > c ? a : c;
	return a > b ? a : b;
}

double mabs(double a) {
	return a > 0 ? a : -a;
}

/*
* Distance Functions
* d(char)  |  sqED(int)  |  Lp-norms(L1,L2 and Linfinite)
*/
int dc(char x, char y) {
	return x - y > 0 ? x - y : y - x;
}
int di(int x, int y) {
	return x - y > 0 ? x - y : y - x;
}
double dd(double x, double y) {
	return x - y > 0 ? x - y : y - x;
}
int sqED(int a, int b) {
	return (a - b)*(a - b);
}
double L1(Point* p1, Point* p2) {
	return mabs(p1->latitude - p2->latitude) + mabs(p1->longitude - p2->longitude);
}
double L2(Point* p1, Point* p2) {
	return sqrt((p1->latitude - p2->latitude)*(p1->latitude - p2->latitude) + mabs(p1->longitude - p2->longitude)*mabs(p1->longitude - p2->longitude));
}
double Linfinite(Point* p1, Point* p2) {
	return mmax(mabs(p1->latitude - p2->latitude), mabs(p1->longitude - p2->longitude));
}

//convertor between char and binary char
union Char2Binary {
	char value;
	unsigned char data[1];
};
union Char2Binary char2Binary;

//convertor between int and binary int
union Int2Binary {
	int value;
	unsigned char data[4];
};
union Int2Binary int2Binary;

//convertor between double and binary double
union Double2Binary {
	double value;
	unsigned char data[8];
};
union Double2Binary double2Binary;
class FileReader {
public:
	FileReader(const char* filenamme, bool isbinary) {
		this->m_isbinary = isbinary;
		this->m_fileptr = fopen(filenamme, isbinary ? "rb" : "r");
	}
	FileReader(char* filenamme, char* options, bool isbinary) {
		this->m_isbinary = isbinary;
		this->m_fileptr = fopen(filenamme, options);
	}
	char GetNextChar() {
		if (this->m_isbinary) {
			if (fread(char2Binary.data, sizeof(unsigned char), 1, this->m_fileptr) < 1) return EOF;
			return char2Binary.value;
		}
		else {
			char temp;
			if (fscanf(this->m_fileptr, "%c", &temp) == EOF) {
				return EOF;
			}
			return temp;
		}
	}
	int GetNextInt() {
		if (this->m_isbinary) {
			if (fread(int2Binary.data, sizeof(unsigned char), 4, this->m_fileptr) < 4) return EOF;
			return int2Binary.value;
		}
		else {
			int temp;
			if (fscanf(this->m_fileptr, "%d", &temp) == EOF) {
				return EOF;
			}
			return temp;
		}
	}
	double GetNextDouble() {
		if (this->m_isbinary) {
			if (fread(double2Binary.data, sizeof(unsigned char), 8, this->m_fileptr) < 8) return EOF;
			return double2Binary.value;
		}
		else {
			double temp;
			if (fscanf(this->m_fileptr, "%lf", &temp) == EOF) {
				return EOF;
			}
			return temp;
		}
	}
	char* GetNextString() {
		char* temp = new char[256];
		if (this->m_isbinary) {
			int i = 0;
			while (fread(char2Binary.data, sizeof(unsigned char), 1, this->m_fileptr) > 0) {
				temp[i] = (char)char2Binary.value;
				if (temp[i++] == 0 || i > 254) {
					break;
				}
			}
			if (i == 0) {
				return temp;
			}
			temp[i] = 0;
			return temp;
		}
		else {
			if (fscanf(this->m_fileptr, "%s", temp) == EOF) {
				return temp;
			}
			return temp;
		}
	}
	bool IsBinary() {
		return this->m_isbinary;
	}
	void Close() {
		fclose(this->m_fileptr);
	}
	~FileReader() {
		fclose(this->m_fileptr);
	}
private:
	FILE* m_fileptr;
	bool m_isbinary;
};

class FileWriter {
public:
	FileWriter(const char* filename, bool isbinary) {
		this->m_isbinary = isbinary;
		this->m_fileptr = fopen(filename, isbinary ? "wb" : "w");
	}

	FileWriter(const char* filename, char* options, bool isbinary) {
		this->m_isbinary = isbinary;
		this->m_fileptr = fopen(filename, options);
	}
	void WriteChar(char value) {
		if (this->m_isbinary) {
			char2Binary.value = value;
			fwrite(char2Binary.data, sizeof(unsigned char), 1, this->m_fileptr);
		}
		else {
			fprintf(this->m_fileptr, "%c", value);
		}
	}
	void WriteInt(int value) {
		if (this->m_isbinary) {
			int2Binary.value = value;
			fwrite(int2Binary.data, sizeof(unsigned char), 4, this->m_fileptr);
		}
		else {
			fprintf(this->m_fileptr, "%d ", value);
		}
	}
	void WriteDouble(double value) {
		if (this->m_isbinary) {
			double2Binary.value = value;
			fwrite(double2Binary.data, sizeof(unsigned char), 8, this->m_fileptr);
		}
		else {
			fprintf(this->m_fileptr, "%lf ", value);
		}
	}
	bool IsBinary() {
		return this->m_isbinary;
	}
	void Close() {
		fclose(this->m_fileptr);
	}
	~FileWriter() {
		fclose(this->m_fileptr);
	}
private:
	FILE* m_fileptr;
	bool m_isbinary;
};

#endif // ! tool_h