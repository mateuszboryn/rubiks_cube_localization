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
	bool locateCube(const cv::Mat& image);

	std::list<RKWall> walls;
protected:
	RKLConfig config;

	ColorClassifier colorClassifier;
	Segmentation segmentation;

	int minSegmentArea;

	cv::Mat filteredImage;
	cv::Mat colorClassifiedImage;
	//cv::Mat colorClassifiedImageRGB;
	RKPattern pattern;
	SizeFilter sizeFilter;
	ShapeFilter shapeFilter;


	void showIndexedImage(const cv::Mat& indexedImage);
	cv::Mat classifiedRgb;
	std::vector<cv::Mat> classifiedRgbPlanes;
};

#endif /* RUBIKSCUBELOCALIZATOR_H_ */
