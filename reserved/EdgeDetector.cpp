
#include "EdgeDectector.h"
#include <bitset>
#include <vector>
#include <algorithm>
#include <utility>
using namespace std;
#define eps 1e-9
//#include "Kernel.h"

//0, 45, 90, , 135
const int posx[] = { 0, -1,  1, 1 };
const int posy[] = { 1, 1, 0, 1 };
const int negx[] = { 0, 1, -1, -1 };
const int negy[] = { -1, -1, 0, -1 };

double def[][5] = { { 2, 4, 5, 4, 2 },
					{ 4, 9, 12, 9, 4 },
					{ 5, 12, 15, 12, 5 },
					{ 4, 9, 12, 9, 4 },
					{ 2, 4, 5, 4, 2 } };

double mGx[][3] = {
	{ -1, 0, 1 },
	{ -2, 0, 2 },
	{ -1, 0, 1 }
};

double mGy[][3] = {
	{ -1, -2, -1 },
	{ 0, 0, 0 },
	{ 1, 2, 1 }
};
const double MY_PI = acos(-1);
Mat kernel, Gx, Gy;

void Init()
{
	int sz = 5;
	kernel = Mat(sz, sz, CV_32FC1, Scalar_<float>(0));
	for (int i = 0; i < sz; ++i)
		for (int j = 0; j < sz; ++j)
		{
			kernel.at<float>(i, j) = 1.0 / 159 * def[i][j];
		}
	
	int gSz = 3;
	Gx = Mat(gSz, gSz, CV_32FC1, Scalar_<float>(0));
	Gy = Mat(gSz, gSz, CV_32FC1, Scalar_<float>(0));
	for (int i = 0; i < gSz; ++i)
		for (int j = 0; j < gSz; ++j)
		{
			Gx.at<float>(i, j) =mGx[i][j];
			Gy.at<float>(i, j) =mGy[i][j];
		}
}


void convolution(Mat src, Mat& des, Mat kernel)
{
	Mat res = src.clone();//Mat(src.size().height, src.size().width, CV_32FC1, Scalar_<float>(0));
	int k = kernel.size().width / 2;
	for (int i = k; i < src.size().height-k; ++i)
		for (int j = k; j < src.size().width-k; ++j)
		{
			res.at<float>(i,j) = 0;
			float tmp = 0;
			for (int u = -k; u <= k; ++u)
			{
				for (int v = -k; v <= k; ++v)
				{
					tmp += src.at<float>(i - u, j - v)*kernel.at<float>(k + u, k + v);
				}

			}
				
					

			res.at<float>(i, j) = tmp;
		}
	des = res;
}

bool isGreater(float a, float b)
{
	return a  > b+eps;
}

