#ifndef _HEADER_
#define _HEADER_

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/affine.hpp>
#include <opencv2/core/mat.hpp>
#include <iostream>
#include <algorithm>
#include <cmath>
#include "stdio.h"

using namespace std;
using namespace cv;

const double PI = acos(-1);
const Mat RGB_HSV = (Mat_<float>(3,3) << sqrt(3)/3, sqrt(3)/3, sqrt(3)/3, 0, sqrt(2)/2, -sqrt(2)/2, sqrt(2)/sqrt(3), -sqrt(6)/6, -sqrt(6)/6);

typedef unsigned __int8 uint8_t;
typedef unsigned __int16 uint16_t;
typedef __int8 int8_t;
#endif // _HEADER_
