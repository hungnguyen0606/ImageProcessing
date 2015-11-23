// OpenCVProject.cpp : Defines the entry point for the console application.
//


#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <math.h>

using namespace cv;
using namespace std;

#define DEFAULT_SRC		"face.jpg"
//Interface
void	customizeColor(Mat srcImg);
Mat		cvt2Linear(Mat srcImg);
Mat		cvt2NonLinear(Mat srcImg);
Mat		cvtEqualizeHist(Mat srcImg);

void	customizeGeometry(Mat srcImg);
Mat		scale(Mat srcImg);
Mat		rotate(Mat srcImg);

void	customizePreProcess(Mat srcImg);
Mat		smooth(Mat srcImg);
Mat		detectEdge(Mat srcImg);

//Implementation
void demoLib(Mat img){
	int selection = -1;
	cout << "CHON 1 TRONG 4 LUA CHON SAU:" << endl;
	cout << "   1 - Hieu chinh mau sac." << endl;
	cout << "   2 - Bien doi hinh hoc." << endl;
	cout << "   3 - Tien xu ly." << endl;
	cout << "   4 - Thoat." << endl;

	while (selection < 4)  {
		cout << "LUA CHON CHUNG: ";
		cin >> selection;

		switch (selection)  {
		case 1:
			customizeColor(img);
			break;
		case 2:
			customizeGeometry(img);
			break;
		case 3:
			customizePreProcess(img);
			break;
		}
		waitKey(0);
	}
}


void customizeColor(Mat srcImg)  {
//	Mat srcImg = imread(DEFAULT_SRC);
//	if (srcImg.empty())  {
//		cout << "Khong the tai anh len!" << endl;
//		return;
//	}

	int selection = -1;
	cout << "\nCHON 1 TRONG 3 LUA CHON SAU:" << endl;
	cout << "   1 - Chuyen mau theo Mo hinh Tuyen tinh." << endl;
	cout << "   2 - Chuyen mau theo Mo hinh Phi tuyen tinh." << endl;
	cout << "   3 - Chuyen mau theo Mo hinh Thong ke." << endl;
	cout << "LUA CHON TRONG 'HIEU CHINH MAU SAC': ";
	cin >> selection;

	switch (selection)  {
		case 1:  {
			Mat linearImg = cvt2Linear(srcImg);
			imshow("Anh goc", srcImg);
			imshow("Anh chuyen mau theo Mo hinh Tuyen tinh", linearImg);
			break;
		}
		case 2: {
			Mat nonLinearImg = cvt2NonLinear(srcImg);
			imshow("Anh goc", srcImg);
			imshow("Anh chuyen mau theo Mo hinh Phi tuyen tinh", nonLinearImg);
			break;
		}
		case 3:  {
			Mat equalHitsImg = cvtEqualizeHist(srcImg);
			imshow("Anh goc", srcImg);
			imshow("Anh chuyen mau theo Mo hinh Thong ke", equalHitsImg);
			break;
		}

	}
	waitKey(0);
}

Mat cvt2Linear(Mat srcImg)  {
	int alpha, beta;
	cout << "\nCHUYEN MAU THEO MO HINH TUYEN TINH" << endl;
	cout << "   - Nhap gia tri alpha: ";
	cin >> alpha;
	cout << "   - Nhap gia tri beta: ";
	cin >> beta;

	Mat res;
	srcImg.convertTo(res, -1, alpha, beta);
	return res;
}

Mat cvt2NonLinear(Mat srcImg)  {
	int choice, c;
	cout << "\nCHUYEN MAU THEO MO HINH PHI TUYEN TINH" << endl;
	cout << "Chon 1 trong 2 cach sau: " << endl;
	cout << "   1.Chuyen theo ham logarithm." << endl;
	cout << "   2.Chuyen theo ham mu." << endl;
	cout << "Lua chon: ";
	cin >> choice;

	switch (choice)  {
			case 1:  {
				cout << "   - Nhap gia tri c: ";
				cin >> c;
				Mat res = Mat::zeros(srcImg.size(), srcImg.type());
				srcImg.convertTo(srcImg, CV_32F);
				log(srcImg, res);
				res.mul(res, c);
				return res;
			}
			case 2:  {
				Mat res = Mat::zeros(srcImg.size(), srcImg.type());
				srcImg.convertTo(srcImg, CV_32F);
				exp(srcImg, res);
				return res;
			}
			default:
				return Mat();
	}
}

