/*
 * ShapeFilter.h
 *
 *  Created on: 2010-06-09
 *      Author: mateusz
 */

#ifndef SHAPEFILTER_H_
#define SHAPEFILTER_H_

#include "SegmentFilter.h"

class ShapeFilter: public SegmentFilter {
public:
	ShapeFilter();
	virtual ~ShapeFilter();

	virtual void filter(std::list<Segment>& segments);

	ImageInvariants min, max;
};

#endif /* SHAPEFILTER_H_ */
