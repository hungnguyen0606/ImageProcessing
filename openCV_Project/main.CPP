#include "header.h"
#include "Contrast&BrightnessChange.h"
#include "Histogram.h"
#include "convert_ColorModel.h"
#include "operator.h"
#include "Gradient.h"
#include "Kernel.h"

using namespace std;
using namespace cv;

void    demo(Mat img)
{
    imshow("RGB", img);

    Mat RGBMat;
    cvtColor(convert_RGB2HSV(img), RGBMat, CV_HSV2BGR);
    imshow("RGB2HSV", RGBMat);

    Mat HSVMat = convert_RGB2HSV(img);
    imshow("HSV2RGB", convert_HSV2RGB(HSVMat));

    Mat change = changeBriAndCon(img, 1.25, 20);
    imshow("Change", change);

    Mat gray;
    cvtColor(img, gray, CV_RGB2GRAY);
    Mat ad;
    adaptiveThreshold(gray, ad, 255, CV_ADAPTIVE_THRESH_GAUSSIAN_C, CV_THRESH_BINARY, 35, 10);
    imshow("Adaptive Threshold Gaussian", ad);

    imshow("Histogram Equalization", histogramEqualization(img));
    drawHistogram(histogramEqualization(img));

    Mat convolutionMat;
    convolutionRGB(img, GAUSS(3), convolutionMat);
    imshow("Convolution", convolutionMat);

    Mat med;
    MedianRGB(img, 7, med);
    imshow("Median", med);
}

Mat     input()
{
//    Mat img = imread("Image/rgb.vn_cmyk-rgb.jpg");
    Mat img = imread("Image/benthanh.png");
//    Mat img = imread("Image/lena.jpg");
//    Mat blackimg = Mat(img.size().height, img.size().width, CV_8UC3, Scalar(0, 0, 0));
//    Mat img = imread("Image/white.png");
//    Mat img = imread("Image/maru.jpg");

    return img;
}

int main()
{
    Mat img = input();
    if (!img.size().width || !img.size().height)
    {
        cout << "Error in reading image!\n";
        return 0;
    }


    waitKey(0);

    return 0;
}
