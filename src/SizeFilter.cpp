/*
 * SizeFilter.cpp
 *
 *  Created on: 2010-06-09
 *      Author: mateusz
 */

#include "SizeFilter.h"
#include "logger.h"

SizeFilter::SizeFilter()
{
}

SizeFilter::~SizeFilter()
{
}

void SizeFilter::filter(std::list<Segment>& segments)
{
	std::list<Segment>::iterator it;
	for (it = segments.begin(); it != segments.end(); ) {
		if (!(minArea < it->getArea() && it->getArea() < maxArea)) {
			it = segments.erase(it);
			continue;
		}
		if (it == segments.end()) {
			break;
		}
		++it;
	}
}
