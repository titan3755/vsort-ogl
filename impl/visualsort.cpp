#include <visualsort.h>

VisualSort::VisualSort(unsigned int mloc)
{
	this->modelLoc = mloc;
	generateSequentialArray();
	createRectangles();
	shuffleArray();
}

VisualSort::~VisualSort()
{
}

void VisualSort::generateSequentialArray()
{
	for (int i = 0; i < AMOUNT; i++) {
		arrayToBeSorted[i] = i;
	}
}

void VisualSort::shuffleArray()
{
	for (int i = 0; i < AMOUNT; i++)
	{
		int randomIndex = rand() % AMOUNT;
		swap(arrayToBeSorted[i], arrayToBeSorted[randomIndex]);
		swap(rectangles[i], rectangles[randomIndex]);
	}
}

void VisualSort::createRectangles()
{
	for (int i = 0; i < AMOUNT; i++)
	{
		// the rectangle positions must be within normalized device coordinates
		rectangles.emplace_back(glm::vec2(-1.0f + (2.0f / AMOUNT) * i, -2.0f), glm::vec2(0.04f, std::abs(arrayToBeSorted[i] * 0.0025f)), glm::vec3(0.0f, 0.0f, 0.0f));
	}
}

void VisualSort::bubbleSort()
{
	int n = AMOUNT;
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

void VisualSort::bubbleSortStep()
{
	static int i = 0;
	static int j = 0;
	int n = AMOUNT;
	if (i < n - 1)
	{
		if (j < n - i - 1)
		{
			if (arrayToBeSorted[j] > arrayToBeSorted[j + 1])
			{
				swap(arrayToBeSorted[j], arrayToBeSorted[j + 1]);
				swap(rectangles[j], rectangles[j + 1]);
			}
			j++;
		}
		else
		{
			i++;
			j = 0;
		}
	}
	else {
		i = 0;
		j = 0;
	}
}

void VisualSort::selectionSort()
{
	int n = AMOUNT;
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

void VisualSort::selectionSortStep()
{
	static int i = 0;
	static int j = 0;
	int n = AMOUNT;
	if (i < n - 1)
	{
		int min_idx = i;
		if (j < n)
		{
			if (arrayToBeSorted[j] < arrayToBeSorted[min_idx])
			{
				min_idx = j;
			}
			j++;
		}
		else
		{
			swap(arrayToBeSorted[min_idx], arrayToBeSorted[i]);
			swap(rectangles[min_idx], rectangles[i]);
			i++;
			j = i;
		}
	}
	else
	{
		i = 0;
		j = 0;
	}
}

void VisualSort::insertionSort()
{
	int n = AMOUNT;
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

void VisualSort::insertionSortStep()
{
	static int i = 1;
	static int j = 0;
	int n = AMOUNT;
	if (i < n)
	{
		int key = arrayToBeSorted[i];
		j = i - 1;
		while (j >= 0 && arrayToBeSorted[j] > key)
		{
			arrayToBeSorted[j + 1] = arrayToBeSorted[j];
			rectangles[j + 1] = rectangles[j];
			j = j - 1;
		}
		arrayToBeSorted[j + 1] = key;
		rectangles[j + 1] = rectangles[i];
		i++;
	}
	else
	{
		i = 1;
		j = 0;
	}
}

//void VisualSort::mergeSort(int l, int r)
//{
//	if (l < r)
//	{
//		int m = l + (r - l) / 2;
//		mergeSort(l, m);
//		mergeSort(m + 1, r);
//		merge(l, m, r);
//	}
//}

void VisualSort::swap(Rectangle& a, Rectangle& b)
{
	Rectangle temp = a;
	a = b;
	b = temp;
	a.resetModelAndSetPosition(glm::vec2(a.position.x, a.position.y), modelLoc);
	b.resetModelAndSetPosition(glm::vec2(b.position.x, b.position.y), modelLoc);
}

void VisualSort::swap(int& a, int& b)
{
	int temp = a;
	a = b;
	b = temp;
}

void VisualSort::printArray()
{
	for (int i = 0; i < AMOUNT; i++)
	{
		std::cout << arrayToBeSorted[i] << " ";
	}
	std::cout << std::endl;
}

void VisualSort::drawRectangles()
{
	for (int i = 0; i < AMOUNT; i++)
	{
		rectangles[i].draw(modelLoc);
	}
}

//void VisualSort::updateRectangles()
//{
//	for (int i = 0; i < AMOUNT; i++)
//	{
//		rectangles[i].update();
//	}
//}

//void VisualSort::resetRectangles()
//{
//	for (int i = 0; i < AMOUNT; i++)
//	{
//		rectangles[i].reset();
//	}
//}