#ifndef _MORPHOLOGY_H_
#define _MORPHOLOGY_H_

#include "header.h"


//input includes a grayscale image, a structure function B whose each element is 0 or a nonzero number, and
//a pair of integer to indicate the center of B.
#define infinity 111111111
typedef unsigned __int8 uint8_t;
typedef unsigned __int16 uint16_t;
// Lưu ý: các phép Dilation/Erosion trong đây thực hiện việc dãn/co đối tượng trong ảnh nhị phân (màu đen),
//ngược với phép Dilation/Erosion trong opencv là dãn/co nền ảnh (màu trắng).
//Basis operators
Mat BinaryDilation(Mat src, Mat B, std::pair<int, int> center);
Mat BinaryErosion(Mat src, Mat B, std::pair<int, int> center);
Mat BinaryOpening(Mat src, Mat B, std::pair<int, int> center);
Mat BinaryClosing(Mat src, Mat B, std::pair<int, int> center);


//Phép giãn (dilation) độ xám: với 1 điểm ảnh ta chọn điểm ảnh có giá trị = (giá trị độ xám cộng 
//giá trị b trong phần tử cấu trúc B) lớn nhất làm giá trị độ xám cho pixel đó
//. Ngược lại phép co (erosion) độ xám thì chọn giá trị =( giá trị độ xám trừ đi
//giá trị (b) trong mảng cấu trúc B) nhỏ nhất
Mat GrayscaleDilation(Mat src, Mat B, std::pair<int, int> center);
Mat GrayscaleErosion(Mat src, Mat B, std::pair<int, int> center);
Mat GrayscaleOpening(Mat src, Mat B, std::pair<int, int> center);
Mat GrayscaleClosing(Mat src, Mat B, std::pair<int, int> center);


//Application of above operators

//toán tử làm trơn (ảnh độ xám)
Mat SmoothOperator(Mat src, Mat B, std::pair<int, int> center);

//toán tử trích biên (ảnh nhị phân)
Mat BinaryBoundaryExtraction(Mat src);

Mat MorphologyGradient(Mat src, Mat B, std::pair<int, int> center);

Mat topHat(Mat src, Mat B, std::pair<int, int> center);

Mat regionFilling(Mat src, std::pair<int, int> startingPoint);
Mat getSkeleton(Mat src);

//mặc định cho làm mảnh tối đa (loop -> infinity)
Mat ThinningTransform(Mat src, int maxLoop= 111111111);
Mat ThickeningTransform(Mat src);
Mat CreateStructureMat(int size, int val = 0);
Mat ConvexHull(Mat src);
#endif