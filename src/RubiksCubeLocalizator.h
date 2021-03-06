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
	RubiksCubeLocalizator();
	virtual ~RubiksCubeLocalizator();
	bool locateCube(const cv::Mat& image);

	std::list<RKWall> walls;

//	void setConfig(const RKLConfig & config);
	bool showFilteredImage;
	bool showColorsClassifiedImage;
	bool showSegments;

	ColorClassifier& getColorClassifier();
protected:
//	RKLConfig config;

	ColorClassifier colorClassifier;
	Segmentation segmentation;

	int minSegmentArea;

	cv::Mat filteredImage;
	cv::Mat colorClassifiedImage;
	RKPattern pattern;
	SizeFilter sizeFilter;
	ShapeFilter shapeFilter;


	void showIndexedImage(const cv::Mat& indexedImage);
	cv::Mat classifiedRgb;
	std::vector<cv::Mat> classifiedRgbPlanes;
};

#endif /* RUBIKSCUBELOCALIZATOR_H_ */
