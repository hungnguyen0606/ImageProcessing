#include "Morphology.h"

using namespace std;
#include <algorithm>
#include <utility>
#include <functional>
char hit[][25] = { "000000100110111011001000", 
				   "010110110110010011011011",
				   "111110100000000000001011"};
char miss[][25] = { "111011001000000000100110",
				   "000001001001000100100100",
				   "000000001011111110100000" };
Mat CreateStructureMat(int size, int val)
{
	Mat kernel = Mat(size, size, CV_8UC1, Scalar_<uint8_t>(0));
	for (int i = 0; i < size; ++i)
		for (int j = 0; j < size; ++j)
			kernel.at<uint8_t>(i, j) = val;
	return kernel;
}

//Lấy ảnh giá trị tuyệt đối hiệu độ xám 2 ảnh
Mat getDifference(Mat im1, Mat im2)
{
	Mat ret = im1.clone();
	for (int i = 0; i < im1.size().height; ++i)
		for (int j = 0; j < im1.size().width; ++j)
		{
			int temp = abs(im1.at<uint8_t>(i, j) - im2.at<uint8_t>(i, j));
			temp = max(min(temp, 255), 0);
			ret.at<uint8_t>(i, j) = temp;
		}
	return ret;
}
Mat BinaryDilation(Mat src, Mat B, pair<int, int> center)
{
	Mat ret;
	
	ret = src.clone();
	int n = ret.size().height;
	int m = ret.size().width;
	
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < m; ++j)
		{
			//int gg = src.at<uint8_t>(i, j);
			//if (src.at<uint8_t>(i, j) < 255)
			{
				ret.at<uint8_t>(i, j) = 255;
				bool ok = false;
				for (int u = 0; u < B.size().height; ++u)
				{
					for (int v = 0; v < B.size().width; ++v)
						if (B.at<uint8_t>(u, v) != 0)
						{
							int newx = i - (u - center.first);
							int newy = j - (v - center.second);
							if (newx >= 0 && newy >= 0 && newx < n && newy < m && src.at<uint8_t>(newx, newy) < 255)
							{
								ret.at<uint8_t>(i, j) = 0;
								ok = true;
								break;
							}

						}
					if (ok)
						break;
				}
					
			}
		}
			


	return ret;
}

Mat BinaryErosion(Mat src, Mat B, pair<int, int> center)
{
	Mat ret;

	ret = src.clone();
	int n = ret.size().height;
	int m = ret.size().width;
	//ret = Mat(n, m, CV_8UC1, Scalar_<uint8_t>(255));
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < m; ++j)
			//if (src.at<uint8_t>(i, j) > 0)
			{
				bool ok = false;
				ret.at<uint8_t>(i, j) = 0;
				for (int u = 0; u < B.size().height; ++u)
				{
					for (int v = 0; v < B.size().width; ++v)
						if (B.at<uint8_t>(u, v) > 0)
						{
							int newx = u - center.first + i;
							int newy = v - center.second + j;
							if (newx >= 0 && newy >= 0 && newx < n && newy < m)
								if (src.at<uint8_t>(newx, newy) == 255)
									ok = true;
								else;
							else
								ok = true;//xóa các điểm ở biên

							if (ok)
								break;
						}
					if (ok)
						break;
				}
				if (ok)
					ret.at<uint8_t>(i, j) = 255;

			}


	return ret;
}

Mat BinaryOpening(Mat src, Mat B, std::pair<int, int> center)
{
	return BinaryDilation(BinaryErosion(src, B, center), B, center);
}
Mat BinaryClosing(Mat src, Mat B, std::pair<int, int> center)
{
	return BinaryErosion(BinaryDilation(src, B, center), B, center);
}

Mat GrayscaleDilation(Mat src, Mat B, std::pair<int, int> center)
{
	Mat ret = src.clone();
	int n = ret.size().height;
	int m = ret.size().width;

	for (int i = 0; i < n; ++i)
		for (int j = 0; j < m; ++j)
		{
			int res = -infinity;
			for (int u = 0; u < B.size().height; ++u)
				for (int v = 0; v < B.size().width; ++v)
				{
					int newx = i - (u - center.first);
					int newy = j - (v - center.second);
					
					if (newx >= 0 && newy >= 0 && newx < n && newy < m)
					{
						res = max(res, int(src.at<uint8_t>(newx, newy)) + B.at<uint8_t>(u, v));
					}
				}
			ret.at<uint8_t>(i, j) = max(min(res, 255), 0);
		}
	return ret;
}

