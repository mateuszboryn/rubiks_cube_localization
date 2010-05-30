/*
 * RubiksCubeLocalizator.h
 *
 *  Created on: 2010-05-30
 *      Author: mateusz
 */

#ifndef RUBIKSCUBELOCALIZATOR_H_
#define RUBIKSCUBELOCALIZATOR_H_

#include <cv.h>

class RubiksCubeLocalizator {
public:
	RubiksCubeLocalizator();
	virtual ~RubiksCubeLocalizator();
	bool locateCube(cv::Mat& image);
protected:

	//cv::Mat binaryImage;
	//cv::Mat segmentedImage;

	void doBinarization(const cv::Mat& image);
	//void doSegmentation(const cv::Mat& image);
};

#endif /* RUBIKSCUBELOCALIZATOR_H_ */
