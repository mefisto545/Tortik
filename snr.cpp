#include <vector>

using namespace std;

double SNR(vector <double> &y, int a, int b, double median, double trigg, int w)
{
    double sig2x = 0, sig2w = 0;
    int nx = 0, nw = 0;
    //calculation of signal's zero-mean
    for(int i = a; i <= b; i++)
        if(!(y[i] < median + trigg && y[i] > median - trigg))
        {
            sig2x += (y[i] - median)*(y[i] - median);
            nx++;
        }
    //calculation of noise's zero-mean on the left
    for(int i = a - w; i < a; i++)
        if(i > 0 && y[i] < median + trigg && y[i] > median - trigg)
        {
            sig2w += (y[i] - median)*(y[i] - median);
            nw++;
        }
    //calculation of noise's zero-mean on the right
    for(unsigned int i = b + 1; i <= (unsigned int)(b + w); i++)
        if(i < y.size() && y[i] < median + trigg && y[i] > median - trigg)
        {
            sig2w += (y[i] - median)*(y[i] - median);
            nw++;
        }
    sig2x /= nx + 1;
    sig2w /= nw + 1;
    if (sig2w == 0)
        return -1;
    return sig2x / sig2w;
}