Mat cvtEqualizeHist(Mat srcImg)  {
	cout << "\nCHUYEN MAU THEO MO HINH THONG KE" << endl;
	if (srcImg.channels() >= 3)  {
		Mat ycrcbImg;
		// Chuyen anh sang dang YCbCr
		cvtColor(srcImg, ycrcbImg, CV_BGR2YCrCb);

		// Tach cac kenh ra
		vector<Mat> channels;
		split(ycrcbImg, channels);

		// Thuc hien phep bien doi tren tung kenh
		for (int i = 0; i < 3; ++i)
			equalizeHist(channels[i], channels[i]);

		// Gop cac kenh lai
		Mat result;
		merge(channels, ycrcbImg);

		// Chuyen anh ve dang RGB
		cvtColor(ycrcbImg, result, CV_YCrCb2BGR);

		return result;
	}
	return Mat();
}


void customizeGeometry(Mat srcImg)  {
//	Mat srcImg = imread(DEFAULT_SRC);
//	if (srcImg.empty())  {
//		cout << "Khong the tai anh len!" << endl;
//		return;
//	}

	int selection = -1;
	cout << "\nCHON 1 TRONG 2 LUA CHON SAU:" << endl;
	cout << "   1 - Phep co gian." << endl;
	cout << "   2 - Phep xoay." << endl;
	cout << "LUA CHON TRONG 'BIEN DOI HINH HOC': ";
	cin >> selection;

	switch (selection)  {
		case 1:  {
			Mat scaleImg = scale(srcImg);
			imshow("Anh goc", srcImg);
			imshow("Anh bien doi hinh hoc theo Phep Co gian", scaleImg);
			break;
		}
		case 2: {
			Mat rotateImg = rotate(srcImg);
			imshow("Anh goc", srcImg);
			imshow("Anh bien doi hinh hoc theo Phep Xoay", rotateImg);
			break;
		}
	}
	waitKey(0);
}

Mat	scale(Mat srcImg)  {
	int type, choice, method;
	cout << "\nBIEN DOI ANH THEO PHEP CO GIAN" << endl;

	cout << "Chon lua chon sau:" << endl;
	cout << "   1. Phong to." << endl;
	cout << "   2. Thu nho." << endl;
	cout << "Lua chon: ";
	cin >> type;

	cout << "\nChon tiep cac lua chon sau:" << endl;
	cout << "   1. Theo chieu doc." << endl;
	cout << "   2. Theo chieu ngang." << endl;
	cout << "   3. Ca hai chieu." << endl;
	cout << "Lua chon: ";
	cin >> choice;

	cout << "\nChon phuong thuc thuc hien:" << endl;
	cout << "   1. Song tuyen tinh." << endl;
	cout << "   2. Lan can gan nhat." << endl;
	cout << "Lua chon: ";
	cin >> method;

	switch (method)  {
		case 1:
			method = CV_INTER_LINEAR;
			break;
		case 2:
			method = CV_INTER_NN;
			break;
		default:
			method = CV_INTER_NN;
			break;
	}

	int fx = 1;
	int fy = 1;
	switch (choice)  {
		case 1:
			cout << "\nNhap gia tri bien doi chieu ngang (so nguyen): ";
			cin >> fx;
			break;
		case 2:
			cout << "\nNhap gia tri bien doi chieu doc (so nguyen): ";
			cin >> fy;
			break;
		case 3:
			cout << "\nNhap gia tri bien doi chieu ngang ca hai chieu (so nguyen): ";
			cin >> fx;
			fy = fx;
			break;
		default:
			break;
	}

	Mat res;
	switch (type)  {
		case 1:  {
			res = Mat::zeros(srcImg.rows*fx, srcImg.cols*fy, srcImg.type());
			break;
		}
		case 2:  {
			res = Mat::zeros(srcImg.rows/fx, srcImg.cols/fy, srcImg.type());
			break;
		}
		default:  {
			cout << "\nNhap thong tin sai! Anh chua qua bien doi!" << endl;
			return Mat();
		}
	}

	resize(srcImg, res, res.size(), 0, 0, method);
	return res;
}

Mat	rotate(Mat srcImg)  {
	int choice, angle;
	cout << "\nBIEN DOI ANH THEO PHEP XOAY" << endl;

	cout << "Nhap so do muon xoay (so nguyen duong - nguoc chieu kim dong ho): ";
	cin >> angle;

	Point2f center = Point(srcImg.rows / 2, srcImg.cols / 2);
	Mat res = Mat::zeros(srcImg.size(), srcImg.type());
	Mat rot = getRotationMatrix2D(center, angle, 1.0);
	warpAffine(srcImg, res, rot, Size(srcImg.cols, srcImg.rows));
	return res;
}


