#ifndef _OPERATOR_
#define _OPERATOR_
#include "header.h"

using namespace std;

//apply convolution of 1-channel image with the resust type is float
int     convolutionFloat(Mat src, Mat kernel, Mat &res)
{
	if (src.type() != 0)
	{
		cout << "Error in convolution: Image type must be unsigned int.\n\n";
		return 0;
	}
	if (kernel.type() != 5)
	{
		cout << "Error in convolution: Kernel type must be float.\n\n";
		return 0;
	}
	if (kernel.size().width != kernel.size().height || kernel.size().width % 2 == 0)
	{
		cout << "Error in convolution: Size of Kernel must be (2k + 1) * (2k + 1) (k >= 0).\n\n";
		return 0;
	}
	//get kernel size w = 2 * k + 1
	int k = kernel.size().width / 2;
	int w = kernel.size().width;

	//get image size
	int height = src.size().height;
	int width = src.size().width;

	//copy source image to result image
	src.convertTo(res, CV_32F);
	for (int i = k; i < height - k; ++i)
	{
		for (int j = k; j < width - k; ++j)
		{
			//apply convolution to window size sz * sz from i - k, j - k
			float tmp = 0;
			for (int u = -k; u <= k; ++u)
				for (int v = -k; v <= k; ++v)
					tmp += float(src.at<uint8_t>(i - u, j - v)* kernel.at<float>(k + u, k + v));

			res.at<float>(i, j) = tmp;
		}
	}
	return 1;
}

int     convolution(Mat src, Mat kernel, Mat &res)
{
	if (src.type() != 0)
	{
		cout << "Error in convolution: Image type must be unsigned int.\n\n";
		return 0;
	}
	if (kernel.type() != 5)
	{
		cout << "Error in convolution: Kernel type must be float.\n\n";
		return 0;
	}
	if (kernel.size().width != kernel.size().height || kernel.size().width % 2 == 0)
	{
		cout << "Error in convolution: Size of Kernel must be (2k + 1) * (2k + 1) (k >= 0).\n\n";
		return 0;
	}
	//get kernel size w = 2 * k + 1
	int k = kernel.size().width / 2;
	int w = kernel.size().width;

	//get image size
	int height = src.size().height;
	int width = src.size().width;

	//copy source image to result image
	res = src.clone();
	for (int i = k; i < height - k; ++i)
	{
		for (int j = k; j < width - k; ++j)
		{
			//apply convolution to window size sz * sz from i - k, j - k
			float tmp = 0;
			for (int u = -k; u <= k; ++u)
				for (int v = -k; v <= k; ++v)
					tmp += float(src.at<uint8_t>(i - u, j - v)* kernel.at<float>(k + u, k + v));

			res.at<uint8_t>(i, j) = uint8_t(tmp);
		}
	}
	return 1;
}

//apply convolution of 3-channel image
int     convolutionRGB(Mat src, Mat kernel, Mat &res)
{
	if (kernel.type() != 5)
	{
		cout << "Error in convolution: Kernel type must be float.\n\n";
		return 0;
	}
	if (kernel.size().width != kernel.size().height || kernel.size().width % 2 == 0)
	{
		cout << "Error in convolution: Size of Kernel must be (2k + 1) * (2k + 1) (k >= 0).\n\n";
		return 0;
	}
	if (kernel.size().width != kernel.size().height || kernel.size().width % 2 == 0)
		return 0;

	//split image to 3 channels
	vector<Mat> res_rgb;
	split(src, res_rgb);

	//apply convolution for each channel
	for (int i = 0, sz = res_rgb.size(); i < sz; ++i)
	{
		if (convolution(res_rgb[i], kernel, res_rgb[i]) != 1)
			return 0;
	}

	//merge 3 chanenls into result image
	merge(res_rgb, res);

	//return 1 if sucess
	return 1;
}

//apply median value of each window size sz * sz of 1-channel image
int     Meadian(Mat src, int sz, Mat &res)
{
	//apply just for odd window size
	sz += (sz % 2 == 0);

	//get size of image
	int width = src.size().width;
	int height = src.size().height;

	//copy source to result
	res = src.clone();

	//sz = 2 * k + 1
	int k = sz / 2;

	//array save all elements of window from i - k, j - k
	int window_arr[10000];

	for (int i = k; i < height - k; ++i)
		for (int j = k; j < width - k; ++j)
		{
			//assign all elements of window from ị-k, j- k  to window_arr
			for (int u = 0; u < sz; ++u)
				for (int v = 0; v < sz; ++v)
					window_arr[u * sz + v] = src.at<uint8_t>(i - k + u, j - k + v);
			//sort window_arr ascending
			sort(window_arr, window_arr + sz *sz);

			//assign median of window_arr to result(i, j)
			res.at<uint8_t>(i, j) = window_arr[sz * sz / 2];
		}

	//return 1 if sucess
	return 1;
}


//apply median value of each window size sz * sz of 3-channel image
int     MedianRGB(Mat src, int sz, Mat &res)
{
	//split image to 3 channels
	vector<Mat> res_rgb;
	split(src, res_rgb);

	//apply meadian to each channel
	for (int i = 0, sz_rgb = res_rgb.size(); i < sz_rgb; ++i)
	{
		//if error occurs in any channel, return 0
		if (Meadian(res_rgb[i], sz, res_rgb[i]) != 1)
			return 0;
	}

	//merge 3 channel into result image
	merge(res_rgb, res);

	//return 1 if sucess
	return 1;
}

//apply mean value of each window size sz * sz of 1-channel image
int     Mean(Mat src, int sz, Mat &res)
{
	//apply just for odd window size
	sz += (sz % 2 == 0);

	//get size of image
	int width = src.size().width;
	int height = src.size().height;

	//copy source to result
	res = src.clone();

	//sz = 2 * k + 1
	int k = sz / 2;

	for (int i = k; i < height - k; ++i)
		for (int j = k; j < width - k; ++j)
		{
			//get window size sz * sz from image
			Rect windowRect = Rect(j - k, i - k, sz, sz);
			Mat window = src(windowRect);

			//assign value average of window to result image at (i, j)
			res.at<uint8_t>(i, j) = uint8_t(sum(window)[0] / (sz * sz));
		}

	//return 1 if sucess
	return 1;
}


//apply mean value of each window size sz * sz of 3-channel image
int     MeanRGB(Mat src, int sz, Mat &res)
{
	//split image to 3 channels
	vector<Mat> res_rgb;
	split(src, res_rgb);

	//apply meadian to each channel
	for (int i = 0, sz_rgb = res_rgb.size(); i < sz_rgb; ++i)
	{
		//if error occurs in any channel, return 0
		if (Mean(res_rgb[i], sz, res_rgb[i]) != 1)
			return 0;
	}

	//merge 3 channel into result image
	merge(res_rgb, res);

	//return 1 if sucess
	return 1;
}

#endif // _OPERATOR_
