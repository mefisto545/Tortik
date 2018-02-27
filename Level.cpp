#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <vector>

using namespace std;

// n = number of data points
// x,y  = arrays of data
// *b = output intercept
// *m  = output slope

void Level(vector <double> &x, vector <double> &y, double* m, double* b)
{
    double   sumx = 0.0;                      /* sum of x     */
    double   sumx2 = 0.0;                     /* sum of x**2  */
    double   sumxy = 0.0;                     /* sum of x * y */
    double   sumy = 0.0;                      /* sum of y     */
    double   sumy2 = 0.0;                     /* sum of y**2  */
    int size = x.size();
    for (int i=0; i < size; i++)
    {
        sumx  += x[i];
        sumx2 += x[i] * [i];
        sumxy += x[i] * y[i];
        sumy  += y[i];
        sumy2 += y[i] * y[i];
    }
    double denom = (size * sumx2 - sumx * sumx);
    *m = (size * sumxy  -  sumx * sumy) / denom;
    *b = (sumy * sumx2  -  sumx * sumxy) / denom;
}
