#ifndef _KERNEL_
#define _KERNEL_

#include "header.h"


using namespace std;
using namespace cv;

Mat     GAUSS(int sz)
{
    double xi = sqrt(0.25);
    sz = sz + (sz % 2 == 0);
    int k = sz / 2;
    Mat res = Mat(sz, sz, CV_32FC1, Scalar_<float>(0));
    for (int i = 0; i < sz; ++i)
        for (int j = 0; j < sz; ++j)
        {
            int tmpi = (i - k) * (i - k);
            int tmpj = (j - k) * (j - k);
            res.at<float>(i, j) = 1 / (2 * PI * xi * xi) * exp(-(tmpi + tmpj) / (2 * xi * xi));
        }
    return res;
}

Mat     means(int sz)
{
    return (Mat::ones(sz, sz, CV_32FC1) / (sz * sz));
}

#endif // _KERNEL_
