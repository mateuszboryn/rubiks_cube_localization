/*
 * RKPattern.h
 *
 *  Created on: 2010-06-10
 *      Author: mateusz
 */

#ifndef RKPATTERN_H_
#define RKPATTERN_H_

#include <cv.h>
#include <vector>

#include "Segment.h"
#include "RKWall.h"

class RKPattern {
public:
	RKPattern();
	virtual ~RKPattern();

	const std::vector<RKWall>& findCube(const std::vector<Segment>& segments);

protected:
	std::vector<Segment> findClosestSegments(const std::vector<Segment>& segments, const Segment& centralSegment);

	double dist(cv::Point p1, cv::Point p2);

	std::vector<RKWall> walls;
};

#endif /* RKPATTERN_H_ */
