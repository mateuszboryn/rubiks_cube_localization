/*
 * ColorClassifier.h
 *
 *  Created on: 2010-06-09
 *      Author: mateusz
 */

#ifndef COLORCLASSIFIER_H_
#define COLORCLASSIFIER_H_

#include <cv.h>
#include <vector>

#include "ColorDefinition.h"

class ColorClassifier {
public:
	ColorClassifier();
	virtual ~ColorClassifier();

	cv::Mat& classify(const cv::Mat& image);

	//void setColors(const std::vector<ColorDefinition> & colors);
	void setHueShift(int shift);

	bool showColorChannels;
protected:
	const static int maxColorClasses = 30;
	cv::Mat thresholdedImage;
//	cv::Mat YCrCb;
	cv::Mat HSV;

	std::vector<ColorDefinition> colors;
//	int YClasses[256], CrClasses[256], CbClasses[256];

	int HClasses[256], SClasses[256], VClasses[256];

//	std::vector<cv::Mat> planesYCrCb;
	std::vector<cv::Mat> planesHSV;

	int shift;
};

#endif /* COLORCLASSIFIER_H_ */
