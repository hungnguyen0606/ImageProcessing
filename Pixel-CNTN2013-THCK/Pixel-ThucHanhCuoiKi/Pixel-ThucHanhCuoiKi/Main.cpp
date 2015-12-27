#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "header.h"
#include "Morphology.h"
#include "DemoMorphology.h"
using namespace std;
using namespace cv;

int thres = 200;
int count(Mat a)
{
	int u = 0;
	for (int i = 0; i < a.size().height; ++i)
		for (int j = 0; j < a.size().width; ++j)
			if (a.at<uint8_t>(i, j) == 0)
				++u;
	cout << a.size().height << ' ' << a.size().width << ' ' << u << endl;
	return u;
}
void DemoMorphologyCallback(int, void*)
{
	Mat img = imread("Image/devil.png", CV_LOAD_IMAGE_GRAYSCALE);
	cv::threshold(img, img, thres, 255, cv::THRESH_BINARY);
	
	//create function structure
	int sz =3;
	Mat kernel = Mat(sz, sz, CV_8UC1, Scalar_<uint8_t>(0));
	for (int i = 0; i < sz; ++i)
		for (int j = 0; j < sz; ++j)
			kernel.at<uint8_t>(i, j) = 1;
	
	//kernel.at<uint8_t>(5, 0) = 1;
	//kernel.at<uint8_t>(5, 9) = 1;
	std::pair<int,int> center = std::pair<int,int>(sz / 2, sz / 2);
	//
	count(img);
	imshow("Original image", img);
	//Mat temp = BinaryDilation(img, kernel, center);
	//Mat temp2 = BinaryErosion(temp, kernel, center);
	//count(temp);
//	count(temp2);
	//cout << img << endl;
	//cout << temp;
	//Mat temp = -BinaryDilation(img, kernel, center)+BinaryErosion(img, kernel, center);
	//imshow("Ero", temp);
	imshow("Dilate", BinaryBoundaryExtraction(img));
}
void DemoMorpho()
{
	/*Mat element = cv::getStructuringElement(cv::MORPH_CROSS, cv::Size(10, 10));
	Mat img = imread("Image/devil.png", CV_LOAD_IMAGE_GRAYSCALE);
	cv::threshold(img, img, 100, 255, cv::THRESH_BINARY);
	erode(img, img, element);*/
	//imshow("Original image", img);
	namedWindow("Result", CV_WINDOW_AUTOSIZE);
	createTrackbar("BinaryThreshold", "Result", &thres, 255, DemoMorphologyCallback);
	DemoMorphologyCallback(0, 0);
	//cout << img < 100;
	waitKey(0);
}

int main()
{
	demoConvexHull();
	//demoThinning();
	//demoThickening();
	//demoSkeleton();
	/*Mat img = imread("Image/devil.png", CV_LOAD_IMAGE_GRAYSCALE);
	cv::threshold(img, img, thres, 255, cv::THRESH_BINARY);
	Mat temp = img.clone();
	bitwise_not(img, img);
	bitwise_and(img, temp, img);
	imshow("hello", img);*/
	//demoFillingRegion();
	//DemoMorpho();
	//demoTopHat();
	/*demoMorphologyGradient();
	demoBinaryDilation();
	demoBinaryErosion();*/
	//Mat img = imread("Image/labyrinth.png", CV_LOAD_IMAGE_GRAYSCALE);
	//imshow("temp", 255 - img);
	int sz = 5;
	Mat kernel = Mat(sz, sz, CV_8UC1, Scalar_<uint8_t>(0));
	for (int i = 0; i < sz; ++i)
		for (int j = 0; j < sz; ++j)
		{
			kernel.at<uint8_t>(i, j) = 30;
			
		}
			
	//imshow("Origin", img);
	//imshow("Boundary extraction", BinaryBoundaryExtraction(img));
	//imshow("Graydilate", MorphologyGradient(img, kernel, std::make_pair(2, 2)));
	//imshow("Dinh non", img - GrayscaleOpening(img, kernel, std::make_pair(sz / 2, sz / 2)));
	//cout << img - GrayscaleOpening(img, kernel, std::make_pair(sz / 2, sz / 2));
	waitKey(0);
	return 0;
}