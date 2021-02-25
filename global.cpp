#include "global.h"

namespace app_global {

int realStringSize(const char *data, int destLen)
{
    int strlen = 0;
    for(int i = 0; data[i] != '\0'; ++i) {
        if(i % 2 == 0
                || std::isalnum(data[i])
                || std::ispunct(data[i])
                || std::isspace(data[i]))
            strlen += 1;
    }
    return std::strlen(data) + destLen - strlen;
}

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

}
