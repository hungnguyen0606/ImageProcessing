#ifndef _HISTOGRAM_
#define _HISTOGRAM

#include "header.h"

using namespace std;

void    drawHistogram(Mat img)
{
    int width = img.size().width, height = img.size().height;
    int win_h = 400, win_w = 400;
    int size_his = 256;
    float range[] = {0, size_his-1};
    const float* his_range = {range};
    int bin = cvRound(double(win_w) / (size_his-1));

    vector<Mat> img_rgb;
    vector<Mat> his;
    his.clear();
    for (int i = 0; i < 3; ++i)
        his.push_back(Mat());

    split(img, img_rgb);

    //tinh histogram
    for (int i = 0; i < 3; ++i)
    {
        his[i] = Mat(1, size_his, CV_32FC1, Scalar_<float>(0));
        for (int x = 0; x < height; ++x)
            for (int y = 0; y < width; ++y)
        {
            uint8_t t = img_rgb[i].at<uint8_t>(x, y);
            ++(his[i].at<float>(t));
        }

    }

    //Scale theo window
    for (int i = 0; i < 3; ++i)
    {
        double Min, Max;
        minMaxLoc(his[i], &Min, &Max);
        for (int j = 0; j < size_his; ++j)
            his[i].at<float>(j) = (his[i].at<float>(j) * win_h) / Max;
    }

    //ve histogram
    vector<Mat> disp;
    for (int i = 0; i < 3; ++i)
        disp.push_back(Mat(win_h, win_w, CV_8UC3, Scalar(255, 255, 255)));

    imshow("src", img);
    for (int i = 0; i < 255; ++i)
    {
        line(disp[0], Point(bin*(i), win_h), Point(bin*(i), win_h - cvRound(his[0].at<float>(i))), Scalar(0, 0, 255), 2, 8, 0);
        line(disp[1], Point(bin*(i), win_h), Point(bin*(i), win_h - cvRound(his[1].at<float>(i))), Scalar(0, 255, 0), 2, 8, 0);
        line(disp[2], Point(bin*(i), win_h), Point(bin*(i), win_h - cvRound(his[2].at<float>(i))), Scalar(255, 0, 0), 2, 8, 0);
    }

    for (int j = 0; j < 3; ++j)
    {
        char name[200];
        sprintf(name, "Channel %d", j);
        imshow(name, disp[j]);
    }
    waitKey(0);
}


Mat    histogramEqualization(Mat img)
{
    int height = img.size().height, width = img.size().width;
    int size_his = 256;
    float range[] = {0, size_his};
    const float* his_range = {range};

    vector<Mat> img_rgb;
    vector<Mat> his;
    his.clear();
    for (int i = 0; i < 3; ++i)
        his.push_back(Mat());

    split(img, img_rgb);
    for (int i = 0; i < 3; ++i)
    {
        his[i] = Mat(1, size_his, CV_32FC1, Scalar_<float>(0));
        for (int x = 0; x < height; ++x)
            for (int y = 0; y < width; ++y)
        {
			
            int t = img_rgb[i].at<uint8_t>(x, y);
            ++(his[i].at<float>(t));
        }

    }

    for (int i = 0; i < 3; ++i)
        for (int j = 1; j < size_his; ++j)
            his[i].at<float>(j) += his[i].at<float>(j - 1);

    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < size_his; ++j)
            his[i].at<float>(j) = (his[i].at<float>(j) * (size_his-1)) / (width * height);

    Mat res = Mat(height, width, CV_8UC3);

    for (int x = 0; x < height;  ++x)
        for (int y = 0; y < width; ++y)
            for (int i = 0; i < 3; ++i)
            {
                int t = img.at<Vec3b>(x, y)[i];
                res.at<Vec3b>(x, y)[i] = uint8_t(his[i].at<float>(t));
            }
    return res;
}


#endif // _HISTOGRAM_

