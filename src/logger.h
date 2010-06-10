/*
 * logger.h
 *
 *  Created on: 2010-06-09
 *      Author: mateusz
 */

#ifndef LOGGER_H_
#define LOGGER_H_

/** Is log enabled*/
extern bool log_enabled, log_dbg_enabled;

void p(const char *fmt, ...);

/**
 * Print message to the console only if logEnabled is set to true.
 * @param fmt printf-like format
 */
void log(const char *fmt, ...);

/**
 * Print message to the console only if logDbgEnabled is set to true.
 * @param fmt printf-like format
 */
void log_dbg(const char *fmt, ...);

#endif /* LOGGER_H_ */
