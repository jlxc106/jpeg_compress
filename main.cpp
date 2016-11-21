#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include "CImg/CImg.h"
#include <math.h>
#define PI 3.14159265

using namespace cimg_library;


float Coefficient(int x)
{
	if(x==0)
		//return (float)0.70710678118;
		return (float)(1.0/sqrt(2.0));
	else
		return (float)1.0;
	
}

int main()
{	
	const float inv16 = 1.0/16.0;
	CImg<unsigned char> image("stock.jpg");
	image.blur(2.5);
	CImgDisplay main_disp(image,"stock.jpg");
	
	float cosine[8][8] = {{ 0.0 }};
	int DCT[8][8] = {{ 0 }};


	int **Pixel = new int*[image.width()];
	for(int i=0; i< image.width(); ++i){
		Pixel[i]=new int[image.height()];
	}

	for(int i=0; i<image.height(); i++)
	{
		for(int j=0; j<image.width(); j++)
		{
			Pixel[i][j] = (int)image.atXY(j,i) - 128; // loading and preprocessing step
		}
	}
	
	for(int i = 0; i<8; i++)
	{
		for(int j =0; j<8; j++)
		{
			cosine[i][j] = (float)cos((PI*j*((2.0*i)+1))*inv16);
		}
	}


	int test[8][8]= {{140, 144, 147, 140, 140, 155, 179, 175},
			{144, 152, 140, 147, 140, 148, 167, 179},
			{152, 155, 136, 167, 163, 162, 152, 172},
			{168, 145, 156, 160, 152, 155, 136, 160},
			{162, 148, 156, 148, 140, 136, 147, 162},
			{147, 167, 140, 155, 155, 140, 136, 162},
			{136, 156, 123, 167, 162, 144, 140, 147},
			{148, 155, 136, 155, 152, 147, 147, 136}};
	
	int qLum[8][8] = {{16, 11, 10, 16, 24, 40, 51, 61},
			{12, 12, 14, 19, 26, 58, 60, 55},
			{14, 13, 16, 24, 40, 57, 69, 56},
			{14, 17, 22, 29, 51, 87, 80, 62},
			{18, 22, 37, 56, 68, 109, 103, 77},
			{24, 35, 55, 64, 81, 104, 113, 92},
			{49, 64, 78, 87, 103, 121, 120, 101},
			{72, 92, 95, 98, 112, 100, 103, 99}};
	
	/*
	{{5,	176	,193,	168	,168,	170	,167,165},
		{6,	176,	158,	172,	162,	177,	168,	151},
		{5,	167,	172,	232,	158,	61,	145,	214},
		{33,	179,	169,	174,	5,	5,	135,	178},
		{8,	104,	180,	178,	172,	197,	188,	169},
		{63,	5,	102,	101,	160,	142,	133,	139},
		{51,	47,	63,	5,	180,	191,	165,	5},
		{49,	53,	43,	5	,184,	170	,168,	74}};

*/
	//[row][column]

	for(int i=0; i<8; ++i)
		for(int j =0; j<8; ++j)
		{
			test[i][j] -=128;
		}

/*
	int A[8][8] = {{0}};
	for (int i = 0; i<8; i++)
	{
		for(int j=0; j<8; j++)
		{
			A[i][j]=100;
		}
	}
*/

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			float temp = 0.0;
			for (int x = 0; x < 8; x++) {
				for (int y = 0; y < 8; y++) {
					temp += cosine[x][i] * cosine[y][j] * test[x][y]; //
					//temp += cosine[x][i] * cosine[y][j] * Pixel[x][y];
				}
			}
			//temp *= ((1.0/4.0) * Coefficient(i)*Coefficient(j));
			//std::cout << "i: "<<Coefficient(i) << std::endl;
			//std::cout << "j: "<< Coefficient(j) << std::endl;
			//std::cout << "wtf??: "<< 1.0/4.0 << std::endl;
			temp *= ((1.0/4.0)*Coefficient(i)*Coefficient(j));
			//std::cout << "DCT["<< i << "][" << j << "]: "<< round(temp) << std::endl;
			//temp *= inv16 * Coefficient(i)*Coefficient(j);
			DCT[i][j] = round(temp);
			std::cout << DCT[i][j]<<std::endl;
		}
	}

	int QuantizedValue[8][8]={{ 0 }};
	for(int i =0; i< 8; i++)
	{
		for(int j=0; j<8; j++)
		{
			QuantizedValue[i][j] = round(DCT[i][j]/qLum[i][j]);
			//std::cout << "i: "<< i << " j: " << j << " | " << QuantizedValue[i][j] << std::endl;
		}
	}


	/* uncomment this for gui
	while(!main_disp.is_closed()){
		int abc=0;
		std::cout << "Enter value: " << std::endl;
		std::cin >> abc;
		std::cout << std::endl;
		CImg<unsigned char> img= image.get_blur(abc);
		img.display(main_disp);
	}*/
	
	return 0;
}
