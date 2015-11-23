// OpenCVProject.cpp : Defines the entry point for the console application.
//

#include "header.h"
#include "MyFunc.h"

using namespace cv;
using namespace std;

#define DEFAULT_SRC		"face.jpg"
//Interface
void    viewImage(Mat img);
void    viewImageVideo(Mat img, VideoCapture *video);

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


Mat     inputImage()
{
	Mat img = imread("Image/maru.jpg");
//    Mat img = imread("Image/rgb.vn_cmyk-rgb.jpg");
//    Mat img = imread("Image/benthanh.png");
//    Mat img = imread("Image/lena.jpg");
//    Mat blackimg = Mat(img.size().height, img.size().width, CV_8UC3, Scalar(0, 0, 0));
//    Mat img = imread("Image/white.png");
//    Mat img = imread("Image/maru.jpg");

    return img;
}

VideoCapture    inputVideo()
{
    char inputPath[] = "MARU.MP4";
    cout << string(inputPath);
    VideoCapture  video;
    video.open(inputPath);
    return video;
}

//Implementation
int     main(){
    Mat img = inputImage();
    VideoCapture video = inputVideo();

	int selection = -1;
	cout << "CHON 1 TRONG 4 LUA CHON SAU:" << endl;
	cout << "   1 - Hien thi anh - video." << endl;
	cout << "   2 - Hieu chinh mau sac." << endl;
	cout << "   3 - Bien doi hinh hoc." << endl;
	cout << "   4 - Tien xu ly." << endl;
	cout << "   5 - Thoat." << endl;

	while (selection < 5)  {
		cout << "LUA CHON CHUNG: ";
		cin >> selection;

		switch (selection)  {
            case 1:
                viewImageVideo(img, &video);
                break;
            case 2:
                customizeColor(img);
                break;
            case 3:
                customizeGeometry(img);
                break;
            case 4:
                customizePreProcess(img);
                break;
            default: break;
		}
		destroyAllWindows();
		waitKey(0);
        cout << endl;
	}
	return 0;
}
void    viewImageVideo(Mat img, VideoCapture *video)
{
    cout << "\nCHON 1 TRONG 2 LUA CHON SAU:" << endl;
    cout << "  1 - Hien thi anh\n";
    cout << "  2 - Hien thi video\n";
    cout << "  Lua chon: ";
    int choose;
    cin >> choose;
    switch(choose)
    {
        case 1: viewImage(img); break;
        case 2: myfunc_viewVideo(video); break;
        default: break;
    }
}

void    viewImage(Mat img)
{
    cout << "\nCHON 1 TRONG 3 LUA CHON SAU:" << endl;
    cout << "  1 - Hien thi anh mau.\n";
    cout << "  2 - Hien thi anh do sau.\n";
    cout << "  3 - Kiem tra Chuyen doi RGB thanh HSV va nguoc lai.\n";
    cout << "  4 - Kiem tra Chuyen doi RGB thanh LUV va nguoc lai.\n";
    cout << "  5 - Kiem tra Chuyen doi RGB thanh Lab va nguoc lai.\n";
    cout << "  6 - Kiem tra Chuyen doi RGB thanh YCbCr va nguoc lai.\n";
    cout << "  Lua chon: ";
    int choose;
    cin >> choose;
    Mat res;
    switch(choose)
    {
        case 1: imshow("Color Image", img); break;
        case 2: myfunc_ViewDepthImage(img); break;
        case 3: myfunc_RGB2HSV(img), myfunc_HSV2RGB(img);
                cvtColor(img, res, CV_BGR2HSV);
                cvtColor(res, res, CV_HSV2BGR);
                imshow("Library: RGB2HSV and HSV2RGB", res);
                break;
        case 4: myfunc_RGB2LUV(img), myfunc_LUV2RGB(img);
                cvtColor(img, res, CV_BGR2Luv);
                cvtColor(res, res, CV_Luv2BGR);
				imshow("Library: RGB2LUV and LUV2RGB", res);
                break;
        case 5: myfunc_RGB2Lab(img), myfunc_Lab2RGB(img);
                cvtColor(img, res, CV_BGR2Lab);
                cvtColor(res, res, CV_Lab2BGR);
				imshow("Library: RGB2LAB and LAB2RGB", res);
                break;
        case 6: myfunc_RGB2YCbCr(img), myfunc_YCbCr2RGB(img);
                cvtColor(img, res, CV_BGR2YCrCb);
				cvtColor(res, res, CV_YCrCb2BGR);
					imshow("Library: RGB2YCrCb and HSV2YCrCb", res);;
                break;
        default: break;
    }
    waitKey(0);
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
			imshow("Original Image", srcImg);
			imshow("Library: Linear Change", linearImg);
			break;
		}
		case 2: {
			Mat nonLinearImg = cvt2NonLinear(srcImg);
			imshow("Original Image", srcImg);
			imshow("Library: Non Linear Change", nonLinearImg);
			break;
		}
		case 3:  {
			Mat equalHitsImg = cvtEqualizeHist(srcImg);
			imshow("Original Image", srcImg);
			imshow("Library: Histogram Equalization", equalHitsImg);
			myfunc_HistogramEqualization(srcImg);
			break;
		}

	}
	waitKey(0);
}

