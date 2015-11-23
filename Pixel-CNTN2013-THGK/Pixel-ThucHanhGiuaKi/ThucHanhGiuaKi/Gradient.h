#ifndef  _GRADIENT_
#define _GRADIENT_

#include "header.h"

using namespace cv;

void     GradientPrewitt(int sz, Mat &Gx, Mat &Gy)
//create Prewitt Gradient with size sz
{
	//only use gradient with odd size
	sz += (sz % 2 == 0);
	int k = sz / 2;

	Gx = Mat(sz, sz, CV_32FC1, Scalar_<float>(0));

	for (int i = 0; i < sz; ++i)
		for (int j = 0; j < sz; ++j)
			Gx.at<float>(i, j) = j - k;

	Gy = Mat(sz, sz, CV_32FC1, Scalar_<float>(0));

	for (int i = 0; i < sz; ++i)
		for (int j = 0; j < sz; ++j)
			Gy.at<float>(i, j) = Gx.at<float>(j, i);

}

void     GradientSobel(int sz, Mat &Gx, Mat &Gy)
//create Sobel Gradient with size sz
{
	//only use Gradient with odd size
	sz = sz + (sz % 2 == 0);
	int k = sz / 2;

	Gx = Mat(sz, sz, CV_32FC1, Scalar_<float>(0));

	double hs = 0;
	for (int i = 0; i < sz; ++i)
		for (int j = 0; j < sz; ++j)
		{
			Gx.at<float>(i, j) = (1 - 2 * (j < k)) * (abs(j - k) - abs(i - k) + k);
			hs += Gx.at<float>(i, j);
		}

	Gx.at<float>(k, k) = 0;
	Gx /= hs;

	Gy = Mat(sz, sz, CV_32FC1, Scalar_<float>(0));

	for (int i = 0; i < sz; ++i)
		for (int j = 0; j < sz; ++j)
			Gy.at<float>(i, j) = Gx.at<float>(j, i);
}

void     GradientFrei_Chen(Mat &Gx, Mat &Gy)
//create Frei_Chen Gradient with size = 3
{
	int sz = 3;
	Gx = Mat::zeros(sz, sz, CV_32FC1);
	Gx.at<float>(0, 0) = Gx.at<float>(2, 0) = 1;
	Gx.at<float>(0, 2) = Gx.at<float>(2, 2) = -1;
	Gx.at<float>(1, 0) = sqrt(2);
	Gx.at<float>(1, 2) = -sqrt(2);

	Gy = Mat(sz, sz, CV_32FC1, Scalar_<float>(0));

	for (int i = 0; i < sz; ++i)
		for (int j = 0; j < sz; ++j)
			Gy.at<float>(i, j) = Gx.at<float>(j, i);

	
}

#endif  _GRADIENT
