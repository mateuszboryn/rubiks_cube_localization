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

RKPattern::RKPattern()
{
}

RKPattern::~RKPattern()
{
}

class BricksSort {
public:
	BricksSort(double x0, double y0) :
		x0(x0), y0(y0)
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

const std::vector<RKWall>& RKPattern::findCube(const vector<Segment>& segments)
{
	walls.clear();

	vector<Segment>::const_iterator it;
	for (it = segments.begin(); it != segments.end(); ++it) {
		vector<Segment> closestSegments;
		closestSegments = findClosestSegments(segments, *it);

		if (closestSegments.size() == 9) {
			vector<pair<Segment, double> > bricksToSort;
			log("RKPattern::findCube(): closestSegments.size() == 9: ");
			for (int i = 0; i < closestSegments.size(); ++i) {
				log("    (%d, %d), area: %d, colorClass: %d\n", closestSegments[i].getMassCenter().x,
						closestSegments[i].getMassCenter().y, closestSegments[i].getArea(),
						closestSegments[i].getColorClass());
			}

			BricksSort comp(closestSegments[0].getMassCenter().x, closestSegments[0].getMassCenter().y);

			sort(++closestSegments.begin(), closestSegments.end(), comp);


			if (dist(closestSegments[0].getMassCenter(), closestSegments[2].getMassCenter()) < dist(
					closestSegments[0].getMassCenter(), closestSegments[1].getMassCenter())) {
				rotate(++closestSegments.begin(), --closestSegments.end(), closestSegments.end());
			}

			walls.push_back(RKWall(closestSegments));
		}
	}

	return walls;
}

vector<Segment> RKPattern::findClosestSegments(const vector<Segment>& segments, const Segment& centralSegment)
{
	vector<Segment> closestSegments;
	closestSegments.push_back(centralSegment);

	double minDistance = sqrt(centralSegment.getArea()) / 2;
	double maxDistance = sqrt(centralSegment.getArea()) * 2;
	int minArea = centralSegment.getArea() / 2;
	int maxArea = centralSegment.getArea() * 2;

	log_dbg("centralSegment: (%d, %d), area: %d\n", centralSegment.getMassCenter().x, centralSegment.getMassCenter().y,
			centralSegment.getArea());

	vector<Segment>::const_iterator it;
	for (it = segments.begin(); it != segments.end(); ++it) {
		double d = dist(centralSegment.getMassCenter(), it->getMassCenter());
		if (minArea <= it->getArea() && it->getArea() <= maxArea && minDistance <= d && d <= maxDistance) {
			closestSegments.push_back(*it);
		}
	}
	return closestSegments;
}

double RKPattern::dist(cv::Point p1, cv::Point p2)
{
	return sqrt((p2.x - p1.x) * (p2.x - p1.x) + (p2.y - p1.y) * (p2.y - p1.y));
}
