#include "TriMath.h"

#include <iostream>

namespace Tritium{

	unsigned factorial(unsigned x){
		unsigned y=1.0;
		while(x>0)
			y*=(x--);
		return y;
	}

	double one_over_factorial(unsigned i){
		unsigned temp = factorial(i+1);
		if(temp>32767*2)
			return 1./double(factorial(i));
		return 1./double(factorial(i))+one_over_factorial(i+1);

	}
	double compute_e(){
		return 1.+one_over_factorial(1);
	}

	double powerf3(double& x, double& y, unsigned iter){
		if(iter > 17) return 1;
		return double(iter+2)*(x+2.)-(2.*double(iter+1)-y*y)*x*x/powerf3(x,y,iter+2);
	}
	double powerf2(double& x, double& y){
		return 2.+(1.-y)*x-(1-y*y)*x*x/powerf3(x,y,1);
	}	

	double power(double x, double y){
		if( y <= dbl_epsilon )
	       	return 1.;
	    double z = x-1;
	    return 1+2.*(z*y)/powerf2(z,y);
	}  

	double exponent(double x){
		return power(nat, x);
	}

	double exponent_taylor(double x, int n_iter){
		double value=1.;
		unsigned i=1;
		unsigned factor = factorial(i);
		while(factor<32767*2 ){
			value+=power(x,i)/double(factor);
			factor = factorial(++i);
		}
		return value;
	}

	double log_taylor(double x, int n_iter){
		double value=0;
		unsigned i=1;
		while(i<32767*2){
			if(i%2==0)	
				value-=power(x-1., i)/double(i);
			else
				value+=power(x-1., i)/double(i);
			i++;
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
		return int(x/power(10, double(i) ))%10;
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
			d=(x/power(a,double(n_digits-1) )-a )/n_digits;
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