/*
 * OpenblasTest.cpp
 *
 *  Created on: April 4, 2019
 *      Author: Woong
 */

#include <iostream>
#include <testbench.hpp>
#include <lga.hpp>
#include <precisetimer.hpp>
#include <cblas.h>

using namespace std;
using namespace testbench;

/**
 * create module parameters in LGA area.
 */
TESTBENCH_MODULE(t_testbenchParam, OpenblasTest);

/**
 * define time spec used in this module.
 */
t_timespec tspec_OpenblasTest = {
	.iter = 1000,					// number of iteration
	.unroll = 50,					// number of unroll
	.elapsed = vector<double>(0,0),	// dummy
	.opcycle = 0,					// dummy
};

/**
 * MAIN function of this module.
 * @param pTestbenchMod: testbench handler class containing iteration information.
 */
void MAINFUNC(OpenblasTest)(tbHandler* pHandler)
{

	// iteration information
	int len = pHandler->getIter();
	// the code in loop should be matched with unroll.
//	int unroll = pHandler->getUnroll();

	// time slices to store duration
	double durations[len];

	// Random Matrix Generation
	const int M = 128;
	const int K = 128;
	const int N = 128;
	
	int sizeA = M*K;
	int sizeB = K*N;
	int sizeC = M*N;
	float R = 1.0;

	cout << "OpenBLAS!! " << endl;
	float *numPtrMatA = (float*)malloc(sizeof(float) * sizeA );
	float *numPtrMatB = (float*)malloc(sizeof(float) * sizeB );
	float *numPtrMatC = (float*)malloc(sizeof(float) * sizeC );
	for (int i = 0; i < sizeA; i++){
		numPtrMatA[i] = 2*(float)rand()/(float)(RAND_MAX)-1;
	}
	for (int i = 0; i < sizeB; i++){
		numPtrMatB[i] = 2*(float)rand()/(float)(RAND_MAX)-1;
	}
	for (int i = 0; i < sizeC; i++){
		numPtrMatC[i] = 1.0;
	}

	for (auto i = 0; i < len; i++){


		//Matrix multiplication
		precisetimer::kick();

		cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans,M,N,K,1.0,numPtrMatA, K, numPtrMatB, N,0.0,numPtrMatC,N);
		cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans,M,N,K,1.0,numPtrMatA, K, numPtrMatB, N,0.0,numPtrMatC,N);
		cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans,M,N,K,1.0,numPtrMatA, K, numPtrMatB, N,0.0,numPtrMatC,N);
		cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans,M,N,K,1.0,numPtrMatA, K, numPtrMatB, N,0.0,numPtrMatC,N);
		cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans,M,N,K,1.0,numPtrMatA, K, numPtrMatB, N,0.0,numPtrMatC,N);
		cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans,M,N,K,1.0,numPtrMatA, K, numPtrMatB, N,0.0,numPtrMatC,N);
		cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans,M,N,K,1.0,numPtrMatA, K, numPtrMatB, N,0.0,numPtrMatC,N);
		cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans,M,N,K,1.0,numPtrMatA, K, numPtrMatB, N,0.0,numPtrMatC,N);
		cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans,M,N,K,1.0,numPtrMatA, K, numPtrMatB, N,0.0,numPtrMatC,N);
		cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans,M,N,K,1.0,numPtrMatA, K, numPtrMatB, N,0.0,numPtrMatC,N); //10

		cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans,M,N,K,1.0,numPtrMatA, K, numPtrMatB, N,0.0,numPtrMatC,N);
		cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans,M,N,K,1.0,numPtrMatA, K, numPtrMatB, N,0.0,numPtrMatC,N);
		cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans,M,N,K,1.0,numPtrMatA, K, numPtrMatB, N,0.0,numPtrMatC,N);
		cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans,M,N,K,1.0,numPtrMatA, K, numPtrMatB, N,0.0,numPtrMatC,N);
		cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans,M,N,K,1.0,numPtrMatA, K, numPtrMatB, N,0.0,numPtrMatC,N);
		cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans,M,N,K,1.0,numPtrMatA, K, numPtrMatB, N,0.0,numPtrMatC,N);
		cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans,M,N,K,1.0,numPtrMatA, K, numPtrMatB, N,0.0,numPtrMatC,N);
		cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans,M,N,K,1.0,numPtrMatA, K, numPtrMatB, N,0.0,numPtrMatC,N);
		cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans,M,N,K,1.0,numPtrMatA, K, numPtrMatB, N,0.0,numPtrMatC,N);
		cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans,M,N,K,1.0,numPtrMatA, K, numPtrMatB, N,0.0,numPtrMatC,N); //20
		cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans,M,N,K,1.0,numPtrMatA, K, numPtrMatB, N,0.0,numPtrMatC,N);
		cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans,M,N,K,1.0,numPtrMatA, K, numPtrMatB, N,0.0,numPtrMatC,N);
		cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans,M,N,K,1.0,numPtrMatA, K, numPtrMatB, N,0.0,numPtrMatC,N);
		cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans,M,N,K,1.0,numPtrMatA, K, numPtrMatB, N,0.0,numPtrMatC,N);
		cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans,M,N,K,1.0,numPtrMatA, K, numPtrMatB, N,0.0,numPtrMatC,N);
		cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans,M,N,K,1.0,numPtrMatA, K, numPtrMatB, N,0.0,numPtrMatC,N);
		cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans,M,N,K,1.0,numPtrMatA, K, numPtrMatB, N,0.0,numPtrMatC,N);
		cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans,M,N,K,1.0,numPtrMatA, K, numPtrMatB, N,0.0,numPtrMatC,N);
		cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans,M,N,K,1.0,numPtrMatA, K, numPtrMatB, N,0.0,numPtrMatC,N);
		cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans,M,N,K,1.0,numPtrMatA, K, numPtrMatB, N,0.0,numPtrMatC,N); //30

		cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans,M,N,K,1.0,numPtrMatA, K, numPtrMatB, N,0.0,numPtrMatC,N);
		cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans,M,N,K,1.0,numPtrMatA, K, numPtrMatB, N,0.0,numPtrMatC,N);
		cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans,M,N,K,1.0,numPtrMatA, K, numPtrMatB, N,0.0,numPtrMatC,N);
		cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans,M,N,K,1.0,numPtrMatA, K, numPtrMatB, N,0.0,numPtrMatC,N);
		cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans,M,N,K,1.0,numPtrMatA, K, numPtrMatB, N,0.0,numPtrMatC,N);
		cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans,M,N,K,1.0,numPtrMatA, K, numPtrMatB, N,0.0,numPtrMatC,N);
		cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans,M,N,K,1.0,numPtrMatA, K, numPtrMatB, N,0.0,numPtrMatC,N);
		cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans,M,N,K,1.0,numPtrMatA, K, numPtrMatB, N,0.0,numPtrMatC,N);
		cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans,M,N,K,1.0,numPtrMatA, K, numPtrMatB, N,0.0,numPtrMatC,N);
		cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans,M,N,K,1.0,numPtrMatA, K, numPtrMatB, N,0.0,numPtrMatC,N); //40

		cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans,M,N,K,1.0,numPtrMatA, K, numPtrMatB, N,0.0,numPtrMatC,N);
		cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans,M,N,K,1.0,numPtrMatA, K, numPtrMatB, N,0.0,numPtrMatC,N);
		cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans,M,N,K,1.0,numPtrMatA, K, numPtrMatB, N,0.0,numPtrMatC,N);
		cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans,M,N,K,1.0,numPtrMatA, K, numPtrMatB, N,0.0,numPtrMatC,N);
		cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans,M,N,K,1.0,numPtrMatA, K, numPtrMatB, N,0.0,numPtrMatC,N);
		cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans,M,N,K,1.0,numPtrMatA, K, numPtrMatB, N,0.0,numPtrMatC,N);
		cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans,M,N,K,1.0,numPtrMatA, K, numPtrMatB, N,0.0,numPtrMatC,N);
		cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans,M,N,K,1.0,numPtrMatA, K, numPtrMatB, N,0.0,numPtrMatC,N);
		cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans,M,N,K,1.0,numPtrMatA, K, numPtrMatB, N,0.0,numPtrMatC,N);
		cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans,M,N,K,1.0,numPtrMatA, K, numPtrMatB, N,0.0,numPtrMatC,N); //50
		

		precisetimer::stop();
	
		durations[i] = precisetimer::duration<double,std::nano>();
	}

	pHandler->analyze(len, durations);

	return;
}

/**
 * SETUP function of this module.
 */
void SETUPFUNC(OpenblasTest)()
{
	// create testbench handler using timespec.
	tbHandler* tb_OpenblasTestHandler = new tbHandler(&tspec_OpenblasTest, toString(OpenblasTest));

	tb_OpenblasTestHandler->gplot = PARAM(OpenblasTest).flagGnuPlot;

	// execute main function of this module
	MAINFUNC(OpenblasTest)(tb_OpenblasTestHandler);

	delete tb_OpenblasTestHandler;
}

