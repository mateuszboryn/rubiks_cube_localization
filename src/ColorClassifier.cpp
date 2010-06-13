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

ColorClassifier::ColorClassifier() :
	showColorChannels(false), shift(0)
{
	for (int i = 0; i < 256; ++i) {
		//		YClasses[i] = CrClasses[i] = CbClasses[i] = 0;
		HClasses[i] = SClasses[i] = VClasses[i] = 0;
	}

	// green
	colors.push_back(ColorDefinition(0, 255, 0, 105 / 2, 135 / 2, 61, 255, 51, 255));

	// blue
	colors.push_back(ColorDefinition(0, 0, 255, 225 / 2, 255 / 2, 61, 255, 35, 255));

	// yellow
	colors.push_back(ColorDefinition(255, 255, 0, 45 / 2 + 1, 75 / 2, 61, 255, 35, 255));

	// white
	//colors.push_back(ColorDefinition(255, 255, 255, 0, 255, 0, 60, 35, 255));

	// red/orange
	colors.push_back(ColorDefinition(255, 0, 0, 345 / 2, 15 / 2, 0, 60, 35, 255));

	if (colors.size() > maxColorClasses) {
		throw logic_error("config.colors.size() > maxColorClasses");
	}

	for (int i = 0; i < colors.size(); ++i) {
		for (int j = colors[i].min0; j < colors[i].max0; j = (j + 1) % 256) {
			//			YClasses[j] |= 1 << i;
			HClasses[j] |= 1 << i;
		}
		for (int j = colors[i].min1; j < colors[i].max1; j = (j + 1) % 256) {
			//			CrClasses[j] |= 1 << i;
			SClasses[j] |= 1 << i;
		}
		for (int j = colors[i].min2; j < colors[i].max2; j = (j + 1) % 256) {
			//			CbClasses[j] |= 1 << i;
			VClasses[j] |= 1 << i;
		}
	}
}

ColorClassifier::~ColorClassifier()
{
}

//void ColorClassifier::setColors(const std::vector<ColorDefinition> & colors)
//{
//	this->colors = colors;
//}

cv::Mat& ColorClassifier::classify(const cv::Mat& image)
{
	thresholdedImage.create(image.size(), CV_32S);

	//	YCrCb.create(image.size(), CV_8UC3);
	//	cvtColor(image, YCrCb, CV_BGR2YCrCb);

	HSV.create(image.size(), CV_8UC3);
	cvtColor(image, HSV, CV_BGR2HSV);

	if (showColorChannels) {
		//		split(YCrCb, planesYCrCb);
		//		namedWindow("Y", CV_WINDOW_AUTOSIZE);
		//		imshow("Y", planesYCrCb[0]);
		//
		//		namedWindow("Cr", CV_WINDOW_AUTOSIZE);
		//		imshow("Cr", planesYCrCb[1]);
		//
		//		namedWindow("Cb", CV_WINDOW_AUTOSIZE);
		//		imshow("Cb", planesYCrCb[2]);

		split(HSV, planesHSV);
		namedWindow("H", CV_WINDOW_AUTOSIZE);
		imshow("H", planesHSV[0]);

		namedWindow("S", CV_WINDOW_AUTOSIZE);
		imshow("S", planesHSV[1]);

		namedWindow("V", CV_WINDOW_AUTOSIZE);
		imshow("V", planesHSV[2]);
	}

	//	MatIterator_<Vec<uchar, 3> > YCrCbIt = YCrCb.begin<Vec<uchar, 3> > ();
	//	MatIterator_<Vec<uchar, 3> > YCrCbEnd = YCrCb.end<Vec<uchar, 3> > ();
	//
	//	MatIterator_<int> thIt = thresholdedImage.begin<int> ();
	//	MatIterator_<int> thEnd = thresholdedImage.end<int> ();
	//	for (; YCrCbIt != YCrCbEnd && thIt != thEnd; ++YCrCbIt, ++thIt) {
	//		uchar Y = (*YCrCbIt)[0];
	//		uchar Cr = (*YCrCbIt)[1];
	//		uchar Cb = (*YCrCbIt)[2];
	//		*thIt = YClasses[Y] & CrClasses[Cr] & CbClasses[Cb];
	//	}
	//
	//	if (YCrCbIt != YCrCbEnd || thIt != thEnd) {
	//		p("ColorClassifier::classify(): YCrCbIt != YCrCbEnd || thIt != thEnd\n");
	//	}

	MatIterator_<Vec<uchar, 3> > HSVIt = HSV.begin<Vec<uchar, 3> > ();
	MatIterator_<Vec<uchar, 3> > HSVEnd = HSV.end<Vec<uchar, 3> > ();

	MatIterator_<int> thIt = thresholdedImage.begin<int> ();
	MatIterator_<int> thEnd = thresholdedImage.end<int> ();
	for (; HSVIt != HSVEnd && thIt != thEnd; ++HSVIt, ++thIt) {
		uchar H = (*HSVIt)[0];
		uchar S = (*HSVIt)[1];
		uchar V = (*HSVIt)[2];
		H = (H + shift) % 180;
		*thIt = HClasses[H] & SClasses[S] & VClasses[V];
	}

	if (HSVIt != HSVEnd || thIt != thEnd) {
		p("ColorClassifier::classify(): HSVIt != HSVEnd || thIt != thEnd\n");
	}

	return thresholdedImage;
}

void ColorClassifier::setHueShift(int shift)
{
	this->shift = shift;
}
