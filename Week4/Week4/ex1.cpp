#include "opencv2\opencv.hpp"

using namespace cv;

int main()
{
	Mat src;

	/// Load image
	src = imread("lena_color.jpg", CV_LOAD_IMAGE_COLOR);

	if (!src.data)
	{
		return -1;
	}

	Mat hsvMat;
	cvtColor(src, hsvMat, CV_BGR2HSV);

	// 영상을 각 도메인으로 분리
	std::vector<Mat> channels;
	// Vector 변수에 미리 3개의 영역을 할당
	std::vector<Mat> result(3); 
	
	// 영상을 각 도메인으로 분리(여기서 H, S, V)
	split(hsvMat, channels);

	result[0] = channels[0];
	result[1] = channels[1];
	// V(명도) 도메인만 Historgram Equalization 적용
	equalizeHist(channels[2], result[2]);
	
	Mat imageMerge;
	// 각 도메인을 하나로 합병
	merge(result, imageMerge);

	Mat dst;
	cvtColor(imageMerge, dst, CV_HSV2BGR);
	imshow("org", src);
	imshow("hsv histogram equalization", dst);
	cvWaitKey();

	// RGB 각 도메인을 Historgram Equalization 한 뒤
	// 결과를 보이시오.(imshow와 cvWaitKey를 이용하여 Window를 띄우세요)
	split(src, channels);
	Mat mer;
	equalizeHist(channels[0], result[0]);
	equalizeHist(channels[1], result[1]);
	equalizeHist(channels[2], result[2]);

	Mat rgb;
	merge(result, rgb);
	imshow("rgb histogram equalization", rgb);
	cvWaitKey();

	
	return 0;
}

