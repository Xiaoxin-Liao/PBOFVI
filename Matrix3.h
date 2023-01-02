

#pragma once

class Matrix3
{
public:
	int width;
	int height;
	//int n_width; //neighborhood width
	//int n_height; //neighborhood height
    int t;
	
	double* data;	
	
	Matrix3(int width, int height, int t, double* data);
	
	inline double operator ()(int w, int h, int t) const
	{
		return data[width*height*t + h*width + w];
	}

	inline double& operator ()(int w, int h, int t)
	{
		return data[width*height*t + h*width + w];
	}	
};