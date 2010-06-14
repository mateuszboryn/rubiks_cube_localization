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

	const std::vector<ColorDefinition>& getColors() const;

	bool showColorChannels;
	int shift;
	int minGray;
protected:
	const static int maxColorClasses = 30;
	cv::Mat thresholdedImage;
	cv::Mat HSV;
//	cv::Mat gray;
//	cv::Mat grayEroded;

	std::vector<ColorDefinition> colors;
	int HClasses[256], SClasses[256], VClasses[256];

	std::vector<cv::Mat> planesHSV;
};

#endif /* COLORCLASSIFIER_H_ */
