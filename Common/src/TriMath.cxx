#include "TriMath.h"

namespace Tritium{

	template<typename T>
	T Power(T x, int n){
		T x0=1.0;
		for(int i=0; i<n;i++){
			x0*=x;
		}
		return x0;
	}

	int factorial(int x){
		int y=1.0;
		while(x>0){
			y*(--x);
		}
		return y;
	}

	double exponent_taylor(double x, int n_iter){
		double value=0.;
		for(int i=0; i<n_iter;i++){
			value+=Power<double>(x,i)/double(factorial(i));
		}
		return value;
	}

	double log_taylor(double x, int n_iter){
		double value=0;
		for(int i=0; i<n_iter; i++){
			value+=(Power<double>(-1.0, (i+1))/double(i) )*(Power<double>(x-1,i ) );
		}
		return value;
	}

	double absolute(const double x){
		if ( x < 0.) return x-2.0*x;
		return x;
	}

	template <typename T>
	unsigned int n_digits(T x){
		unsigned int count=0;
		x = int(x);
		while(x>0){
			x = int(x/10.);
			++count;
		}
		return count;
	}

	template<typename T>
	int ith_digit(T x, unsigned int i){
		return int(x/Power<int>(10, i))%10;
	}

	double Gamma(double x){
		double result=1.0;
		while( x>0){
			result*=(--x);
		}
		return result;
	}

	double babylonian_sqrt(double x, int n_iter){
		double x_0 = x/2.;
		for(int i=0; i<n_iter; i++){
			x_0 = (x_0+x/x_0)/2.;
		}
		return x_0;
	}

	double digit_sqrt(double x, int n_digits){
		double d,a=1;
		if(!x) return 0.;
		if (n_digits < 1 || (x < 0 && !(n_digits&1))) return 0./0.; /* NaN */
		do{
			d=(x/Power<double>(a,n_digits-1)-a )/n_digits;
			a+=d;
		}
		while(absolute(d)>=absolute(a) *2.2204460492503131e-15  );//not exactly DBL_EPSILON

		return a;
	}

	double sqrt_from_exp(double x, int n_iter){
		return exponent_taylor(0.5*log_taylor(x, n_iter) ,n_iter);
	}

	double sqrt_2_var(double x){
		double a0 = x;
		double c0=x-1.;
		while (absolute(c0) >0 ){
			a0 = a0-a0*c0/2.;
			c0 = c0*c0*(c0-3.)/4.;
		}
		return a0;
	}

}