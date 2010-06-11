/*
 * RKPattern.h
 *
 *  Created on: 2010-06-10
 *      Author: mateusz
 */

#ifndef RKPATTERN_H_
#define RKPATTERN_H_

#include <cv.h>
#include <list>
#include <vector>

#include "Segment.h"
#include "RKWall.h"

class RKPattern {
public:
	RKPattern();
	virtual ~RKPattern();

	const std::list<RKWall>& findCube(const std::list<Segment>& segments);

protected:
	void findClosestSegments(const std::list<Segment>& segments, const Segment& centralSegment);
	std::vector<Segment> closestSegments;

	double dist(cv::Point p1, cv::Point p2);

	std::list<RKWall> walls;
};

#endif /* RKPATTERN_H_ */
