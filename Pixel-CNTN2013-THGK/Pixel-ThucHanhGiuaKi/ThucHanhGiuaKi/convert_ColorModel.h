#ifndef _CONVERT_COLORMODEL_
#define _CONVERT_COLORMODEL_

#include "header.h"

using namespace std;
using namespace cv;

// ---------------------------------RGB to GRAY -----------------------------------
Mat     convert_RGB2GRAY(Mat src)
// intensity = 0.2989*red + 0.5870*green + 0.1140*blue
{
//    int height = src.size().height;
//    int width = src.size().width;
    Mat gray;
    vector<Mat> img_rgb;
    split(src, img_rgb);

    img_rgb[0] = img_rgb[0] * 0.1140;
    img_rgb[1] = img_rgb[1] * 0.5870;
    img_rgb[2] = img_rgb[2] * 0.2989;

    gray = img_rgb[0] + img_rgb[1] + img_rgb[2];

//    Mat gray = Mat(height, width, CV_8UC1);
//    for (int i = 0; i < height; ++i)
//        for (int j = 0; j <width; ++j)
//            gray.at<uint8_t>(i, j) = (src.at<Vec3b>(i, j)[0] + src.at<Vec3b>(i, j)[1] + src.at<Vec3b>(i, j)[2]) / 3;
    return gray;
}


// ---------------------------------RGB and HSV -----------------------------------
Mat     convert_RGB2HSV(Mat img)
{
    int height = img.size().height;
    int width = img.size().width;
    Mat res = Mat(height, width, CV_8UC3);

    for (int i = 0; i < height; ++i)
        for (int j = 0; j < width; ++j)
        {
            int R = img.at<Vec3b>(i, j)[2];
            int G = img.at<Vec3b>(i, j)[1];
            int B = img.at<Vec3b>(i, j)[0];

            int H, S, V;

            int M = max(R, max(G, B));
            int m = min(R, min(G, B));

            int C = M - m;

            V = M;
            if (V == 0 || C == 0)
                S = 0;
            else
                S = float(C) / V * 255;
            if (C == 0)
                H = 0;
            else
            {
                float H_tmp;
                if (M == R)
                    H_tmp = float(G - B)/ C;
                else
                {
                    if (M == G)
                        H_tmp = float(B - R) / C + 2;
                    else
                        H_tmp = float(R - G) / C + 4;
                }
                if (H_tmp < 0) H_tmp += 6;
                H = H_tmp * 30;
            }

            res.at<Vec3b>(i, j)[2] = V;
            res.at<Vec3b>(i, j)[1] = S;
            res.at<Vec3b>(i ,j)[0] = H;
        }
    return res;
}

//Suy ra từ hàm RGB2HSV
Mat     convert_HSV2RGB(Mat img)
{
    int height = img.size().height;
    int width = img.size().width;

//    Mat img = Mat(height, width, CV_8UC3);
    Mat res = Mat(height, width, CV_8UC3);

    vector<Mat> img_rgb;
    split(img, img_rgb);

    for (int i = 0; i < height; ++i)
        for (int j = 0; j < width; ++j)
        {
            float H, S, V;
            if (img.type() == 16)
            {
                V = float(img.at<Vec3b>(i, j)[2]) / 255;
                S = float(img.at<Vec3b>(i, j)[1]) / 255;
                H = float(img.at<Vec3b>(i, j)[0]) * 2;
            }
            else
            {
                V = img.at<Vec3f>(i, j)[2];
                S = img.at<Vec3f>(i, j)[1];
                H = img.at<Vec3f>(i, j)[0];
            }

            float C = V * S;
            float Min = V - C;

            H /= 60;

            float R2, G2, B2;
            if (0 <= H && H < 1)
                R2 = C, G2 = H * C, B2 = 0;
            else if (1 <= H && H < 2)
                R2 = (2 - H) * C, G2 = C, B2 = 0;
            else if (2 <= H && H < 3)
                R2 = 0, G2 = C, B2 = (H - 2) * C;
            else if (3 <= H && H < 4)
                R2 = 0, G2 = (4 - H) * C , B2 = C;
            else if (4 <= H && H < 5)
                R2 = (H - 4) * C, G2 = 0, B2 = C;
            else if (5 <= H && H < 6)
                R2 = C, G2 = 0, B2 = (6 - H) * C;

            res.at<Vec3b>(i, j)[0] = uint8_t((B2 + Min) * 255);
            res.at<Vec3b>(i, j)[1] = uint8_t((G2 + Min) * 255);
            res.at<Vec3b>(i, j)[2] = uint8_t((R2 + Min ) * 255);
        }
    return res;
}

