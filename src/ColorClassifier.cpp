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
	showColorChannels(false), shift(0), minGray(0)
{
	for (int i = 0; i < 256; ++i) {
		//		YClasses[i] = CrClasses[i] = CbClasses[i] = 0;
		HClasses[i] = SClasses[i] = VClasses[i] = 0;
	}

	// green
	colors.push_back(ColorDefinition(0, 255, 0, 45, 85, 100, 255, 100, 255));

	// blue
	colors.push_back(ColorDefinition(0, 0, 255, 90, 140, 100, 255, 120, 255));

	// yellow
	colors.push_back(ColorDefinition(255, 255, 0, 20, 44, 100, 255, 200, 255));

	// white
	colors.push_back(ColorDefinition(255, 255, 255, 0, 255, 0, 60, 220, 255));

	// red
	colors.push_back(ColorDefinition(255, 0, 0, 150, 7, 150, 230, 130, 255));

	// orange
	colors.push_back(ColorDefinition(255, 128, 64, 8, 19, 130, 230, 200, 255));

	if (colors.size() > maxColorClasses) {
		throw logic_error("config.colors.size() > maxColorClasses");
	}

	vector<ColorDefinition>::const_iterator it;
	int i = 0;
	for (it = colors.begin(); it != colors.end(); ++it, ++i) {
		for (int j = 0; j < 256; ++j) {
			if ((it->min0 <= j && j <= it->max0) || (it->min0 > it->max0 && (j <= it->max0 || it->min0 <= j))) {
				HClasses[j] |= 1 << i;
			}
			if ((it->min1 <= j && j <= it->max1) || (it->min1 > it->max1 && (j <= it->max1 || it->min1 <= j))) {
				SClasses[j] |= 1 << i;
			}
			if ((it->min2 <= j && j <= it->max2) || (it->min2 > it->max2 && (j <= it->max2 || it->min2 <= j))) {
				VClasses[j] |= 1 << i;
			}

		}

		log_dbg("LUT (%d, %d, %d): ", it->r, it->g, it->b);
		for (int j = 0; j < 256; ++j) {
			log_dbg("%02X", (int) HClasses[j]);
		}
		for (int j = 0; j < 256; ++j) {
			log_dbg("%02X", (int) SClasses[j]);
		}
		for (int j = 0; j < 256; ++j) {
			log_dbg("%02X", (int) VClasses[j]);
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

	if (log_dbg_enabled) {
		for (int j = 0; j < 256; ++j) {
			log_dbg("%3d: %08X    %08X    %08X\n", j, HClasses[j], SClasses[j], VClasses[j]);
		}
	}

	HSV.create(image.size(), CV_8UC3);
	cvtColor(image, HSV, CV_BGR2HSV);

	//	split(HSV, planesHSV);
	//	erode(planesHSV[2], grayEroded, Mat());
	//	adaptiveThreshold(grayEroded, gray, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY, 5, 6);

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
		namedWindow("H", CV_WINDOW_AUTOSIZE);
		imshow("H", planesHSV[0]);

		namedWindow("S", CV_WINDOW_AUTOSIZE);
		imshow("S", planesHSV[1]);

		namedWindow("V", CV_WINDOW_AUTOSIZE);
		imshow("V", planesHSV[2]);

		//namedWindow("gray", CV_WINDOW_AUTOSIZE);
		//imshow("gray", gray);
	}

	log_dbg("ColorClassifier::ColorClassifier(): colors.size()=%d\n", colors.size());
	log_dbg("ColorClassifier::classify(): shift = %d\n", shift);

	//	MatIterator_<uchar> grayIt = gray.begin<uchar> ();
	//	MatIterator_<uchar> grayEnd = gray.end<uchar> ();

	MatIterator_<Vec<uchar, 3> > HSVIt = HSV.begin<Vec<uchar, 3> > ();
	MatIterator_<Vec<uchar, 3> > HSVEnd = HSV.end<Vec<uchar, 3> > ();

	MatIterator_<int> thIt = thresholdedImage.begin<int> ();
	MatIterator_<int> thEnd = thresholdedImage.end<int> ();
	for (; HSVIt != HSVEnd && thIt != thEnd /*&& grayIt != grayEnd*/; ++HSVIt, ++thIt /*, ++grayIt*/) {
		uchar H = (*HSVIt)[0];
		uchar S = (*HSVIt)[1];
		uchar V = (*HSVIt)[2];
		H = (H + shift) % 180;
		//if(*grayIt){
		*thIt = HClasses[H] & SClasses[S] & VClasses[V];
		//		}
		//		else{
		//			*thIt = 0;
		//		}
	}

	if (HSVIt != HSVEnd || thIt != thEnd /*|| grayIt != grayEnd*/) {
		p("ColorClassifier::classify(): HSVIt != HSVEnd || thIt != thEnd\n");
	}

	return thresholdedImage;
}

const std::vector<ColorDefinition>& ColorClassifier::getColors() const
{
	return colors;
}