bool inRange(int x, int a, int b)
{
	return x >= a && x <= b;
}
void getNeighbor(uint8_t angle, int x, int y, int &x1, int &y1, int &x2, int &y2)
{
	int dir = angle / 45;
	x1 = x + posx[dir];
	y1 = y + posy[dir];

	x2 = x + negx[dir];
	y2 = y + negy[dir];
}
void myCanny(Mat src, Mat& dest, int lowThreshold, int highThreshold)
{
	Init();

	Mat src_gr, src_x, src_y;
	int sz = 5;
	cvtColor(src, src_gr, CV_BGR2GRAY);
	
	int n = src.size().height;
	int m = src.size().width;
	Mat src_gray = Mat(n, m, CV_32FC1, Scalar_<float>(0));
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < m; ++j)
			src_gray.at<float>(i, j) = src_gr.at<uint8_t>(i, j);
	
	
	//filter out noise, using Gaussian kernel
	convolution(src_gray, src_gray, kernel);

	//find the intensity gradient of the image
	convolution(src_gray, src_x, Gx);
	convolution(src_gray, src_y, Gy);



	//find gradient strength and direction
	Mat G = Mat(n, m, CV_32FC1, Scalar_<float>(0));
	Mat Edir = src_gr.clone();


	for (int i = 0; i < n; ++i)
		for (int j = 0; j < m; ++j)
		{
		//	cout << i << ' ' << j << endl;
			float x = src_x.at<float>(i, j);
			float y = src_y.at<float>(i, j);
		
			G.at<float>(i, j) = sqrt(x*x + y*y);
			float theta = atan2(y, x)/MY_PI*180;
			uint8_t newAngle = 11;
			if (((theta < 22.5) && (theta > -22.5)) || (theta > 157.5) || (theta < -157.5))
				newAngle = 0;
			if (((theta > 22.5) && (theta < 67.5)) || ((theta < -112.5) && (theta > -157.5)))
				newAngle = 45;
			if (((theta > 67.5) && (theta < 112.5)) || ((theta < -67.5) && (theta > -112.5)))
				newAngle = 90;
			if (((theta > 112.5) && (theta < 157.5)) || ((theta < -22.5) && (theta > -67.5)))
				newAngle = 135;
			
			Edir.at<uint8_t>(i,j) = newAngle;

		}

	//Non - maximum suppression
	vector<vector<bool> > preserved;
	preserved.resize(n);
	//
	for (int i = 0; i < n; ++i)
	{
		preserved[i].resize(m, true);
		
		for (int j = 0; j < m; ++j)
		{ 
			
			int x1, y1, x2, y2;
			getNeighbor(Edir.at<uint8_t>(i, j), i, j, x1, y1, x2, y2);
			if (inRange(x1, 0, n - 1) && inRange(y1, 0, m - 1) && !isgreater(G.at<float>(i, j), G.at<float>(x1, y1)))
				preserved[i][j] = false;
			if (inRange(x2, 0, n - 1) && inRange(y2, 0, m - 1) && !isgreater(G.at<float>(i, j), G.at<float>(x2, y2)))
				preserved[i][j] = false;
		
		}
	}

	//Hysteresis
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < m; ++j)
			if (preserved[i][j])
			{
				if (isGreater(G.at<float>(i, j), highThreshold))
					continue;
				preserved[i][j] = false;
				
				if (isGreater(G.at<float>(i, j),lowThreshold) && isGreater(highThreshold,G.at<float>(i, j)) )
				{
						
					int x1, y1, x2, y2;
					getNeighbor(Edir.at<uint8_t>(i, j), i, j, x1, y1, x2, y2);

					if (inRange(x1, 0, n - 1) && inRange(y1, 0, m - 1) && isGreater(G.at<float>(x1, y1), highThreshold))
						preserved[i][j] = true;
					if (inRange(x2, 0, n - 1) && inRange(y2, 0, m - 1) && isGreater(G.at<float>(x2, y2), highThreshold))
						preserved[i][j] = true;
				}
			}
	//create binary image, with white pixels, representing edges, and black pixels, representing background.
	dest = src_gr.clone();
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < m; ++j)
			if (preserved[i][j])
				dest.at<uint8_t>(i, j) = 255;
			else
				dest.at<uint8_t>(i, j) = 0;

}

//for debugging
/*
int dir = Edir.at<uint8_t>(i, j) / 4;

switch (Edir.at<uint8_t>(i,j))
{
case 0:
{
if (j > 0 && G.at<float>(i, j) + eps < G.at<float>(i, j - 1))
preserved[i][j] = false;
if (j < m-1 && G.at<float>(i, j) + eps < G.at<float>(i, j + 1))
preserved[i][j] = false;
break;
}

case 90:
{
if (i > 0 && G.at<float>(i, j) + eps < G.at<float>(i - 1, j))
preserved[i][j] = false;
if (i < n - 1 && G.at<float>(i, j) + eps < G.at<float>(i + 1, j))
preserved[i][j] = false;
break;
}

case 45:
{
if (i > 0  && j < m-1 && G.at<float>(i, j) + eps < G.at<float>(i - 1, j + 1))
preserved[i][j] = false;
if (i < n - 1 && j > 0 && G.at<float>(i, j) + eps < G.at<float>(i + 1, j - 1))
preserved[i][j] = false;
break;
}

case 135:
{
if (i > 0 && j > 0 && G.at<float>(i, j) + eps < G.at<float>(i - 1, j - 1))
preserved[i][j] = false;
if (i < n - 1 && j < m - 1 && G.at<float>(i, j) + eps < G.at<float>(i + 1, j + 1))
preserved[i][j] = false;
break;
}
default:

break;
}
*/