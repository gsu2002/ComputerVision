#pragma once
#include "opencv2\opencv.hpp"
class Morph
{
public:
	void Dilation(const int msize_x, const int msize_y, const cv::Mat& src, cv::Mat& dst);
	void Erosion(const int msize_x, const int msize_y, const cv::Mat& src, cv::Mat& dst);

	void Closing(const int msize_x, const int msize_y, const cv::Mat& src, cv::Mat& dst);
	void Opening(const int msize_x, const int msize_y, const cv::Mat& src, cv::Mat& dst);
};