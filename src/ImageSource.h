/*
 * ImageSource.h
 *
 *  Created on: 2010-06-10
 *      Author: mateusz
 */

#ifndef IMAGESOURCE_H_
#define IMAGESOURCE_H_

#include <cv.h>
#include <highgui.h>

class ImageSource {
public:
	ImageSource();
	virtual ~ImageSource();

	virtual bool isFrameReady() = 0;
	virtual void waitForFrame() = 0;
	virtual void getFrame(cv::Mat& image)=0;
};

#endif /* IMAGESOURCE_H_ */
