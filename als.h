#ifndef ALS_H
#define ALS_H
#include "als.cpp"

void als(cp in, cp out, int N, double smooth, double p, int maxIter);
int mainals(vector<double>& baseline, double p, double smooth, int maxIter);

#endif // ALS_H
