

#include "Matrix.h"

void releaseMatrix(Matrix a)
{
	delete[] a.data;
}

Matrix::Matrix(int width, int height, double *data)
{
	this->width = width;
	this->height = height;
	this->data = data;
}