#include "opencv2\opencv.hpp"
using namespace cv;

void BiLinear_Interpolation(Mat &src, Mat &dst)
{
	//Bilinear 보간을 완성하시오
	
	float scale = dst.rows / (float)src.rows;
	for (int y = 0; y < dst.rows; y++)
	{
		for (int x = 0; x < dst.cols; x++)
		{
			// src x,y 좌표
			int sx = (x / scale);	
			int sy = (y / scale);
			
			// src x,y 좌표에서 보간 과정 중 범위를 넘는 경우
			if(sx+1 >= src.cols || sy+1 >= src.rows)
				dst.at<uchar>(y, x) = src.at<uchar>(sy, sx);

			else
			{
				double fx1 = (double)x / scale - (double)sx;
				double fx2 = 1 - fx1;
				double fy1 = (double)y / scale - (double)sy;
				double fy2 = 1 - fy1;

				double w1 = fx2 * fy2;
				double w2 = fx1 * fy2;
				double w3 = fx2 * fy1;
				double w4 = fx1 * fy1;

				uchar P1 = src.at<uchar>(sy, sx);
				uchar P2 = src.at<uchar>(sy, sx + 1);
				uchar P3 = src.at<uchar>(sy + 1, sx);
				uchar P4 = src.at<uchar>(sy + 1, sx + 1);
				int bil = w1 * P1 + w2*P2 + w3*P3 + w4*P4;

				dst.at<uchar>(y, x) = bil;
			}

			

		}
	}
	
}


int main()
{
	Mat src, dst;

	/// Load image
	src = imread( "lena.jpg",CV_LOAD_IMAGE_GRAYSCALE );

	if( !src.data )
	{ return -1; }
		
	dst.create(src.rows * 1.7, src.cols * 1.7, CV_8UC1);
	BiLinear_Interpolation(src, dst);	
	
	imshow("Orginal Demo", src );
	imshow("Bilinear Demo", dst );	
	waitKey(0);
	return 0;
}

