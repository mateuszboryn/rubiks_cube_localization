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

	colorClassifier.colors = config.colors;
}

RubiksCubeLocalizator::~RubiksCubeLocalizator()
{
}

bool RubiksCubeLocalizator::locateCube(Mat& image)
{
	medianBlur(image, filteredImage, 3);

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

	colorClassifiedImage = colorClassifier.classify(filteredImage);
	if (log_dbg_enabled) {
		Mat img = convertIndexedToRgb(colorClassifiedImage);
		namedWindow("colorsClassified", CV_WINDOW_AUTOSIZE);
		imshow("colorsClassified", img);
	}

	segmentation.extractAllSegments(colorClassifiedImage);

	log("number of segments: %d\n", segmentation.segments.size());

	sizeFilter.minArea = 100;
	sizeFilter.maxArea = image.size().width * image.size().width / 9;
	sizeFilter.filter(segmentation.segments);

	if (log_dbg_enabled) {
		for (int i = 0; i < segmentation.segments.size(); ++i) {
			log("Size-Filtered %d: (%d, %d) M1: %g, M7: %g, colorClass: %d\n", i,
					segmentation.segments[i].getMassCenter().x, segmentation.segments[i].getMassCenter().y,
					segmentation.segments[i].getInvariants().M1, segmentation.segments[i].getInvariants().M7,
					segmentation.segments[i].getColorClass());
		}
	}

	ImageInvariants min(0.162, -INFINITY, -INFINITY, -INFINITY, -INFINITY, -INFINITY, 6.5e-3);
	ImageInvariants max(0.175, INFINITY, INFINITY, INFINITY, INFINITY, INFINITY, 7.5e-3);

	shapeFilter.min = min;
	shapeFilter.max = max;

	shapeFilter.filter(segmentation.segments);

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

	walls = pattern.findCube(segmentation.segments);

	return walls.size() > 0;
}

cv::Mat RubiksCubeLocalizator::convertIndexedToRgb(const cv::Mat& indexedImage)
{
	Mat rgb(indexedImage.size(), CV_8UC3);
	vector<Mat> planes;
	split(rgb, planes);

	int w = indexedImage.size().width;
	int h = indexedImage.size().height;
	for (int y = 0; y < h; ++y) {
		for (int x = 0; x < w; ++x) {
			int colorClass = indexedImage.at<int> (y, x);
			for (int i = 0; i < config.colors.size(); ++i) {
				if (1 << i == colorClass) {
					planes[0].at<uchar> (y, x) = config.colors[i].b;
					planes[1].at<uchar> (y, x) = config.colors[i].g;
					planes[2].at<uchar> (y, x) = config.colors[i].r;
				}
			}
		}
	}

	merge(planes, rgb);
	return rgb;
}
