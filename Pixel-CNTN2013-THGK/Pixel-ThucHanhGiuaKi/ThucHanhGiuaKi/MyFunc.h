#ifndef _MyFunc_
#define _MyFunc_

#include <iostream>
#include "EdgeDectector.h"
#include "convert_ColorModel.h"
#include "Transform.h"
#include "operator.h"
#include "Kernel.h"
#include "Gradient.h"
#include "video.h"
#include "Histogram.h"
#include "changeColor.h"
#include "DepthImage.h"

using namespace cv;
using namespace std;

Mat src, src_gray;
Mat dst, detected_edges;
/**
* @function CannyThreshold
* @brief Trackbar callback - Canny thresholds input with a ratio 1:3
*/

void myfunc_Canny(Mat img)
{
	//showDepthImage(img);
	myCanny(img, img, 20, 30);
	imshow("My function: Edge Dectecting - Canny", img);
}
void    myfunc_viewVideo(VideoCapture *video)
{
    readAndShowVideo(video);
}

void    myfunc_ViewDepthImage(Mat img)
{
    //[HUNG]
	showDepthImage(img);
}


void    myfunc_RGB2HSV(Mat img)
{
    //use our function convert_RGB2HSV,
    //then use library function and show RGBMat to check whether convert_RGB2HSV works correctly
    Mat RGBMat;
    cvtColor(convert_RGB2HSV(img), RGBMat, CV_HSV2BGR);
    imshow("My Function: RGB to HSV", RGBMat);
}

void    myfunc_HSV2RGB(Mat img)
{
    //use library function convert_BGR2HSV,
    //then use our function and show the result to check whether convert_HSV2RGB works correctly

    Mat HSVMat;
    cvtColor(img, HSVMat, CV_BGR2HSV);
    imshow("My Function: HSV to RGB", convert_HSV2RGB(HSVMat));
}

void    myfunc_RGB2Gray(Mat img)
{
	imshow("My Function: RGB to Gray", convert_RGB2GRAY(img));
}

void    myfunc_RGB2LUV(Mat img)
{
    //[HUNG]
	imshow("My function: RGB -> LUV and reverse", convert_LUV2RGB(convert_RGB2LUV(img)));
}

void    myfunc_LUV2RGB(Mat img)
{
    //[HUNG]
	//convert_LUV2RGB(img);
}


void    myfunc_RGB2Lab(Mat img)
{
    //[HUNG]
	imshow("My function: RGB -> Lab and reverse", convert_LAB2RGB(convert_RGB2LAB(img)));

}

void    myfunc_Lab2RGB(Mat img)
{
    //[HUNG]
	//img = convert_LAB2RGB(img);
}

void    myfunc_RGB2YCbCr(Mat img)
{
    //[HUNG]
	imshow("My function: RGB -> YCbCr and reverse", convert_YCbCr2RGB(convert_RGB2YCbCr(img)));
}


void    myfunc_YCbCr2RGB(Mat img)
{
    //[HUNG]
	//img = convert_YCbCr2RGB(img);
}

void    myfunc_linearChange(Mat img, double alpha, int beta)
{
    //g(x, y) = f(x, y) * alpha + beta
    imshow("My Function: Linear Change", linearChange(img, alpha, beta));
}

void    myfunc_nonLinearChange_Log(Mat im, double k)
{
    //g(x, y) = k * log(f(x, y) + 1)
    imshow("My Function: Log Change", nonLinearChange(im, k, 1));
}

void    myfunc_nonLinearChange_Exp(Mat im, double k)
{
    //g(x, y) = k * e ^(f(x, y))
    imshow("My Function: Exp Change", nonLinearChange(im, k, 2));
}

void    myfunc_HistogramEqualization(Mat img)
{
    imshow("My Function: Histogram Equalization", histogramEqualization(img));
}


void    myfunc_Zoom(Mat img, double alpha_x, double alpha_y, int type)
{
    char name[200];
    sprintf(name, "My Function: Zoom %.2fxWidth %.2fxHeight - Method %d", alpha_x, alpha_y, type);
    imshow(name, zoom(img, alpha_x, alpha_y, type));
}

void    myfunc_Rotate(Mat img, double angle)
{
    //[AN]
	char name[200];
	sprintf(name, "My Function: Rotate %.2f angel", angle);
	imshow(name, rotateImage(img, angle));
}

void    myfunc_Mean(Mat im, int kernelsize)
{
	MeanRGB(im, kernelsize, im);
	imshow("My Function: Mean Filter", im);
}

void    myfunc_Median(Mat im, int kernelsize)
{
    Mat img2;
	MedianRGB(im, kernelsize, img2);
	imshow("My Function: Median Filter", img2);
}

void    myfunc_Prewitt(Mat im, int kernelsize)
{
	Mat img2, Gx, Gy;
	GradientPrewitt(kernelsize, Gx, Gy);

	Mat imx, imy;
	convolutionFloat(im, Gx, imx);
	convolutionFloat(im, Gy, imy);

	pow(imx.mul(imx) + imy.mul(imy), 0.5, img2);
	img2 = img2 / sqrt(2 * 255 * 255);

	imshow("My Function: Prewitt Filter", img2);
}

void    myfunc_Gauss(Mat im, int kernelsize, double sigma)
{
	Mat img2;
	Mat ker = GAUSS(kernelsize, sigma);
	convolutionRGB(im, ker, img2);
	imshow("My Function: Gauss Filter", img2);
}

//im must be grayscale image
void    myfunc_Sobel(Mat im, int kernelsize)
{
	Mat img2, Gx, Gy;
	GradientSobel(kernelsize, Gx, Gy);

	Mat imx, imy;
	convolutionFloat(im, Gx, imx);
	convolutionFloat(im, Gy, imy);

	pow(imx.mul(imx) + imy.mul(imy), 0.5, img2);
	img2 = img2 / sqrt(2 * 255 * 255);

	imshow("My Function: Sobel Filter", img2);
}


void    myfunc_FreiChen(Mat im)
{
	Mat img2, Gx, Gy;
	GradientFrei_Chen(Gx, Gy);

	Mat imx, imy;
	convolutionFloat(im, Gx, imx);
	convolutionFloat(im, Gy, imy);

	pow(imx.mul(imx) + imy.mul(imy), 0.5, img2);
	img2 = img2 / sqrt(2 * 255 * 255);

	imshow("My Function: FreiChen Filter", img2);
}



#endif // _MyFunc_
