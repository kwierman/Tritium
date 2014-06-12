/*  \file TrConstants.h
	\author Kevin Wierman

	\brief Constants in MKS units
*/

#ifndef TriConstants_h_
#define TriConstants_h_ 1

#include "TriQuantity.h"
#include "TriMath.h"

namespace Tritium
{
	const static TriScalar 				Pi 					= TriScalar(3.1415926535897932);
	const static TriCharge 				FundamentalCharge 	= TriCharge(1.60217646e-19);  //Coulombs
	const static TriMass 				ElectronMass 		= TriMass(9.10938215e-31); // kg
	const static TriEnergy 				ElectronMasseV 		= TriEnergy(510998.910);//eV
	const static TriAction 				H 					= TriAction(6.62606896e-34); // J*s Planck's constants
	const static TriVelocity 			C 					= TriVelocity(299792458.0); // m/s
	const static TriAction	 			HBar 				= TriAction(H/(TriScalar(2.0)*Pi ) );  //J*s
	const static TriFermiQuantity 		Gf 					= TriFermiQuantity(4.5438e-14); // J^(-2)  here Gf = G_f/(hbar*c)^3 
	const static TriMass 				AMU					= TriMass(1.66053886e-27); // kg atomic mass unit
	const static TriMagneticFluxDensity Mu0 				= TriMagneticFluxDensity(4.0e-7*Pi.Value()); //vacuum magnetic permeability
	const static TriElectricFluxDensity Ep0 				= TriElectricFluxDensity( TriScalar(1.0)/(C*C*Mu0 ) ); //vacuum electric permittivity
	const static TriScalar 				Alpha 				= TriScalar(7.2973525376e-3); //unitless (fine structure constant)
	const static TriScalar 				Vud 				= TriScalar(0.97425); //The absolute value of the (1,1) element of the CKM matrix
	const static TriScalar 				eV 					= TriScalar(1.60217646e-19); //eV to Joules conversion constant;
	const static TriScalar 				m_to_cm 			= TriScalar(100.0); //meters to centimeters conversion constant;
	const static TriScalar 				cos_theta_c 		= TriScalar(0.97427); //The cosine of the cabbibo angle
	const static TriScalar 				Fv 					= TriScalar(1.0); //vector coupling coefficient
	const static TriScalar 				Fa 					= TriScalar(1.247); //axial coupling coefficient
	const static TriScalar 				MFermi 				= TriScalar(1.0); //Fermi maxtrix element magnitude
	const static TriScalar 				MGamowTeller 		= TriScalar(0.962*sqrt_from_exp(3.0, 10) ); //Gamow Teller matrix element magnitude
	const static TriScalar 				NuclearMatrixElementSquared = Fv*Fv*MFermi*MFermi + Fa*Fa*MGamowTeller*MGamowTeller;
	const static TriTime 				TritiumHalfLife		= TriTime(12.32*365*24*60*60 ); //half life in seconds
	const static TriTime 				TritiumLifetime 	= TriTime(TritiumHalfLife.Value() / log_taylor(2.0,10) ); //lifetime in seconds
	const static TriMass 				TritiumMass 		= TriScalar(3.01604927767)*AMU;
	const static TriMass 				Helium3Mass 		= TriScalar(3.01602931914)*AMU;
	
}
#endif /* TriConstants_h_ */