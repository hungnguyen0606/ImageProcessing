#ifndef _TRANSFORM_
#define _TRANSFORM_

#include "header.h"

//type = 1: round, type = 2: noi suy tuyen tinh, type = 3: affine - chua cai
//alpha < 1: zoom in; alpha > 1: zoom out
Mat     zoom(Mat img, double alpha, int type = 1);
Mat     zoom(Mat img, double alpha, int type)
{
    int height = img.size().height;
    int width = img.size().width;

    int new_height = height * alpha;
    int new_width = width * alpha;
    Mat res = Mat(new_height, new_width, CV_8UC3);

    for (int i = 0; i < new_height - (type > 1); ++i)
        for (int j = 0; j < new_width - (type > 1); ++j)
        {
			//cout << i << ' ' << j << endl;
			if (j == 1918)
				cout << "";
            int x = i / alpha + 1;
            int y = j / alpha + 1;
            if (type == 1)
                res.at<Vec3b>(i, j) = img.at<Vec3b>(min(x, height-1), min(y,width-1));
            if (type == 2)
            {
                int u = int(double(i)/alpha - x + 0.5);
                int v = int(double(j)/alpha - y + 0.5);
                res.at<Vec3b>(i, j) = (1 - u) * (1 - v) * img.at<Vec3b>(min(x,height-1), min(y,width-1)) + u*(1 - v) * img.at<Vec3b>(min(x + 1,height-1), min(y,width-1))
                                    + (1 - u) * v * img.at<Vec3b>(min(x,height-1), min(y + 1,width-1)) + u * v *img.at<Vec3b>(min(x + 1, height-1), min(y + 1,width-1));
            }
        }
    return res;
}

#endif // _TRANSFORM_

