/*
 * FileSource.h
 *
 *  Created on: 2010-06-10
 *      Author: mateusz
 */

#ifndef FILESOURCE_H_
#define FILESOURCE_H_

#include <string>

#include "ImageSource.h"

class FileSource: public ImageSource {
public:
	FileSource(const std::string& fileName);
	virtual ~FileSource();

	virtual bool isFrameReady();
	virtual void waitForFrame();
	virtual void getFrame(cv::Mat& image);

private:
	std::string fileName;
	bool fileLoaded;
};

#endif /* FILESOURCE_H_ */
