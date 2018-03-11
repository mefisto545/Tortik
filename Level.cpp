#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <vector>

using namespace std;

inline double median(double f,double k, double y0)
{
    return f*k + y0;
}
// n = number of data points
// x,y  = arrays of data
// *y0 = output intercept
// *k  = output slope

void level(vector <double> &x, vector <double> &y, double* k, double* y0, double trigg)
{
    double   sumx = 0.0;                      /* sum of x     */
    double   sumx2 = 0.0;                     /* sum of x**2  */
    double   sumxy = 0.0;                     /* sum of x * y */
    double   sumy = 0.0;                      /* sum of y     */
    double   sumy2 = 0.0;                     /* sum of y**2  */
    int size = x.size();
    int N = 0;
    if (*k == 0 && *y0 == 0)
    {
        for (int i=0; i < size; i++)
        {
            sumx  += x[i];
            sumx2 += x[i] * x[i];
            sumxy += x[i] * y[i];
            sumy  += y[i];
            sumy2 += y[i] * y[i];
        }
    }
    else
    {
        for (int i=0; i < size; i++)
        {
            if((y[i] > median(x[i], *k, *y0) - trigg) && (y[i] < median(x[i], *k, *y0) + trigg))
            {
                sumx  += x[i];
                sumx2 += x[i] * x[i];
                sumxy += x[i] * y[i];
                sumy  += y[i];
                sumy2 += y[i] * y[i];
                N++;
            }
        }
        size = N;
    }
    double denom = (size * sumx2 - sumx * sumx);
    if (denom == 0)
        abort();
    *k = (size * sumxy  -  sumx * sumy) / denom;
    *y0 = (sumy * sumx2  -  sumx * sumxy) / denom;
}