// ---------------------------------RGB and CMYK -----------------------------------

Mat   convert_RGB2CYMK(Mat img)
{
    int width = img.size().width;
    int height = img.size().height;
    Mat res = Mat(height, width, CV_8UC4, Scalar_<uint8_t>(0, 0, 0, 0));

    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            int C = 255 - img.at<Vec3b>(i, j)[2];
            int M = 255 - img.at<Vec3b>(i, j)[1];
            int Y = 255 - img.at<Vec3b>(i, j)[0];
            int K = double(min(min(C, M), Y)) / 2.55;
            res.at<Vec4b>(i, j)[3] = uint8_t(K);
            if (K == 100)
                C = M = Y = 255;
            else
            {
                C = int((double(C)/2.55 - K) * 255 / (100 - K));
                M = int((double(M)/2.55 - K) * 255 / (100 - K));
                Y = int((double(Y)/2.55 - K) * 255 / (100 - K));
            }
            res.at<Vec4b>(i, j)[2] = uint8_t(C);
            res.at<Vec4b>(i, j)[1] = uint8_t(M);
            res.at<Vec4b>(i, j)[0] = uint8_t(Y);
        }
    }
    return res;
}

// scale R, G, B value to range [0,255]
void normalize(int &R, int &G, int &B)
{
	R = max(min(R, 255), 0);
	B = max(min(B, 255), 0);
	G = max(min(G, 255), 0);
}
// ---------------------------------------------RGB,LUV,LAB<->XYZ------------------------------
//XYZ is a middle Color model to convert images between RGB, LUV, LAB
Mat   convert_RGB2XYZ(Mat img)
{
	int delta = 128;
	int n = img.size().height;
	int m = img.size().width;

	Mat res = Mat(n, m, CV_32FC3, Scalar_<float>(0, 0, 0));
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < m; ++j)
		{
			float R = img.at<Vec3b>(i, j)[2];
			float G = img.at<Vec3b>(i, j)[1];
			float B = img.at<Vec3b>(i, j)[0];
			R = R / 255;
			G = G / 255;
			B = B / 255;

			if (R > 0.04045)
				R = pow((R + 0.055) / 1.055, 2.4);
			else
				R = R / 12.92;

			if (G > 0.04045)
				G = pow((G + 0.055) / 1.055, 2.4);
			else
				G = G / 12.92;

			if (B > 0.04045)
				B = pow((B + 0.055) / 1.055, 2.4);
			else
				B = B / 12.92;

			R = R * 100;
			G = G * 100;
			B = B * 100;
			res.at<Vec3f>(i, j)[0] = R*0.4124 + G*0.3576 + B*0.1805;
			//cout << res.at<Vec3f>(i, j);
			res.at<Vec3f>(i, j)[1] = R*0.2126 + G*0.7152 + B*0.0722;
			res.at<Vec3f>(i, j)[2] = R*0.0193 + G*0.1192 + B*0.9505;



		}

	return res;
}

Mat   convert_XYZ2RGB(Mat img)
{
	int delta = 128;
	int n = img.size().height;
	int m = img.size().width;

	Mat res = Mat(n, m, CV_8UC3, Scalar_<uint8_t>(0, 0, 0));
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < m; ++j)
		{
			float X = img.at<Vec3f>(i, j)[0] / 100;
			float Y = img.at<Vec3f>(i, j)[1] / 100;
			float Z = img.at<Vec3f>(i, j)[2] / 100;
			float vR = X *  3.2406 + Y * (-1.5372) + Z * (-0.4986);
			float vG = X * (-0.9689) + Y *  1.8758 + Z *  0.0415;
			float vB = X *  0.0557 + Y * (-0.2040) + Z *  1.0570;

			if (vR > 0.0031308)
				vR = 1.055*pow(vR, 1.0 / 2.4) - 0.055;
			if (vG > 0.0031308)
				vG = 1.055*pow(vG, 1.0 / 2.4) - 0.055;
			if (vB > 0.0031308)
				vB = 1.055*pow(vB, 1.0 / 2.4) - 0.055;
			int R = vR * 255;
			int G = vG * 255;
			int B = vB * 255;
			normalize(R, G, B);
			res.at<Vec3b>(i, j)[2] = R;
			res.at<Vec3b>(i, j)[1] = G;
			res.at<Vec3b>(i, j)[0] = B;
		}
	return res;
}

