#include "opencv2\opencv.hpp"
#include "Geometry.h"
using namespace cv;



int main()
{
	Mat src, dst, dst2;

	/// Load image
	src = imread( "lena.jpg",CV_LOAD_IMAGE_GRAYSCALE );

	if( !src.data )
	{ return -1; }

	imshow("src Demo", src );

	CGeometry geometry;	
	// Move
	geometry.Move(-(src.rows/2), -(src.cols/2));	
	dst.create(src.size(), CV_8UC1);
	dst2.create(src.size(), CV_8UC1);
	geometry.ForwardingMapping(src, dst);
	geometry.BackwardingMapping(src, dst2);
	imshow("Geometry Forwarding Mapping Demo", dst );
	imshow("Geometry Backwarding Mapping Demo", dst2);
	waitKey(0);

	// Reset Variable
	geometry.Reset();
	dst.release();
	dst2.release();
	dst.create(src.size(), CV_8UC1);
	dst2.create(src.size(), CV_8UC1);

	// Rotate
	geometry.Rotate(30);
	geometry.ForwardingMapping(src, dst);
	geometry.BackwardingMapping(src, dst2);
	imshow("Geometry Forwarding Mapping Demo", dst );
	imshow("Geometry Backwarding Mapping Demo", dst2);
	waitKey(0);

	// Reset Variable
	geometry.Reset();
	dst.release();
	dst2.release();
	dst.create(src.size(), CV_8UC1);
	dst2.create(src.size(), CV_8UC1);

	// Scale
	geometry.Scale(0.5, 0.5);
	geometry.ForwardingMapping(src, dst);
	geometry.BackwardingMapping(src, dst2);
	imshow("Geometry Forwarding Mapping Demo", dst );
	imshow("Geometry Backwarding Mapping Demo", dst2);
	waitKey(0);

	// Reset Variable
	geometry.Reset();
	dst.release();
	dst2.release();
	dst.create(src.size(), CV_8UC1);
	dst2.create(src.size(), CV_8UC1);

	// Rotate at the center
	geometry.Move(-(src.rows/2), -(src.cols/2));
	geometry.Rotate(70);
	geometry.Move(src.rows/2, src.cols/2);	
	
	geometry.ForwardingMapping(src, dst);
	geometry.BackwardingMapping(src, dst2);
	imshow("Geometry Forwarding Mapping Demo", dst );
	imshow("Geometry Backwarding Mapping Demo", dst2);
	waitKey(0);

	waitKey(0);
	return 0;
}

