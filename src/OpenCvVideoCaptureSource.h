/*
 * OpenCvVideoCaptureSource.h
 *
 *  Created on: 2010-06-10
 *      Author: mateusz
 */

#ifndef OPENCVVIDEOCAPTURESOURCE_H_
#define OPENCVVIDEOCAPTURESOURCE_H_

#include "ImageSource.h"

class OpenCvVideoCaptureSource: public ImageSource {
public:
	OpenCvVideoCaptureSource(int device);
	virtual ~OpenCvVideoCaptureSource();

	virtual bool isFrameReady();
	virtual void waitForFrame();
	virtual void getFrame(cv::Mat& image);
private:
	cv::VideoCapture capture;
};

#endif /* OPENCVVIDEOCAPTURESOURCE_H_ */
