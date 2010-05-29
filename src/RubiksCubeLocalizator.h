/*
 * RubiksCubeLocalizator.h
 *
 *  Created on: 2010-05-30
 *      Author: mateusz
 */

#ifndef RUBIKSCUBELOCALIZATOR_H_
#define RUBIKSCUBELOCALIZATOR_H_

#include <cv.h>

class RubiksCubeLocalizator
{
public:
	RubiksCubeLocalizator();
	virtual ~RubiksCubeLocalizator();
	bool locateCube(IplImage *image);
protected:
	IplImage *filteredImage;
	IplImage *binaryImage;
	IplImage *segmentedImage;

	void doFiltering(IplImage *image);
	void doBinarization(IplImage *image);
	void doSegmentation(IplImage *image);
};

#endif /* RUBIKSCUBELOCALIZATOR_H_ */
