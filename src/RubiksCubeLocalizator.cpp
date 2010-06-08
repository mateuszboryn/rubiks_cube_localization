/*
 * RubiksCubeLocalizator.cpp
 *
 *  Created on: 2010-05-30
 *      Author: mateusz
 */

#include <cv.h>
#include <highgui.h>

#include "RubiksCubeLocalizator.h"

using namespace cv;

RubiksCubeLocalizator::RubiksCubeLocalizator()
{
}

RubiksCubeLocalizator::~RubiksCubeLocalizator()
{
}

bool RubiksCubeLocalizator::locateCube(Mat& image)
{
	Mat filteredImage;
	medianBlur(image, filteredImage, 3);
	namedWindow("filteredImage", CV_WINDOW_AUTOSIZE);
	imshow("filteredImage", filteredImage);

	//Mat binaryImage;
	doBinarization(filteredImage);
	/*cvNamedWindow("binaryImage");
	 cvShowImage("binaryImage", binaryImage);

	 doBinarization(binaryImage);
	 cvNamedWindow("segmentedImage");
	 cvShowImage("segmentedImage", segmentedImage);*/
	return false;
}
std::vector<boost::shared_ptr<Segment> > RubiksCubeLocalizator::segmentation(const cv::Mat& image)
{

}

cv::Mat RubiksCubeLocalizator::colorClassification(const cv::Mat& yCrCbImage)
{

}
