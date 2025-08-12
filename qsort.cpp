
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <functional> // std::less

// array generator for int/float T
template <typename T>
void gen(T* arr, const int size)
{
    srand(clock());
    for (T* i = arr; i < arr + size; ++i)
        *i = rand() % 10;
}

template <typename T>
void out(const T* arr, const int size)
{
    for (const T* i = arr; i < arr + size; ++i)
    {
        std::cout << *i << ' ';
        if (*i < 10) std::cout << ' ';
    }
    std::cout << '\n';
}

template <typename T, typename Compare>
bool check(const T* arr, const int size, Compare comp)
{
    for (const T* i = arr; i < arr + size - 1; ++i)
        if (comp(*(i + 1), *i))
            return false;
    return true;
}

template <typename T>
void swap(T &a, T &b)
{
    T tmp = a;
    a = b;
    b = tmp;
}

template <typename T, typename Compare>
void qSort(T* arr, const int start, const int end, Compare comp)
{
    if (start >= end) return;

    int l = start;
    int r = end;

    T pivot = arr[start + (end - start) / 2];

    while (l <= r)
    {
        while (comp(arr[l], pivot)) ++l;
        while (comp(pivot, arr[r])) --r;

        if (l <= r)
        {
            swap (arr[l], arr[r]);
            ++l;
            --r;
        }
    }

    qSort(arr, start, r, comp);
    qSort(arr, l, end, comp);
}


int main()
{
    const int size = 10;
    int* arr = new int[size]();

    gen(arr, size);
    out(arr, size);

    qSort(arr, 0, size - 1, std::less<int>());
    out(arr, size);

    if (!check(arr, size, std::less<int>())) return 1;
    
    return 0;
}
