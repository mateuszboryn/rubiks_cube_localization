/*
 * ShapeFilter.cpp
 *
 *  Created on: 2010-06-09
 *      Author: mateusz
 */

#include "ShapeFilter.h"

ShapeFilter::ShapeFilter()
{
}

ShapeFilter::~ShapeFilter()
{
}

void ShapeFilter::filter(std::vector<Segment>& segments)
{
	std::vector<Segment>::iterator it;
	for (it = segments.begin(); it != segments.end();) {
		if (!(min <= it->getInvariants() && it->getInvariants() <= max)) {
			it = segments.erase(it);
			continue;
		}
		if (it == segments.end()) {
			break;
		}
		++it;
	}
}
