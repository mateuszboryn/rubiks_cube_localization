/*
 * RKLConfig.h
 *
 *  Created on: 2010-05-30
 *      Author: mateusz
 */

#ifndef RKLCONFIG_H_
#define RKLCONFIG_H_

#include <string>
#include <vector>

#include "ColorDefinition.h"

class RKLConfig {
public:
	RKLConfig();
	virtual ~RKLConfig();

	void readConfig(const std::string& filename);

	std::vector<ColorDefinition> colors;
};

#endif /* RKLCONFIG_H_ */
