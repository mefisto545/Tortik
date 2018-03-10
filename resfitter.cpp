#include "resfitter.h"

ResFitter::ResFitter(double maxSteps, double minError, double step, FileData* file, double y0, double k)
{
    this->maxSteps = maxSteps;
    this->minError = minError;
    this->file = file;
    this->step = step;
    this->k = k;
    this->y0 = y0;
}

double ResFitter::lorentz(double x, double y0, double yc, double xc, double w)
{
    return y0 + (yc - y0) * pow(w, 2.0) / (4.0 * pow(x-xc, 2.0) + pow(w, 2.0));
}

double ResFitter::lorentz(double x, double *params)
{
    return ResFitter::lorentz(x, params[0], params[1], params[2], params[3]);
}

double ResFitter::lorentzDy0(double x, double xc, double w)
{
    return 1.0 / (1.0 + pow(w, 2.0) / (4.0 * pow(x - xc,2.0)));
}

double ResFitter::lorentzDy0(double x, double *params)
{
    double result = ResFitter::lorentzDy0(x, params[2], params[3]);
    return result;
}

double ResFitter::lorentzDyc(double x, double xc, double w)
{
    return 1.0 / (1.0 + 4.0 * pow(x - xc, 2.0) / pow(w, 2.0) );
}

double ResFitter::lorentzDyc(double x, double* params)
{
    return ResFitter::lorentzDyc(x, params[2], params[3]);
}

double ResFitter::lorentzDxc(double x, double y0, double yc, double xc, double w)
{
    return 8.0 * (yc - y0) * (x - xc) * pow(w, 2.0) / pow (4.0 * pow(x - xc, 2.0) + pow(w, 2.0), 2.0);
}

double ResFitter::lorentzDxc(double x, double *params)
{
    return ResFitter::lorentzDxc(x, params[0], params[1], params[2], params[3]);
}

double ResFitter::lorentzDw(double x, double y0, double yc, double xc, double w)
{
    return 8.0 * (yc - y0) * pow(x - xc, 2.0) * w / pow(4.0 * pow(x-xc, 2.0) + pow(w, 2.0), 2.0);
}

double ResFitter::lorentzDw(double x, double *params)
{
    return ResFitter::lorentzDw(x, params[0], params[1], params[2], params[3]);
}

double ResFitter::errorMSE(double *params)
{
    int size = freq.size();
    int i = 0;
    double sum = 0.0;
    for (i = 0; i < size; i++){
        sum += pow((theta[i] - lorentz(freq[i], params)), 2.0);
    }
    return sum / (double)size;
}

void ResFitter::gradDescentStep(double *params, double step)
{
    double dxc = 0.0, dw = 0.0, dyc = 0.0;
    int i, size = freq.size();
    for (i = 0; i < size; i ++)
    {
        dyc -= 2.0 * (theta[i] - ResFitter::lorentz(freq[i], params)) * ResFitter::lorentzDyc(freq[i], params) / (double) size;
        dxc -= 2.0 * (theta[i] - ResFitter::lorentz(freq[i], params)) * ResFitter::lorentzDxc(freq[i], params) / (double) size;
        dw -= 2.0 * (theta[i] - ResFitter::lorentz(freq[i], params)) * ResFitter::lorentzDw(freq[i], params) / (double) size;
    }
    double dParams[] = {0.0, step * dyc, step * dxc, step * dw};

    for (int i = 1; i < 4; i ++)
    {
        double newParam = params[i] - dParams[i];
        if (newParam > 0.0)
        {
            params[i] = newParam;
        }
    }
}

void ResFitter::gradDescent(double *params, double step)
{
    double locError = 1;
    int steps = 1;
    vector<double>().swap(errors);
    errors.push_back(ResFitter::errorMSE(params));
    while(steps < maxSteps && locError > minError)
    {
        gradDescentStep(params, step);
        locError = ResFitter::errorMSE(params);
        errors.push_back(locError);
        steps += 1;
    }
}

bool ResFitter::readDataFromStack(stack <struct Resonance> &st)
{
    vector<double>().swap(freq);
    vector<double>().swap(theta);

    if (!st.empty())
    {
        resonance = st.top();
        int s = resonance.a, f = resonance.b;
        for (int i = s; i <=f;i++)
        {
            freq.push_back(file->freqData[i]);
            theta.push_back(file->phaseData[i]);
        }
        st.pop();
    }
    else return false;
    return true;
}

void ResFitter::findParams()
{
    double sum = 0;
    int min = 0, i = 0, size = theta.size();
    for (i =0; i <size; i++)
    {
        sum += freq[i];
        if (theta[i] < theta[min]) min = i;
    }
    params[0] = y0 + freq[min] * k;
    params[1]= theta[min];
    params[2]= freq[min];
    params[3]= (freq.back() - freq[0]) / 2.0;
}

void ResFitter::fitData(stack <struct Resonance> &stack)
{
    ofstream ofile("FitResult.txt");
    ofile.close();
    while (ResFitter::readDataFromStack(stack))
    {
        findParams();
        ResFitter::gradDescent(this->params, step);

        /*Write fitting data to file*/
        vector<double> params;
        vector<double> lastError;
        vector<double> numberOfSteps;
        string names[] = {"Freq", "Theta", "Parameters(y0, yc, xc, width)", "MSE:", "NumberOfSteps"};

        params.insert(params.begin() , this->params , this->params + 4) ;
        lastError.push_back(errors.back());
        numberOfSteps.push_back(errors.size());
        vector<double> data[] = {freq, theta, params, lastError, numberOfSteps};

        file->writeRows("FitResult.txt" , names, data, 5);

        /*Write fitting data to stack*/
        Resonance fittedResonance;

        fittedResonance.a = resonance.a;
        fittedResonance.b = resonance.b;
        fittedResonance.mse = errors.back();
        fittedResonance.y0 = params[0];
        fittedResonance.yc = params[1];
        fittedResonance.xc = params[2];
        fittedResonance.width = params[3];
        fittedResonance.snr =resonance.snr;

        fittedData.push(fittedResonance);
    }
}
