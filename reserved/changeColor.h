#ifndef _CHANGE_COLOR_
#define _CHANGE_COLOR_

#include "header.h"

using namespace cv;

Mat    linearChange(Mat img, double alpha, int beta)
//change color by equation f(x,y) * alpha + beta
{
    //get image size
    int width = img.size().width;
    int height = img.size().height;

    //copy img to res
    Mat res = img.clone();

    //apply equation for all pixels of res
    for (int i = 0; i < height; ++i)
        for (int j = 0; j < width; ++j)
        {
            for (int k = 0; k < 3; ++k)
                res.at<Vec3b>(i, j)[k] = saturate_cast<uchar>(alpha * img.at<Vec3b>(i, j)[k] + beta);
        }

    return res;
}

Mat     nonLinearChange(Mat img, double k, int type)
// type = 1: k * log(f(x, y) + 1), +1 to avoid log(0)
// type = 2: e^ f(x, y)
{
//    Mat res = img.clone();
//    for (int i = 0, height = img.size().height; i < height; ++i)
//        for (int j = 0, width = img.size().width; j < width; ++j)
//            for (int c = 0; c < 3; ++c)
//                if (type == 1)
//                    res.at<Vec3b>(i, j)[c] = uint8_t(k * ( 255 * log(img.at<Vec3b>(i, j)[c] + 1) / log(256)));
//                else
//                    res.at<Vec3b>(i, j)[c] = uint8_t(k * exp(img.at<Vec3b>(i, j)[c] *1.0 / 255) / exp(1) * 255);

    int height = img.size().height;
    int width = img.size().width;
    Mat img2 = Mat(height, width, CV_32F);
    for (int i = 0; i <height; ++i)
        for (int j = 0; j < width; ++j)
            for (int c = 0; c < 3; ++c)
                img2.at<Vec3f>(i, j)[c] = float(img.at<Vec3b>(i, j)[c] + 1) / 255;

    Mat res;
    log(img2, res);
    res = res * k;
    res = res/log(255) * 255;
    return res;
}

#endif // _CHANGE_COLOR_
