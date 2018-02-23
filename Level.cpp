#include <iostream>
#include <string>
#include <stdlib.h>
#include <math.h>
#include <vector>

using namespace std;

inline static double sqr(double x)
{
    return x*x;
}

// n = number of data points
// x,y  = arrays of data
// *b = output intercept
// *m  = output slope
const int N = 1000000;

int linreg(int n, vector <double> x, vector <double> y, double* m, double* b)
{
    double   sumx = 0.0;                      /* sum of x     */
    double   sumx2 = 0.0;                     /* sum of x**2  */
    double   sumxy = 0.0;                     /* sum of x * y */
    double   sumy = 0.0;                      /* sum of y     */
    double   sumy2 = 0.0;                     /* sum of y**2  */

    for (int i=0;i<n;i++)
    {
        sumx  += x[i];
        sumx2 += sqr(x[i]);
        sumxy += x[i] * y[i];
        sumy  += y[i];
        sumy2 += sqr(y[i]);
    }

    double denom = (n * sumx2 - sqr(sumx));
    if (!denom)
        return 1;
    *m = (n * sumxy  -  sumx * sumy) / denom;
    *b = (sumy * sumx2  -  sumx * sumxy) / denom;
    return 0;
}

int main()
{
    int n = N;
    vector <double> x(N);
    vector <double> y(N);
    int i=0;
    for (i=0; i<N; i++)
        x[i]=y[i]=i;
    double m,b;
    linreg(n,x,y,&m,&b);
    cout << "m=" << m << " b=" << b << endl;
    return 0;
}
