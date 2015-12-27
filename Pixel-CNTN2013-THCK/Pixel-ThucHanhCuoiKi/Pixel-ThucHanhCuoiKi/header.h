#ifndef _HEADER_
#define _HEADER_

#include <iostream>
#include <stdio.h>
#include <math.h>
#include <vector>
#include <iterator>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;
using namespace std;

const double PI = acos(-1);
const int MAX_SIZE = 300;
#define wrtCrss { cout << "----------------------------------------------------------------------------\n";}


int getSelection(char* name, int nArr, const char **selectArr);

#endif // _HEADER_


