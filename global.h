#ifndef APP_GLOBAL_H
#define APP_GLOBAL_H

#include <cassert>

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

const int numberMaxLen = 13;
const int brandMaxLen = 100;
const int colorMaxLen = 100;
const int yearMaxLen = 100;
const int availableMaxLen = 100;

};

int numberOfLetters(const char *data);
int realFilledStringSize(const char *data, int destLen, int maxLen = -1);

};

#endif // APP_GLOBAL_H
