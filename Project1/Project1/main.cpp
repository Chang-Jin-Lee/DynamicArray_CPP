#include <iostream>
#include <functional>
#include "DynamicArray.hpp"
#include "windows.h"

using dataType = int;
constexpr int testSize = 1000;

LARGE_INTEGER timer, start, end;
float deltaTime1 = 0;
float deltaTime2 = 0;

void eraseFunction(DynamicArray<dataType>& arr)
{
	for (int i = 0; i < testSize; i++)
	{
		arr.erase(0);
	}
}

void erase_unorderedFunction(DynamicArray<dataType>& arr)
{
	for (int i = 0; i < testSize; i++)
	{
		arr.erase_unordered(0);
	}
}

float TestFunction(DynamicArray<dataType>& arr, std::function<void(DynamicArray<dataType>&)> f)
{
	for (int i = 0; i < testSize; i++)
	{
		arr.push_back(2000);
	}

	QueryPerformanceCounter(&start);
	f(arr);
	QueryPerformanceCounter(&end);

	return (float)(end.QuadPart - start.QuadPart) / timer.QuadPart;
}


int main()
{
	QueryPerformanceFrequency(&timer);

	DynamicArray<dataType> arr;

	deltaTime1 = TestFunction(arr, eraseFunction);
	deltaTime2 = TestFunction(arr, erase_unorderedFunction);

	std::cout << "\neraseFunction<dataType>(arr) : " << deltaTime1 << " microseconds\n\n";
	std::cout << "erase_unorderedFunction<dataType>(arr) : " << deltaTime2 << " microseconds\n\n";
	std::cout << "unordered가 " << deltaTime1 - deltaTime2 << " microseconds 만큼 빠릅니다.\n";
}