/*
 * ColorDefinition.h
 *
 *  Created on: 2010-06-08
 *      Author: mateusz
 */

#ifndef COLORDEFINITION_H_
#define COLORDEFINITION_H_

#include <string>

class ColorDefinition {
public:
	ColorDefinition(const std::string& definition);
	//ColorDefinition(const ColorDefinition & o);
	virtual ~ColorDefinition();

	//std::string name;
	//int rgbRepresentation;
	int min0, max0, min1, max1, min2, max2;
	int r,g,b;
protected:

};

#endif /* COLORDEFINITION_H_ */
