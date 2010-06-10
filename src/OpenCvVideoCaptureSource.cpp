/*
 * OpenCvVideoCaptureSource.cpp
 *
 *  Created on: 2010-06-10
 *      Author: mateusz
 */

#include <stdexcept>
#include <cv.h>
#include "logger.h"

#include "OpenCvVideoCaptureSource.h"

using namespace std;

OpenCvVideoCaptureSource::OpenCvVideoCaptureSource(int device) :
	capture(device)
{
	if (!capture.isOpened()) {
		throw runtime_error("!capture.isOpened()");
	}
}

OpenCvVideoCaptureSource::~OpenCvVideoCaptureSource()
{
}

bool OpenCvVideoCaptureSource::isFrameReady()
{
	return true;
}

void OpenCvVideoCaptureSource::waitForFrame()
{

}

void OpenCvVideoCaptureSource::getFrame(cv::Mat& image)
{
	if (!capture.grab()) {
		log("!capture.grab()\n");
	}
	if (!capture.retrieve(image)) {
		log("!capture.retrieve(image)\n");
	}

	log("OpenCvVideoCaptureSource::getFrame: image.type(): %d\n", image.type());
}
