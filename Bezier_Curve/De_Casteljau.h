#pragma once
#include<fstream>

using namespace std;

class De_Casteljau
{
public:

	int Degree;
	int Control_Point;

	double** Control_Coordinate;

	double t;
	int parameter;
	int k;

	int Control_Size;

	int i;
	int j;
	int n;
	int start_X;
	int end_X;
	int boundary;

	int last_X;
	double x;
	double y;
	double x_y;

	int R;
	double pointerm_x;
	double pointerm_y;


	double** Coordinate;
	int X;
	int Y;

	double** Result;

	void fileLoad();
	void calculate();
	void saveFile();

	void normalization();
	void solveNormalization();
};