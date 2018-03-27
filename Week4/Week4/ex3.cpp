#include "opencv2\opencv.hpp"
#include "Morph.h"
using namespace cv;

void SimplePynamid(const int Q, const int Widht, const int Height, 
	const Mat &src, std::vector<Mat>& vec)
{
	
	int newWidth = Widht;
	int newHeight = Height;

	Mat temp;
	src.copyTo(temp);
	for (int q = 0; q < Q; ++q)
	{
		Mat dst(cv::Size(newWidth / 2, newHeight / 2), CV_8UC1);

		for (int h = 0; h < dst.rows; ++h)
		{
			for (int w = 0; w < dst.cols; ++w)
			{
				dst.at<uchar>(h, w) = temp.at<uchar>(h * 2, w * 2);
			}
		}
		vec.push_back(dst);
		dst.copyTo(temp);

		newWidth = newWidth/2;
		newHeight = newHeight / 2;
	}
}

void WeightPynamid(const int Q, const int Widht, const int Height,
	const Mat &src, std::vector<Mat>& vec)
{
	int newWidth = Widht;
	int newHeight = Height;

	

	double weight[5][5] =
	{ {0.0025, 0.0125, 0.02, 0.0125, 0.0025},
	{ 0.0125, 0.0625, 0.1, 0.0625, 0.0125 },
	{ 0.02, 0.1, 0.16, 0.1, 0.02 },
	{ 0.0125, 0.0625, 0.1, 0.0625, 0.0125 },
	{ 0.0025, 0.0125, 0.02, 0.0125, 0.0025 }
	};

	Mat temp;
	src.copyTo(temp);
	int halfSizeY = 2;
	int halfSizeX = 2;
	for (int q = 0; q < Q; ++q)
	{
		Mat dst(cv::Size(newWidth / 2, newHeight / 2), CV_8UC1);

		for (int h = 0; h < dst.rows; ++h)
		{
			for (int w = 0; w < dst.cols; ++w)
			{
				double sum = 0.0;
				for(int mY = -halfSizeY; mY <= halfSizeY;  ++mY)
				{
					for(int mX = -halfSizeX; mX <= halfSizeX; ++mX)
					{
						int idxY = 2*h+mY;
						int idxX = 2*w+mX;

						if (idxY < 0)
							idxY = 0;
						if (idxY >= temp.rows)
							idxY = temp.rows - 1;

						if (idxX < 0)
							idxX = 0;
						if (idxX >= temp.cols)
							idxX = temp.cols - 1;

						sum += (temp.at<uchar>(idxY , idxX) * weight[2+mY][2+mX]);		
					}
				}
				dst.at<uchar>(h, w) = cv::saturate_cast<uchar>(sum);
			}
		}

		vec.push_back(dst);
		dst.copyTo(temp);

		newWidth = newWidth / 2;
		newHeight = newHeight / 2;
	}

}
void main()
{
	Mat src;	
	/// Load image
	std::vector<Mat> octImage;
	src = imread("lena.jpg", CV_LOAD_IMAGE_GRAYSCALE);

	WeightPynamid(5, src.rows, src.cols, src, octImage);

	int idx = 0;
	for (auto& v : octImage)
	{
		std::string str = std::to_string(idx++);
		cvNamedWindow(str.c_str(), (CV_WINDOW_NORMAL));
		imshow(str.c_str(), v);
	}	
	cvWaitKey();
}