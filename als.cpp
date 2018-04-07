// Copyright (c) 2016, The Regents of the University of California (Regents).
// All rights reserved.

// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:

//    1. Redistributions of source code must retain the above copyright
//       notice, this list of conditions and the following disclaimer.

//    2. Redistributions in binary form must reproduce the above
//       copyright notice, this list of conditions and the following
//       disclaimer in the documentation and/or other materials provided
//       with the distribution.

//    3. Neither the name of the copyright holder nor the names of its
//       contributors may be used to endorse or promote products derived
//       from this software without specific prior written permission.

// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS AS IS
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.

// Please contact the author(s) of this library if you have any questions.
// Author: Michael Kellman   ( kellman@eecs.berkeley.edu )

#include <vector>
#include <iostream>
#include <stdlib.h>
#include "Libs/Eigen/Eigen/Eigen"
#include "Libs/Eigen/Eigen/Sparse"
#include "Libs/fftw-3.3.7/api/fftw3.h"
#include <time.h>
#include <memory>

using namespace Eigen;

typedef Triplet <double> T;
typedef SparseMatrix <double> SpMat;
typedef std::shared_ptr <fftw_complex> cp;
typedef Triplet <double> T;
using MyType_t = std::shared_ptr<int>;

using namespace std;

void als(cp in, cp out, int N, double smooth, double p, int maxIter)
{

    clock_t start;
    start = clock();

    // Initialize weights
    vector<T> weights;
    VectorXd vweights(N);
    VectorXd sig(N);
    weights.reserve(N);
    for (int ii = 0; ii < N; ++ii)
    {
        weights.push_back(T(ii,ii,1));
        vweights[ii] = 1;

        //setup the in vector
        sig[ii] = in.get()[ii][0];
    }

    // Initialize Diff matrix
    vector<T> difftriplet;
    difftriplet.reserve(N);
    for (int ii = 0; ii < N-2; ++ii)
    {
        difftriplet.push_back(T(ii,ii,1));
        difftriplet.push_back(T(ii,ii+1,-2));
        difftriplet.push_back(T(ii,ii+2,1));
    }

    SpMat D(N,N);
    SpMat W(N,N);
    D.setFromTriplets(difftriplet.begin(),difftriplet.end());
    SpMat Dset(N,N);
    Dset = smooth*D.transpose()*D;


    double t = (clock() - start)/(double)CLOCKS_PER_SEC;
    cout << "setup time: " << t << endl;
    start = clock();

    SpMat temp(N,N);

    VectorXd x(N);

    for(int ii = 0; ii < maxIter; ii++)
    {
        cout << "Iteration: " << ii+1 << endl;
        // decomposition
        W.setFromTriplets(weights.begin(),weights.end());
        SimplicialCholesky<SpMat> chol(W+Dset);
        x = chol.solve(sig.cwiseProduct(vweights));
        // update
        for(int jj = 0; jj < N; jj++)
        {
            if(sig[jj] > x[jj])
            {
                vweights[jj] = p;
            }
            else
            {
                vweights[jj] = 1-p;
            }
            weights[jj] =  T(jj,jj,vweights[jj]);
        }
    }

    // subtract the baseline
    for(int ii = 0;ii < N; ii++)
    {
        out.get()[ii][0] = x[ii];
        out.get()[ii][1] = 0; // This should remain 0.
        // cout << in.get()[ii][0] << " : " << out.get()[ii][0] << " : " << x[ii] << endl;
        // cout << out.get()[ii][0] << " : " << x[ii] << endl;
    }

    t = (clock() - start)/(double)CLOCKS_PER_SEC;
    cout << "compute time: " << t << endl;

}

int mainals(vector<double> &baseline, double p, double smooth, int maxIter)
{
    int N = baseline.size();
	// in data
	cp in(new fftw_complex[N]);
	for (int ii = 0; ii < N; ++ii)
	{
        in.get()[ii][0] = baseline[ii];
		in.get()[ii][1] = 0;
	}

	// parameters
	cp out(new fftw_complex[N]);

    als(in, out, N, smooth, p, maxIter);

	for(int ii = 0; ii < N; ii++)
	{
        baseline[ii] = out.get()[ii][0];
	}

	return 0;
}