Mat   convert_XYZ2LAB(Mat img)
{
	float refX = 95.047;
	float refY = 100;
	float refZ = 108.883;

	int n = img.size().height;
	int m = img.size().width;

	Mat res = Mat(n, m, CV_32FC3, Scalar_<float>(0, 0, 0));
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < m; ++j)
		{

			float X = img.at<Vec3f>(i, j)[0] / refX;
			float Y = img.at<Vec3f>(i, j)[1] / refY;
			float Z = img.at<Vec3f>(i, j)[2] / refZ;

			if (X > 0.008856)
				X = pow(X, 1.0 / 3);
			else
				X = (7.787*X) + (16.0 / 116);

			if (Y > 0.008856)
				Y = pow(Y, 1.0 / 3);
			else
				Y = (7.787*Y) + (16.0 / 116);

			if (Z > 0.008856)
				Z = pow(Z, 1.0 / 3);
			else
				Z = (7.787*Z) + (16.0 / 116);

			res.at<Vec3f>(i, j)[0] = 116 * Y - 16;
			res.at<Vec3f>(i, j)[1] = 500 * (X - Y);
			res.at<Vec3f>(i, j)[2] = 200 * (Y - Z);
		}

	return res;
}

Mat   convert_LAB2XYZ(Mat img)
{
	float refX = 95.047;
	float refY = 100;
	float refZ = 108.883;

	int n = img.size().height;
	int m = img.size().width;

	Mat res = Mat(n, m, CV_32FC3, Scalar_<float>(0, 0, 0));
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < m; ++j)
		{
			float vY = (img.at<Vec3f>(i, j)[0] + 16) / 116;
			float vX = img.at<Vec3f>(i, j)[1] / 500 + vY;
			float vZ = vY - img.at<Vec3f>(i, j)[2] / 200.0;

			if (pow(vY, 3) > 0.008856)
				vY = pow(vY, 3);
			else
				vY = (vY - 16.0 / 116) / 7.787;

			if (pow(vX, 3) > 0.008856)
				vX = pow(vX, 3);
			else
				vX = (vX - 16.0 / 116) / 7.787;

			if (pow(vZ, 3) > 0.008856)
				vZ = pow(vZ, 3);
			else
				vZ = (vZ - 16.0 / 116) / 7.787;


			res.at<Vec3f>(i, j)[0] = vX*refX;
			res.at<Vec3f>(i, j)[1] = vY*refY;
			res.at<Vec3f>(i, j)[2] = vX*refZ;
		}

	return res;
}


Mat   convert_XYZ2LUV(Mat img)
{
	float refX = 95.047;
	float refY = 100;
	float refZ = 108.883;

	int n = img.size().height;
	int m = img.size().width;

	Mat res = Mat(n, m, CV_32FC3, Scalar_<float>(0, 0, 0));
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < m; ++j)
		{

			float X = img.at<Vec3f>(i, j)[0];
			float Y = img.at<Vec3f>(i, j)[1];
			float Z = img.at<Vec3f>(i, j)[2];

			float vU = (4 * X) / (X + (15 * Y) + (3 * Z));
			float vV = (9 * Y) / (X + (15 * Y) + (3 * Z));
			float vY = Y / 100;

			if (vY > 0.008856)
				vY = pow(vY, 1.0 / 3);
			else
				vY = (7.787*vY) + (16.0 / 116);

			float rU = (4 * refX) / (refX + (15 * refY) + (3 * refZ));
			float rV = (9 * refY) / (refX + (15 * refY) + (3 * refZ));

			res.at<Vec3f>(i, j)[0] = (116 * vY) - 16;
			res.at<Vec3f>(i, j)[1] = 13 * res.at<Vec3f>(i, j)[0] * (vU - rU);
			res.at<Vec3f>(i, j)[2] = 13 * res.at<Vec3f>(i, j)[0] * (vV - rV);
		}

	return res;
}

