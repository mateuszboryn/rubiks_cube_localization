/*
 * FileSource.cpp
 *
 *  Created on: 2010-06-10
 *      Author: mateusz
 */

#include <limits.h>
#include <stdexcept>

#include "FileSource.h"

using namespace cv;
using namespace std;

FileSource::FileSource(const std::string& fileName) :
	fileName(fileName), fileLoaded(false)
{
}

FileSource::~FileSource()
{
}

bool FileSource::isFrameReady()
{
	return !fileLoaded;
}

void FileSource::waitForFrame()
{
	if (fileLoaded) {
		sleep(UINT_MAX);
	}
}

void FileSource::getFrame(cv::Mat& image)
{
	image = imread(fileName.c_str());
	if (image.data == NULL) {
		throw runtime_error("image.data == NULL");
	}
	fileLoaded = true;
}
