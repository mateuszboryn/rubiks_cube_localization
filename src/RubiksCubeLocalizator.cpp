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

RubiksCubeLocalizator::RubiksCubeLocalizator() :
	showFilteredImage(false), showColorChannels(false), showColorsClassifiedImage(false), showSegments(false)
{
	minSegmentArea = 100;
}

RubiksCubeLocalizator::~RubiksCubeLocalizator()
{
}

//void RubiksCubeLocalizator::setConfig(const RKLConfig & config)
//{
//	this->config = config;
//	//colorClassifier.setColors(config.colors);
//}

bool RubiksCubeLocalizator::locateCube(const Mat& image)
{
	medianBlur(image, filteredImage, 3);
	if (showFilteredImage) {
		namedWindow("filteredImage", CV_WINDOW_AUTOSIZE);
		imshow("filteredImage", filteredImage);
	}

	colorClassifier.showColorChannels = showColorChannels;
	colorClassifier.setHueShift(hueShift);
	colorClassifiedImage = colorClassifier.classify(filteredImage);
	if (showColorsClassifiedImage) {
		showIndexedImage(colorClassifiedImage);
	}

	segmentation.extractAllSegments(colorClassifiedImage);

	log_dbg("segments found: %d\n", segmentation.segments.size());

	sizeFilter.minArea = 100;
	sizeFilter.maxArea = image.size().width * image.size().width / 9;
	sizeFilter.filter(segmentation.segments);

	if (log_dbg_enabled) {
		int i = 0;
		for (list<Segment>::iterator it = segmentation.segments.begin(); it != segmentation.segments.begin(); ++it, ++i) {
			log_dbg("Size-Filtered %d: (%d, %d) M1: %g, M7: %g, colorClass: %d\n", i, it->getMassCenter().x, it->getMassCenter().y,
					it->getInvariants().M1, it->getInvariants().M7, it->getColorClass());
		}
	}

	ImageInvariants min(0.162, -INFINITY, -INFINITY, -INFINITY, -INFINITY, -INFINITY, 6.5e-3);
	ImageInvariants max(0.175, INFINITY, INFINITY, INFINITY, INFINITY, INFINITY, 7.5e-3);

	shapeFilter.min = min;
	shapeFilter.max = max;

	shapeFilter.filter(segmentation.segments);

	log_dbg("filtered segments: %d\n", segmentation.segments.size());

	if (showSegments) {
		int i = 0;
		for (std::list<Segment>::const_iterator it = segmentation.segments.begin(); it != segmentation.segments.end(); ++it, ++i) {
			char txt[123];
			sprintf(txt, "Segment %d", i);
			namedWindow(txt, CV_WINDOW_AUTOSIZE);
			imshow(txt, it->getImage());
			log("%s: M1: %g, M7: %g, colorClass: %d\n", txt, it->getInvariants().M1, it->getInvariants().M7, it->getColorClass());
		}
	}
	walls = pattern.findCube(segmentation.segments);

	return walls.size() > 0;
}

void RubiksCubeLocalizator::showIndexedImage(const cv::Mat& indexedImage)
{
	classifiedRgb.create(indexedImage.size(), CV_8UC3);

	const vector<ColorDefinition> & colors = colorClassifier.getColors();

	split(classifiedRgb, classifiedRgbPlanes);

	int w = indexedImage.size().width;
	int h = indexedImage.size().height;
	for (int y = 0; y < h; ++y) {
		for (int x = 0; x < w; ++x) {
			int colorClass = indexedImage.at<int> (y, x);
			classifiedRgbPlanes[0].at<uchar> (y, x) = 0;
			classifiedRgbPlanes[1].at<uchar> (y, x) = 0;
			classifiedRgbPlanes[2].at<uchar> (y, x) = 0;
			for (int i = 0; i < colors.size(); ++i) {
				if (1 << i == colorClass) {
					classifiedRgbPlanes[0].at<uchar> (y, x) = colors[i].b;
					classifiedRgbPlanes[1].at<uchar> (y, x) = colors[i].g;
					classifiedRgbPlanes[2].at<uchar> (y, x) = colors[i].r;
				}
			}
		}
	}

	merge(classifiedRgbPlanes, classifiedRgb);
	imshow("colorsClassified", classifiedRgb);
}
