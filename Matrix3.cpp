

#include "Matrix3.h"

void releaseMatrix(Matrix3 a)
{
	delete[] a.data;
}

Matrix3::Matrix3(int width, int height, int t, double *data)
{
	this->width = width;
	this->height = height;
	//this->n_width = n_width;
	//this->n_height = n_height;
    this->t = t;
	this->data = data;
}