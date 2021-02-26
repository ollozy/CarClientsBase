#ifndef APP_GLOBAL_H
#define APP_GLOBAL_H

#include <cassert>
#include <cctype>
#include <cstring>

namespace app_global {

const int dateLen = 11;
const int orderNumMaxLen = 3;

namespace client {

const int licenseLen = 100;
const int nameMaxLen = 100;
const int passportMaxLen = 100;
const int addressMaxLen = 100;

};

namespace car {

const int numberMaxLen = 100;
const int brandMaxLen = 100;
const int colorMaxLen = 100;
const int yearMaxLen = 100;
const int availableMaxLen = 100;

};


int realStringSize(const char *data, int destLen);
int numberOfLetters(const char *data);

};

#endif // APP_GLOBAL_H
