#ifndef _TRANSFORM_
#define _TRANSFORM_

#include "header.h"

//type = 1: song tuyen tinh, type = 2: round
//alpha < 1: zoom in; alpha > 1: zoom out
Mat     zoom(Mat img, double alpha_y, double alpha_x, int type = 1);
Mat     zoom(Mat img, double alpha_y, double alpha_x, int type)
{
	int height = img.size().height;
	int width = img.size().width;

	int new_height = height * alpha_x;
	int new_width = width * alpha_y;
	Mat res = Mat(new_height, new_width, CV_8UC3);

	for (int i = 0; i < new_height; ++i)
		for (int j = 0; j < new_width; ++j)
		{
			int x = i / alpha_x + 1;
			int y = j / alpha_y + 1;
			int u = int(double(i) / alpha_x - x + 0.5);
			int v = int(double(j) / alpha_y - y + 0.5);
			res.at<Vec3b>(i, j) = (1 - u) * (1 - v) * img.at<Vec3b>(min(x, height - 1), min(y, width - 1)) + u*(1 - v) * img.at<Vec3b>(min(x + 1, height - 1), min(y, width - 1))
				+ (1 - u) * v * img.at<Vec3b>(min(x, height - 1), min(y + 1, width - 1)) + u * v *img.at<Vec3b>(min(x + 1, height - 1), min(y + 1, width - 1));
		}
	return res;
}

Mat     rotateImage(Mat img, double angel)
{
	angel = angel * PI / 180;
	int height = img.size().height;
	int width = img.size().width;

	Mat res = Mat(img.size(), CV_8UC3);

	//    Mat kernel = (Mat_<float>(2, 2) << cos(angel), -sin(angel), sin(angel), cos(angel));
	for (int i = 0; i < height; ++i)
		for (int j = 0; j < width; ++j)
		{
			int newi = max(0, min(height-1, int(cos(angel) * i - sin(angel) * j)));
			int newj = max(0, min(width-1, int(sin(angel) * i + cos(angel) * j)));

			res.at<Vec3b>(newi, newj) = img.at<Vec3b>(i, j);
		}
	return res;
}

#endif // _TRANSFORM_

