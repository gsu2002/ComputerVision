#include "opencv2\opencv.hpp"
#include "Morph.h"
using namespace cv;

int main()
{
	Mat src;
	Morph morph;
	/// Load image
	src = imread("lena.jpg", CV_LOAD_IMAGE_GRAYSCALE);

	Mat dst;
	morph.Dilation(5, 5, src, dst);

	Mat dst2;
	morph.Erosion(5, 5, src, dst2);

	Mat dst3;
	morph.Closing(5, 5, src, dst3);

	Mat dst4;
	morph.Opening(5, 5, src, dst4);

	imshow("org", src);
	imshow("Dilation", dst);
	imshow("Erosion", dst2);
	
	imshow("Closing", dst3);
	imshow("Opening", dst4);
	cvWaitKey();
}