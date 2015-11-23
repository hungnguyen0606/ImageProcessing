#ifndef  _GRADIENT_
#define _GRADIENT_
#include "header.h"

using namespace cv;
//const Mat SOBEL = (Mat_<uint8_t>(3,3) << -1, 0, 1, -2, 0, 2, -1, 0, 1);

Mat     GradientPrewitt(int sz)
{
    sz += (sz % 2 == 0);
    Mat res = Mat (sz, sz, CV_32FC1, Scalar_<float>(0));

    int k = sz/2;
    for (int i = 0; i < sz; ++i)
        for (int j = 0; j < sz; ++j)
            res.at<float>(i, j) = abs(j - k);
    return res;
}

Mat     GradientSobel(int sz)
{
    sz = sz + (sz % 2 == 0);

    Mat res = Mat(sz, sz, CV_32FC1, Scalar_<float>(0));
    int k = sz/2;
    double hs = 0;
    for (int i = 0; i < sz; ++i)
        for (int j = 0; j < sz; ++j)
        {
            res.at<float>(i, j) = (1 - 2 * (j > k)) * (abs(j - k) - abs(i - k) + k);
            hs += res.at<float>(i, j);
        }

    res.at<float>(k , k) = 0;
    res /= hs;

    return res;
}

Mat     Frei_Chen()
{
    int sz = 3;
    Mat res = Mat::zeros(sz, sz, CV_32FC1);
    res.at<float>(0, 0) = res.at<float>(2, 0) = 1;
    res.at<float>(0, 2) = res.at<float>(2, 2) = -1;
    res.at<float>(1, 0) = res.at<float>(1, 2) = sqrt(2);
    return res / (2 + sqrt(2));
}

#endif  _GRADIENT
