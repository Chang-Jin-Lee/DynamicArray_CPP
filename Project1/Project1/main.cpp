#include <iostream>
#include "DynamicArray.hpp"
#include "windows.h"

using dataType = int;
constexpr int testSize = 1000;

LARGE_INTEGER timer, start, end;
float deltaTime1 = 0;
float deltaTime2 = 0;

template <typename T>
void eraseFunction(DynamicArray<T>& arr)
{
	for (int i = 0; i < testSize; i++)
	{
		arr.erase(0);
	}
}

template <typename T>
void erase_unorderedFunction(DynamicArray<T>& arr)
{
	for (int i = 0; i < testSize; i++)
	{
		arr.erase_unordered(0);
	}
}

float Test_erase(DynamicArray<dataType>& arr)
{
	for (int i = 0; i < testSize; i++)
	{
		arr.push_back(2000);
	}

	QueryPerformanceCounter(&start);
	eraseFunction<dataType>(arr);
	QueryPerformanceCounter(&end);

	return (float)(end.QuadPart - start.QuadPart) / timer.QuadPart;
}

float Test_erase_unordered(DynamicArray<dataType>& arr)
{
	for (int i = 0; i < testSize; i++)
	{
		arr.push_back(2000);
	}

	QueryPerformanceCounter(&start);
	erase_unorderedFunction<dataType>(arr);
	QueryPerformanceCounter(&end);

	return (float)(end.QuadPart - start.QuadPart) / timer.QuadPart;
}


int main()
{
	QueryPerformanceFrequency(&timer);

	DynamicArray<dataType> arr;

	deltaTime1 = Test_erase(arr);
	deltaTime2 = Test_erase_unordered(arr);

	std::cout << "\neraseFunction<dataType>(arr) : " << deltaTime1 << " microseconds\n\n";
	std::cout << "erase_unorderedFunction<dataType>(arr) : " << deltaTime2 << " microseconds\n\n";
	std::cout << "unordered가 " << deltaTime1 - deltaTime2 << " microseconds 만큼 빠릅니다.\n";
}