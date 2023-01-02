

#include "Matrix4.h"

void releaseMatrix(Matrix4 a)
{
	delete[] a.data;
}

Matrix4::Matrix4(int width, int height, int n_width, int n_height, double *data)
{
	this->width = width;
	this->height = height;
	this->n_width = n_width;
	this->n_height = n_height;

	this->data = data;
}