#ifndef _OPERATOR_
#define _OPERATOR_
#include "header.h"

using namespace std;

int     convolution(Mat src, Mat kernel, Mat &res)
{
	cout << src.type() << endl;
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

    int k = kernel.size().width / 2;
    int w = kernel.size().width;

    int height = src.size().height;
    int width = src.size().width;

    res = src.clone();
    for (int i = k; i < height - k; ++i)
    {
        for (int j = k; j < width - k; ++j)
        {
            float tmp = 0;
            for (int u = 0; u < w; ++u)
                for (int v = 0; v < w; ++v)
                    tmp = tmp + float(kernel.at<float>(u, v) * src.at<uint8_t>(i - k + u, j - k + v));

            if (tmp < 0)
                tmp = 0;
            if (tmp > 255)
                tmp = 255;

            res.at<uint8_t>(i, j) = uint8_t(tmp);
        }
    }

    return 1;
}

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

    vector<Mat> res_rgb;
    split(src, res_rgb);

    for (int i = 0, sz = res_rgb.size(); i < sz; ++i)
    {
        if (convolution(res_rgb[i], kernel, res_rgb[i]) != 1)
            return 0;
    }
    merge(res_rgb, res);
    return 1;
}


int     Meadian(Mat src, int sz, Mat &res)
{
    cout << "ok\n";
    sz += (sz % 2 == 0);
    int width = src.size().width;
    int height = src.size().height;

    res = src.clone();
    int k = sz/2;
    for (int i = k; i < height - k; ++i)
        for (int j = k; j < width - k; ++j)
        {
            vector<uint8_t> tmp;
            tmp.clear();
            for (int u = -k; u <= k; ++u)
                for (int v = -k; v < k; ++v)
                    tmp.push_back(src.at<uint8_t>(i + u, j + v));
            sort(tmp.begin(), tmp.end());
            res.at<uint8_t>(i, j) = tmp[sz * sz / 2];
        }
    return 1;
}

int     MedianRGB(Mat src, int sz, Mat &res)
{
    vector<Mat> res_rgb;
    split(src, res_rgb);

    for (int i = 0, sz = res_rgb.size(); i < sz; ++i)
    {
        if (Meadian(res_rgb[i], sz, res_rgb[i]) != 1)
            return 0;
    }
    merge(res_rgb, res);
    return 1;
}


#endif // _OPERATOR_