Mat GrayscaleErosion(Mat src, Mat B, std::pair<int, int> center)
{
	Mat ret = src.clone();
	int n = ret.size().height;
	int m = ret.size().width;

	for (int i = 0; i < n; ++i)
		for (int j = 0; j < m; ++j)
		{
			int res = infinity;
			for (int u = 0; u < B.size().height; ++u)
				for (int v = 0; v < B.size().width; ++v)
				{
					int newx = i + u - center.first;
					int newy = j + v - center.second;

					if (newx >= 0 && newy >= 0 && newx < n && newy < m)
					{
						res = min(res, int(src.at<uint8_t>(newx, newy)) - B.at<uint8_t>(u, v));
					}
				}
			ret.at<uint8_t>(i, j) = max(min(res, 255), 0);
		}
	return ret;
}
Mat GrayscaleOpening(Mat src, Mat B, std::pair<int, int> center)
{
	return GrayscaleDilation(GrayscaleErosion(src, B, center), B, center);
}
Mat GrayscaleClosing(Mat src, Mat B, std::pair<int, int> center)
{
	return GrayscaleErosion(GrayscaleDilation(src, B, center), B, center);
}


Mat SmoothOperator(Mat src, Mat B, std::pair<int, int> center)
{
	return GrayscaleClosing(GrayscaleOpening(src, B, center), B, center);
}

Mat MorphologyGradient(Mat src, Mat B, std::pair<int, int> center)
{
	Mat t1 = GrayscaleDilation(src, B, center);
	Mat t2 = GrayscaleErosion(src, B, center);
	/*Mat ret = src.clone();
	for (int i = 0; i < t1.size().height; ++i)
		for (int j = 0; j < t1.size().width; ++j)
		{
			int temp = abs(t1.at<uint8_t>(i, j) - t2.at<uint8_t>(i, j));
			temp = max(min(temp, 255), 0);
			ret.at<uint8_t>(i, j) = temp;
		}*/
	return getDifference(t1,t2);
	//return GrayscaleDilation(src, B, center) - GrayscaleErosion(src, B, center);
}


Mat BinaryBoundaryExtraction(Mat src)
{
	Mat B = CreateStructureMat(3,1);
	pair<int, int> center(1, 1);
	return BinaryErosion(src, B, center) - src;

}

Mat topHat(Mat src, Mat B, std::pair<int, int> center)
{
	return getDifference(src, GrayscaleOpening(src, B, center));
}

//binary intersection
//rút các điểm chung có giá trị 0 (màu đen)
Mat getIntersection(Mat a, Mat b)
{
	Mat x, y;
	
	bitwise_not(a, x);
	bitwise_not(b, y);
	bitwise_and(x, y, x);
	bitwise_not(x, x);

	return x;

}

Mat regionFilling(Mat src, std::pair<int, int> startingPoint)
{
	int n = src.size().height;
	int m = src.size().width;
	Mat X(src.size(), CV_8UC1, cv::Scalar(255));
	Mat ret = src.clone();

	X.at<uint8_t>(startingPoint.first, startingPoint.second) = 0;

	Mat comp = 255 - src;
	
	Mat B = CreateStructureMat(3, 1);
	pair<int, int> center = make_pair(1, 1);

	while (true)
	{
		
		Mat Y = getIntersection(BinaryDilation(X, B, center),comp);

		Mat diff = X != Y;
		X = Y;
		
		if (countNonZero(diff) == 0)//two matrixs equal.
			break;
			
		
	}

	for (int i = 0; i < n; ++i)
		for (int j = 0; j < m; ++j)
			if (X.at<uint8_t>(i, j) == 0)
				ret.at<uint8_t>(i, j) = 0;
	return ret;
	
}

Mat getSkeleton(Mat src)
{
	
	int ss = src.size().height*src.size().width;
	
	Mat img = src.clone();
	Mat skel(src.size(), CV_8UC1, cv::Scalar(0));
	Mat temp, eroded;

	
	//tùy theo hàm cấu trúc mà sẽ rút trích được cấu trúc ảnh khác nhau
	Mat B = CreateStructureMat(3, 1);
	B.at<uint8_t>(0, 0) = 0;
	B.at<uint8_t>(2, 2) = 0;
	B.at<uint8_t>(0, 2) = 0;
	B.at<uint8_t>(2, 0) = 0;

	bool isEnded;
	int cc = 300;
	pair<int, int> center = make_pair(1, 1);
	do{
		
		eroded = BinaryErosion(img, B, center);
		temp = BinaryDilation(eroded, B, center);
		cv::subtract(temp, img, temp);

		//tổng hợp cấu trúc ảnh
		cv::bitwise_or(skel, temp, skel);

		eroded.copyTo(img);

		//dừng lại nếu ảnh đã bị co hoàn toàn (số pixel đen = 0)/(pixel trăng = kích thước ảnh)
		isEnded = (cv::countNonZero(img) == ss);
	} while (!isEnded);
	

	return skel;
}

