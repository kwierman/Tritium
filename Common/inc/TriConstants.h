/*  \file TrConstants.h
	\author Kevin Wierman

	\brief Constants in MKS units
*/

#ifndef TriConstants_h_
#define TriConstants_h_ 1

#include "TMath.h"

//Defining units and dimensionality
namespace TritiumDimensions{

	struct TritiumNestedType{
		enum{value=0};
	};

	template<int i>
	struct TritiumInt2Type : public TritiumNestedType {
		enum { value=v };
	};

	typedef TritiumNestedType dimension[7];
	dimension const mass = {TritiumInt2Type<1>,
							TritiumInt2Type<0>,
							TritiumInt2Type<0>,
							TritiumInt2Type<0>,
							TritiumInt2Type<0>,
							TritiumInt2Type<0>,
							TritiumInt2Type<0>};//mass (kg)
	dimension const length = {TritiumInt2Type<0>,
							TritiumInt2Type<1>,
							TritiumInt2Type<0>,
							TritiumInt2Type<0>,
							TritiumInt2Type<0>,
							TritiumInt2Type<0>,
							TritiumInt2Type<0>};// length (meter)
	dimension const time = {TritiumInt2Type<0>,
							TritiumInt2Type<0>,
							TritiumInt2Type<1>,
							TritiumInt2Type<0>,
							TritiumInt2Type<0>,
							TritiumInt2Type<0>,
							TritiumInt2Type<0>};// time (s)
	dimension const charge ={TritiumInt2Type<0>,
							TritiumInt2Type<0>,
							TritiumInt2Type<0>,
							TritiumInt2Type<1>,
							TritiumInt2Type<0>,
							TritiumInt2Type<0>,
							TritiumInt2Type<0>};// charge (coulombs)
	dimension const temperature = {TritiumInt2Type<0>,
							TritiumInt2Type<0>,
							TritiumInt2Type<0>,
							TritiumInt2Type<0>,
							TritiumInt2Type<1>,
							TritiumInt2Type<0>,
							TritiumInt2Type<0>};// temperature (Kelvin)
	dimension const intensity = {TritiumInt2Type<0>,
							TritiumInt2Type<0>,
							TritiumInt2Type<0>,
							TritiumInt2Type<0>,
							TritiumInt2Type<0>,
							TritiumInt2Type<1>,
							TritiumInt2Type<0>};// intensity (db)
	dimension const angle = {TritiumInt2Type<0>,
							TritiumInt2Type<0>,
							TritiumInt2Type<0>,
							TritiumInt2Type<0>,
							TritiumInt2Type<0>,
							TritiumInt2Type<0>,
							TritiumInt2Type<1>};// angle (rad)
}



namespace Tritium
{
	//from PDG
	const static double FundamentalCharge = 1.60217646e-19;  //Coulombs
	const static double ElectronMass = 9.10938215e-31;;//9.10938215e-31; // kg
	const static double ElectronMasseV = 510998.910;//eV
	const static double H = 6.62606896e-34; // J*s Planck's constants
	const static double C = 299792458; // m/s
	const static double HBar = H/(2.0*TMath::Pi());  //J*s
	const static double Gf = 4.5438e-14; // J^(-2)  here Gf = G_f/(hbar*c)^3 
	const static double AMU = 1.66053886e-27; // kg atomic mass unit
	const static double Mu0 = 4.0e-7*TMath::Pi(); //vacuum magnetic permeability
	const static double Ep0 = 1.0/(C*C*Mu0); //vacuum electric permittivity
	const static double Alpha = 7.2973525376e-3; //unitless (fine structure constant)
	const static double Vud = 0.97425; //The absolute value of the (1,1) element of the CKM matrix
	const static double eV = 1.60217646e-19; //eV to Joules conversion constant;
	const static double m_to_cm = 100; //meters to centimeters conversion constant;
	const static double cos_theta_c = 0.97427; //The cosine of the cabbibo angle


	const static double Fv = 1.0; //vector coupling coefficient
	const static double Fa = 1.247; //axial coupling coefficient
	const static double MFermi = 1.0; //Fermi maxtrix element magnitude
	const static double MGamowTeller = 0.962*TMath::Sqrt(3.0); //Gamow Teller matrix element magnitude
	const static double NuclearMatrixElementSquared = Fv*Fv*MFermi*MFermi + Fa*Fa*MGamowTeller*MGamowTeller;
	const static double TritiumHalfLife = 12.32*365*24*60*60; //half life in seconds
	const static double TritiumLifetime = TritiumHalfLife/TMath::Log(2.0); //lifetime in seconds

	//These In Kilgrams
	const static double TritiumMass = 3.01604927767*AMU;
	const static double Helium3Mass = 3.01602931914*AMU;


}
#endif /* TriConstants_h_ */