/*
 * ColorDefinition.cpp
 *
 *  Created on: 2010-06-08
 *      Author: mateusz
 */

#include <cstdio>
#include <stdexcept>

#include "ColorDefinition.h"

ColorDefinition::ColorDefinition(const std::string& definition)
{
	//	char name_txt[256];
	if (sscanf(definition.c_str(), "(%d, %d, %d) min0: %d, max0: %d, min1: %d, max1: %d, min2: %d, max2: %d", &r, &g, &b, &min0, &max0, &min1, &max1, &min2, &max2) != 9) {
		throw std::runtime_error("Zla definicja: \"" + definition + "\"");
	}
}

ColorDefinition::~ColorDefinition()
{
}