Mat HitMissTransform(Mat src, Mat C, Mat D, std::pair<int,int> center)
{
	Mat comp = src.clone();
	bitwise_not(comp, comp);

	return getIntersection(BinaryErosion(src, C, center), BinaryErosion(comp, D, center));
}

Mat ThinningTransform(Mat src, int maxLoop)
{
	Mat baseHit = CreateStructureMat(3, 0);
	Mat baseMiss = CreateStructureMat(3, 0);
	vector<Mat> bHit, bMiss;
	for (int i = 0; i < 8; ++i)
	{
		int baseIndex = i * 3;
		for (int u = 0; u < 3; ++u)
			for (int v = 0; v < 3; ++v)
			{
				baseHit.at<uint8_t>(u, v) = hit[u][baseIndex + v] - '0';
				baseMiss.at<uint8_t>(u, v) = miss[u][baseIndex + v] - '0';
			}
		bHit.push_back(baseHit.clone());
		bMiss.push_back(baseMiss.clone());
	}
	Mat ret;
	Mat Xn = src.clone();
	Mat Y(src.size(), CV_8UC1, cv::Scalar(0));
	Mat X(src.size(), CV_8UC1, cv::Scalar(0));
	pair<int, int>center = make_pair(1, 1);
	//int cc = 10;
	while (--maxLoop > 0 && countNonZero(Xn != Y) > 0)//(countNonZero(Xn != Y))
	{
		Xn.copyTo(Y);
		Xn.copyTo(X);
		for (int i = 0; i < bHit.size(); ++i)
		{
			Mat temp = HitMissTransform(X, bHit[i], bMiss[i], center);
			bitwise_not(temp, temp);
			X = getIntersection(X, temp);
		}
		X.copyTo(Xn);
	}
	return Xn;
}

Mat ThickeningTransform(Mat src)
{
	Mat C = src.clone();
	bitwise_not(C, C);
	C = ThinningTransform(C, 5);
	bitwise_not(C, C);
	return C;
}

Mat ConvexHull(Mat src)
{
	cout << src.size().height << ' ' << src.size().width;
	char cvHit[][16] = { "100111001000000",
						 "100000001000010",
						 "100000001111000" };
	Mat compSrc;
	bitwise_not(src, compSrc);
	Mat base = CreateStructureMat(3, 0);
	vector<Mat> bHit, X;
	Mat bMiss;
	for (int i = 0; i < 5; ++i)
	{
		int baseIndex = i * 3;
		for (int u = 0; u < 3; ++u)
			for (int v = 0; v < 3; ++v)
				base.at<uint8_t>(u, v) = cvHit[u][baseIndex + v] - '0';
		bHit.push_back(base.clone());
	}
	for (int i = 0; i < 4; ++i)
		X.push_back(src.clone());
	
	bool isDiff;
	pair<int, int> center = make_pair(1, 1);
	int lastDiff = -1;
	do
	{
		int cDiff = 0;
		vector<Mat> xTemp;
		for (int i = 0; i < bHit.size() - 1; ++i)
		{
			Mat temp = HitMissTransform(X[i], bHit[i], bHit[bHit.size() - 1], center);
			bitwise_not(temp, temp);
			bitwise_or(temp, compSrc, temp);
			bitwise_not(temp, temp);
			xTemp.push_back(temp);
			cDiff += countNonZero(temp != X[i]);
		}
		//cout << X[0] - xTemp[0];
		X = xTemp;
		//cout << cDiff << endl;
		//không thay đổi bao lồi được nữa
		isDiff = cDiff != lastDiff;
		lastDiff = cDiff;
	} while (isDiff);
	Mat ret = X[0];
	bitwise_not(ret, ret);
	for (int i = 1; i < 4; ++i)
	{
		bitwise_not(X[i], X[i]);
		bitwise_or(ret, X[i], ret);
	}
	bitwise_not(ret,ret);
	return ret;

}