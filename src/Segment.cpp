/*
 * Segment.cpp
 *
 *  Created on: 2010-06-08
 *      Author: mateusz
 */

#include "Segment.h"

#include "logger.h"

using namespace cv;

ImageInvariants::ImageInvariants(double M1, double M2, double M3, double M4, double M5, double M6, double M7) :
	M1(M1), M2(M2), M3(M3), M4(M4), M5(M5), M6(M6), M7(M7)
{
}

bool ImageInvariants::operator<=(const ImageInvariants& o) const
{
	return M1 <= o.M1 && M2 <= o.M2 && M3 <= o.M3 && M4 <= o.M4 && M5 <= o.M5 && M6 <= o.M6 && M7 <= o.M7;
}

Segment::Segment(cv::Mat& image, int area, int colorClass /*, cv::Point leftUpperCorner, cv::Point rightLowerCorner*/) :
	//	image(image), area(area), leftUpperCorner(leftUpperCorner), rightLowerCorner(rightLowerCorner), invariantsCalculated(false)
			image(image), area(area), colorClass(colorClass), invariantsCalculated(false)
{
}

Segment::~Segment()
{
}

//cv::Rect Segment::getRect()
//{
//	return Rect(leftUpperCorner.x, leftUpperCorner.y, rightLowerCorner.x - leftUpperCorner.x, rightLowerCorner.y - rightLowerCorner.y);
//}

cv::Mat& Segment::getImage()
{
	return image;
}
const cv::Mat& Segment::getImage() const
{
	return image;
}

int Segment::getArea() const
{
	return area;
}

#define sqr(x) ((x)*(x))

void Segment::calculateMoments() const
{
	m = moments(image, 1);

	massCenter.x = m.m10 / m.m00;
	massCenter.y = m.m01 / m.m00;

	invariants.M1 = m.nu20 + m.nu02;
	invariants.M4 = sqr(m.nu30 + m.nu12) + sqr(m.nu21 + m.nu03);
	invariants.M7 = m.nu20 * m.nu02 - m.nu11 * m.nu11;

	invariantsCalculated = true;

	log("Segment::calculateMoments() color class %d:\n", colorClass);
//	log("    m00=%g m10=%g m01=%g m20=%g m11=%g m02=%g %g %g %g %g\n", m.m00, m.m10, m.m01, m.m20, m.m11, m.m02, m.m30, m.m21, m.m12, m.m03);
//	log("    area: %d (m00=%g)\n", area, m.m00);
	log("    (x0, y0) = (%d, %d)\n", massCenter.x, massCenter.y);
	log("    M1: %g, M4: %g, M7: %g\n", invariants.M1, invariants.M4, invariants.M7);
}

const ImageInvariants& Segment::getInvariants() const
{
	if (!invariantsCalculated) {
		calculateMoments();
	}
	return invariants;
}

const cv::Point& Segment::getMassCenter() const
{
	if (!invariantsCalculated) {
		calculateMoments();
	}
	return massCenter;
}

int Segment::getColorClass() const
{
	return colorClass;
}
