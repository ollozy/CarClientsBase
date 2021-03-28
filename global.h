#ifndef APP_GLOBAL_H
#define APP_GLOBAL_H

#include <cassert>
#include <cstring>

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

template<typename Container, typename Iter, typename Pred>
void sort(Container &cont, Iter begin, Iter end, Pred pred)
{
    if(!begin.isValid() || !end.isValid() || !(begin < end))
        return;

    Iter temp;
    Iter left = begin;
    Iter right = end;
    Iter pivod = begin + (end - begin) / 2;     //так как списов поддерживается отсортированным при каждом добавлении
    while (left.isValid() && left < right) {

        while(pred(*left, *pivod) < 0)
            ++left;
        while(pred(*pivod, *right) < 0)
            --right;
        if(left < right && pred(*left, *right) != 0) {
            bool swapPivod = left == pivod;
            bool swapBegin = left == begin;
            bool swapEnd = right == end;
            cont.swap(left, right);
            temp = left;
            left = right;
            right = temp;
            if(swapPivod)
                pivod = left;
            if(swapBegin)
                begin = left;
            if(swapEnd)
                end = right;
        }
        if(pred(*left, *right) == 0 && left != right)
            ++left;
    }
    if(begin < end) {
        sort(cont, begin, pivod, pred);
        sort(cont, ++pivod, end, pred);
    }

}

};

#endif // APP_GLOBAL_H
