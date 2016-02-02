#include "DemoMorphology.h"

const int binaryThreshold = 100;

Mat toBinary(Mat src, int threshold)
{
	Mat ret; 
	cv::threshold(src, ret, threshold, 255, cv::THRESH_BINARY);

	return ret;
}

void demoBinaryDilation()
{
	Mat img = imread("Image/devil.png", CV_LOAD_IMAGE_GRAYSCALE);
	img = toBinary(img, binaryThreshold);
	imshow("Origin", img);
	imshow("Binary Dilation", BinaryDilation(img, CreateStructureMat(3, 1), std::make_pair(1, 1)));
	waitKey(0);
}

void demoBinaryErosion()
{
	Mat img = imread("Image/devil.png", CV_LOAD_IMAGE_GRAYSCALE);
	img = toBinary(img, binaryThreshold);
	imshow("Origin", img);
	imshow("Binary Erosion", BinaryErosion(img, CreateStructureMat(3, 1), std::make_pair(1, 1)));
	waitKey(0);
}

void demoBinaryOpening()
{
	Mat img = imread("Image/devil.png", CV_LOAD_IMAGE_GRAYSCALE);
	img = toBinary(img, binaryThreshold);
	imshow("Origin", img);
	imshow("Binary Opening", BinaryOpening(img, CreateStructureMat(3, 1), std::make_pair(1, 1)));
	waitKey(0);
}

void demoBinaryClosing()
{
	Mat img = imread("Image/devil.png", CV_LOAD_IMAGE_GRAYSCALE);
	img = toBinary(img, binaryThreshold);
	imshow("Origin", img);
	imshow("Binary Closing", BinaryClosing(img, CreateStructureMat(3, 1), std::make_pair(1, 1)));
	waitKey(0);
}


void demoFillingRegion()
{
	Mat img = imread("Image/labyrinth.png", CV_LOAD_IMAGE_GRAYSCALE);
	img = toBinary(img, 100);
	imshow("Origin", img);
	imshow("Filling", regionFilling(img, std::make_pair(70, 70)));
	cout << img.size().height << ' ' << img.size().width << endl;
	waitKey(0);
}

void demoSkeleton()
{
	Mat img = imread("Image/snowflake.png", CV_LOAD_IMAGE_GRAYSCALE);
	img = toBinary(img, 100);
	//bitwise_not(img, img);

	imshow("Origin", img);
	imshow("skeleton", getSkeleton(img));
	waitKey(0);
}


void demoThinning()
{
	Mat img = imread("Image/horse2.png", CV_LOAD_IMAGE_GRAYSCALE);
	img = toBinary(img, 100);
	bitwise_not(img, img);

	imshow("Origin", img);
	imshow("Thinning", ThinningTransform(img));
	waitKey(0);
}

void demoThickening()
{
	Mat img = imread("Image/horse2.png", CV_LOAD_IMAGE_GRAYSCALE);
	img = toBinary(img, 50);
	bitwise_not(img, img);

	imshow("Origin", img);
	imshow("Thickening", ThickeningTransform(img));
	waitKey(0);
}
void demoConvexHull()
{
	Mat img = imread("Image/snowflake.png", CV_LOAD_IMAGE_GRAYSCALE);
	img = toBinary(img, 100);
	//bitwise_not(img, img);

	imshow("Origin", img);
	imshow("Convex hull", ConvexHull(img));
	waitKey(0);
}

void demoGrayscaleDilation()
{
	Mat img = imread("Image/horse.png", CV_LOAD_IMAGE_GRAYSCALE);
	imshow("Origin", img);
	imshow("Grayscale Dilation", GrayscaleDilation(img, CreateStructureMat(11, 10), std::make_pair(5, 5)));
	waitKey(0);
}
void demoGrayscaleErosion()
{
	Mat img = imread("Image/horse.png", CV_LOAD_IMAGE_GRAYSCALE);
	imshow("Origin", img);
	imshow("Grayscale Erosion", GrayscaleErosion(img, CreateStructureMat(5, 10), std::make_pair(2, 2)));
	waitKey(0);
}
void demoGrayscaleOpening()
{
	Mat img = imread("Image/horse.png", CV_LOAD_IMAGE_GRAYSCALE);
	imshow("Origin", img);
	imshow("Grayscale Opening", GrayscaleOpening(img, CreateStructureMat(13, 10), std::make_pair(6, 6)));
	waitKey(0);
}
void demoGrayscaleClosing()
{
	Mat img = imread("Image/horse.png", CV_LOAD_IMAGE_GRAYSCALE);
	imshow("Origin", img);
	imshow("Grayscale Closing", GrayscaleClosing(img, CreateStructureMat(13, 20), std::make_pair(6, 6)));
	waitKey(0);
}

void demoMorphologyGradient()
{
	Mat img = imread("Image/horse.png", CV_LOAD_IMAGE_GRAYSCALE);
	imshow("Origin", img);
	imshow("Morphology Gradient", MorphologyGradient(img, CreateStructureMat(5, 30), std::make_pair(2, 2)));
	waitKey(0);
}

void demoBinaryBoundaryExtraction()
{

	Mat img = imread("Image/devil.png", CV_LOAD_IMAGE_GRAYSCALE);
	cv::threshold(img, img, binaryThreshold, 255, cv::THRESH_BINARY);

	imshow("Binary Image", img);
	imshow("Boundary", BinaryBoundaryExtraction(img));
	waitKey(0);
}

void demoTopHat()
{
	Mat img = imread("Image/pill.png", CV_LOAD_IMAGE_GRAYSCALE);
	imshow("Origin", img);
	imshow("Top hat", 2 * topHat(img, CreateStructureMat(51, 0), std::make_pair(25, 25)));
	waitKey(0);
}

void demoSmoothingOperation()
{
	Mat img = imread("Image/horse.png", CV_LOAD_IMAGE_GRAYSCALE);
	imshow("Origin", img);
	imshow("Smoothing  operation", SmoothOperator(img, CreateStructureMat(11, 0), std::make_pair(5, 5)));
	waitKey(0);
}