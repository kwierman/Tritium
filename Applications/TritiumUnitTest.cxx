#include "TriUtilities.h"
#include "TriConstants.h"
#include "TriQuantity.h"
//#include "TriLogger.h"

#include <iostream>
#include <iomanip>
#include "TriMath.h"


using namespace Tritium;
int main(int argc, char* argv[]){

	std::cout<<"Math Test?"<<std::endl;
	std::cout<<dbl_epsilon<<std::endl;
	std::cout<<std::setprecision(15)<<nat<<std::endl;
	std::cout<<power(3.0,2.0)<<std::endl;
	std::cout<<9-power(3.,2.)<<std::endl;
	std::cout<<factorial(3)<<std::endl;
	std::cout<<exponent_taylor(2,1000)<<std::endl;
	std::cout<<exponent(2)<<std::endl;
	std::cout<<log_taylor(2,10)<<std::endl;
	std::cout<<sqrt_from_exp(2,1000)<<std::endl;
	std::cout<<power(2.,0.5)<<std::endl;
	
	TriScalar scaler 	= 	TriRate(1.0)	*	TriTime(1.0);		//This works
	TriAction act 		=	TriEnergy(20.0)	*	TriTime(5.0);		//Also works
	//TriScalar doesntWork = TriTime(0.0)*TriTime(0.0); //This doesn't work

	TriEnergy energy = TriMass(66.0)*TriLength(100.0)*TriLength(100.0)/TriTime(1.0)/TriTime(1.0);

	std::cout<<"Math Check: "<<energy.Value()<<" == "<<(66.*100.*100.)<<" ?"<<std::endl;
	std::cout<<"Gamow Teller Constant: "<<MGamowTeller.Value()<<std::endl;

	//some other things
	return 0;
}