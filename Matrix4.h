

#pragma once

class Matrix4
{
public:
	int width;
	int height;
	int n_width; //neighborhood width
	int n_height; //neighborhood height
	
	double* data;	
	
	Matrix4(int width, int height, int n_width, int n_height, double* data);
	
	inline double operator ()(int w, int h, int nw, int nh) const
	{
		return data[width*height*( nh * n_width + nw) + h*width + w];
	}

	inline double& operator ()(int w, int h, int nw, int nh)
	{
		return data[width*height*( nh * n_width + nw) + h*width + w];
	}	
};