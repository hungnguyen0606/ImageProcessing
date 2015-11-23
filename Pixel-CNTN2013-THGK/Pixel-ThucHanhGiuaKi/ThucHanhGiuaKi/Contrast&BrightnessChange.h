#ifndef _CHANGE_BRIGHT_
#define _CHANGE_BRIGHT_

#include "header.h"

using namespace cv;

Mat    changeBriAndCon(Mat img, double alpha, int beta)
{
    int width = img.size().width;
    int height = img.size().height;
    Mat res = img.clone();
    for (int i = 0; i < height; ++i)
        for (int j = 0; j < width; ++j)
        {
            for (int k = 0; k < 3; ++k)
                res.at<Vec3b>(i, j)[k] = saturate_cast<uchar>(alpha * img.at<Vec3b>(i, j)[k] + beta);
        }
    return res;
}

#endif // _CHANGE_BRIGHT_
