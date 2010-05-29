/*
 * RubiksCubeLocalizator.cpp
 *
 *  Created on: 2010-05-30
 *      Author: mateusz
 */

#include <highgui.h>

#include "RubiksCubeLocalizator.h"

RubiksCubeLocalizator::RubiksCubeLocalizator() :
	filteredImage(NULL), binaryImage(NULL), segmentedImage(NULL)
{

}

RubiksCubeLocalizator::~RubiksCubeLocalizator()
{
	cvReleaseImage(&filteredImage);
	cvReleaseImage(&binaryImage);
	cvReleaseImage(&segmentedImage);
}

bool RubiksCubeLocalizator::locateCube(IplImage *image)
{
	doFiltering(image);
	cvNamedWindow("filteredImage");
	cvShowImage("filteredImage", filteredImage);

	/*doBinarization(filteredImage);
	cvNamedWindow("binaryImage");
	cvShowImage("binaryImage", binaryImage);

	doBinarization(binaryImage);
	cvNamedWindow("segmentedImage");
	cvShowImage("segmentedImage", segmentedImage);*/
	return false;
}

void RubiksCubeLocalizator::doFiltering(IplImage *image)
{
	filteredImage = cvCreateImage(cvGetSize(image), image->depth, image->nChannels);
	cvSmooth(image, filteredImage, CV_MEDIAN);
}

void RubiksCubeLocalizator::doBinarization(IplImage *image)
{
	/*IplImage* hsv = cvCreateImage(cvGetSize(image), image->depth, image->nChannels);
	cvCvtColor(image, hsv, CV_BGR2H)*/
}

void RubiksCubeLocalizator::doSegmentation(IplImage *image)
{
}
