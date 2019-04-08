/*
 * NeonTest.cpp
 *
 *  Created on: April 4, 2019
 *      Author: Woong
 */

#include <iostream>
#include <testbench.hpp>
#include <lga.hpp>
#include <precisetimer.hpp>

#include "arm_compute/core/Types.h"
#include "arm_compute/runtime/NEON/NEFunctions.h"
#include "arm_compute/runtime/NEON/NEScheduler.h"
#include "utils/Utils.h"
#include <cstdlib>

using namespace std;
using namespace testbench;

using namespace arm_compute;
using namespace utils;

/**
 * create module parameters in LGA area.
 */
TESTBENCH_MODULE(t_testbenchParam, NeonTest);

/**
 * define time spec used in this module.
 */
t_timespec tspec_NeonTest = {
	.iter = 1000,					// number of iteration
	.unroll = 50,					// number of unroll
	.elapsed = vector<double>(0,0),	// dummy
	.opcycle = 0,					// dummy
};

class NESGEMMExample : public Example
{
public:
    bool do_setup() //override
    {
        NPYLoader npy0, npy1, npy2;
        alpha = 1.0f;
        beta  = 0.0f;
        std::ifstream stream;

        size_t M = 128;
        size_t K = 128;
        size_t N = 128;

        src0.allocator()->init(TensorInfo(TensorShape(K, M), 1, DataType::F32));
        src1.allocator()->init(TensorInfo(TensorShape(N, K), 1, DataType::F32));

        init_sgemm_output(dst, src0, src1, DataType::F32);

        // Configure function
        sgemm.configure(&src0, &src1, nullptr, &dst, alpha, beta);

        // Allocate all the images
        src0.allocator()->allocate();
        src1.allocator()->allocate();
        dst.allocator()->allocate();

        // Fill the input images with either the data provided or random data
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

    }
    void do_teardown() //override
    {
        if(!output_filename.empty()) /* Save to .npy file */
        {
            save_to_npy(dst, output_filename, is_fortran);
        }
    }

private:
    Tensor      src0{}, src1{}, src2{}, dst{};
    NEGEMM      sgemm{};
    float       alpha{}, beta{};
    bool        is_fortran{};
    std::string output_filename{};
};

/**
 * MAIN function of this module.
 * @param pTestbenchMod: testbench handler class containing iteration information.
 */
void MAINFUNC(NeonTest)(tbHandler* pHandler)
{

	int len = pHandler->getIter();
	double durations[len];

	cout << "Hello Neon!! " << endl;
	
	NESGEMMExample* tb_NESGEMMExample = new NESGEMMExample;
	tb_NESGEMMExample->do_setup();

	for (auto i = 0; i < len; i++){

		precisetimer::kick();

		tb_NESGEMMExample->do_run();
		tb_NESGEMMExample->do_run();
		tb_NESGEMMExample->do_run();
		tb_NESGEMMExample->do_run();
		tb_NESGEMMExample->do_run();
		tb_NESGEMMExample->do_run();
		tb_NESGEMMExample->do_run();
		tb_NESGEMMExample->do_run();
		tb_NESGEMMExample->do_run();
		tb_NESGEMMExample->do_run(); //10

		tb_NESGEMMExample->do_run();
		tb_NESGEMMExample->do_run();
		tb_NESGEMMExample->do_run();
		tb_NESGEMMExample->do_run();
		tb_NESGEMMExample->do_run();
		tb_NESGEMMExample->do_run();
		tb_NESGEMMExample->do_run();
		tb_NESGEMMExample->do_run();
		tb_NESGEMMExample->do_run();
		tb_NESGEMMExample->do_run(); //20

		tb_NESGEMMExample->do_run();
		tb_NESGEMMExample->do_run();
		tb_NESGEMMExample->do_run();
		tb_NESGEMMExample->do_run();
		tb_NESGEMMExample->do_run();
		tb_NESGEMMExample->do_run();
		tb_NESGEMMExample->do_run();
		tb_NESGEMMExample->do_run();
		tb_NESGEMMExample->do_run();
		tb_NESGEMMExample->do_run(); //30

		tb_NESGEMMExample->do_run();
		tb_NESGEMMExample->do_run();
		tb_NESGEMMExample->do_run();
		tb_NESGEMMExample->do_run();
		tb_NESGEMMExample->do_run();
		tb_NESGEMMExample->do_run();
		tb_NESGEMMExample->do_run();
		tb_NESGEMMExample->do_run();
		tb_NESGEMMExample->do_run();
		tb_NESGEMMExample->do_run(); //40

		tb_NESGEMMExample->do_run();
		tb_NESGEMMExample->do_run();
		tb_NESGEMMExample->do_run();
		tb_NESGEMMExample->do_run();
		tb_NESGEMMExample->do_run();
		tb_NESGEMMExample->do_run();
		tb_NESGEMMExample->do_run();
		tb_NESGEMMExample->do_run();
		tb_NESGEMMExample->do_run();
		tb_NESGEMMExample->do_run(); //50

		precisetimer::stop();


		durations[i] = precisetimer::duration<double,std::nano>();
	}
	delete tb_NESGEMMExample;
	pHandler->analyze(len, durations);


	
	return;
}

/**
 * SETUP function of this module.
 */
void SETUPFUNC(NeonTest)()
{
	// create testbench handler using timespec.
	tbHandler* tb_NeonTestHandler = new tbHandler(&tspec_NeonTest, toString(NeonTest));
	tb_NeonTestHandler->gplot = PARAM(NeonTest).flagGnuPlot;

	// execute main function of this module
	MAINFUNC(NeonTest)(tb_NeonTestHandler);

	delete tb_NeonTestHandler;
}

