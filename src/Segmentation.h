/*
 * Segmentation.h
 *
 *  Created on: 2010-06-09
 *      Author: mateusz
 */

#ifndef SEGMENTATION_H_
#define SEGMENTATION_H_

#include <vector>
#include <cv.h>

#include "Segment.h"

class Segmentation {
public:
	Segmentation();
	virtual ~Segmentation();

	void extractAllSegments(const cv::Mat& image);

	std::vector<Segment> segments;
protected:
	Segment extractSegment(cv::Mat& image, int y, int x, int colorClass);
};

#endif /* SEGMENTATION_H_ */
