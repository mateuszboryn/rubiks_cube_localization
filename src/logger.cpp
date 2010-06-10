/*
 * logger.cpp
 *
 *  Created on: 2010-06-09
 *      Author: mateusz
 */

#include "logger.h"

#include <cstdio>
#include <cstdarg>

using namespace std;

bool log_enabled = true;
bool log_dbg_enabled = false;

void p(const char *fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);

	vfprintf(stdout, fmt, ap);
	fflush(stdout);
	va_end(ap);
}


void log(const char *fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);

	if (!log_enabled) {
		va_end(ap);
		return;
	}

	vfprintf(stdout, fmt, ap);
	fflush(stdout);
	va_end(ap);
}

void log_dbg(const char *fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);

	if (!log_dbg_enabled) {
		va_end(ap);
		return;
	}

	vfprintf(stdout, fmt, ap);
	fflush(stdout);
	va_end(ap);
}
