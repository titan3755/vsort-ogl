#include <visualsort.h>

VisualSort::VisualSort(unsigned int mloc, int arry[AMOUNT])
{
	std::copy(arry, arry + AMOUNT, this->arrayToBeSorted);
	this->modelLoc = mloc;
	this->reverse = true;
}

VisualSort::~VisualSort()
{
	for (int i = 0; i < AMOUNT; i++) {
		rectangles[i].deleteObj();
	}
}

void VisualSort::debugInitialRectangleConfig()
{
	rectangles.reserve(AMOUNT);
	for (int i = 0; i < AMOUNT; i++)
	{
		rectangles.emplace_back(glm::vec2(-1.0f + (2.0f / AMOUNT) * i, -1.0f), glm::vec2(0.01f, std::abs(i * 0.0005f)), glm::vec3(0.0f, 0.0f, 0.0f));
	}
	for (int i = 0; i < AMOUNT; i++)
	{
		rectangles[i].setupBuffers();
	}
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
		if (reverse && i + 1 < AMOUNT) {
			swap(i, i + 1);
		}
		else if (reverse && i + 1 == AMOUNT) {
			swap(i, i - 1);
		}
		else {
			swap(i, i - 1);
		}
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

void VisualSort::properlyPlaceRectangles()
{
	for (int i = 0; i < AMOUNT; i++)
	{
		rectangles[i].setScale(glm::vec2(0.04f, std::abs(arrayToBeSorted[i] * 0.0025f)));
		// centralize and normalize the rectangles
		rectangles[i].setPosition(glm::vec2(-1.0f + (2.0f / AMOUNT) * i, -2.0f));
		rectangles[i].resetModelAndSetPosition(glm::vec2(rectangles[i].position.x, rectangles[i].position.y), modelLoc);
	}
}

//void VisualSort::bubbleSort()
//{
//	int n = AMOUNT;
//	for (int i = 0; i < n - 1; i++)
//	{
//		for (int j = 0; j < n - i - 1; j++)
//		{
//			if (arrayToBeSorted[j] > arrayToBeSorted[j + 1])
//			{
//				swap(arrayToBeSorted[j], arrayToBeSorted[j + 1]);
//				swap(rectangles[j], rectangles[j + 1]);
//			}
//		}
//	}
//}
//
//void VisualSort::bubbleSortStep()
//{
//	static int i = 0;
//	static int j = 0;
//	int n = AMOUNT;
//	if (i < n - 1)
//	{
//		if (j < n - i - 1)
//		{
//			if (arrayToBeSorted[j] > arrayToBeSorted[j + 1])
//			{
//				swap(arrayToBeSorted[j], arrayToBeSorted[j + 1]);
//				swap(rectangles[j], rectangles[j + 1]);
//			}
//			j++;
//		}
//		else
//		{
//			i++;
//			j = 0;
//		}
//	}
//	else {
//		i = 0;
//		j = 0;
//	}
//}
//
//void VisualSort::selectionSort()
//{
//	int n = AMOUNT;
//	for (int i = 0; i < n - 1; i++)
//	{
//		int min_idx = i;
//		for (int j = i + 1; j < n; j++)
//		{
//			if (arrayToBeSorted[j] < arrayToBeSorted[min_idx])
//			{
//				min_idx = j;
//			}
//		}
//		swap(arrayToBeSorted[min_idx], arrayToBeSorted[i]);
//		swap(rectangles[min_idx], rectangles[i]);
//	}
//}
//
//void VisualSort::selectionSortStep()
//{
//	static int i = 0;
//	static int j = 0;
//	int n = AMOUNT;
//	if (i < n - 1)
//	{
//		int min_idx = i;
//		if (j < n)
//		{
//			if (arrayToBeSorted[j] < arrayToBeSorted[min_idx])
//			{
//				min_idx = j;
//			}
//			j++;
//		}
//		else
//		{
//			swap(arrayToBeSorted[min_idx], arrayToBeSorted[i]);
//			swap(rectangles[min_idx], rectangles[i]);
//			i++;
//			j = i;
//		}
//	}
//	else
//	{
//		i = 0;
//		j = 0;
//	}
//}

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

void VisualSort::swap(int a, int b)
{
	Rectangle temp = rectangles[a];
	this->rectangles[a] = rectangles[b];
	this->rectangles[b] = temp;
	this->rectangles[a].resetModelAndSetPosition(glm::vec2(rectangles[a].position.x, rectangles[a].position.y + 0.04f), modelLoc);
	this->rectangles[b].resetModelAndSetPosition(glm::vec2(rectangles[b].position.x, rectangles[b].position.y - 0.04f), modelLoc);
}

void VisualSort::swapArr(int& a, int& b)
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

void VisualSort::drawRectangles(unsigned int mloc)
{
	for (int i = 0; i < AMOUNT; i++)
	{
		rectangles[i].draw(mloc);
	}
}

bool VisualSort::getReverse()
{
	return reverse;
}

void VisualSort::setReverse(bool rev)
{
	this->reverse = rev;
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