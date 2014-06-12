#ifndef TriMath_h_
#define TriMath_h_

namespace Tritium{

	template<typename T>
	T Power(T x, int n);

	int factorial(int x);

	double exponent_taylor(double x, int n_iter);

	double log_taylor(double x, int n_iter);

	double absolute(const double& x);

	template<typename T>
	unsigned int n_digits(T x);

	template<typename T>
	int ith_digit(T x, unsigned  i);

	double Gamma(double x);

	double babylonian_sqrt(double& x, int n_iter=100);

	double digit_sqrt(double& x, int n_digits);

	double sqrt_from_exp(double& x, int n_iter);

	//only valid for 0<x<3. Best for x approx 1
	double sqrt_2_var(double x);
}


#endif  //TriMath_h_