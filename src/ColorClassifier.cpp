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
}

ColorClassifier::~ColorClassifier()
{
}

cv::Mat ColorClassifier::classify(const cv::Mat& image)
{
	Mat thresholdedImage(image.size(), CV_32S);
	Mat YCrCb;

	YCrCb = image.clone();
	cvtColor(image, YCrCb, CV_BGR2YCrCb);

	vector<Mat> planesYCrCb;

	split(YCrCb, planesYCrCb);

	if (log_enabled) {
		namedWindow("Y", CV_WINDOW_AUTOSIZE);
		imshow("Y", planesYCrCb[0]);

		namedWindow("Cr", CV_WINDOW_AUTOSIZE);
		imshow("Cr", planesYCrCb[1]);

		namedWindow("Cb", CV_WINDOW_AUTOSIZE);
		imshow("Cb", planesYCrCb[2]);
	}

	uchar YClasses[256], CrClasses[256], CbClasses[256];

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

	for (int y = 0; y < image.size().height; ++y) {
		for (int x = 0; x < image.size().width; ++x) {
			uchar Y = planesYCrCb[0].at<uchar> (y, x);
			uchar Cr = planesYCrCb[1].at<uchar> (y, x);
			uchar Cb = planesYCrCb[2].at<uchar> (y, x);
			thresholdedImage.at<int> (y, x) = YClasses[Y] & CrClasses[Cr] & CbClasses[Cb];
		}
	}

	return thresholdedImage;
}
