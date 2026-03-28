#include "De_Casteljau.h"
#include<iostream>
#include<string>
#include<fstream>

using namespace std;

/*--- Function ---*/
void De_Casteljau::fileLoad()
{

	/*--- input parameter ---*/
	parameter = 11;
	R = 5;

	/*--- FileLoading ---*/
	ifstream fin("degree6.txt");
	if (!fin)
	{
		std::cout << "You can't load this file" << endl;
	}

	/*--- Save Degree & Control Point ---*/
	fin >> Degree;
	std::cout << "Degree = " << Degree << endl;
	Control_Point = Degree + 1;



	Control_Size = Control_Point;
	for (int k = Control_Point - 1; k > 0; k--)
	{
		Control_Size = Control_Size + k;
	}

	/*--- control point dynamic memory allocation ---*/
	Control_Coordinate = new double* [Control_Point];
	for (int x = 0; x < Control_Point; x++)
	{
		Control_Coordinate[x] = new double[4];
	}
	for (int x = 0; x < Control_Point; x++)
	{
		fin >> Control_Coordinate[x][0];
		fin >> Control_Coordinate[x][1];

	}
	Coordinate = new double* [Control_Size];
	for (int x = 0; x < Control_Size; x++)
	{
		Coordinate[x] = new double[4];
	}

	for (int X = 0; X < Control_Point; X++)
	{
		for (int Y = 0; Y < 2; Y++)
		{
			Coordinate[X][Y] = Control_Coordinate[X][Y];
			std::cout << Coordinate[X][Y] << "";
		}
		std::cout << endl;
	}

	Result = new double* [parameter];
	for (j = 0; j <= parameter; j++)
	{
		Result[j] = new double[4];
	}

	for (j = 0; j <= parameter; j++)
	{
		Result[j][0] = 0;
		Result[j][1] = 0;
	}

	fin.close();
}

void De_Casteljau::calculate()
{
	std::cout << "Coordinate of Control Point" << endl;
	/*--- Parameter Version ---*/
	for (k = 0; k <= parameter; k++)
	{
		t = (double)k / parameter;

		/*--- Compute control points using the De Casteljau algorithm ---*/
		for (Y = 0; Y < 2; Y++)
		{
			boundary = 0;

			for (i = 1; i <= Degree; i++)
			{
				n = Degree - i + 1;
				start_X = boundary + 1;
				end_X = boundary + n + 1;

				for (X = start_X; X < end_X; X++)
				{
					Coordinate[X + n][Y] = (1 - t) * Coordinate[X - 1][Y] + t * Coordinate[X][Y];
				}

				boundary += (Control_Point - i + 1);
			}
		}

		/*--- Terminal Output ---*/
		last_X = Control_Size - 1;
		x = Coordinate[last_X][0];
		y = Coordinate[last_X][1];

		Result[k][0] = x;
		Result[k][1] = y;
	}
}

void De_Casteljau::saveFile()
{
	/*--- Writing on files ---*/
	ofstream txtFile("Coordinate_degree3.txt");
	ofstream psFile("curve.ps");

	if (!txtFile || !psFile)
	{
		/*--- When can't file output ---*/
		std::cout << "You can't load this file" << endl;
	}

	/*--- Post Script Header ---*/
	psFile << "%!PS" << endl;
	psFile << "newpath" << endl;

	for (k = 0; k <= parameter; k++)
	{
		txtFile << Result[k][0] << " " << Result[k][1] << endl;
		std::cout << Result[k][0] << " " << Result[k][1] << endl;

		if (k == 0)
		{
			/*--- Start Point ---*/
			psFile << Result[k][0] << " " << Result[k][1] << " moveto" << endl;
		}
		else
		{
			/*--- Line ---*/
			psFile << Result[k][0] << " " << Result[k][1] << " lineto" << endl;
		}
	}
	psFile << "stroke" << endl;

	for (X = 0; X < Control_Point; X++)
	{
		pointerm_x = Control_Coordinate[X][0];
		pointerm_y = Control_Coordinate[X][1];

		psFile << "newpath" << endl;
		if (X == 0 || X == Degree)
		{
			psFile << pointerm_x << " " << pointerm_y << " " << R << " " << "0 360 arc" << endl;
			psFile << "fill" << endl;
		}

		else
		{
			psFile << pointerm_x << " " << pointerm_y << " " << R << " " << "0 360 arc" << endl;
			psFile << "stroke" << endl;
		}

	}
	psFile << "newpath" << endl;
	for (X = 0; X < Control_Point; X++)
	{
		pointerm_x = Control_Coordinate[X][0];
		pointerm_y = Control_Coordinate[X][1];

		if (X == 0)
		{
			psFile << pointerm_x << " " << pointerm_y << " moveto" << endl;

		}
		else
		{
			psFile << pointerm_x << " " << pointerm_y << " lineto" << endl;
		}
	}


	psFile << "stroke" << endl;
	psFile << "showpage" << endl;

	txtFile.close();
	psFile.close();
}

void De_Casteljau::normalization()
{
	double dx = Control_Coordinate[Degree][0] - Control_Coordinate[0][0];
	double dy = Control_Coordinate[Degree][1] - Control_Coordinate[0][1];
	double x_y = sqrt(dx * dx + dy * dy);

	for (X = 0; X < Control_Point; X++)
	{
		Coordinate[X][0] = (Coordinate[X][0] - Control_Coordinate[0][0]) / x_y;
		Coordinate[X][1] = (Coordinate[X][1] - Control_Coordinate[0][1]) / x_y;
	}
}

void De_Casteljau::solveNormalization()
{
	double dx = Control_Coordinate[Degree][0] - Control_Coordinate[0][0];
	double dy = Control_Coordinate[Degree][1] - Control_Coordinate[0][1];
	double x_y = sqrt(dx * dx + dy * dy);

	for (k = 0; k <= parameter; k++)
	{
		Result[k][0] = Result[k][0] * x_y + Control_Coordinate[0][0];
		Result[k][1] = Result[k][1] * x_y + Control_Coordinate[0][1];
	}
}