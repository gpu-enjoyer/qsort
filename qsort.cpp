
#include <iostream>   // check result
#include <cstdlib>    // rand()
#include <ctime>      // rand() seed
#include <functional> // std::less
#include <thread>     // parallel
#include <cassert>    // unit tests

#define PAR_THRESH 100

// array generator for int/float T
template <typename T>
void gen(T* arr, const int size)
{
    srand(clock());
    for (T* i = arr; i < arr + size; ++i)
        *i = rand() % 10;
}

// output array
template <typename T>
void out(const T* arr, const int size)
{
    for (const T* i = arr; i < arr + size; ++i)
    {
        std::cout << *i << ' ';
        if (*i < 10) std::cout << ' ';
    }
    std::cout << "\n\n";
}

// check sort result
template <typename T, typename Compare>
bool check(const T* arr, const int size, Compare comp)
{
    for (const T* i = arr; i < arr + size - 1; ++i)
        if (comp(*(i + 1), *i))
            return false;
    return true;
}

// swap 2 elements
template <typename T>
void swap(T &a, T &b)
{
    T tmp = a;
    a = b;
    b = tmp;
}

// parallel quick sort
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

    if (r - start > PAR_THRESH && end - l > PAR_THRESH)
    {
        std::thread leftThread(qSort<T, Compare>, arr, start, r, comp);
        qSort(arr, l, end, comp);
        leftThread.join();
    }
    else
    {
        qSort(arr, start, r, comp);
        qSort(arr, l, end, comp);
    }
}


// tests
void runTests()
{
    // empty array
    {
        int arr[] = {};

        qSort(arr, 0, -1, std::less<int>());
        out(arr, 0);

        assert(check(arr, 0, std::less<int>()) && "empty array test fail");
    }

    // single element array
    {
        int arr[] = {1};

        qSort(arr, 0, 0, std::less<int>());
        out(arr, 1);

        assert(check(arr, 1, std::less<int>()) && "single element array test fail");
    }

    // float array
    {
        float arr[] = {1.1f, 5.5f, 0.2f};

        qSort(arr, 0, 3, std::less<float>());
        out(arr, 3);

        assert(check(arr, 3, std::less<float>()) && "float array test fail");
    }

    // int random array
    {
        const int size = 300;
        int* arr = new int[size];

        gen(arr, size);
        qSort(arr, 0, size - 1, std::less<int>());
        out(arr, size);

        assert(check(arr, size, std::less<int>()) && "int random array test fail");

        delete[] arr;
    }

    std::cout << "all tests passed \n"; 
}

int main()
{
    runTests();
    return 0;
}
