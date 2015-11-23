#ifndef _HISTOGRAM_
#define _HISTOGRAM

#include "header.h"
#include "convert_ColorModel.h"

using namespace std;

void    drawHistogram(Mat img, char *name)
{
    int width = img.size().width, height = img.size().height;
    int win_h = 400, win_w = 400;
    int size_his = 256;
    float range[] = {0, size_his-1};
    const float* his_range = {range};
    int bin = cvRound(double(win_w) / (size_his-1));

    //split img into 3 channels
    vector<Mat> img_channels;
    split(img, img_channels);

    //create a vector to save histogram of each channel
    vector<Mat> his;
    his.clear();
    for (int i = 0; i < 3; ++i)
        his.push_back(Mat());

    //calculate histogram
    for (int i = 0; i < 3; ++i)
    {
        his[i] = Mat(1, size_his, CV_32FC1, Scalar_<float>(0));
        for (int x = 0; x < height; ++x)
            for (int y = 0; y < width; ++y)
            {
                uint8_t t = img_channels[i].at<uint8_t>(x, y);
                ++(his[i].at<float>(t));
            }
    }

    //Scale with window
    for (int i = 0; i < 3; ++i)
    {
        double Min, Max;
        minMaxLoc(his[i], &Min, &Max);
        for (int j = 0; j < size_his; ++j)
            his[i].at<float>(j) = (his[i].at<float>(j) * win_h) / Max;
    }

    //draw histogram
    vector<Mat> disp;
    for (int i = 0; i < 3; ++i)
        disp.push_back(Mat(win_h, win_w, CV_8UC3, Scalar(255, 255, 255)));

    for (int i = 0; i < 255; ++i)
    {
        //draw first channel with blue color
        line(disp[0], Point(bin*(i), win_h), Point(bin*(i), win_h - cvRound(his[0].at<float>(i))), Scalar(255, 0, 0), 2, 8, 0);
        //draw second channel with green color
        line(disp[1], Point(bin*(i), win_h), Point(bin*(i), win_h - cvRound(his[1].at<float>(i))), Scalar(0, 255, 0), 2, 8, 0);
        //draw third channel with red color
        line(disp[2], Point(bin*(i), win_h), Point(bin*(i), win_h - cvRound(his[2].at<float>(i))), Scalar(0, 0, 255), 2, 8, 0);
    }

    //show 3 channel
    for (int j = 0; j < 3; ++j)
    {
        char channel_name[200];
        sprintf(channel_name, "%s: Channel %d", name, j);
        imshow(channel_name, disp[j]);
    }
    waitKey(0);
}

Mat    equalizeHis(Mat src)
{
    int size_his = 256;
    int height = src.size().height, width = src.size().width;

    //create a vector to save histogram of channel
    Mat his = Mat(1, size_his, CV_32FC1, Scalar_<float>(0));
    for (int x = 0; x < height; ++x)
        for (int y = 0; y < width; ++y)
        {
            int t = src.at<uint8_t>(x, y);
            ++(his.at<float>(t));
        }

    //calculate histogram
    for (int j = 1; j < size_his; ++j)
        his.at<float>(j) += his.at<float>(j - 1);

    //equalize histogram
    for (int j = 0; j < size_his; ++j)
        his.at<float>(j) = (his.at<float>(j) * (size_his-1)) / (width * height);

    //find new value for img with equalized histogram
    Mat res = Mat(height, width, CV_8UC1);
    for (int x = 0; x < height;  ++x)
        for (int y = 0; y < width; ++y)
        {
            int t = src.at<uint8_t>(x, y);
            res.at<uint8_t>(x, y) = uint8_t(his.at<float>(t));
        }

    return res;
}


Mat    histogramEqualization(Mat img)
{
    //convert img in rgb to hsv
    Mat hsv = convert_RGB2HSV(img);
//    Mat v_channel = hsv[:,:, 2];
    vector<Mat> hsv_channels;

//    split hsv to 3 channels: H, S, V
    split(hsv, hsv_channels);

    //equalize v channel
    hsv_channels[2] = equalizeHis(hsv_channels[2]);

    //merge 3 channels H, S, V into hsv
    merge(hsv_channels, hsv);

    //convert img in hsv back to rgb and return the result
    return convert_HSV2RGB(hsv);
}


#endif // _HISTOGRAM_

