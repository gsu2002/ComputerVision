#include "Morph.h"
using namespace cv;
void Morph::Dilation(const int msize_x, const int msize_y, const cv::Mat & src, cv::Mat & dst)
{
	if (dst.empty())
		dst.create(src.size(), CV_8UC1);

	const int halfSizeX = msize_x / 2;
	const int halfSizeY = msize_y / 2;

	for (int h = 0; h < src.rows; ++h)
	{
		for (int w = 0; w < src.cols; ++w)
		{
			int maxVal = INT_MIN;
			for (int mY = -halfSizeY; mY <= halfSizeY; ++mY)
			{
				int idxY = h + mY;
				// 예외처리
				if (idxY < 0)
					idxY = 0;
				if (idxY >= src.rows)
					idxY = src.rows - 1;
				for (int mX = -halfSizeX; mX <= halfSizeX; ++mX)
				{
					int idxX = w + mX;
					// 예외처리
					if (idxX < 0)
						idxX = 0;
					if (idxX >= src.cols)
						idxX = src.cols - 1;

					uchar val = src.at<uchar>(idxY, idxX);
					if (maxVal < val)
						maxVal = val;
				}
			}
			dst.at<uchar>(h, w) = maxVal;
		}
	}
}

void Morph::Erosion(const int msize_x, const int msize_y, const cv::Mat & src, cv::Mat & dst)
{
	//  구현하시오
	if (dst.empty())
		dst.create(src.size(), CV_8UC1);

	const int halfSizeX = msize_x / 2;
	const int halfSizeY = msize_y / 2;

	for (int h = 0; h < src.rows; ++h)
	{
		for (int w = 0; w < src.cols; ++w)
		{
			int minVal = INT_MAX;
			for (int mY = -halfSizeY; mY <= halfSizeY; ++mY)
			{
				int idxY = h - mY;
				// 예외처리
				if (idxY < 0)
					idxY = 0;
				if (idxY >= src.rows)
					idxY = src.rows - 1;
				for (int mX = -halfSizeX; mX <= halfSizeX; ++mX)
				{
					int idxX = w - mX;
					// 예외처리
					if (idxX < 0)
						idxX = 0;
					if (idxX >= src.cols)
						idxX = src.cols - 1;

					uchar val = src.at<uchar>(idxY, idxX);
					if (minVal > val)
						minVal = val;
				}
			}
			dst.at<uchar>(h, w) = minVal;
		}
	}
}

void Morph::Closing(const int msize_x, const int msize_y, const cv::Mat & src, cv::Mat & dst)
{
	cv:: Mat temp;
	Morph::Dilation(msize_x, msize_y, src, temp);
	Morph::Erosion(msize_x, msize_y, temp, dst);
	
}

void Morph::Opening(const int msize_x, const int msize_y, const cv::Mat & src, cv::Mat & dst)
{
	cv:: Mat temp;
	Morph::Erosion(msize_x, msize_y, src, temp);
	Morph::Dilation(msize_x, msize_y, temp, dst);
}
