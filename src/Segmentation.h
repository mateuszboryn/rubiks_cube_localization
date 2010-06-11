/*
 * Segmentation.h
 *
 *  Created on: 2010-06-09
 *      Author: mateusz
 */

#ifndef SEGMENTATION_H_
#define SEGMENTATION_H_

#include <vector>
#include <list>
#include <cv.h>

#include "Segment.h"

class Segmentation {
public:
	Segmentation();
	virtual ~Segmentation();

	void extractAllSegments(cv::Mat& image);

	std::list<Segment> segments;
protected:
	Segment extractSegment(cv::Mat& image, int y, int x, int colorClass);
};

#endif /* SEGMENTATION_H_ */
