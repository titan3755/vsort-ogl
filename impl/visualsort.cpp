#include <visualsort.h>

VisualSort::VisualSort()
{
	generateRandomArray();
	createRectangles();
}

VisualSort::~VisualSort()
{
}

void VisualSort::generateRandomArray()
{
	for (int i = 0; i < 4000; i++)
	{
		arrayToBeSorted[i] = rand() % 4000 + 1;
	}
}

void VisualSort::createRectangles()
{
	for (int i = 0; i < 4000; i++)
	{
		rectangles.emplace_back(glm::abs(glm::vec2(-1.0f + i * 0.0005f, 0.0f)), glm::vec2(0.04f, arrayToBeSorted[i]), glm::vec3(0.0f, 0.0f, 0.0f));
	}
}

void VisualSort::bubbleSort()
{
	int n = 4000;
	for (int i = 0; i < n - 1; i++)
	{
		for (int j = 0; j < n - i - 1; j++)
		{
			if (arrayToBeSorted[j] > arrayToBeSorted[j + 1])
			{
				swap(arrayToBeSorted[j], arrayToBeSorted[j + 1]);
				swap(rectangles[j], rectangles[j + 1]);
			}
		}
	}
}

void VisualSort::selectionSort()
{
	int n = 4000;
	for (int i = 0; i < n - 1; i++)
	{
		int min_idx = i;
		for (int j = i + 1; j < n; j++)
		{
			if (arrayToBeSorted[j] < arrayToBeSorted[min_idx])
			{
				min_idx = j;
			}
		}
		swap(arrayToBeSorted[min_idx], arrayToBeSorted[i]);
		swap(rectangles[min_idx], rectangles[i]);
	}
}

void VisualSort::insertionSort()
{
	int n = 4000;
	for (int i = 1; i < n; i++)
	{
		int key = arrayToBeSorted[i];
		int j = i - 1;
		while (j >= 0 && arrayToBeSorted[j] > key)
		{
			arrayToBeSorted[j + 1] = arrayToBeSorted[j];
			rectangles[j + 1] = rectangles[j];
			j = j - 1;
		}
		arrayToBeSorted[j + 1] = key;
		rectangles[j + 1] = rectangles[i];
	}
}

void VisualSort::mergeSort(int l, int r)
{
	if (l < r)
	{
		int m = l + (r - l) / 2;
		mergeSort(l, m);
		mergeSort(m + 1, r);
		merge(l, m, r);
	}
}

void VisualSort::swap(Rectangle& a, Rectangle& b)
{
	Rectangle temp = a;
	a = b;
	b = temp;
}

void VisualSort::swap(int& a, int& b)
{
	int temp = a;
	a = b;
	b = temp;
}

void VisualSort::printArray()
{
	for (int i = 0; i < 4000; i++)
	{
		std::cout << arrayToBeSorted[i] << " ";
	}
	std::cout << std::endl;
}

