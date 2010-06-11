/*
 * RKPattern.cpp
 *
 *  Created on: 2010-06-10
 *      Author: mateusz
 */

#include <cmath>
#include <algorithm>

#include "RKPattern.h"
#include "logger.h"

using namespace std;
using namespace cv;

RKPattern::RKPattern()
{
}

RKPattern::~RKPattern()
{
}

class BricksSort {
public:
	BricksSort(Point p) :
		x0(p.x), y0(p.y)
	{
	}

	bool operator()(const Segment& s1, const Segment& s2)
	{
		double a1, a2;
		double x1, y1, x2, y2;
		x1 = s1.getMassCenter().x;
		y1 = s1.getMassCenter().y;

		x2 = s2.getMassCenter().x;
		y2 = s2.getMassCenter().y;

		a1 = atan2(y1 - y0, x1 - x0);
		a2 = atan2(y2 - y0, x2 - x0);
		return a1 < a2;
	}

private:
	double x0, y0;
};

const std::list<RKWall>& RKPattern::findCube(const list<Segment>& segments)
{
	walls.clear();

	list<Segment>::const_iterator it;
	for (it = segments.begin(); it != segments.end(); ++it) {
		findClosestSegments(segments, *it);

		if (closestSegments.size() == 9) {
			log("RKPattern::findCube(): closestSegments.size() == 9: ");

			vector<Segment>::const_iterator it2;
			for (it2 = closestSegments.begin(); it2 != closestSegments.end(); ++it2) {
				log("    (%d, %d), area: %d, colorClass: %d\n", it2->getMassCenter().x, it2->getMassCenter().y,
						it2->getArea(), it2->getColorClass());
			}

			BricksSort comp(closestSegments.begin()->getMassCenter());

			sort(++closestSegments.begin(), closestSegments.end(), comp);

			if (dist(closestSegments.begin()->getMassCenter(), (++(++closestSegments.begin()))->getMassCenter())
					< dist(closestSegments.begin()->getMassCenter(), (++closestSegments.begin())->getMassCenter())) {
				rotate(++closestSegments.begin(), --closestSegments.end(), closestSegments.end());
			}

			walls.push_back(RKWall(closestSegments));
		}
	}

	return walls;
}

void RKPattern::findClosestSegments(const list<Segment>& segments, const Segment& centralSegment)
{
	closestSegments.push_back(centralSegment);

	double minDistance = sqrt(centralSegment.getArea()) / 2;
	double maxDistance = sqrt(centralSegment.getArea()) * 2;
	int minArea = centralSegment.getArea() / 2;
	int maxArea = centralSegment.getArea() * 2;

	log_dbg("centralSegment: (%d, %d), area: %d\n", centralSegment.getMassCenter().x, centralSegment.getMassCenter().y,
			centralSegment.getArea());

	list<Segment>::const_iterator it;
	for (it = segments.begin(); it != segments.end(); ++it) {
		double d = dist(centralSegment.getMassCenter(), it->getMassCenter());
		if (minArea <= it->getArea() && it->getArea() <= maxArea && minDistance <= d && d <= maxDistance) {
			closestSegments.push_back(*it);
		}
	}
}

double RKPattern::dist(cv::Point p1, cv::Point p2)
{
	return sqrt((p2.x - p1.x) * (p2.x - p1.x) + (p2.y - p1.y) * (p2.y - p1.y));
}
