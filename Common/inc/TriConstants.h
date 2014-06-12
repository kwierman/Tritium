/*  \file TrConstants.h
	\author Kevin Wierman

	\brief Constants in MKS units
*/

#ifndef TriConstants_h_
#define TriConstants_h_ 1

#include "TriQuantity"
#include "TriMath.h"

namespace Tritium
{
	const static TriScalar 		Pi 					= TriScalar(3.1415926535897932);
	const static TriCharge 		FundamentalCharge 	= TriCharge(1.60217646e-19);  //Coulombs
	const static TriMass 		ElectronMass 		= TriMass(9.10938215e-31); // kg
	const static TriEnergy 		ElectronMasseV 		= TriEnergy(510998.910);//eV
	const static TriAction 		H 					= TriAction(6.62606896e-34); // J*s Planck's constants
	const static TriVelocity 	C 					= TriVelocity(299792458); // m/s
	const static TriAction	 	HBar 				= TriAction(H/(2.0*P ) );  //J*s
	const static TriDesign::TriQuantity<double, > Gf = 4.5438e-14; // J^(-2)  here Gf = G_f/(hbar*c)^3 
	const static TriMass AMU 						= TriMass(1.66053886e-27); // kg atomic mass unit
	const static TriDesign::TriQuantity<double, > Mu0 = 4.0e-7*TMath::Pi(); //vacuum magnetic permeability
	const static TriDesign::TriQuantity<double, > Ep0 = 1.0/(C*C*Mu0); //vacuum electric permittivity
	const static TriDesign::TriQuantity<double, > Alpha = 7.2973525376e-3; //unitless (fine structure constant)
	const static TriDesign::TriQuantity<double, > Vud = 0.97425; //The absolute value of the (1,1) element of the CKM matrix
	const static TriDesign::TriQuantity<double, > eV = 1.60217646e-19; //eV to Joules conversion constant;
	const static TriDesign::TriQuantity<double, > m_to_cm = 100; //meters to centimeters conversion constant;
	const static TriDesign::TriQuantity<double, > cos_theta_c = 0.97427; //The cosine of the cabbibo angle


	const static TriDesign::TriQuantity<double, > Fv = 1.0; //vector coupling coefficient
	const static TriDesign::TriQuantity<double, > Fa = 1.247; //axial coupling coefficient
	const static TriDesign::TriQuantity<double, > MFermi = 1.0; //Fermi maxtrix element magnitude
	const static TriDesign::TriQuantity<double, > MGamowTeller = 0.962*TMath::Sqrt(3.0); //Gamow Teller matrix element magnitude
	const static TriDesign::TriQuantity<double, > NuclearMatrixElementSquared = Fv*Fv*MFermi*MFermi + Fa*Fa*MGamowTeller*MGamowTeller;
	const static TriDesign::TriQuantity<double, > TritiumHalfLife = 12.32*365*24*60*60; //half life in seconds
	const static TriDesign::TriQuantity<double, > TritiumLifetime = TritiumHalfLife/TMath::Log(2.0); //lifetime in seconds

	//These In Kilgrams
	const static TriDesign::TriQuantity<double, > TritiumMass = 3.01604927767*AMU;
	const static TriDesign::TriQuantity<double, > Helium3Mass = 3.01602931914*AMU;


}
#endif /* TriConstants_h_ */