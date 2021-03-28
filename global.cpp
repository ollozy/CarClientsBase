#include "global.h"

#include <iostream>
#include <cctype>

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

void clearConsole()
{
#ifdef unix
    system("clear");
#elif
    system("cls");
#endif
}

bool textSearch(const char *key, const char *text)
{
    int dataLen = std::strlen(text);
    int keyLen = std::strlen(key);

    if(keyLen > dataLen)
        return false;

    else if(keyLen == dataLen)
        return std::strncmp(text, key, dataLen) == 0;

    const char *dataPtr = text;
    for(int i = 0; i < dataLen - keyLen + 1; ++i, ++dataPtr) {
        if(std::strncmp(dataPtr, key, keyLen) == 0)
            return true;
    }
    return false;
}

}
