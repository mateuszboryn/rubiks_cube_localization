/*
 * Segmentation.cpp
 *
 *  Created on: 2010-06-09
 *      Author: mateusz
 */

#include <stdexcept>
#include <stack>

#include "Segmentation.h"

using namespace std;
using namespace cv;

Segmentation::Segmentation()
{
}

Segmentation::~Segmentation()
{
}

void Segmentation::extractAllSegments(cv::Mat& image)
{
	segments.clear();
	if (image.type() != CV_32S) {
		throw runtime_error("Segmentation::segmentAllSegments(): image.type() != CV_32S");
	}

	int w = image.size().width;
	int h = image.size().height;
	for (int y = 0; y < h; ++y) {
		for (int x = 0; x < w; ++x) {
			int colorClass = image.at<int> (y, x);
			if (colorClass > 0) {
				segments.push_back(extractSegment(image, y, x, colorClass));
			}
		}
	}
}

Segment Segmentation::extractSegment(cv::Mat& image, int y, int x, int colorClass)
{
	int w = image.size().width - 1, h = image.size().height - 1;

	Mat extractedImage = Mat::zeros(image.size(), CV_8U);
	int area = 0;
//	segment.leftUpperCorner.x = segment.rightLowerCorner.x = x;
//	segment.leftUpperCorner.y = segment.rightLowerCorner.y = y;

	stack<Point> points;
	points.push(Point(x, y));
	image.at<int> (points.top()) = -colorClass;

	while (!points.empty()) {
		Point p = points.top();
		points.pop();

		extractedImage.at<uchar> (p) = 255;
		++area;
//		segment.leftUpperCorner.x = min(segment.leftUpperCorner.x, p.x);
//		segment.leftUpperCorner.y = min(segment.leftUpperCorner.y, p.y);
//
//		segment.rightLowerCorner.x = max(segment.rightLowerCorner.x, p.x);
//		segment.rightLowerCorner.y = max(segment.rightLowerCorner.y, p.y);

		if (p.x > 0) { // left
			Point newP(p.x - 1, p.y);
			if (image.at<int> (newP) == colorClass) {
				points.push(newP);
				image.at<int> (newP) = -colorClass;
			}
		}
		if (p.x > 0 && p.y > 0) { // left upper
			Point newP(p.x - 1, p.y - 1);
			if (image.at<int> (newP) == colorClass) {
				points.push(newP);
				image.at<int> (newP) = -colorClass;
			}
		}
		if (p.y > 0) { // upper
			Point newP(p.x, p.y - 1);
			if (image.at<int> (newP) == colorClass) {
				points.push(newP);
				image.at<int> (newP) = -colorClass;
			}
		}
		if (p.x < w && p.y > 0) { // right upper
			Point newP(p.x + 1, p.y - 1);
			if (image.at<int> (newP) == colorClass) {
				points.push(newP);
				image.at<int> (newP) = -colorClass;
			}
		}
		if (p.x < w) { // right
			Point newP(p.x + 1, p.y);
			if (image.at<int> (newP) == colorClass) {
				points.push(newP);
				image.at<int> (newP) = -colorClass;
			}
		}
		if (p.x < w && p.y < h) { // right lower
			Point newP(p.x + 1, p.y + 1);
			if (image.at<int> (newP) == colorClass) {
				points.push(newP);
				image.at<int> (newP) = -colorClass;
			}
		}
		if (p.y < h) { // lower
			Point newP(p.x, p.y + 1);
			if (image.at<int> (newP) == colorClass) {
				points.push(newP);
				image.at<int> (newP) = -colorClass;
			}
		}
		if (p.x > 0 && p.y < h) { // left lower
			Point newP(p.x - 1, p.y + 1);
			if (image.at<int> (newP) == colorClass) {
				points.push(newP);
				image.at<int> (newP) = -colorClass;
			}
		}
	}

	return Segment(extractedImage, area, colorClass);
}
