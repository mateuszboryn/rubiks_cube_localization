/*
 * RubiksCubeLocalizator.h
 *
 *  Created on: 2010-05-30
 *      Author: mateusz
 */

#ifndef RUBIKSCUBELOCALIZATOR_H_
#define RUBIKSCUBELOCALIZATOR_H_

#include <cv.h>
#include <boost/shared_ptr.hpp>
#include <vector>

#include "Segmentation.h"
#include "ColorClassifier.h"
#include "RKLConfig.h"
#include "RKWall.h"
#include "RKPattern.h"
#include "ShapeFilter.h"
#include "SizeFilter.h"

class RubiksCubeLocalizator {
public:
	RubiksCubeLocalizator(const RKLConfig & config);
	virtual ~RubiksCubeLocalizator();
	bool locateCube(cv::Mat& image);

	std::vector<RKWall> walls;
protected:
	RKLConfig config;
	cv::Mat convertIndexedToRgb(const cv::Mat& indexedImage);

	ColorClassifier colorClassifier;
	Segmentation segmentation;

	int minSegmentArea;

	cv::Mat filteredImage;
	cv::Mat colorClassifiedImage;
	RKPattern pattern;
	SizeFilter sizeFilter;
	ShapeFilter shapeFilter;
};

#endif /* RUBIKSCUBELOCALIZATOR_H_ */
