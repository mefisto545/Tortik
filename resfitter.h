#ifndef RESFITTER_H
#define RESFITTER_H

#define DEF_MAX_STEPS 1e2;
#define DEF_MIN_ERROR 1e-3;
#define DEF_STEP 0.5;

#include <vector>
#include "filedata.h"
#include <math.h>
#include <stack>
#include <iostream>

using namespace std;

class ResFitter
{
    int maxSteps;
    double minError;
    double step;
    vector<double> errors;
    vector<double> freq;
    vector<double> theta;
    vector<struct Resonance> resData;
    Resonance resonance;
    double params[4];
    FileData *file;

    double lorentz(double x, double y0, double yc, double xc, double w);
    double lorentz(double x, double *params);

    double lorentzDyc(double x, double xc, double w);
    double lorentzDyc(double x, double *params);

    double lorentzDxc(double x, double y0, double yc, double xc, double w);
    double lorentzDxc(double x, double *params);

    double lorentzDw(double x, double y0, double yc, double xc, double w);
    double lorentzDw(double x, double *params);

    double errorMSE(double *params);
    void gradDescentStep(double *params, double step);
    void gradDescent(double *params, double step);
    bool readDataFromStack(stack <struct Resonance> & stack);
    void findParams(double y0);

public:
    vector<struct Resonance> fittedData;
    /*ResFitter - method that perform fitting data with Lorentz peak function. The result of fitting writes in text files.
     * maxSteps - maximum number of steps that can be performed in gradient descend
     * minError - the minimum error level that will stop the descend
     * step - the value in gradient descend method  y1 = y0 - step*grad
     * file - element of class, that contain the fitting data*/
    ResFitter(double maxSteps, double minError, double step, FileData *file);

    void fitData(stack <struct Resonance> &stack, const vector<double> &baseline);
};

#endif // RESFITTER_H
