#pragma once

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

// visual sort class
class VisualSort
{
private:
	std::vector<Rectangle> rectangles;
	ShaderManager shaderManager;
	unsigned int modelLoc;
public:
	int arrayToBeSorted[4000];
	VisualSort();
	~VisualSort();
	void generateRandomArray();
	void createRectangles();
	void bubbleSort();
	void selectionSort();
	void insertionSort();
	void mergeSort(int l, int r);
	void merge(int l, int m, int r);
	void quickSort(int low, int high);
	void drawRectangles();
	void updateRectangles();
	void resetRectangles();
	void swap(Rectangle& a, Rectangle& b);
	void swap(int& a, int& b);
	void printArray();
};

#endif // VISUALSORT_H
