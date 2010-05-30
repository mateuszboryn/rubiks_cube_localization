/*
 * RubiksCubeLocalizator.cpp
 *
 *  Created on: 2010-05-30
 *      Author: mateusz
 */

#include <cv.h>
#include <highgui.h>

#include "RubiksCubeLocalizator.h"

using namespace cv;

RubiksCubeLocalizator::RubiksCubeLocalizator()
{
}

RubiksCubeLocalizator::~RubiksCubeLocalizator()
{
}

bool RubiksCubeLocalizator::locateCube(Mat& image)
{
	Mat filteredImage;
	medianBlur(image, filteredImage, 3);
	namedWindow("filteredImage", CV_WINDOW_AUTOSIZE);
	imshow("filteredImage", filteredImage);

	//Mat binaryImage;
	doBinarization(filteredImage);
	/*cvNamedWindow("binaryImage");
	 cvShowImage("binaryImage", binaryImage);

	 doBinarization(binaryImage);
	 cvNamedWindow("segmentedImage");
	 cvShowImage("segmentedImage", segmentedImage);*/
	return false;
}

//void RubiksCubeLocalizator::doBinarization(const Mat& image)
//{
//	Mat hsv =
//	IplImage* h = cvCreateImage(cvGetSize(image), image->depth, 1);
//	IplImage* s = cvCreateImage(cvGetSize(image), image->depth, 1);
//	IplImage* v = cvCreateImage(cvGetSize(image), image->depth, 1);
//	cvCvtColor(image, hsv, CV_BGR2HLS);
//	cvSplit(hsv, h, s, v, NULL);
//
//	cvNamedWindow("h");
//	cvShowImage("h", h);
//
//	cvNamedWindow("s");
//	cvShowImage("s", s);
//
//	cvNamedWindow("v");
//	cvShowImage("v", v);
//
//	IplImage* YCrCb = cvCreateImage(cvGetSize(image), image->depth, image->nChannels);
//	IplImage* Y = cvCreateImage(cvGetSize(image), image->depth, 1);
//	IplImage* Cr = cvCreateImage(cvGetSize(image), image->depth, 1);
//	IplImage* Cb = cvCreateImage(cvGetSize(image), image->depth, 1);
//	cvCvtColor(image, YCrCb, CV_BGR2YCrCb);
//	cvSplit(YCrCb, Y, Cr, Cb, NULL);
//
//	cvNamedWindow("Y");
//	cvShowImage("Y", Y);
//
//	cvNamedWindow("Cr");
//	cvShowImage("Cr", Cr);
//
//	cvNamedWindow("Cb");
//	cvShowImage("Cb", Cb);
//}
//
//void RubiksCubeLocalizator::doSegmentation(const Mat& image)
//{
//}
