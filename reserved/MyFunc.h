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

using namespace cv;
using namespace std;

Mat src, src_gray;
Mat dst, detected_edges;
/**
* @function CannyThreshold
* @brief Trackbar callback - Canny thresholds input with a ratio 1:3
*/

void    myfunc_viewVideo(VideoCapture *video)
{
    readAndShowVideo(video);
}

void    myfunc_ViewDepthImage(Mat img)
{
    //[HUNG]
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
}

void    myfunc_LUV2RGB(Mat img)
{
    //[HUNG]
}


void    myfunc_RGB2Lab(Mat img)
{
    //[HUNG]
}

void    myfunc_LabRGB(Mat img)
{
    //[HUNG]
}

void    myfunc_RGB2YCbCr(Mat img)
{
    //[HUNG]
}


void    myfunc_YCbCr2RGB(Mat img)
{
    //[HUNG]
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
	Mat ker = GradientPrewitt(kernelsize);
	convolutionRGB(im, ker, im);
	imshow("My Function: Prewitt Filter", im);
}

void    myfunc_Gauss(Mat im, int kernelsize)
{
	Mat ker = GAUSS(kernelsize);
	convolutionRGB(im, ker, im);
	imshow("My Function: Gauss Filter", im);
}

void    myfunc_Sobel(Mat im, int kernelsize)
{
	Mat ker = GradientSobel(kernelsize);
	convolutionRGB(im, ker, im);
	imshow("My Function: Sobel Filter", im);
}

void    myfunc_FreiChen(Mat im)
{
	Mat ker = GradientFrei_Chen();
	convolutionRGB(im, ker, im);
	imshow("My Function: FreiChen Filter", im);
}



#endif // _MyFunc_
