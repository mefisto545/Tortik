#include "resfitter.h"

ResFitter::ResFitter(double maxSteps, double minError, FileData* file)
{
    this->maxSteps = maxSteps;
    this->minError = minError;
    this->file = file;
    minNormDiff = DEF_MIN_NORM_DIFF;
}

vector<double> ResFitter::eigenSolver(const std::vector<double>& coeffA)
{
    if (coeffA.empty())
        return {};
    using namespace Eigen;
    VectorXd coeff =  VectorXd::Map(coeffA.data(), coeffA.size());

    Eigen::PolynomialSolver<double, Eigen::Dynamic> psolve(coeff);
    std::vector<double> realRoots;
    psolve.realRoots( realRoots );
    return realRoots;
}

vector<double> ResFitter::eigenSolverMonic(const std::vector<double>& coefficients)
{
    if (coefficients.empty())
        return {};

    std::vector<double> ceRev;
    std::copy(coefficients.rbegin(), coefficients.rend(), std::back_inserter(ceRev));
    ceRev.push_back(1.);
    return eigenSolver(ceRev);

}

int ResFitter::randInt()
{
    double sum_of_weight = 0.0;
    vector<double> weights;
    for(int i = 0; i < freq.size(); i++)
    {
        weights.push_back(abs(1/(theta[i]-params[0])));
    }
    for(int i = 0; i < weights.size(); i++) {
       sum_of_weight += weights[i];
    }
    double rnd = (double)(qrand()%((int)sum_of_weight + 1));
    for(int i = 0; i < weights.size(); i++) {
      if(rnd < weights[i])
        return i;
      rnd -= weights[i];
    }
    return weights.size()/2;
}