void customizePreProcess(Mat srcImg)  {
//	Mat srcImg = imread(DEFAULT_SRC);
//	if (srcImg.empty())  {
//		cout << "Khong the tai anh len!" << endl;
//		return;
//	}

	int selection = -1;
	cout << "\nCHON 1 TRONG 2 LUA CHON SAU:" << endl;
	cout << "   1 - Lam tron anh." << endl;
	cout << "   2 - Phat hien bien canh." << endl;
	cout << "LUA CHON TRONG 'TIEN XU LY': ";
	cin >> selection;

	switch (selection)  {
	case 1:  {
				 Mat smoothImg = smooth(srcImg);
				 imshow("Anh goc", srcImg);
				 imshow("Anh da duoc lam tron", smoothImg);
				 break;
	}
	case 2: {
				Mat detectEdgeImg = detectEdge(srcImg);
				imshow("Anh goc", srcImg);
				imshow("Bien canh cua anh", detectEdgeImg);
				break;
	}
	}
	waitKey(0);
}

Mat	smooth(Mat srcImg)  {
	int choice;
	cout << "\nTIEN XU LY ANH - LAM TRON" << endl;
	cout << "Chon mot trong cac toan tu sau:" << endl;
	cout << "   1. Toan tu Trung binh." << endl;
	cout << "   2. Toan tu Gauss." << endl;
	cout << "   3. Toan tu Trung vi." << endl;
	cout << "Lua chon: ";
	cin >> choice;


	int MAX_KERNEL_LENGTH = 31;
	Mat res = srcImg.clone();

	switch (choice)  {
		case 1:
			for (int i = 1; i < MAX_KERNEL_LENGTH; i = i + 2)
				blur(srcImg, res, Size(i, i), Point(-1, -1));
			break;

		case 2:
			for (int i = 1; i < MAX_KERNEL_LENGTH; i = i + 2)
				GaussianBlur(srcImg, res, Size(i, i), 0, 0);
			break;

		case 3:
			for (int i = 1; i < MAX_KERNEL_LENGTH; i = i + 2)
				medianBlur(srcImg, res, i);
			break;

		default:
			return Mat();
	}

	return res;
}

Mat	detectEdge(Mat srcImg)  {
	int choice;
	cout << "\nTIEN XU LY ANH - PHAT HIEN BIEN CANH" << endl;
	cout << "Chon mot trong cac lua chon sau:" << endl;
	cout << "   1. Toan tu Gradient - Sobel." << endl;
	cout << "   2. PP Canny." << endl;
	//cout << "   3. Toan tu Trung vi." << endl;
	cout << "Lua chon: ";
	cin >> choice;

	Mat srcGrayImg;
	Mat res;

	// Chuyen sang anh do xam
	cvtColor(srcImg, srcGrayImg, CV_RGB2GRAY);
	switch (choice)  {
		case 1:  {
			int scale = 1;
			int delta = 0;
			int ddepth = CV_16S;
			Mat gradX, gradY;
			Mat absGradX, absGradY;

			// Khu nhieu
			GaussianBlur(srcImg, srcImg, Size(3, 3), 0, 0, BORDER_DEFAULT);

			/// Gradient X
			Sobel(srcGrayImg, gradX, ddepth, 1, 0, 3, scale, delta, BORDER_DEFAULT);
			convertScaleAbs(gradX, absGradX);

			/// Gradient Y
			Sobel(srcGrayImg, gradY, ddepth, 0, 1, 3, scale, delta, BORDER_DEFAULT);
			convertScaleAbs(gradY, absGradY);

			addWeighted(absGradX, 0.5, absGradY, 0.5, 0, res);

			return res;
		}

		case 2:  {
					 int edgeThresh = 1;
					 int lowThreshold = 0;
					 int const max_lowThreshold = 100;
					 int ratio = 3;
					 int kernel_size = 3;
					 Mat detected_edges;

					 res = srcImg.clone();
					 blur(srcGrayImg, detected_edges, Size(3, 3));
					 Canny(srcImg, detected_edges, lowThreshold, lowThreshold*ratio, kernel_size);
					 res = Scalar::all(0);
					 srcImg.copyTo(res, detected_edges);

					 return res;
		}
		default:
			return Mat();
	}
}


