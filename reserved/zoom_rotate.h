#ifndef _ZOOMROTATE_
#define _ZOOMROTATE_

#include "header.h"

using namespace std;
using namespace cv;

Mat     affine(Mat img, Mat kernel)
{
    Mat res = img.clone();
    double angle = 45;
    double scale = 1.5;

    Point2f center = (img.cols/2, img.rows/2);

    for (int i = 0; i < img.cols; ++i)
        for (int j = 0; j < )
}

#endif // _ZOOMROTATE_
