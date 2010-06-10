/*
 * SizeFilter.h
 *
 *  Created on: 2010-06-09
 *      Author: mateusz
 */

#ifndef SIZEFILTER_H_
#define SIZEFILTER_H_

#include "SegmentFilter.h"

class SizeFilter: public SegmentFilter {
public:
	SizeFilter();
	virtual ~SizeFilter();

	virtual void filter(std::vector<Segment>& segments);

	int minArea;
	int maxArea;
protected:

};

#endif /* SIZEFILTER_H_ */
