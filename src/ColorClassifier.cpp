/*
 * ColorClassifier.cpp
 *
 *  Created on: 2010-06-09
 *      Author: mateusz
 */

#include <highgui.h>
#include <stdexcept>

#include "ColorClassifier.h"
#include "logger.h"

using namespace std;
using namespace cv;

ColorClassifier::ColorClassifier()
{
	for (int i = 0; i < 256; ++i) {
		YClasses[i] = CrClasses[i] = CbClasses[i] = 0;
	}
}

ColorClassifier::~ColorClassifier()
{
}

void ColorClassifier::setColors(const std::vector<ColorDefinition> & colors)
{
	this->colors = colors;

	for (int i = 0; i < 256; ++i) {
		YClasses[i] = CrClasses[i] = CbClasses[i] = 0;
	}

	if (colors.size() > maxColorClasses) {
		throw runtime_error("config.colors.size() > maxColorClasses");
	}

	for (int i = 0; i < colors.size(); ++i) {
		for (int j = colors[i].min0; j < colors[i].max0; j = (j + 1) % 256) {
			YClasses[j] |= 1 << i;
		}
		for (int j = colors[i].min1; j < colors[i].max1; j = (j + 1) % 256) {
			CrClasses[j] |= 1 << i;
		}
		for (int j = colors[i].min2; j < colors[i].max2; j = (j + 1) % 256) {
			CbClasses[j] |= 1 << i;
		}
	}
}

//cv::Mat& ColorClassifier::classify(const cv::Mat& image)
//{
//	thresholdedImage.create(image.size(), CV_32S);
//
//	YCrCb.create(image.size(), CV_8UC3);
//	cvtColor(image, YCrCb, CV_BGR2YCrCb);
//
//	split(YCrCb, planesYCrCb);
//
//	if (log_enabled) {
//		namedWindow("Y", CV_WINDOW_AUTOSIZE);
//		imshow("Y", planesYCrCb[0]);
//
//		namedWindow("Cr", CV_WINDOW_AUTOSIZE);
//		imshow("Cr", planesYCrCb[1]);
//
//		namedWindow("Cb", CV_WINDOW_AUTOSIZE);
//		imshow("Cb", planesYCrCb[2]);
//	}
//
//	for (int y = 0; y < image.size().height; ++y) {
//		for (int x = 0; x < image.size().width; ++x) {
//			uchar Y = planesYCrCb[0].at<uchar> (y, x);
//			uchar Cr = planesYCrCb[1].at<uchar> (y, x);
//			uchar Cb = planesYCrCb[2].at<uchar> (y, x);
//			thresholdedImage.at<int> (y, x) = YClasses[Y] & CrClasses[Cr] & CbClasses[Cb];
//		}
//	}
//
//	return thresholdedImage;
//}


cv::Mat& ColorClassifier::classify(const cv::Mat& image)
{
	thresholdedImage.create(image.size(), CV_32S);

	YCrCb.create(image.size(), CV_8UC3);
	cvtColor(image, YCrCb, CV_BGR2YCrCb);

//	if (log_enabled) {
//		namedWindow("Y", CV_WINDOW_AUTOSIZE);
//		imshow("Y", planesYCrCb[0]);
//
//		namedWindow("Cr", CV_WINDOW_AUTOSIZE);
//		imshow("Cr", planesYCrCb[1]);
//
//		namedWindow("Cb", CV_WINDOW_AUTOSIZE);
//		imshow("Cb", planesYCrCb[2]);
//	}

	MatIterator_<Vec<uchar, 3> > YCrCbIt = YCrCb.begin<Vec<uchar, 3> > ();
	MatIterator_<Vec<uchar, 3> > YCrCbEnd = YCrCb.end<Vec<uchar, 3> > ();

	MatIterator_<int> thIt = thresholdedImage.begin<int> ();
	MatIterator_<int> thEnd = thresholdedImage.end<int> ();
	for (; YCrCbIt != YCrCbEnd && thIt != thEnd; ++YCrCbIt, ++thIt) {
		uchar Y = (*YCrCbIt)[0];
		uchar Cr = (*YCrCbIt)[1];
		uchar Cb = (*YCrCbIt)[2];
		*thIt = YClasses[Y] & CrClasses[Cr] & CbClasses[Cb];
	}

	if (YCrCbIt != YCrCbEnd || thIt != thEnd) {
		p("ColorClassifier::classify(): YCrCbIt != YCrCbEnd || thIt != thEnd\n");
	}

	return thresholdedImage;
}
