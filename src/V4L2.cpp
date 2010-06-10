/*
 * V4L2.cpp
 *
 *  Created on: 2010-06-10
 *      Author: mateusz
 */

#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>

#include "V4L2.h"

using namespace std;

V4L2::V4L2()
{
}

V4L2::~V4L2()
{
}

void V4L2::openDevice(const std::string& fileName)
{
	struct stat st;

	if (stat(fileName.c_str(), &st) == -1) {
		throw runtime_error("Cannot stat \"" + fileName + "\": " + strerror(errno));
	}

	if (!S_ISCHR(st.st_mode)) {
		throw runtime_error("File \"" + fileName + "\" is not a device");
	}

	if ((fd = open(dev_name, O_RDWR | O_NONBLOCK, 0)) == -1) {
		throw runtime_error("Cannot open \"" + fileName + "\": " + strerror(errno));
	}
}
void V4L2::initDevice()
{
	struct v4l2_capability cap;
	struct v4l2_cropcap cropcap;
	struct v4l2_crop crop;
	struct v4l2_format fmt;
	unsigned int min;

	if (xioctl(fd, VIDIOC_QUERYCAP, &cap) == -1) {
		if (EINVAL == errno) {
			fprintf(stderr, "%s is no V4L2 device\n", dev_name);
			exit(EXIT_FAILURE);
		} else {
			errno_exit("VIDIOC_QUERYCAP");
		}
	}

	if (!(cap.capabilities & V4L2_CAP_VIDEO_CAPTURE)) {
		fprintf(stderr, "%s is no video capture device\n", dev_name);
		exit(EXIT_FAILURE);
	}

	switch (io) {
		case IO_METHOD_READ:
			if (!(cap.capabilities & V4L2_CAP_READWRITE)) {
				fprintf(stderr, "%s does not support read i/o\n", dev_name);
				exit(EXIT_FAILURE);
			}

			break;

		case IO_METHOD_MMAP:
		case IO_METHOD_USERPTR:
			if (!(cap.capabilities & V4L2_CAP_STREAMING)) {
				fprintf(stderr, "%s does not support streaming i/o\n", dev_name);
				exit(EXIT_FAILURE);
			}

			break;
	}

	/* Select video input, video standard and tune here. */

	CLEAR(cropcap);

	cropcap.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;

	if (0 == xioctl(fd, VIDIOC_CROPCAP, &cropcap)) {
		crop.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
		crop.c = cropcap.defrect; /* reset to default */

		if (-1 == xioctl(fd, VIDIOC_S_CROP, &crop)) {
			switch (errno) {
				case EINVAL:
					/* Cropping not supported. */
					break;
				default:
					/* Errors ignored. */
					break;
			}
		}
	} else {
		/* Errors ignored. */
	}

	CLEAR(fmt);

	fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	fmt.fmt.pix.width = 640;
	fmt.fmt.pix.height = 480;
	fmt.fmt.pix.pixelformat = V4L2_PIX_FMT_YUYV;
	fmt.fmt.pix.field = V4L2_FIELD_INTERLACED;

	if (-1 == xioctl(fd, VIDIOC_S_FMT, &fmt))
		errno_exit("VIDIOC_S_FMT");

	/* Note VIDIOC_S_FMT may change width and height. */

	/* Buggy driver paranoia. */
	min = fmt.fmt.pix.width * 2;
	if (fmt.fmt.pix.bytesperline < min)
		fmt.fmt.pix.bytesperline = min;
	min = fmt.fmt.pix.bytesperline * fmt.fmt.pix.height;
	if (fmt.fmt.pix.sizeimage < min)
		fmt.fmt.pix.sizeimage = min;

	switch (io) {
		case IO_METHOD_READ:
			init_read(fmt.fmt.pix.sizeimage);
			break;

		case IO_METHOD_MMAP:
			init_mmap();
			break;

		case IO_METHOD_USERPTR:
			init_userp(fmt.fmt.pix.sizeimage);
			break;
	}
}

void V4L2::startCapturing()
{
}

void V4L2::uninitDevice()
{
}

void V4L2::closeDevice()
{
}

int xioctl(int fd, int request, void * arg)
{
	int r;


	do
		r = ioctl(fd, request, arg);
	while (-1 == r && EINTR == errno);

	return r;
}
