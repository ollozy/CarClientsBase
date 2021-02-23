#ifndef APP_GLOBAL_H
#define APP_GLOBAL_H

#include <cassert>

typedef unsigned int uint;

namespace app_global {

const uint dateLen = 11;

namespace client {

const uint licenseLen = 15;
const uint nameMaxLen = 100;
const uint passportMaxLen = 100;
const uint addressMaxLen = 100;

};

namespace car {

const uint numberLen = 13;
const uint brandMaxLen = 100;
const uint colorMaxLen = 100;

};

};

#endif // APP_GLOBAL_H
