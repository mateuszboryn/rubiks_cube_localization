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

	void setColors(const std::vector<ColorDefinition> & colors);

	bool showColorChannels;
protected:
	const static int maxColorClasses = 30;
	cv::Mat thresholdedImage;
	cv::Mat YCrCb;
	std::vector<ColorDefinition> colors;
	int YClasses[256], CrClasses[256], CbClasses[256];

	std::vector<cv::Mat> planesYCrCb;
};

#endif /* COLORCLASSIFIER_H_ */
