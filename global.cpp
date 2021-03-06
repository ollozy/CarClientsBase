#include "global.h"

#include <cctype>
#include <cstring>

namespace app_global {

int numberOfLetters(const char *data)
{
    int strlen = 0;
    for(int i = 0; data[i] != '\0'; ++i) {
        if(i % 2 == 0
                || std::isalnum(data[i])
                || std::ispunct(data[i])
                || std::isspace(data[i]))
            strlen += 1;
    }
    return strlen;
}

int realFilledStringSize(const char *data, int destLen, int maxLen)
{
    if(maxLen < 0)
        maxLen = destLen;
    int strlen = 0;
    int numOfLet = 0;
    for(int i = 0; data[i] != '\0'; ++i) {
        if(i % 2 == 0
                && !std::isalnum(data[i])
                && !std::ispunct(data[i])
                && !std::isspace(data[i])) {
            strlen += 2;
        }
        else if(std::isalnum(data[i])
                || std::ispunct(data[i])
                || std::isspace(data[i])) {
            strlen += 1;
        }
        else
            continue;
        ++numOfLet;
        if(numOfLet >= maxLen)
            break;
    }
    return destLen < numOfLet ? strlen : destLen - numOfLet + strlen;
}

}
