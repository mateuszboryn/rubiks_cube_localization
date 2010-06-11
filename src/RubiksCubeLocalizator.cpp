/*
 * RubiksCubeLocalizator.cpp
 *
 *  Created on: 2010-05-30
 *      Author: mateusz
 */

#include <cv.h>
#include <highgui.h>
#include <vector>
#include <stdexcept>
#include <stack>
#include <cstdio>
#include <algorithm>

#include "RubiksCubeLocalizator.h"
#include "logger.h"

using namespace std;
using namespace cv;

RubiksCubeLocalizator::RubiksCubeLocalizator(const RKLConfig & config) :
	config(config)
{
	minSegmentArea = 100;

	colorClassifier.setColors(config.colors);

	//	namedWindow("colorsClassified", CV_WINDOW_AUTOSIZE);
}

RubiksCubeLocalizator::~RubiksCubeLocalizator()
{
}

bool RubiksCubeLocalizator::locateCube(const Mat& image)
{
	//	p("1");
	//medianBlur(image, filteredImage, 3);
	//	p("2");
	//	if (log_dbg_enabled) {
	//		namedWindow("filteredImage", CV_WINDOW_AUTOSIZE);
	//		imshow("filteredImage", filteredImage);
	//	}

	//	Mat afterErosion;
	//	erode(filteredImage, afterErosion, Mat());

	//	if (log_dbg_enabled) {
	//		namedWindow("afterErosion", CV_WINDOW_AUTOSIZE);
	//		imshow("afterErosion", afterErosion);
	//	}

	colorClassifiedImage = colorClassifier.classify(image);
	//return false;
	//	p("3");
	//	if (log_dbg_enabled) {
	// showIndexedImage(colorClassifiedImage);
	//	}

	segmentation.extractAllSegments(colorClassifiedImage);
	//	p("4");
	log_dbg("number of segments: %d\n", segmentation.segments.size());

	sizeFilter.minArea = 100;
	sizeFilter.maxArea = image.size().width * image.size().width / 9;
	sizeFilter.filter(segmentation.segments);

	if (log_dbg_enabled) {
		int i=0;
		for (list<Segment>::iterator it = segmentation.segments.begin(); it != segmentation.segments.begin(); ++it, ++i) {
			log_dbg("Size-Filtered %d: (%d, %d) M1: %g, M7: %g, colorClass: %d\n", i, it->getMassCenter().x,
					it->getMassCenter().y, it->getInvariants().M1, it->getInvariants().M7, it->getColorClass());
		}
	}

	ImageInvariants min(0.162, -INFINITY, -INFINITY, -INFINITY, -INFINITY, -INFINITY, 6.5e-3);
	ImageInvariants max(0.175, INFINITY, INFINITY, INFINITY, INFINITY, INFINITY, 7.5e-3);

	shapeFilter.min = min;
	shapeFilter.max = max;

	shapeFilter.filter(segmentation.segments);
	//	p("5");
	//	if (log_dbg_enabled) {
	//		for (int i = 0; i < segmentation.segments.size(); ++i) {
	//			char txt[123];
	//			sprintf(txt, "Segment %d", i);
	//			namedWindow(txt, CV_WINDOW_AUTOSIZE);
	//			imshow(txt, segmentation.segments[i].getImage());
	//			log("%s: M1: %g, M7: %g, colorClass: %d\n", txt, segmentation.segments[i].getInvariants().M1,
	//					segmentation.segments[i].getInvariants().M7, segmentation.segments[i].getColorClass());
	//		}
	//	}
	return false;
	walls = pattern.findCube(segmentation.segments);
	//	p("6");
	return walls.size() > 0;
}

void RubiksCubeLocalizator::showIndexedImage(const cv::Mat& indexedImage)
{
	classifiedRgb.create(indexedImage.size(), CV_8UC3);

	split(classifiedRgb, classifiedRgbPlanes);

	int w = indexedImage.size().width;
	int h = indexedImage.size().height;
	for (int y = 0; y < h; ++y) {
		for (int x = 0; x < w; ++x) {
			int colorClass = indexedImage.at<int> (y, x);
			for (int i = 0; i < config.colors.size(); ++i) {
				if (1 << i == colorClass) {
					classifiedRgbPlanes[0].at<uchar> (y, x) = config.colors[i].b;
					classifiedRgbPlanes[1].at<uchar> (y, x) = config.colors[i].g;
					classifiedRgbPlanes[2].at<uchar> (y, x) = config.colors[i].r;
				} else {
					classifiedRgbPlanes[0].at<uchar> (y, x) = 0;
					classifiedRgbPlanes[1].at<uchar> (y, x) = 0;
					classifiedRgbPlanes[2].at<uchar> (y, x) = 0;
				}
			}
		}
	}

	merge(classifiedRgbPlanes, classifiedRgb);
	imshow("colorsClassified", classifiedRgb);
}
