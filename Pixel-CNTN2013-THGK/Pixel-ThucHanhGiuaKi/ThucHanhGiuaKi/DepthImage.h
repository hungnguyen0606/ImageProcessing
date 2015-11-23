#ifndef _DEPTHIMAGE_H
#define _DEPTHIMAGE_H

#include "header.h"
void showDepthImage(Mat img)
{
	/*double low, high;
	cv::minMaxIdx(img, &low, &high);
	cv::Mat adjMap;
	cv::convertScaleAbs(img, adjMap, 255 / high);
	cv::imshow("Depth Image", adjMap);*/

	Mat src = imread("Image/maru.jpg", CV_LOAD_IMAGE_ANYDEPTH);
	cv::imshow("My function: Depth Image", src);
}

#endif