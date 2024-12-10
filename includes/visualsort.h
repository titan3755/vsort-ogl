#pragma once
#define GLM_ENABLE_EXPERIMENTAL
#include <shader_manager.h>
#include <rectangle.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>

#ifndef VISUALSORT_H
#define VISUALSORT_H

#define AMOUNT 4000

// visual sort class
class VisualSort
{
private:
	ShaderManager shaderManager;
	unsigned int modelLoc;
	bool reverse;
public:
	std::vector<Rectangle> rectangles;
	int arrayToBeSorted[AMOUNT];
	VisualSort(unsigned int mloc, int arry[AMOUNT]);
	~VisualSort();
	void debugInitialRectangleConfig();
	void generateSequentialArray();
	void shuffleArray();
	void createRectangles();
	void properlyPlaceRectangles();
	void bubbleSort();
	void bubbleSortStep();
	void selectionSort();
	void selectionSortStep();
	void insertionSort();
	void insertionSortStep();
	//void mergeSort(int l, int r);
	//void merge(int l, int m, int r);
	//void quickSort(int low, int high);
	void drawRectangles(unsigned int mloc);
	//void updateRectangles();
	//void resetRectangles();
	void swap(int a, int b);
	void swapArr(int& a, int& b);
	void printArray();
	bool getReverse();
	void setReverse(bool rev);
};

#endif // VISUALSORT_H
