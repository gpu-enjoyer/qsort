
#include <iostream>
#include "stdlib.h"
#include "time.h"

void gen(int* arr, const int size)
{
    srand(clock());
    for (int* i = arr; i < arr + size; ++i)
        *i = rand() % 10;
}

void out(const int* arr, const int size)
{
    for (const int* i = arr; i < arr + size; ++i)
    {
        std::cout << *i << ' ';
        if (*i < 10) std::cout << ' ';
    }
    std::cout << '\n';
}

bool check(const int* arr, const int size)
{
    for (const int* i = arr; i < arr + size - 1; ++i)
        if (*i > *(i + 1))
            return false;
    return true;
}

void qsort(int* arr, const int size)
{
    // ...
    
    return;
}

int main()
{
    int size = 10;
    int* arr = new int[size]();

    out(arr, size);
    gen(arr, size);
    out(arr, size);
    
    return 0;
}
