/*
 * Segment.cpp
 *
 *  Created on: 2010-06-08
 *      Author: mateusz
 */

#include "Segment.h"

Segment::Segment()
{
}

Segment::~Segment()
{
}

void Segment::setImage(const cv::Mat& image)
{
	this->image = image;
}

cv::Mat& Segment::getImage()
{
	return image;
}
