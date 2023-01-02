

#include "mex.h"

#include <algorithm>
#include <cmath>
using namespace std;

#include "Matrix.h"
#include "Matrix3.h"

inline double non_zero(double x, double s_val)
{
    //if x is to close to zero, return s_val
    //otherwise return x
    
    double y = x;
    if ( 0 <= x && x < s_val ) y = s_val;
    if (-s_val < x < 0) y = - s_val;
    
    return y;
}

void brightness_transform(Matrix3 C, Matrix I)
{    
    double s_val = 1e-06; // a small value to avoid division by zero
    
    int nt = C.t;
   
    
    int dx2 = (3 - 1)/2;
    int dy2 = (3 - 1)/2;
	
	double b = 1.0/nt;
    
    for (int j = 0; j < I.height; j++)
    {
        for (int i = 0; i < I.width; i++)
        {
            //bool is_nan_of_inf = false;
            //compute the local mean
            double meanI = 0;
            for (int y = -dy2; y <= dy2; y++)
            {                
                int jpy = j + y;
                if (jpy < 0) jpy = 0;                    
                if (jpy > I.height - 1) jpy = I.height - 1;                               
                
                for (int x = -dx2; x <= dx2; x++)
                {                    
                    int ipx = i + x;
                    if (ipx < 0) ipx = 0;
                    if (ipx > I.width - 1) ipx = I.width - 1;                    
                    					
					meanI = meanI + b*I(ipx, jpy);
                    
                    //if (mxIsNaN(I(ipx, jpy)) || mxIsInf(I(ipx, jpy))) is_nan_of_inf = true;
                }
			}
			
			//local standard deviation
            double stdI = 0;
            for (int y = -dy2; y <= dy2; y++)
            {                
                int jpy = j + y;
                if (jpy < 0) jpy = 0;                    
                if (jpy > I.height - 1) jpy = I.height - 1;                               
                
                for (int x = -dx2; x <= dx2; x++)
                {                    
                    int ipx = i + x;
                    if (ipx < 0) ipx = 0;
                    if (ipx > I.width - 1) ipx = I.width - 1;                    
                    					
					double diff = non_zero(I(ipx, jpy) - meanI, s_val);
                
					stdI = stdI + b*diff*diff;
                }
			} 
			
			stdI = sqrt(stdI);
			
			//the correlation transform
			for (int y = -dy2; y <= dy2; y++)
            {                
                int jpy = j + y;
                if (jpy < 0) jpy = 0;                    
                if (jpy > I.height - 1) jpy = I.height - 1;                               
                
                for (int x = -dx2; x <= dx2; x++)
                {                    
                    int ipx = i + x;
                    if (ipx < 0) ipx = 0;
                    if (ipx > I.width - 1) ipx = I.width - 1;                    
                    										               
					double diff = non_zero(I(ipx, jpy) - meanI, s_val);
                    int temp = (x+dx2) * 3 + (y+dy2);
                    C(i, j, temp) = diff/stdI;
                   // C(i, j, x+dx2, y+dy2) = diff/stdI;
                    //if (is_nan_of_inf == false) C(i, j, x+dx2, y+dy2) = diff/stdI;
                    //else                 C(i, j, x+dx2, y+dy2) = sqrt(-1.0); //assign nan value
                }
			}
                        
        }
    }
    
}		
        
/* the gateway function */
void mexFunction( int nlhs, mxArray *plhs[],
        int nrhs, const mxArray *prhs[])
{
    if(nrhs != 2)
        mexErrMsgTxt("Two inputs required.");
    if(nlhs != 0)
        mexErrMsgTxt("No outputs required.");
    
    //get the inputs
    
    /*  get the dimensions of the matrix input data */
    //Warning: the dimension are inversed; width becames height after matlab's implicit transposition
    const int* dims_C = mxGetDimensions(prhs[0]);
    int width = (int) dims_C[0];
    int height = (int) dims_C[1];
    int dims_C_4_or_2 = (int) mxGetNumberOfDimensions(prhs[0]);
    int t = 1; //if the number of dimensions is 2, then n_width = 1;
    
    if (dims_C_4_or_2 == 3)
    {
        t = (int) dims_C[2];
          
    }
    
    /*  create the input structures */
    Matrix3 C(width, height, t, (double*) mxGetPr(prhs[0]));
    Matrix I(width, height, (double*) mxGetPr(prhs[1]));
    //the function updates the inputs; no outputs required
    
    /*  call the C subroutine */
    brightness_transform(C, I);
}