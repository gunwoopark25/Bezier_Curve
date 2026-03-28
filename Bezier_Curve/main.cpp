#include "De_Casteljau.h"
#include<iostream>
#include<string>
#include<fstream>

using namespace std;

void main()
{
	De_Casteljau Bezier;

	/*--- function ---*/
	Bezier.fileLoad();
	Bezier.normalization();
	Bezier.calculate();
	Bezier.solveNormalization();
	Bezier.saveFile();
}