/*
 * RKWall.cpp
 *
 *  Created on: 2010-06-10
 *      Author: mateusz
 */

#include <cv.h>

#include "RKWall.h"

using namespace std;
using namespace cv;


RKWall::RKWall(const std::vector<Segment>& bricks) :
	bricks(bricks)
{
}

RKWall::~RKWall()
{
}

void RKWall::draw(cv::Mat& image)
{
	if (bricks.size() == 0) {
		return;
	}
	Point p1, p2;
	int lineColor = 0;
	p1 = bricks[0].getMassCenter();
	circle(image, p1, 5, CV_RGB(255 - lineColor, lineColor, 0), 2);
	for (int j = 1; j < bricks.size(); ++j) {
		p2 = bricks[j].getMassCenter();
		lineColor = j * 255 / bricks.size();
		line(image, p1, p2, CV_RGB(255 - lineColor, lineColor, 0));
		circle(image, p2, 5, CV_RGB(255 - lineColor, lineColor, 0), 2);
		p1 = p2;
	}
}
