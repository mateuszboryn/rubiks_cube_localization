/*
 * Segment.h
 *
 *  Created on: 2010-06-08
 *      Author: mateusz
 */

#ifndef SEGMENT_H_
#define SEGMENT_H_

#include <cv.h>
#include <boost/shared_ptr.hpp>

class Segment {
public:
	Segment();
	virtual ~Segment();

	void setImage(const cv::Mat& image);
	cv::Mat& getImage();
protected:
	cv::Mat image;
	//color
};

#endif /* SEGMENT_H_ */
