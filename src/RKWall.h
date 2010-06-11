/*
 * RKWall.h
 *
 *  Created on: 2010-06-10
 *      Author: mateusz
 */

#ifndef RKWALL_H_
#define RKWALL_H_

#include <cv.h>
#include <list>
#include <vector>

#include "Segment.h"

class RKWall {
public:
	RKWall(const std::vector<Segment>& bricks);
	virtual ~RKWall();
	void draw(cv::Mat& image) const;
protected:
	std::vector<Segment> bricks;
};

#endif /* RKWALL_H_ */
