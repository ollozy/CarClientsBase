#ifndef APP_GLOBAL_H
#define APP_GLOBAL_H

#include <cassert>
#include <cctype>
#include <cstring>

typedef unsigned int uint;

namespace app_global {

const uint dateLen = 11;
const uint orderNumMaxLen = 3;

namespace client {

const uint licenseLen = 100;
const uint nameMaxLen = 100;
const uint passportMaxLen = 100;
const uint addressMaxLen = 100;

};

namespace car {

const uint numberMaxLen = 100;
const uint brandMaxLen = 100;
const uint colorMaxLen = 100;
const uint yearMaxLen = 100;
const uint availableMaxLen = 100;

};


int realStringSize(const char *data, int destLen);
int numberOfLetters(const char *data);

};

#endif // APP_GLOBAL_H
