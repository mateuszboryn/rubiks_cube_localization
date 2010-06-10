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

class ImageInvariants {
public:

	ImageInvariants(double M1 = 0, double M2 = 0, double M3 = 0, double M4 = 0, double M5 = 0, double M6 = 0, double M7 = 0);

	double M1;
	double M2;
	double M3;
	double M4;
	double M5;
	double M6;
	double M7;

	bool operator<=(const ImageInvariants& o) const;
};

class Segment {
public:
	Segment(cv::Mat& image, int area, int colorClass /*, cv::Point leftUpperCorner, cv::Point rightLowerCorner*/);
	virtual ~Segment();

	cv::Mat& getImage();
	const cv::Mat& getImage() const;
	int getArea() const;
	const ImageInvariants& getInvariants() const;
	const cv::Point& getMassCenter() const;
	int getColorClass() const;
protected:
	cv::Mat image;
	int area;
	int colorClass;
	//	cv::Point leftUpperCorner;
	//	cv::Point rightLowerCorner;
	//	cv::Rect getRect();

	void calculateMoments() const;

	mutable bool invariantsCalculated;
	mutable ImageInvariants invariants;
	mutable cv::Moments m;
	mutable cv::Point massCenter;
};

#endif /* SEGMENT_H_ */