Mat cvt2Linear(Mat srcImg)  {
	double alpha;
	int beta;
	cout << "\nCHUYEN MAU THEO MO HINH TUYEN TINH" << endl;
	cout << "   - Nhap gia tri alpha: ";
	cin >> alpha;
	cout << "   - Nhap gia tri beta: ";
	cin >> beta;

    waitKey();

    Mat img = srcImg.clone();
    myfunc_linearChange(img, alpha, beta);

	Mat res;
	srcImg.convertTo(res, -1, alpha, beta);
	return res;
}

Mat cvt2NonLinear(Mat srcImg)  {
	int choice;
	double c;
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
		myfunc_nonLinearChange_Log(srcImg, c);
		// Tạo ảnh kết quả (res) có kích thước và kiểu giống ảnh gốc (srcImg) nhưng các giá trị = 0
		Mat res = Mat::zeros(srcImg.size(), srcImg.type());
		// + 1 để tránh log(0)
		srcImg = srcImg + 1;
		// Chuyển định dạng pixel của ảnh gốc (srcImg) thành CV_32F - dạng float để tính logarithm
		srcImg.convertTo(srcImg, CV_32F);
		// Ảnh kết quả = log(Ảnh gốc)
		log(srcImg, res);
		// Chuyển về [0..255]
		normalize(res, res, 0, 255, NORM_MINMAX);
		convertScaleAbs(res, res);
		// Ảnh kết quả = Ảnh kết quả * c
		res.mul(res, c);
		return res;
	}
	case 2:  {
		cout << "   - Nhap gia tri c: ";
		cin >> c;
		myfunc_nonLinearChange_Exp(srcImg, c);
		// Tạo ảnh kết quả (res) có kích thước và kiểu giống ảnh gốc (srcImg) nhưng các giá trị = 0
		Mat res = Mat::zeros(srcImg.size(), srcImg.type());
		// Chuyển định dạng pixel của ảnh gốc (srcImg) thành CV_32F - dạng float để tính logarithm
		srcImg.convertTo(srcImg, CV_32F);
		// Ảnh kết quả = e ^ (Ảnh gốc)
		exp(srcImg, res);
		res.mul(c);
		return res;
	}

			default:
				return Mat();
	}
}

Mat cvtEqualizeHist(Mat srcImg)  {
	cout << "\nCHUYEN MAU THEO MO HINH THONG KE" << endl;
	if (srcImg.channels() >= 3)  {
		Mat hsvImg;
		// Chuyen anh sang dang YCbCr
		cvtColor(srcImg, hsvImg, CV_BGR2HSV);

		// Tach cac kenh ra
		vector<Mat> channels;
		split(hsvImg, channels);

		// Thuc hien phep bien doi tren kenh V
		equalizeHist(channels[2], channels[2]);

		// Gop cac kenh lai
		merge(channels, hsvImg);

		// Chuyen anh ve dang RGB
		Mat result;
		cvtColor(hsvImg, result, CV_HSV2BGR);

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
			imshow("Original Image", srcImg);
			imshow("Library: Zoom Image", scaleImg);
			break;
		}
		case 2: {
			Mat rotateImg = rotate(srcImg);
			imshow("Original Image", srcImg);
			imshow("Library: Rotate Image", rotateImg);
		
			break;
		}
	}
	waitKey(0);
}

Mat	scale(Mat srcImg)  {
	int type, choice, method;
	double fx, fy;
	cout << "\nBIEN DOI ANH THEO PHEP CO GIAN" << endl;

    cout << "\nNhap he so chieu ngang: ";
    cin >> fx;
    cout << "\nNhap he so chieu doc: ";
    cin >> fy;

//	cout << "\nChon phuong thuc thuc hien:" << endl;
//	cout << "   1. Song tuyen tinh." << endl;
//	cout << "   2. Lan can gan nhat." << endl;
//	cout << "Lua chon: ";
//	cin >> type;

//	switch (type)  {
//		case 1:
//			method = CV_INTER_LINEAR;
//			break;
//		case 2:
//			method = CV_INTER_NN;
//			break;
//		default:
//			method = CV_INTER_NN;
//			break;
//	}
    type = 1;
    method = CV_INTER_NN;

	Mat res;

    res = Mat::zeros(int(srcImg.rows*fy), int(srcImg.cols*fx), srcImg.type());
	resize(srcImg, res, res.size(), 0, 0, method);
    myfunc_Zoom(srcImg, fx, fy, type);
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
	myfunc_Rotate(srcImg, angle);
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
				 imshow("Original Image", srcImg);
				 imshow("Library: Smooth Image", smoothImg);
				 break;
	}
	case 2: {
		Mat detectEdgeImg = detectEdge(srcImg);
		imshow("Original Image", srcImg);
		if (detectEdgeImg.size().height != 0)
		{
			imshow("Library: Edge Detected", detectEdgeImg);
			
		}
			
		break;
	}
	}
	waitKey(0);
}

