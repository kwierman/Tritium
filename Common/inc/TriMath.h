#ifndef TriMath_h_
#define TriMath_h_

namespace Tritium{

	unsigned factorial(unsigned x);

	double one_over_factorial(unsigned i);
	double compute_e();

	//A couple of important numbers
	static const double nat = compute_e();//2.71828182846;
	static const double dbl_epsilon = 2.2204460492503131e-15;
	static double dbl_omega =  1.7e308;

	double powerf3(double& x, double& y, unsigned iter);
	double powerf2(double& x, double& y);

	double power(double x, double y);

	double exponent(double x);

	double exponent_taylor(double x, int n_iter);

	double log_taylor(double x, int n_iter);

	double absolute(const double x);

	template<typename T>
	unsigned int n_digits(T x);

	template<typename T>
	int ith_digit(T x, unsigned  i);

	double Gamma(double x);

	double babylonian_sqrt(double x, int n_iter=100);

	double digit_sqrt(double x, int n_digits);

	double sqrt_from_exp(double x, int n_iter);

	//only valid for 0<x<3. Best for x approx 1
	double sqrt_2_var(double x);
}


#endif  //TriMath_h_