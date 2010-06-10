/*
 * V4L2.h
 *
 *  Created on: 2010-06-10
 *      Author: mateusz
 */

#ifndef V4L2_H_
#define V4L2_H_

#include <string>
#include <stdexcept>
#include <cv.h>

class V4L2 {
public:
	V4L2();
	virtual ~V4L2();



private:
	void openDevice(const std::string& fileName);
	void initDevice();
	void startCapturing();
	void uninitDevice();
	void closeDevice();

	int fd;
};

#endif /* V4L2_H_ */
