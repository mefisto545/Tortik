#include <iostream>
#include <stack>
#include <vector>

using namespace std;

inline static double median(double f,double k, double y0)
{
    return f*k + y0;
}

struct AB
{
    int a;
    int b;
};

int main()
{
    int i=0;
    stack <struct AB> Stack;
    double k, y0;
    struct AB ab;
    double trigg;
    vector <double> y;
    vector <double> x;
    bool END = false;
    while(!END)
    {
        if(y[i] > median(x[i], k, y0) + trigg) //check for antiresonance
        {
            if(y[i+1] > median(x[i], k, y0) + trigg) //check for non-one-point resonance
                if(y[i-1] > median(x[i], k, y0) + trigg) //check that previous point is not a resonance
                    ab.a = i - 1;
                else
                {
                    while(y[i+1] > median(x[i+1], k, y0) + trigg)//go to the end of current antiresonance
                        i++;
                    if(y[i+1] < median(x[i+1], k, y0) - trigg)//check that next point is not a resonance
                        ab.b = i;
                    else
                        ab.b = i + 1;
                }
            else
                if(y[i-1] < median(x[i], k, y0) - trigg || y[i+1] < median(x[i], k, y0) - trigg)//check for "bad" one-point antiresonance
                    ab.a = ab.b = i;
                else
                {
                    ab.a=i-1;
                    while(y[i] > median(x[i], k, y0) + trigg)//go to the end of current antiresonance
                        i++;
                    if(y[i] < median(x[i], k, y0) - trigg)//check that next point is not a resonance
                        ab.b = i - 1;
                    else
                        ab.b = i;
                }
        Stack.push(ab);
        }

        if(y[i] < median(x[i], k, y0) - trigg) //check for resonance
        {
            if(y[i+1] < median(x[i], k, y0) - trigg) //check for non-one-point resonance
                if(y[i-1] < median(x[i], k, y0) - trigg) //check that previous point is not a antiresonance
                    ab.a = i - 1;
                else
                {
                    while(y[i+1] < median(x[i+1], k, y0) - trigg)//go to the end of current resonance
                        i++;
                    if(y[i+1] > median(x[i+1], k, y0) + trigg)//check that next point is not a antiresonance
                        ab.b = i;
                    else
                        ab.b = i + 1;
                }
            else
                if(y[i-1] > median(x[i], k, y0) + trigg || y[i+1] > median(x[i], k, y0) + trigg)//check for "bad" one-point resonance
                    ab.a = ab.b = i;
                else
                {
                    ab.a=i-1;
                    while(y[i] < median(x[i], k, y0) - trigg)//go to the end of current resonance
                        i++;
                    if(y[i] > median(x[i], k, y0) + trigg)//check that next point is not a antiresonance
                        ab.b = i - 1;
                    else
                        ab.b = i;
                }
        Stack.push(ab);
        }
        i++;
    }
}
