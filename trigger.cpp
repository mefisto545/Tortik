#include "filedata.h"
#include <iostream>
using namespace std;

inline double median(double f,double k, double y0)
{
    return f*k + y0;
}

void trigger(vector <double> &x, vector <double> &y, double k, double y0, double trigg, int w,
             bool SNRmatter, double minSNR, stack <struct Resonance> *Stack)
{
    int i=1;
    struct Resonance resonance;
    double size = x.size();
    bool bad; //true means that this resonance/anti- is too close to another anti-/resonanse
    while(i < size-1)
    {
        if(y[i] > median(x[i], k, y0) + trigg) //check for antiresonance
        {
            if(y[i+1] > median(x[i], k, y0) + trigg) //check for non-one-point resonance
            {
                if(y[i-1] > median(x[i], k, y0) - trigg) //check that previous point is not a resonance
                {
                    resonance.a = i - 1;
                    bad = false;
                }
                else
                {
                    resonance.a = i;
                    bad = true;
                }
                while((y[i+1] > median(x[i+1], k, y0) + trigg)&&(i!=size-2))//go to the end of current antiresonance
                    i++;
                if((y[i+1] > median(x[i+1], k, y0) - trigg)&&(bad == false))//check that next point is not a resonance
                    resonance.b = i + 1;
                else
                    resonance.b = i;
            }
            else
                if(y[i-1] < median(x[i], k, y0) - trigg || y[i+1] < median(x[i], k, y0) - trigg)//check for "bad" one-point antiresonance
                    resonance.a = resonance.b = i;
                else
                {
                    resonance.a = i - 1;
                    resonance.b = i + 1;
                }
        resonance.snr = SNR(y, resonance.a, resonance.b, median(x[i], k, y0), trigg, w);
        if(SNRmatter == true)
        {
            if(resonance.snr > minSNR)
                Stack->push(resonance);
        }
        else
            Stack->push(resonance);
        }

        if(y[i] < median(x[i], k, y0) - trigg) //check for resonance
        {
            if(y[i+1] < median(x[i], k, y0) - trigg) //check for non-one-point resonance
            {
                if(y[i-1] < median(x[i], k, y0) + trigg) //check that previous point is not a antiresonance
                {
                    resonance.a = i - 1;
                    bad = false;
                }
                else
                {
                    resonance.a = i;
                    bad = true;
                }
                while((y[i+1] < median(x[i+1], k, y0) - trigg)&&(i!=size-2))//go to the end of current resonance
                    i++;
                if((y[i+1] < median(x[i+1], k, y0) + trigg)&&(bad == false))//check that next point is not a antiresonance
                    resonance.b = i + 1;
                else
                    resonance.b = i;
            }
            else
                if(y[i-1] > median(x[i], k, y0) + trigg || y[i+1] > median(x[i], k, y0) + trigg)//check for "bad" one-point resonance
                    resonance.a = resonance.b = i;
                else
                {
                    resonance.a = i - 1;
                    resonance.b = i + 1;
                }
        resonance.snr = SNR(y, resonance.a, resonance.b, median(x[i], k, y0), trigg, w);
        if(SNRmatter == true)
        {
            if(resonance.snr > minSNR)
                Stack->push(resonance);
        }
        else
            Stack->push(resonance);
        }
        i++;
    }
}