Mat	smooth(Mat srcImg)  {
	int choice;
	int kernelsize;
	cout << "\nTIEN XU LY ANH - LAM TRON" << endl;
	cout << "Chon mot trong cac toan tu sau:" << endl;
	cout << "   1. Toan tu Trung binh." << endl;
	cout << "   2. Toan tu Gauss." << endl;
	cout << "   3. Toan tu Trung vi." << endl;
	cout << "Lua chon: ";
	cin >> choice;

    cout << "\nChon k cho kich thuoc Kernel (Kich thuoc Kernel la 2 * k + 1): ";
    cin >> kernelsize;
    kernelsize = kernelsize * 2 + 1;
	Mat res = srcImg.clone();

	switch (choice)  {
		case 1:
            blur(srcImg, res, Size(kernelsize, kernelsize), Point(-1, -1));
            myfunc_Mean(srcImg, kernelsize);
			break;

		case 2:
			double sigma;
			cout << "   4. Nhap he so sigma cho Gauss: ";
			cin >> sigma;
			GaussianBlur(srcImg, res, Size(kernelsize, kernelsize), sigma, 0);
			myfunc_Gauss(srcImg, kernelsize, sigma);
			break;
		

		case 3:
			medianBlur(srcImg, res, kernelsize);
			myfunc_Median(srcImg, kernelsize);
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
	cout << "   1. Toan tu Gradient - Prewitt." << endl;
	cout << "   2. Toan tu Gradient - Sobel. " << endl;
	cout << "   3. Toan Tu Gradient - Freichen." << endl;
	cout << "   4. PP Canny." << endl;
	cout << "Lua chon: ";
	cin >> choice;

	Mat srcGrayImg;
	Mat res;

	// Chuyen sang anh do xam
	cvtColor(srcImg, srcGrayImg, CV_RGB2GRAY);
	switch (choice)  {
	case 2:  {
		int kernelsize = 3;
		int scale = 1;
		int delta = 0;
		int ddepth = CV_16S;
		Mat gradX, gradY;
		Mat absGradX, absGradY;

		//			// Khu nhieu
		//			GaussianBlur(srcImg, srcImg, Size(kernelsize, kernelsize), 0, 0, BORDER_DEFAULT);

		//sobel tu cai dat
		myfunc_Sobel(srcGrayImg, kernelsize);

		// Gradient X

		Sobel(srcGrayImg, gradX, ddepth, 1, 0, kernelsize, scale, delta, BORDER_DEFAULT);
		convertScaleAbs(gradX, absGradX);

		// Gradient Y
		Sobel(srcGrayImg, gradY, ddepth, 0, 1, kernelsize, scale, delta, BORDER_DEFAULT);
		convertScaleAbs(gradY, absGradY);

		addWeighted(absGradX, 0.5, absGradY, 0.5, 0, res);

		return res;
	}
	case 1:
	{
		int kernelsize = 3;
		GaussianBlur(srcImg, srcImg, Size(kernelsize, kernelsize), 0, 0, BORDER_DEFAULT);
		myfunc_Prewitt(srcGrayImg, kernelsize);
		return Mat();
	}
	case 3:
	{
		int kernelsize = 3;
		GaussianBlur(srcImg, srcImg, Size(kernelsize, kernelsize), 0, 0, BORDER_DEFAULT);
		myfunc_FreiChen(srcGrayImg);
		return Mat();
	}
	case 4:  {
		int edgeThresh = 1;
		int lowThreshold = 50;
		int const max_lowThreshold = 100;
		int ratio = 2;
		int kernelsize = 3;
		Mat detected_edges;

		res = srcImg.clone();
		blur(srcGrayImg, detected_edges, Size(kernelsize, kernelsize));
		Canny(srcImg, detected_edges, lowThreshold, lowThreshold*ratio, kernelsize);
		res = Scalar::all(0);
		srcImg.copyTo(res, detected_edges);

		Mat temp = srcImg.clone();
		myfunc_Canny(temp);
		return res;
	}
	default:
		return Mat();
	}
}
