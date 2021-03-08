#ifndef APP_GLOBAL_H
#define APP_GLOBAL_H

#include <cassert>

#include "./app_core/linklist.h"

namespace app_global {

const int dateLen = 11;
const int orderNumMaxLen = 3;

namespace client {

const int licenseMaxLen = 15;
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

void clearConsole();

bool textSearch(const char *key, const char *text);

template<typename Iter, typename Pred>
Iter find_if(Iter begin, Iter end, Pred predicat)
{
    while (begin != end) {
        if(predicat(*begin))
            return begin;
        ++begin;
    }
    return end;
}

};

#endif // APP_GLOBAL_H
