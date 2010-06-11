/*
 * SegmentFilter.h
 *
 *  Created on: 2010-06-09
 *      Author: mateusz
 */

#ifndef SEGMENTFILTER_H_
#define SEGMENTFILTER_H_


#include <list>
#include <cv.h>

#include "Segment.h"

class SegmentFilter {
public:
	SegmentFilter();
	virtual ~SegmentFilter();

	virtual void filter(std::list<Segment>& segments)=0;
};

#endif /* SEGMENTFILTER_H_ */
