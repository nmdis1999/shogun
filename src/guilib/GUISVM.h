/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * Written (W) 1999-2006 Soeren Sonnenburg
 * Written (W) 1999-2006 Gunnar Raetsch
 * Copyright (C) 1999-2006 Fraunhofer Institute FIRST and Max-Planck-Society
 */

#ifndef _GUISVM_H__
#define _GUISVM_H__ 

#include "classifier/svm/SVM.h"

class CGUI ;

class CGUISVM
{

public:
	CGUISVM(CGUI*);
	~CGUISVM();

	bool new_svm(CHAR* param);
	bool train(CHAR* param, bool auc_maximization);
	bool test(CHAR* param);
	bool load(CHAR* param);
	bool save(CHAR* param);
	bool set_C(CHAR* param);
	bool set_qpsize(CHAR* param);
	bool set_mkl_enabled(CHAR* param);
	bool set_batch_computation_enabled(CHAR* param);
	bool set_linadd_enabled(CHAR* param);
	bool set_svm_epsilon(CHAR* param);
	bool set_svr_tube_epsilon(CHAR* param);
	bool set_svm_one_class_nu(CHAR* param);
	bool set_mkl_parameters(CHAR* param) ;
	bool set_precompute_enabled(CHAR* param) ;

	CLabels* classify(CLabels* output=NULL);
	bool classify_example(INT idx, DREAL& result);

	inline CSVM* get_svm() { return svm; }

 protected:
	CGUI* gui;
	CSVM* svm;
	int qpsize;
	double weight_epsilon;
	double epsilon;
	double tube_epsilon;
	double nu;
	double C1;
	double C2;
	double C_mkl ;
	bool use_mkl, use_batch_computation, use_linadd, use_precompute, use_precompute_subkernel, 
		use_precompute_subkernel_light ;
	bool use_shrinking;
};
#endif
