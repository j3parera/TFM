#ifndef LOGGER_H_
#define LOGGER_H_

#include "iostream"
#include "cmath"
#include "stdio.h"
#include "string"

using namespace std;

enum logtype {
	info, warning, error, progress
};

void consolelog(string, logtype, string);

#endif /* LOGGER_H_ */
