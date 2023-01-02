

#pragma once

class Matrix
{
public:
	int width;
	int height;
	double* data;

	Matrix(void);
	Matrix(int width, int height, double* data);
	
	inline double operator ()(int w, int h) const
	{
		return data[h*width + w];
	}

	inline double& operator ()(int w, int h)
	{
		return data[h*width + w];
	}		
};