Mat   convert_LUV2XYZ(Mat img)
{
	float refX = 95.047;
	float refY = 100;
	float refZ = 108.883;

	int n = img.size().height;
	int m = img.size().width;

	Mat res = Mat(n, m, CV_32FC3, Scalar_<float>(0, 0, 0));
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < m; ++j)
		{
			float L = img.at<Vec3f>(i, j)[0];
			float U = img.at<Vec3f>(i, j)[1];
			float V = img.at<Vec3f>(i, j)[2];
			float vY = (L + 16) / 116;
			if (pow(vY, 3) > 0.008856)
				vY = pow(vY, 3);
			else
				vY = (vY - 16.0 / 116) / 7.787;

			float rU = (4 * refX) / (refX + (15 * refY) + (3 * refZ));
			float rV = (9 * refY) / (refX + (15 * refY) + (3 * refZ));

			float vU = U / (13 * L) + rU;
			float vV = V / (13 * L) + rV;

			float Y = vY * 100;
			float X = -(9 * Y*vU) / ((vU - 4)*vV - vU*vV);
			float Z = (9 * Y - (15 * vV*Y) - (vV*X)) / (3 * vV);
			res.at<Vec3f>(i, j)[0] = X;
			res.at<Vec3f>(i, j)[1] = Y;
			res.at<Vec3f>(i, j)[2] = Z;
		}

	return res;
}

//------------------------------RGB <-> LAB -------------------------------------------------
Mat   convert_LAB2RGB(Mat img)
{
	return convert_XYZ2RGB(convert_LAB2XYZ(img));
}
Mat   convert_RGB2LAB(Mat img)
{
	return convert_XYZ2LAB(convert_RGB2XYZ(img));
}

//------------------------------RGB <-> LUV -----------------------------------------------

Mat   convert_LUV2RGB(Mat img)
{
	return convert_XYZ2RGB(convert_LUV2XYZ(img));
}
Mat   convert_RGB2LUV(Mat img)
{
	return convert_XYZ2LUV(convert_RGB2XYZ(img));
}

Mat   convert_RGB2YCbCr(Mat img)
{
	int delta = 128;
	int n = img.size().height;
	int m = img.size().width;

	Mat res = Mat(n, m, CV_32FC3, Scalar_<float>(0, 0, 0));
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < m; ++j)
		{
			int R = img.at<Vec3b>(i, j)[2];
			int G = img.at<Vec3b>(i, j)[1];
			int B = img.at<Vec3b>(i, j)[0];
			float Y = 0.299*R + 0.587*G + 0.114*B;
			float Cr = (R - Y)*0.713 + delta;
			float Cb = (B - Y)*0.564 + delta;
			res.at<Vec3f>(i, j)[0] = Y;
			res.at<Vec3f>(i, j)[1] = Cr;
			res.at<Vec3f>(i, j)[2] = Cb;
		}
	return res;
}



//--------------------------------------RGB <-> YCbCr------------------------------------------------
Mat   convert_YCbCr2RGB(Mat img)
{
	int delta = 128;
	int n = img.size().height;
	int m = img.size().width;

	Mat res = Mat(n, m, CV_8UC3, Scalar_<uint8_t>(0, 0, 0));
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < m; ++j)
		{
			float Y = img.at<Vec3f>(i, j)[0];
			float Cr = img.at<Vec3f>(i, j)[1];
			float Cb = img.at<Vec3f>(i, j)[2];
			int R = Y + 1.403*(Cr - delta);
			int G = Y - 0.714*(Cr - delta) - 0.344*(Cb - delta);
			int B = Y + 1.773*(Cb - delta);
			normalize(R, G, B);

			res.at<Vec3b>(i, j)[2] = R;
			res.at<Vec3b>(i, j)[1] = G;
			res.at<Vec3b>(i, j)[0] = B;
		}
	return res;
}


#endif // _CONVERT_COLORMODEL_



