#pragma once

//Type declration header


typedef uint64_t counter_t;

typedef unsigned long int simcounter_t;

typedef double n_intensity_t;//! Normalization applied on intensity type. With values restricted between 0 and 1.

typedef double bernoulli_p_t; //! Represents a Bernoulli Probability. With values restricted between 0 and 1. 
typedef bool bin_detect_t;

typedef simcounter_t discrete_freq_t;	
//channel_t → is a template parameter used in the detector framework.




class A
{
	double __attribute__((always_inline)) virtual method1() = 0;
	double __attribute__((always_inline)) virtual method2() = 0;

	double __attribute__((always_inline)) method3()
	{
		return method1()/method2();
	}

	double __attribute__((always_inline)) method4() //Alias of method1
	{
		return method1();
	}
};

class B : public A
{
	//Implements methods A and B.
};

