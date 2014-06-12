#include "TriConstants.h"
#include "TriQuantity.h"
//#include "TriLogger.h"

#include <iostream>

using namespace Tritium;
int main(int argc, char* argv[]){
	TriScalar scale = TriRate(0.0)*TriTime(0.0);
	//TriScalar doesntWork = TriTime(0.0)*TriTime(0.0);
	TriEnergy energy = TriMass(66.0)*TriLength(100.0)*TriLength(100.0)/TriTime(1.0)/TriTime(1.0);
	return 0;
}