double ResFitter::findStep(double* initialParams, double* gradient, int numPoint)
{
    double y0 = initialParams[0], yc = initialParams[1], xc = initialParams[2], w = initialParams[3];
    double yc1 = gradient[1], xc1 = gradient[2], w1 = gradient[3];
    double coefs[8];
    vector<double> polyCoefs(7,0.0);
    vector <double> real_roots;
    int minCoef = 0;
    int error = 0;
    int order = 7;
    double xi = freq[numPoint], yi = theta[numPoint];
    //calculate the coefficients of polynomial eqation of first derivative of error function
    coefs[0] = 2*pow(w1,4.0)*pow(yc1,2.0)*(pow(w1,2.0) + 4*pow(xc1,2.0));
    coefs[1] = 2*pow(w1,2.0)*yc1*(-6*w*pow(w1,3.0)*yc1 - 8*w*w1*pow(xc1,2.0)*yc1 - pow(w1,4.0)*yc + pow(w1,4.0)*yi - 16*pow(w1,2.0)*xc*xc1*yc1 - 4*pow(w1,2.0)*pow(xc1,2.0)*y0 - 4*pow(w1,2.0)*pow(xc1,2.0)*yc + 8*pow(w1,2.0)*pow(xc1,2.0)*yi + 16*pow(w1,2.0)*xc1*xi*yc1 - 16*pow(xc1,4.0)*y0 + 16*pow(xc1,4.0)*yi);
    coefs[2] = 6*pow(w1,2.0)*yc1*(5*pow(w,2.0)*pow(w1,2.0)*yc1 + 2*w*pow(w1,3.0)*yc - 2*w*pow(w1,3.0)*yi + 16*w*w1*xc*xc1*yc1 + 8*w*w1*pow(xc1,2.0)*y0 - 8*w*w1*pow(xc1,2.0)*yi - 16*w*w1*xc1*xi*yc1 + 4*pow(w1,2.0)*pow(xc,2.0)*yc1 + 8*pow(w1,2.0)*xc*xc1*yc - 8*pow(w1,2.0)*xc*xc1*yi - 8*pow(w1,2.0)*xc*xi*yc1 - 8*pow(w1,2.0)*xc1*xi*yc + 8*pow(w1,2.0)*xc1*xi*yi + 4*pow(w1,2.0)*pow(xi,2.0)*yc1 + 32*xc*pow(xc1,3.0)*y0 - 32*xc*pow(xc1,3.0)*yi - 32*pow(xc1,3.0)*xi*y0 + 32*pow(xc1,3.0)*xi*yi);
    coefs[3] = -40*pow(w,3.0)*pow(w1,3.0)*pow(yc1,2.0) + 16*pow(w,3.0)*w1*pow(xc1,2.0)*pow(yc1,2.0) - 30*pow(w,2.0)*pow(w1,4.0)*yc*yc1 + 30*pow(w,2.0)*pow(w1,4.0)*yc1*yi - 96*pow(w,2.0)*pow(w1,2.0)*xc*xc1*pow(yc1,2.0) - 96*pow(w,2.0)*pow(w1,2.0)*pow(xc1,2.0)*y0*yc1 + 48*pow(w,2.0)*pow(w1,2.0)*pow(xc1,2.0)*yc*yc1 + 48*pow(w,2.0)*pow(w1,2.0)*pow(xc1,2.0)*yc1*yi + 96*pow(w,2.0)*pow(w1,2.0)*xc1*xi*pow(yc1,2.0) + 32*pow(w,2.0)*pow(xc1,4.0)*y0*yc1 - 32*pow(w,2.0)*pow(xc1,4.0)*yc1*yi - 80*w*pow(w1,3.0)*pow(xc,2.0)*pow(yc1,2.0) - 32*w*pow(w1,3.0)*xc*xc1*y0*yc1 - 128*w*pow(w1,3.0)*xc*xc1*yc*yc1 + 160*w*pow(w1,3.0)*xc*xc1*yc1*yi + 160*w*pow(w1,3.0)*xc*xi*pow(yc1,2.0) - 16*w*pow(w1,3.0)*pow(xc1,2.0)*y0*yc + 16*w*pow(w1,3.0)*pow(xc1,2.0)*y0*yi + 16*w*pow(w1,3.0)*pow(xc1,2.0)*pow(yc,2.0) - 16*w*pow(w1,3.0)*pow(xc1,2.0)*yc*yi + 32*w*pow(w1,3.0)*xc1*xi*y0*yc1 + 128*w*pow(w1,3.0)*xc1*xi*yc*yc1 - 160*w*pow(w1,3.0)*xc1*xi*yc1*yi - 80*w*pow(w1,3.0)*pow(xi,2.0)*pow(yc1,2.0) - 128*w*w1*xc*pow(xc1,3.0)*y0*yc1 + 128*w*w1*xc*pow(xc1,3.0)*yc1*yi - 64*w*w1*pow(xc1,4.0)*pow(y0,2.0) + 64*w*w1*pow(xc1,4.0)*y0*yc + 64*w*w1*pow(xc1,4.0)*y0*yi - 64*w*w1*pow(xc1,4.0)*yc*yi + 128*w*w1*pow(xc1,3.0)*xi*y0*yc1 - 128*w*w1*pow(xc1,3.0)*xi*yc1*yi + 8*pow(w1,4.0)*pow(xc,2.0)*y0*yc1 - 40*pow(w1,4.0)*pow(xc,2.0)*yc*yc1 + 32*pow(w1,4.0)*pow(xc,2.0)*yc1*yi + 16*pow(w1,4.0)*xc*xc1*y0*yc - 16*pow(w1,4.0)*xc*xc1*y0*yi - 16*pow(w1,4.0)*xc*xc1*pow(yc,2.0) + 16*pow(w1,4.0)*xc*xc1*yc*yi - 16*pow(w1,4.0)*xc*xi*y0*yc1 + 80*pow(w1,4.0)*xc*xi*yc*yc1 - 64*pow(w1,4.0)*xc*xi*yc1*yi - 16*pow(w1,4.0)*xc1*xi*y0*yc + 16*pow(w1,4.0)*xc1*xi*y0*yi + 16*pow(w1,4.0)*xc1*xi*pow(yc,2.0) - 16*pow(w1,4.0)*xc1*xi*yc*yi + 8*pow(w1,4.0)*pow(xi,2.0)*y0*yc1 - 40*pow(w1,4.0)*pow(xi,2.0)*yc*yc1 + 32*pow(w1,4.0)*pow(xi,2.0)*yc1*yi - 384*pow(w1,2.0)*pow(xc,2.0)*pow(xc1,2.0)*y0*yc1 + 384*pow(w1,2.0)*pow(xc,2.0)*pow(xc1,2.0)*yc1*yi + 64*pow(w1,2.0)*xc*pow(xc1,3.0)*pow(y0,2.0) - 64*pow(w1,2.0)*xc*pow(xc1,3.0)*y0*yc - 64*pow(w1,2.0)*xc*pow(xc1,3.0)*y0*yi + 64*pow(w1,2.0)*xc*pow(xc1,3.0)*yc*yi + 768*pow(w1,2.0)*xc*pow(xc1,2.0)*xi*y0*yc1 - 768*pow(w1,2.0)*xc*pow(xc1,2.0)*xi*yc1*yi - 64*pow(w1,2.0)*pow(xc1,3.0)*xi*pow(y0,2.0) + 64*pow(w1,2.0)*pow(xc1,3.0)*xi*y0*yc + 64*pow(w1,2.0)*pow(xc1,3.0)*xi*y0*yi - 64*pow(w1,2.0)*pow(xc1,3.0)*xi*yc*yi - 384*pow(w1,2.0)*pow(xc1,2.0)*pow(xi,2.0)*y0*yc1 + 384*pow(w1,2.0)*pow(xc1,2.0)*pow(xi,2.0)*yc1*yi;
    coefs[4] = 30*pow(w,4.0)*pow(w1,2.0)*pow(yc1,2.0) - 8*pow(w,4.0)*pow(xc1,2.0)*pow(yc1,2.0) + 40*pow(w,3.0)*pow(w1,3.0)*yc*yc1 - 40*pow(w,3.0)*pow(w1,3.0)*yc1*yi + 32*pow(w,3.0)*w1*xc*xc1*pow(yc1,2.0) + 80*pow(w,3.0)*w1*pow(xc1,2.0)*y0*yc1 - 64*pow(w,3.0)*w1*pow(xc1,2.0)*yc*yc1 - 16*pow(w,3.0)*w1*pow(xc1,2.0)*yc1*yi - 32*pow(w,3.0)*w1*xc1*xi*pow(yc1,2.0) + 96*pow(w,2.0)*pow(w1,2.0)*pow(xc,2.0)*pow(yc1,2.0) + 96*pow(w,2.0)*pow(w1,2.0)*xc*xc1*y0*yc1 + 96*pow(w,2.0)*pow(w1,2.0)*xc*xc1*yc*yc1 - 192*pow(w,2.0)*pow(w1,2.0)*xc*xc1*yc1*yi - 192*pow(w,2.0)*pow(w1,2.0)*xc*xi*pow(yc1,2.0) + 48*pow(w,2.0)*pow(w1,2.0)*pow(xc1,2.0)*y0*yc - 48*pow(w,2.0)*pow(w1,2.0)*pow(xc1,2.0)*y0*yi - 48*pow(w,2.0)*pow(w1,2.0)*pow(xc1,2.0)*pow(yc,2.0) + 48*pow(w,2.0)*pow(w1,2.0)*pow(xc1,2.0)*yc*yi - 96*pow(w,2.0)*pow(w1,2.0)*xc1*xi*y0*yc1 - 96*pow(w,2.0)*pow(w1,2.0)*xc1*xi*yc*yc1 + 192*pow(w,2.0)*pow(w1,2.0)*xc1*xi*yc1*yi + 96*pow(w,2.0)*pow(w1,2.0)*pow(xi,2.0)*pow(yc1,2.0) - 64*pow(w,2.0)*xc*pow(xc1,3.0)*y0*yc1 + 64*pow(w,2.0)*xc*pow(xc1,3.0)*yc1*yi + 64*pow(w,2.0)*pow(xc1,4.0)*pow(y0,2.0) - 64*pow(w,2.0)*pow(xc1,4.0)*y0*yc - 64*pow(w,2.0)*pow(xc1,4.0)*y0*yi + 64*pow(w,2.0)*pow(xc1,4.0)*yc*yi + 64*pow(w,2.0)*pow(xc1,3.0)*xi*y0*yc1 - 64*pow(w,2.0)*pow(xc1,3.0)*xi*yc1*yi - 16*w*pow(w1,3.0)*pow(xc,2.0)*y0*yc1 + 128*w*pow(w1,3.0)*pow(xc,2.0)*yc*yc1 - 112*w*pow(w1,3.0)*pow(xc,2.0)*yc1*yi - 32*w*pow(w1,3.0)*xc*xc1*y0*yc + 32*w*pow(w1,3.0)*xc*xc1*y0*yi + 32*w*pow(w1,3.0)*xc*xc1*pow(yc,2.0) - 32*w*pow(w1,3.0)*xc*xc1*yc*yi + 32*w*pow(w1,3.0)*xc*xi*y0*yc1 - 256*w*pow(w1,3.0)*xc*xi*yc*yc1 + 224*w*pow(w1,3.0)*xc*xi*yc1*yi + 32*w*pow(w1,3.0)*xc1*xi*y0*yc - 32*w*pow(w1,3.0)*xc1*xi*y0*yi - 32*w*pow(w1,3.0)*xc1*xi*pow(yc,2.0) + 32*w*pow(w1,3.0)*xc1*xi*yc*yi - 16*w*pow(w1,3.0)*pow(xi,2.0)*y0*yc1 + 128*w*pow(w1,3.0)*pow(xi,2.0)*yc*yc1 - 112*w*pow(w1,3.0)*pow(xi,2.0)*yc1*yi + 384*w*w1*pow(xc,2.0)*pow(xc1,2.0)*y0*yc1 - 384*w*w1*pow(xc,2.0)*pow(xc1,2.0)*yc1*yi + 128*w*w1*xc*pow(xc1,3.0)*pow(y0,2.0) - 128*w*w1*xc*pow(xc1,3.0)*y0*yc - 128*w*w1*xc*pow(xc1,3.0)*y0*yi + 128*w*w1*xc*pow(xc1,3.0)*yc*yi - 768*w*w1*xc*pow(xc1,2.0)*xi*y0*yc1 + 768*w*w1*xc*pow(xc1,2.0)*xi*yc1*yi - 128*w*w1*pow(xc1,3.0)*xi*pow(y0,2.0) + 128*w*w1*pow(xc1,3.0)*xi*y0*yc + 128*w*w1*pow(xc1,3.0)*xi*y0*yi - 128*w*w1*pow(xc1,3.0)*xi*yc*yi + 384*w*w1*pow(xc1,2.0)*pow(xi,2.0)*y0*yc1 - 384*w*w1*pow(xc1,2.0)*pow(xi,2.0)*yc1*yi - 16*pow(w1,4.0)*pow(xc,2.0)*y0*yc + 16*pow(w1,4.0)*pow(xc,2.0)*y0*yi + 16*pow(w1,4.0)*pow(xc,2.0)*pow(yc,2.0) - 16*pow(w1,4.0)*pow(xc,2.0)*yc*yi + 32*pow(w1,4.0)*xc*xi*y0*yc - 32*pow(w1,4.0)*xc*xi*y0*yi - 32*pow(w1,4.0)*xc*xi*pow(yc,2.0) + 32*pow(w1,4.0)*xc*xi*yc*yi - 16*pow(w1,4.0)*pow(xi,2.0)*y0*yc + 16*pow(w1,4.0)*pow(xi,2.0)*y0*yi + 16*pow(w1,4.0)*pow(xi,2.0)*pow(yc,2.0) - 16*pow(w1,4.0)*pow(xi,2.0)*yc*yi + 320*pow(w1,2.0)*pow(xc,3.0)*xc1*y0*yc1 - 320*pow(w1,2.0)*pow(xc,3.0)*xc1*yc1*yi - 192*pow(w1,2.0)*pow(xc,2.0)*pow(xc1,2.0)*pow(y0,2.0) + 192*pow(w1,2.0)*pow(xc,2.0)*pow(xc1,2.0)*y0*yc + 192*pow(w1,2.0)*pow(xc,2.0)*pow(xc1,2.0)*y0*yi - 192*pow(w1,2.0)*pow(xc,2.0)*pow(xc1,2.0)*yc*yi - 960*pow(w1,2.0)*pow(xc,2.0)*xc1*xi*y0*yc1 + 960*pow(w1,2.0)*pow(xc,2.0)*xc1*xi*yc1*yi + 384*pow(w1,2.0)*xc*pow(xc1,2.0)*xi*pow(y0,2.0) - 384*pow(w1,2.0)*xc*pow(xc1,2.0)*xi*y0*yc - 384*pow(w1,2.0)*xc*pow(xc1,2.0)*xi*y0*yi + 384*pow(w1,2.0)*xc*pow(xc1,2.0)*xi*yc*yi + 960*pow(w1,2.0)*xc*xc1*pow(xi,2.0)*y0*yc1 - 960*pow(w1,2.0)*xc*xc1*pow(xi,2.0)*yc1*yi - 192*pow(w1,2.0)*pow(xc1,2.0)*pow(xi,2.0)*pow(y0,2.0) + 192*pow(w1,2.0)*pow(xc1,2.0)*pow(xi,2.0)*y0*yc + 192*pow(w1,2.0)*pow(xc1,2.0)*pow(xi,2.0)*y0*yi - 192*pow(w1,2.0)*pow(xc1,2.0)*pow(xi,2.0)*yc*yi - 320*pow(w1,2.0)*xc1*pow(xi,3.0)*y0*yc1 + 320*pow(w1,2.0)*xc1*pow(xi,3.0)*yc1*yi;
    coefs[5] = -12*pow(w,5.0)*w1*pow(yc1,2.0) - 30*pow(w,4.0)*pow(w1,2.0)*yc*yc1 + 30*pow(w,4.0)*pow(w1,2.0)*yc1*yi - 24*pow(w,4.0)*pow(xc1,2.0)*y0*yc1 + 24*pow(w,4.0)*pow(xc1,2.0)*yc*yc1 - 48*pow(w,3.0)*w1*pow(xc,2.0)*pow(yc1,2.0) - 96*pow(w,3.0)*w1*xc*xc1*y0*yc1 + 96*pow(w,3.0)*w1*xc*xc1*yc1*yi + 96*pow(w,3.0)*w1*xc*xi*pow(yc1,2.0) - 48*pow(w,3.0)*w1*pow(xc1,2.0)*y0*yc + 48*pow(w,3.0)*w1*pow(xc1,2.0)*y0*yi + 48*pow(w,3.0)*w1*pow(xc1,2.0)*pow(yc,2.0) - 48*pow(w,3.0)*w1*pow(xc1,2.0)*yc*yi + 96*pow(w,3.0)*w1*xc1*xi*y0*yc1 - 96*pow(w,3.0)*w1*xc1*xi*yc1*yi - 48*pow(w,3.0)*w1*pow(xi,2.0)*pow(yc1,2.0) - 144*pow(w,2.0)*pow(w1,2.0)*pow(xc,2.0)*yc*yc1 + 144*pow(w,2.0)*pow(w1,2.0)*pow(xc,2.0)*yc1*yi + 288*pow(w,2.0)*pow(w1,2.0)*xc*xi*yc*yc1 - 288*pow(w,2.0)*pow(w1,2.0)*xc*xi*yc1*yi - 144*pow(w,2.0)*pow(w1,2.0)*pow(xi,2.0)*yc*yc1 + 144*pow(w,2.0)*pow(w1,2.0)*pow(xi,2.0)*yc1*yi - 192*pow(w,2.0)*xc*pow(xc1,3.0)*pow(y0,2.0) + 192*pow(w,2.0)*xc*pow(xc1,3.0)*y0*yc + 192*pow(w,2.0)*xc*pow(xc1,3.0)*y0*yi - 192*pow(w,2.0)*xc*pow(xc1,3.0)*yc*yi + 192*pow(w,2.0)*pow(xc1,3.0)*xi*pow(y0,2.0) - 192*pow(w,2.0)*pow(xc1,3.0)*xi*y0*yc - 192*pow(w,2.0)*pow(xc1,3.0)*xi*y0*yi + 192*pow(w,2.0)*pow(xc1,3.0)*xi*yc*yi + 48*w*pow(w1,3.0)*pow(xc,2.0)*y0*yc - 48*w*pow(w1,3.0)*pow(xc,2.0)*y0*yi - 48*w*pow(w1,3.0)*pow(xc,2.0)*pow(yc,2.0) + 48*w*pow(w1,3.0)*pow(xc,2.0)*yc*yi - 96*w*pow(w1,3.0)*xc*xi*y0*yc + 96*w*pow(w1,3.0)*xc*xi*y0*yi + 96*w*pow(w1,3.0)*xc*xi*pow(yc,2.0) - 96*w*pow(w1,3.0)*xc*xi*yc*yi + 48*w*pow(w1,3.0)*pow(xi,2.0)*y0*yc - 48*w*pow(w1,3.0)*pow(xi,2.0)*y0*yi - 48*w*pow(w1,3.0)*pow(xi,2.0)*pow(yc,2.0) + 48*w*pow(w1,3.0)*pow(xi,2.0)*yc*yi - 384*w*w1*pow(xc,3.0)*xc1*y0*yc1 + 384*w*w1*pow(xc,3.0)*xc1*yc1*yi + 1152*w*w1*pow(xc,2.0)*xc1*xi*y0*yc1 - 1152*w*w1*pow(xc,2.0)*xc1*xi*yc1*yi - 1152*w*w1*xc*xc1*pow(xi,2.0)*y0*yc1 + 1152*w*w1*xc*xc1*pow(xi,2.0)*yc1*yi + 384*w*w1*xc1*pow(xi,3.0)*y0*yc1 - 384*w*w1*xc1*pow(xi,3.0)*yc1*yi - 96*pow(w1,2.0)*pow(xc,4.0)*y0*yc1 + 96*pow(w1,2.0)*pow(xc,4.0)*yc1*yi + 192*pow(w1,2.0)*pow(xc,3.0)*xc1*pow(y0,2.0) - 192*pow(w1,2.0)*pow(xc,3.0)*xc1*y0*yc - 192*pow(w1,2.0)*pow(xc,3.0)*xc1*y0*yi + 192*pow(w1,2.0)*pow(xc,3.0)*xc1*yc*yi + 384*pow(w1,2.0)*pow(xc,3.0)*xi*y0*yc1 - 384*pow(w1,2.0)*pow(xc,3.0)*xi*yc1*yi - 576*pow(w1,2.0)*pow(xc,2.0)*xc1*xi*pow(y0,2.0) + 576*pow(w1,2.0)*pow(xc,2.0)*xc1*xi*y0*yc + 576*pow(w1,2.0)*pow(xc,2.0)*xc1*xi*y0*yi - 576*pow(w1,2.0)*pow(xc,2.0)*xc1*xi*yc*yi - 576*pow(w1,2.0)*pow(xc,2.0)*pow(xi,2.0)*y0*yc1 + 576*pow(w1,2.0)*pow(xc,2.0)*pow(xi,2.0)*yc1*yi + 576*pow(w1,2.0)*xc*xc1*pow(xi,2.0)*pow(y0,2.0) - 576*pow(w1,2.0)*xc*xc1*pow(xi,2.0)*y0*yc - 576*pow(w1,2.0)*xc*xc1*pow(xi,2.0)*y0*yi + 576*pow(w1,2.0)*xc*xc1*pow(xi,2.0)*yc*yi + 384*pow(w1,2.0)*xc*pow(xi,3.0)*y0*yc1 - 384*pow(w1,2.0)*xc*pow(xi,3.0)*yc1*yi - 192*pow(w1,2.0)*xc1*pow(xi,3.0)*pow(y0,2.0) + 192*pow(w1,2.0)*xc1*pow(xi,3.0)*y0*yc + 192*pow(w1,2.0)*xc1*pow(xi,3.0)*y0*yi - 192*pow(w1,2.0)*xc1*pow(xi,3.0)*yc*yi - 96*pow(w1,2.0)*pow(xi,4.0)*y0*yc1 + 96*pow(w1,2.0)*pow(xi,4.0)*yc1*yi;
    coefs[6] = 2*pow(w,6.0)*pow(yc1,2.0) + 12*pow(w,5.0)*w1*yc*yc1 - 12*pow(w,5.0)*w1*yc1*yi + 8*pow(w,4.0)*pow(xc,2.0)*pow(yc1,2.0) + 32*pow(w,4.0)*xc*xc1*y0*yc1 - 16*pow(w,4.0)*xc*xc1*yc*yc1 - 16*pow(w,4.0)*xc*xc1*yc1*yi - 16*pow(w,4.0)*xc*xi*pow(yc1,2.0) + 16*pow(w,4.0)*pow(xc1,2.0)*y0*yc - 16*pow(w,4.0)*pow(xc1,2.0)*y0*yi - 16*pow(w,4.0)*pow(xc1,2.0)*pow(yc,2.0) + 16*pow(w,4.0)*pow(xc1,2.0)*yc*yi - 32*pow(w,4.0)*xc1*xi*y0*yc1 + 16*pow(w,4.0)*xc1*xi*yc*yc1 + 16*pow(w,4.0)*xc1*xi*yc1*yi + 8*pow(w,4.0)*pow(xi,2.0)*pow(yc1,2.0) + 16*pow(w,3.0)*w1*pow(xc,2.0)*y0*yc1 + 64*pow(w,3.0)*w1*pow(xc,2.0)*yc*yc1 - 80*pow(w,3.0)*w1*pow(xc,2.0)*yc1*yi + 32*pow(w,3.0)*w1*xc*xc1*y0*yc - 32*pow(w,3.0)*w1*xc*xc1*y0*yi - 32*pow(w,3.0)*w1*xc*xc1*pow(yc,2.0) + 32*pow(w,3.0)*w1*xc*xc1*yc*yi - 32*pow(w,3.0)*w1*xc*xi*y0*yc1 - 128*pow(w,3.0)*w1*xc*xi*yc*yc1 + 160*pow(w,3.0)*w1*xc*xi*yc1*yi - 32*pow(w,3.0)*w1*xc1*xi*y0*yc + 32*pow(w,3.0)*w1*xc1*xi*y0*yi + 32*pow(w,3.0)*w1*xc1*xi*pow(yc,2.0) - 32*pow(w,3.0)*w1*xc1*xi*yc*yi + 16*pow(w,3.0)*w1*pow(xi,2.0)*y0*yc1 + 64*pow(w,3.0)*w1*pow(xi,2.0)*yc*yc1 - 80*pow(w,3.0)*w1*pow(xi,2.0)*yc1*yi - 48*pow(w,2.0)*pow(w1,2.0)*pow(xc,2.0)*y0*yc + 48*pow(w,2.0)*pow(w1,2.0)*pow(xc,2.0)*y0*yi + 48*pow(w,2.0)*pow(w1,2.0)*pow(xc,2.0)*pow(yc,2.0) - 48*pow(w,2.0)*pow(w1,2.0)*pow(xc,2.0)*yc*yi + 96*pow(w,2.0)*pow(w1,2.0)*xc*xi*y0*yc - 96*pow(w,2.0)*pow(w1,2.0)*xc*xi*y0*yi - 96*pow(w,2.0)*pow(w1,2.0)*xc*xi*pow(yc,2.0) + 96*pow(w,2.0)*pow(w1,2.0)*xc*xi*yc*yi - 48*pow(w,2.0)*pow(w1,2.0)*pow(xi,2.0)*y0*yc + 48*pow(w,2.0)*pow(w1,2.0)*pow(xi,2.0)*y0*yi + 48*pow(w,2.0)*pow(w1,2.0)*pow(xi,2.0)*pow(yc,2.0) - 48*pow(w,2.0)*pow(w1,2.0)*pow(xi,2.0)*yc*yi + 64*pow(w,2.0)*pow(xc,3.0)*xc1*y0*yc1 - 64*pow(w,2.0)*pow(xc,3.0)*xc1*yc1*yi + 192*pow(w,2.0)*pow(xc,2.0)*pow(xc1,2.0)*pow(y0,2.0) - 192*pow(w,2.0)*pow(xc,2.0)*pow(xc1,2.0)*y0*yc - 192*pow(w,2.0)*pow(xc,2.0)*pow(xc1,2.0)*y0*yi + 192*pow(w,2.0)*pow(xc,2.0)*pow(xc1,2.0)*yc*yi - 192*pow(w,2.0)*pow(xc,2.0)*xc1*xi*y0*yc1 + 192*pow(w,2.0)*pow(xc,2.0)*xc1*xi*yc1*yi - 384*pow(w,2.0)*xc*pow(xc1,2.0)*xi*pow(y0,2.0) + 384*pow(w,2.0)*xc*pow(xc1,2.0)*xi*y0*yc + 384*pow(w,2.0)*xc*pow(xc1,2.0)*xi*y0*yi - 384*pow(w,2.0)*xc*pow(xc1,2.0)*xi*yc*yi + 192*pow(w,2.0)*xc*xc1*pow(xi,2.0)*y0*yc1 - 192*pow(w,2.0)*xc*xc1*pow(xi,2.0)*yc1*yi + 192*pow(w,2.0)*pow(xc1,2.0)*pow(xi,2.0)*pow(y0,2.0) - 192*pow(w,2.0)*pow(xc1,2.0)*pow(xi,2.0)*y0*yc - 192*pow(w,2.0)*pow(xc1,2.0)*pow(xi,2.0)*y0*yi + 192*pow(w,2.0)*pow(xc1,2.0)*pow(xi,2.0)*yc*yi - 64*pow(w,2.0)*xc1*pow(xi,3.0)*y0*yc1 + 64*pow(w,2.0)*xc1*pow(xi,3.0)*yc1*yi + 128*w*w1*pow(xc,4.0)*y0*yc1 - 128*w*w1*pow(xc,4.0)*yc1*yi - 128*w*w1*pow(xc,3.0)*xc1*pow(y0,2.0) + 128*w*w1*pow(xc,3.0)*xc1*y0*yc + 128*w*w1*pow(xc,3.0)*xc1*y0*yi - 128*w*w1*pow(xc,3.0)*xc1*yc*yi - 512*w*w1*pow(xc,3.0)*xi*y0*yc1 + 512*w*w1*pow(xc,3.0)*xi*yc1*yi + 384*w*w1*pow(xc,2.0)*xc1*xi*pow(y0,2.0) - 384*w*w1*pow(xc,2.0)*xc1*xi*y0*yc - 384*w*w1*pow(xc,2.0)*xc1*xi*y0*yi + 384*w*w1*pow(xc,2.0)*xc1*xi*yc*yi + 768*w*w1*pow(xc,2.0)*pow(xi,2.0)*y0*yc1 - 768*w*w1*pow(xc,2.0)*pow(xi,2.0)*yc1*yi - 384*w*w1*xc*xc1*pow(xi,2.0)*pow(y0,2.0) + 384*w*w1*xc*xc1*pow(xi,2.0)*y0*yc + 384*w*w1*xc*xc1*pow(xi,2.0)*y0*yi - 384*w*w1*xc*xc1*pow(xi,2.0)*yc*yi - 512*w*w1*xc*pow(xi,3.0)*y0*yc1 + 512*w*w1*xc*pow(xi,3.0)*yc1*yi + 128*w*w1*xc1*pow(xi,3.0)*pow(y0,2.0) - 128*w*w1*xc1*pow(xi,3.0)*y0*yc - 128*w*w1*xc1*pow(xi,3.0)*y0*yi + 128*w*w1*xc1*pow(xi,3.0)*yc*yi + 128*w*w1*pow(xi,4.0)*y0*yc1 - 128*w*w1*pow(xi,4.0)*yc1*yi - 64*pow(w1,2.0)*pow(xc,4.0)*pow(y0,2.0) + 64*pow(w1,2.0)*pow(xc,4.0)*y0*yc + 64*pow(w1,2.0)*pow(xc,4.0)*y0*yi - 64*pow(w1,2.0)*pow(xc,4.0)*yc*yi + 256*pow(w1,2.0)*pow(xc,3.0)*xi*pow(y0,2.0) - 256*pow(w1,2.0)*pow(xc,3.0)*xi*y0*yc - 256*pow(w1,2.0)*pow(xc,3.0)*xi*y0*yi + 256*pow(w1,2.0)*pow(xc,3.0)*xi*yc*yi - 384*pow(w1,2.0)*pow(xc,2.0)*pow(xi,2.0)*pow(y0,2.0) + 384*pow(w1,2.0)*pow(xc,2.0)*pow(xi,2.0)*y0*yc + 384*pow(w1,2.0)*pow(xc,2.0)*pow(xi,2.0)*y0*yi - 384*pow(w1,2.0)*pow(xc,2.0)*pow(xi,2.0)*yc*yi + 256*pow(w1,2.0)*xc*pow(xi,3.0)*pow(y0,2.0) - 256*pow(w1,2.0)*xc*pow(xi,3.0)*y0*yc - 256*pow(w1,2.0)*xc*pow(xi,3.0)*y0*yi + 256*pow(w1,2.0)*xc*pow(xi,3.0)*yc*yi - 64*pow(w1,2.0)*pow(xi,4.0)*pow(y0,2.0) + 64*pow(w1,2.0)*pow(xi,4.0)*y0*yc + 64*pow(w1,2.0)*pow(xi,4.0)*y0*yi - 64*pow(w1,2.0)*pow(xi,4.0)*yc*yi;
    coefs[7] = 2*w*(-pow(w,5.0)*yc*yc1 + pow(w,5.0)*yc1*yi - 4*pow(w,3.0)*pow(xc,2.0)*y0*yc1 - 4*pow(w,3.0)*pow(xc,2.0)*yc*yc1 + 8*pow(w,3.0)*pow(xc,2.0)*yc1*yi - 8*pow(w,3.0)*xc*xc1*y0*yc + 8*pow(w,3.0)*xc*xc1*y0*yi + 8*pow(w,3.0)*xc*xc1*pow(yc,2.0) - 8*pow(w,3.0)*xc*xc1*yc*yi + 8*pow(w,3.0)*xc*xi*y0*yc1 + 8*pow(w,3.0)*xc*xi*yc*yc1 - 16*pow(w,3.0)*xc*xi*yc1*yi + 8*pow(w,3.0)*xc1*xi*y0*yc - 8*pow(w,3.0)*xc1*xi*y0*yi - 8*pow(w,3.0)*xc1*xi*pow(yc,2.0) + 8*pow(w,3.0)*xc1*xi*yc*yi - 4*pow(w,3.0)*pow(xi,2.0)*y0*yc1 - 4*pow(w,3.0)*pow(xi,2.0)*yc*yc1 + 8*pow(w,3.0)*pow(xi,2.0)*yc1*yi + 8*pow(w,2.0)*w1*pow(xc,2.0)*y0*yc - 8*pow(w,2.0)*w1*pow(xc,2.0)*y0*yi - 8*pow(w,2.0)*w1*pow(xc,2.0)*pow(yc,2.0) + 8*pow(w,2.0)*w1*pow(xc,2.0)*yc*yi - 16*pow(w,2.0)*w1*xc*xi*y0*yc + 16*pow(w,2.0)*w1*xc*xi*y0*yi + 16*pow(w,2.0)*w1*xc*xi*pow(yc,2.0) - 16*pow(w,2.0)*w1*xc*xi*yc*yi + 8*pow(w,2.0)*w1*pow(xi,2.0)*y0*yc - 8*pow(w,2.0)*w1*pow(xi,2.0)*y0*yi - 8*pow(w,2.0)*w1*pow(xi,2.0)*pow(yc,2.0) + 8*pow(w,2.0)*w1*pow(xi,2.0)*yc*yi - 16*w*pow(xc,4.0)*y0*yc1 + 16*w*pow(xc,4.0)*yc1*yi - 32*w*pow(xc,3.0)*xc1*pow(y0,2.0) + 32*w*pow(xc,3.0)*xc1*y0*yc + 32*w*pow(xc,3.0)*xc1*y0*yi - 32*w*pow(xc,3.0)*xc1*yc*yi + 64*w*pow(xc,3.0)*xi*y0*yc1 - 64*w*pow(xc,3.0)*xi*yc1*yi + 96*w*pow(xc,2.0)*xc1*xi*pow(y0,2.0) - 96*w*pow(xc,2.0)*xc1*xi*y0*yc - 96*w*pow(xc,2.0)*xc1*xi*y0*yi + 96*w*pow(xc,2.0)*xc1*xi*yc*yi - 96*w*pow(xc,2.0)*pow(xi,2.0)*y0*yc1 + 96*w*pow(xc,2.0)*pow(xi,2.0)*yc1*yi - 96*w*xc*xc1*pow(xi,2.0)*pow(y0,2.0) + 96*w*xc*xc1*pow(xi,2.0)*y0*yc + 96*w*xc*xc1*pow(xi,2.0)*y0*yi - 96*w*xc*xc1*pow(xi,2.0)*yc*yi + 64*w*xc*pow(xi,3.0)*y0*yc1 - 64*w*xc*pow(xi,3.0)*yc1*yi + 32*w*xc1*pow(xi,3.0)*pow(y0,2.0) - 32*w*xc1*pow(xi,3.0)*y0*yc - 32*w*xc1*pow(xi,3.0)*y0*yi + 32*w*xc1*pow(xi,3.0)*yc*yi - 16*w*pow(xi,4.0)*y0*yc1 + 16*w*pow(xi,4.0)*yc1*yi + 32*w1*pow(xc,4.0)*pow(y0,2.0) - 32*w1*pow(xc,4.0)*y0*yc - 32*w1*pow(xc,4.0)*y0*yi + 32*w1*pow(xc,4.0)*yc*yi - 128*w1*pow(xc,3.0)*xi*pow(y0,2.0) + 128*w1*pow(xc,3.0)*xi*y0*yc + 128*w1*pow(xc,3.0)*xi*y0*yi - 128*w1*pow(xc,3.0)*xi*yc*yi + 192*w1*pow(xc,2.0)*pow(xi,2.0)*pow(y0,2.0) - 192*w1*pow(xc,2.0)*pow(xi,2.0)*y0*yc - 192*w1*pow(xc,2.0)*pow(xi,2.0)*y0*yi + 192*w1*pow(xc,2.0)*pow(xi,2.0)*yc*yi - 128*w1*xc*pow(xi,3.0)*pow(y0,2.0) + 128*w1*xc*pow(xi,3.0)*y0*yc + 128*w1*xc*pow(xi,3.0)*y0*yi - 128*w1*xc*pow(xi,3.0)*yc*yi + 32*w1*pow(xi,4.0)*pow(y0,2.0) - 32*w1*pow(xi,4.0)*y0*yc - 32*w1*pow(xi,4.0)*y0*yi + 32*w1*pow(xi,4.0)*yc*yi);
    //determine the order of polynomial
    for (int i = 0; i < 7; i++)
    {
        if (abs(coefs[i]) != 0.0)
        {
            order = i;
            break;
        }
    }
    //transform them to the monic polynomial coeffs
    for (int i=0; i < 7 - order;i++)
    {
        polyCoefs[i]=coefs[7-i]/coefs[order];
    }
    real_roots = ResFitter::eigenSolverMonic(polyCoefs);
    for (int i = 0; i < real_roots.size(); i ++)
    {
        double params[4];
        for (int k =0; k < 4; k++)
        {
            params[k] = initialParams[k] - gradient[k] * real_roots[i];
        }
        double locError = errorMSE(params);
        if (i == 0)
            error = locError;
        if (error > locError)
        {
            minCoef = i;
            error = locError;
        }
    }
    if (real_roots.size() > 0 && abs(real_roots[minCoef]) < 1.0)
    {
        return real_roots[minCoef];
    }   
    else return 0.0;
}

