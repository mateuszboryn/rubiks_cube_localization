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

#include "Segment.h"

class RubiksCubeLocalizator {
public:
	RubiksCubeLocalizator();
	virtual ~RubiksCubeLocalizator();
	bool locateCube(cv::Mat& image);
protected:
	cv::Mat colorClassification(const cv::Mat& yCrCbImage);
	std::vector<boost::shared_ptr<Segment> > segmentation(const cv::Mat& image);
};

#endif /* RUBIKSCUBELOCALIZATOR_H_ */
