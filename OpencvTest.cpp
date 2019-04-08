#include <iostream>
#include <testbench.hpp>
#include <lga.hpp>
#include <precisetimer.hpp>

#include "opencv2/opencv.hpp"

#define DMSGN(x) do { std::cout << x << std::endl; } while(0)
#define DMSG(x) do { std::cout << x << " "; } while(0)


using namespace std;
using namespace testbench;

using namespace cv;
void fill_tensor(Mat& src);
/**
 * create module parameters in LGA area.
 */
TESTBENCH_MODULE(t_testbenchParam, OpencvTest);

t_timespec tspec_OpencvTest = {
	.iter = 1000,					// number of iteration
	.unroll = 50,					// number of unroll
	.elapsed = vector<double>(0,0),	// dummy
	.opcycle = 0,					// dummy
};

void MAINFUNC(OpencvTest)(tbHandler* pHandler)
{
	int len = pHandler->getIter();
	double durations[len];
	int M = 128;
	int N = 128;
	int K = 128;
	
	cout << "Opencv test! " << endl;
	Mat src0 = Mat (K, M, CV_32FC1);
	Mat src1 = Mat (N, K, CV_32FC1);
	Mat dst  = Mat (N, M, CV_32FC1);

	fill_tensor(src0);
	fill_tensor(src1);
	for (auto i=0;i<len; ++i){
		precisetimer::kick();
		dst = src1*src0;
		dst = src1*src0;
		dst = src1*src0;
		dst = src1*src0;
		dst = src1*src0;
		dst = src1*src0;
		dst = src1*src0;
		dst = src1*src0;
		dst = src1*src0;
		dst = src1*src0;//10

		dst = src1*src0;
		dst = src1*src0;
		dst = src1*src0;
		dst = src1*src0;
		dst = src1*src0;
		dst = src1*src0;
		dst = src1*src0;
		dst = src1*src0;
		dst = src1*src0;
		dst = src1*src0;//20

		dst = src1*src0;
		dst = src1*src0;
		dst = src1*src0;
		dst = src1*src0;
		dst = src1*src0;
		dst = src1*src0;
		dst = src1*src0;
		dst = src1*src0;
		dst = src1*src0;
		dst = src1*src0;//30

		dst = src1*src0;
		dst = src1*src0;
		dst = src1*src0;
		dst = src1*src0;
		dst = src1*src0;
		dst = src1*src0;
		dst = src1*src0;
		dst = src1*src0;
		dst = src1*src0;
		dst = src1*src0;//40

		dst = src1*src0;
		dst = src1*src0;
		dst = src1*src0;
		dst = src1*src0;
		dst = src1*src0;
		dst = src1*src0;
		dst = src1*src0;
		dst = src1*src0;
		dst = src1*src0;
		dst = src1*src0;//50
		precisetimer::stop();

		durations[i] = precisetimer::duration<double,std::nano>();
		//durations[i] = precisetimer::duration<double,std::seconds>();
	}
	pHandler->analyze(len, durations);
	return ;
}

void SETUPFUNC(OpencvTest)()
{
// create testbench handler using timespec.
	tbHandler* tb_OpencvTestHandler = new tbHandler(&tspec_OpencvTest, toString(OpencvTest));

	tb_OpencvTestHandler->gplot = PARAM(OpencvTest).flagGnuPlot;

	// execute main function of this module
	MAINFUNC(OpencvTest)(tb_OpencvTestHandler);

	delete tb_OpencvTestHandler;
}
void fill_tensor(Mat& src)
{
	float low = -1.0f;
	float high = 1.0f;

	randu(src, Scalar(low), Scalar(high));
}
