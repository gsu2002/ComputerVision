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

	// ������ �� ���������� �и�
	std::vector<Mat> channels;
	// Vector ������ �̸� 3���� ������ �Ҵ�
	std::vector<Mat> result(3); 
	
	// ������ �� ���������� �и�(���⼭ H, S, V)
	split(hsvMat, channels);

	result[0] = channels[0];
	result[1] = channels[1];
	// V(��) �����θ� Historgram Equalization ����
	equalizeHist(channels[2], result[2]);
	
	Mat imageMerge;
	// �� �������� �ϳ��� �պ�
	merge(result, imageMerge);

	Mat dst;
	cvtColor(imageMerge, dst, CV_HSV2BGR);
	imshow("org", src);
	imshow("hsv histogram equalization", dst);
	cvWaitKey();

	// RGB �� �������� Historgram Equalization �� ��
	// ����� ���̽ÿ�.(imshow�� cvWaitKey�� �̿��Ͽ� Window�� ��켼��)
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

