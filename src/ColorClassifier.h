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

	cv::Mat classify(const cv::Mat& image);

	std::vector<ColorDefinition> colors;
protected:
	const static int maxColorClasses = 30;
};

#endif /* COLORCLASSIFIER_H_ */
