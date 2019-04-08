/*
 * imx6Opencl.cpp
 *
 *  Created on: April 4, 2019
 *      Author: Woong
 */

#include <iostream>
#include <testbench.hpp>
#include <lga.hpp>
#include <precisetimer.hpp>

#include "arm_compute/core/Types.h"
#include "arm_compute/runtime/CL/CLFunctions.h"
#include "arm_compute/runtime/CL/CLScheduler.h"
#include "arm_compute/runtime/CL/CLTuner.h"
#include "utils/Utils.h"
#include <cstdlib>

using namespace std;
using namespace testbench;

using namespace arm_compute;
using namespace utils;

/**
 * create module parameters in LGA area.
 */
TESTBENCH_MODULE(t_testbenchParam, imx6Opencl);

/**
 * define time spec used in this module.
 */
t_timespec tspec_Opencl = {
	.iter = 1,					// number of iteration
	.unroll = 50,					// number of unroll
	.elapsed = vector<double>(0,0),	// dummy
	.opcycle = 0,					// dummy
};

class CLSGEMMExample : public Example
{
public:
    bool do_setup() //override
    {
        //NPYLoader npy0, npy1, npy2;
        alpha = 1.0f;
        beta  = 0.0f;

        CLScheduler::get().default_init(&tuner);

        std::ifstream stream;


        size_t M = 128;
        size_t K = 128;
        size_t N = 1;


        src0.allocator()->init(TensorInfo(TensorShape(K, M), 1, DataType::F32));
        src1.allocator()->init(TensorInfo(TensorShape(N, K), 1, DataType::F32));
        init_sgemm_output(dst, src0, src1, DataType::F32);

        // Configure function
        sgemm.configure(&src0, &src1, nullptr, &dst, alpha, beta);
        sgemm.configure(&src0, &src1, nullptr, &dst, alpha, beta); //it is problem in this line

        // Allocate all the images
        src0.allocator()->allocate();
        src1.allocator()->allocate();
        dst.allocator()->allocate();

        fill_random_tensor(src0, -1.f, 1.f);
        fill_random_tensor(src1, -1.f, 1.f);

        // Dummy run for CLTuner
        sgemm.run();

        return true;
    }
    void do_run() //override
    {

        // Execute the function
        sgemm.run();

        // Make sure all the OpenCL jobs are done executing:
        CLScheduler::get().sync();


    }
    void do_teardown() //override
    {
        if(!output_filename.empty()) /* Save to .npy file */
        {
            save_to_npy(dst, output_filename, is_fortran);
        }
    }

private:
    CLTensor    src0{}, src1{}, src2{}, dst{};
    CLGEMM      sgemm{};
    CLTuner     tuner{};
    float       alpha{}, beta{};
    bool        is_fortran{};
    std::string output_filename{};
};

/**
 * MAIN function of this module.
 * @param pTestbenchMod: testbench handler class containing iteration information.
 */
void MAINFUNC(imx6Opencl)(tbHandler* pHandler)
{
	// imx6Opencl setting
	int len = pHandler->getIter();
	double durations[len];

	cout << "Hello Opencl!! " << endl;

	for (auto i = 0; i < len; i++){

		CLSGEMMExample* tb_CLSGEMMExample = new CLSGEMMExample;
		tb_CLSGEMMExample->do_setup();
		
		precisetimer::kick();
		tb_CLSGEMMExample->do_run();
		precisetimer::stop();

		durations[i] = precisetimer::duration<double,std::nano>();
		delete tb_CLSGEMMExample;
	}

	pHandler->analyze(len, durations);

	return;
}

/**
 * SETUP function of this module.
 */
void SETUPFUNC(imx6Opencl)()
{

	tbHandler* tb_OpenclHandler = new tbHandler(&tspec_Opencl, toString(imx6Opencl));
	tb_OpenclHandler->gplot = PARAM(imx6Opencl).flagGnuPlot;

	// execute main function of this module
	MAINFUNC(imx6Opencl)(tb_OpenclHandler);

	delete tb_OpenclHandler;
}

