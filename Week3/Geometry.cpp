#include "Geometry.h"

void CGeometry::MatrixMul(float homoMatrix[3][3])
{
	if(!initMat)
	{
		for(int i = 0; i < 3; ++i)
	        for(int j = 0; j < 3; ++j)
				HMatrix[i][j] = homoMatrix[i][j];  
		initMat = true;
		return;
	}
	
	float mult[3][3] = {0., };

	for(int i = 0; i < 3; ++i)
        for(int j = 0; j < 3; ++j)
            for(int k = 0; k < 3; ++k)            
                mult[i][j] += HMatrix[i][k] * homoMatrix[k][j];

	for(int i = 0; i < 3; ++i)
        for(int j = 0; j < 3; ++j)
			HMatrix[i][j] = mult[i][j];           
}


void CGeometry::MatrixMul(float homoCoord[1][3], float outputCoord[1][3])
{	
	for(int i = 0; i < 1; ++i)
        for(int j = 0; j < 3; ++j)
            for(int k = 0; k < 3; ++k)            
                outputCoord[i][j] += homoCoord[i][k] * HMatrix[k][j];
}

void CGeometry::ForwardingMapping(cv::Mat &src, cv::Mat &dst)
{
	float homoCoord[1][3] = {0., };	
	for(int y = 0; y < src.rows; ++y)
	{
		for(int x = 0; x < src.cols; ++x)
		{
			homoCoord[0][0] = y;
			homoCoord[0][1] = x;
			homoCoord[0][2] = 1;
			float outputCoord[1][3] = {0., };
			MatrixMul(homoCoord, outputCoord);

			if(outputCoord[0][0] < 0 || outputCoord[0][1] < 0 ||
				outputCoord[0][0] > dst.rows - 1 || outputCoord[0][1] > dst.cols - 1)
				continue;

			dst.at<uchar>((int)outputCoord[0][0], (int)outputCoord[0][1]) = src.at<uchar>(y, x);
		}
	}
}

void CGeometry::BackwardingMapping(cv::Mat &src, cv::Mat &dst)
{
	float homoCoord[1][3] = {0., };	
	for(int y = 0; y < src.rows; ++y)
	{
		for(int x = 0; x < src.cols; ++x)
		{
			homoCoord[0][0] = y;
			homoCoord[0][1] = x;
			homoCoord[0][2] = 1;
			float outputCoord[1][3] = {0., };
			MatrixMul(homoCoord, outputCoord);

			if(outputCoord[0][0] < 0 || outputCoord[0][1] < 0 ||
				outputCoord[0][0] > src.rows - 1 || outputCoord[0][1] > src.cols - 1)
				continue;

			dst.at<uchar>(y, x) = src.at<uchar>((int)outputCoord[0][0], (int)outputCoord[0][1]);
		}
	}
}

void CGeometry::Move(const int y, const int x)
{
	float MoveHomoMatrix[3][3] = {1,0,0,0,1,0,y,x,1};
	MatrixMul(MoveHomoMatrix);
}

void CGeometry::Rotate(const int degree)
{

	double radius = GetDadius(degree);
	
	// 회전에 대한 동차행렬을 완성하시오
	float RotateHomoMatrix[3][3] = { {cos(radius),-sin(radius),0}, {sin(radius), cos(radius),0}, {0,0,1}};
	MatrixMul(RotateHomoMatrix);
}

void CGeometry::Scale(const float sy, const float sx)
{
	float ScaleHomoMatrix[3][3] = {sy,0,0,0,sx,0,0,0,1};
	// 스케일에 대한 동차행렬을 완성하시오
	MatrixMul(ScaleHomoMatrix);
}