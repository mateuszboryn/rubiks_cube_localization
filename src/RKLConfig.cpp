/*
 * RKLConfig.cpp
 *
 *  Created on: 2010-05-30
 *      Author: mateusz
 */

#include <cstdio>
#include <stdexcept>

#include "RKLConfig.h"

using namespace std;

RKLConfig::RKLConfig()
{
}

RKLConfig::~RKLConfig()
{
}

void RKLConfig::readConfig(const std::string& filename)
{
	const int linesize=256;
	char line[linesize];
	FILE *fp;
	if ((fp = fopen(filename.c_str(), "r")) == NULL) {
		throw runtime_error("I Can not open file \"" + filename + "\"");
	}

	while( fgets(line, linesize-1, fp) != NULL ){
		ColorDefinition cd(line);
		colors.push_back(cd);
	}

	fclose(fp);
}