double ResFitter::lorentz(double x, double y0, double yc, double xc, double w)
{
    return y0 + (yc - y0) * pow(w, 2.0) / (4.0 * pow(x-xc, 2.0) + pow(w, 2.0));
}

double ResFitter::lorentz(double x, double *params)
{
    return ResFitter::lorentz(x, params[0], params[1], params[2], params[3]);
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

void ResFitter::stochGradDescentStep(double *params, int numPoint)
{
    double dxc = 0.0, dw = 0.0, dyc = 0.0; //components of gradient
    dyc = 2.0 * (theta[numPoint] - ResFitter::lorentz(freq[numPoint], params)) * ResFitter::lorentzDyc(freq[numPoint], params);
    dxc = 2.0 * (theta[numPoint] - ResFitter::lorentz(freq[numPoint], params)) * ResFitter::lorentzDxc(freq[numPoint], params);
    dw = 2.0 * (theta[numPoint] - ResFitter::lorentz(freq[numPoint], params)) * ResFitter::lorentzDw(freq[numPoint], params);
    double grad[] = {0.0, dyc, dxc, dw};
    double step = findStep(params, grad, numPoint);
    double dParams[] = {0.0, step * dyc, step * dxc, step * dw}; // gradient


    for (int i = 1; i < 4; i ++)
    {
        double newParam = params[i] - dParams[i];
        if (newParam > 0.0 || i ==1) // because yc can be lower than zero
        {
            params[i] = newParam;
        }
    }
}

void ResFitter::gradDescent()
{
    qsrand(228.0);
    double locError = 1;
    int steps = 1;
    double minLocalError = ResFitter::errorMSE(params);
    errors.push_back(ResFitter::errorMSE(params));
    double localParams[4];
    copy(params, params + 4, localParams);

    while(steps < maxSteps && locError > minError)
    {
        int numPoint = ResFitter::randInt();
        stochGradDescentStep(localParams, numPoint);
        locError = ResFitter::errorMSE(localParams);
        errors.push_back(locError);      
        steps += 1;
        if (locError < minLocalError)
        {
            minLocalError = locError;
            copy(localParams, localParams+4, params);
        }
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

void ResFitter::findInitialParams(double y0)
{
    double sum = 0;
    int min = 0, i = 0, size = theta.size();
    for (i =0; i <size; i++)
    {
        sum += freq[i];
        if (theta[i] < theta[min]) min = i;
    }
    double depth = abs(y0 - theta[min]);
    double right = -1, left = -1;
    for (int i = min; i < freq.size(); i++)
    {
        if (abs(theta[i]-y0) < 0.5 * depth)
        {
            right =freq[i] + (freq[i] - freq[i-1])*((y0+theta[min])/2.0 - theta[i])/(theta[i] - theta[i-1]);
            right = right - freq[min];
            break;
        }
    }
    for (int i = min; i > 0; i--)
    {
        if (abs(theta[i]-y0) < 0.5 * depth)
        {
            left = freq[i] + (freq[i] - freq[i-1])*((y0+theta[min])/2.0 - theta[i])/(theta[i] - theta[i-1]);
            left = freq[min] - left;
            break;
        }
    }
    //initial parameters for fit
    params[0] = y0;
    params[1]= theta[min];
    params[2]= freq[min];
    if (left > 0.0)
    {
        if (right > 0.0) params[3] = right + left;
        else params[3] = left * 2.0;
    }
    else if (right > 0.0)
    {
        params[3] = right * 2.0;
    }
    else
        params[3] = (freq.back() - freq[0]) / 2.0;
}

void ResFitter::fitData(stack <struct Resonance> &stack, const vector<double> &baseline)
{
    while (ResFitter::readDataFromStack(stack))
    {
        vector<double>().swap(errors);
        int numOfPoints = resonance.b - resonance.a + 1;
        findInitialParams(baseline[resonance.b]);
        if (numOfPoints > 6)
            ResFitter::gradDescent(); // if number of points in resonance > 4 make gradient descend method
        else if (numOfPoints > 1){
            errors.push_back(ResFitter::errorMSE(params)); // else just calculate the error
        }
        else
            errors.push_back(-1.0);

        /*Write fitting data to vector fittedData*/
        Resonance fittedResonance;

        fittedResonance.a = resonance.a;
        fittedResonance.b = resonance.b;
        fittedResonance.mse = errors.back();
        fittedResonance.y0 = params[0];
        fittedResonance.yc = params[1];
        fittedResonance.xc = params[2];
        fittedResonance.width = params[3];
        fittedResonance.snr =resonance.snr;

        fittedData.push_back(fittedResonance);
    }
}
