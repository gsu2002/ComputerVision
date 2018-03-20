#include "opencv2\opencv.hpp"

using namespace cv;

void MakeHistogram(Mat &src, float hist[256])
{
	// 히스토그램을 구현하시오
	for (int y = 0; y < src.rows; y++)
	{
		for(int x = 0; x < src.cols; x++)
		{
			hist[src.at<uchar>(y,x)]++;
		}
	}
}

void ShowHistogram(float hist[256])
{

	float cpHist[256];
	memcpy(cpHist, hist, sizeof(float) * 256);
	Mat histMat = Mat(256, 1, CV_32FC1, cpHist);

	int histSize = 256;

	int hist_w = 512; int hist_h = 400;
	int bin_w = cvRound( (double) hist_w/histSize );

	Mat histImage( hist_h, hist_w, CV_8UC3, Scalar( 0,0,0) );

	normalize(histMat, histMat, 0, histImage.rows, NORM_MINMAX, -1, Mat() );

	// Draw for each channel
	for( int i = 1; i < histSize; i++ )
	{
		line( histImage, Point( bin_w*(i-1), hist_h - cvRound(histMat.at<float>(i-1)) ) ,
			Point( bin_w*(i), hist_h - cvRound(histMat.at<float>(i)) ),
			Scalar( 255, 0, 255), 2, 8, 0  );
	}

	/// Display
	namedWindow("calcHist Demo", CV_WINDOW_AUTOSIZE );
	imshow("calcHist Demo", histImage );

	waitKey(0);
}

void MakeHistorgramEqualizationImg(Mat &src, float hist[256])
{
	Mat dst(src.size(), CV_8UC1);
	
	// 정규화
	float sumArr[256];
	for (int i = 0; i < 256; i++)
	{
		sumArr[i] = hist[i] / (src.rows*src.cols);
	}

	float sum = 0;
	for(int i = 0; i < 256; i++)
	{
		sum += sumArr[i];
		sumArr[i] = sum;
	}
	ShowHistogram(sumArr);
	

	// 히스토그램 평활화를 완성하시오

	for (int i = 0; i < 256; i++)
		hist[i] = cvRound((sumArr[i] * 256-1));

	ShowHistogram(hist);
	for (int y = 0; y < dst.rows; y++)
	{
		for(int x = 0; x < dst.cols; x++)
		{
			dst.at<uchar>(y,x) = hist[src.at<uchar>(y,x)];
		}
	}

	namedWindow("EqualizationImg", CV_WINDOW_AUTOSIZE );
	imshow("EqualizationImg", dst );		// 결과 이미지

	waitKey(0);
}

int main()
{
	Mat src, dst;

	/// Load image
	src = imread( "lena.jpg",CV_LOAD_IMAGE_GRAYSCALE );

	if( !src.data )
	{ return -1; }

	float histArr[256] = {0.0, };
	MakeHistogram(src, histArr);
	ShowHistogram(histArr);
	MakeHistorgramEqualizationImg(src, histArr);


	return 0;
}

