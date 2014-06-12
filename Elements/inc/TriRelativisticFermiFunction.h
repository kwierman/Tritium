#ifndef TriRelativisticFermiFunction_h_
#define TriRelativisticFermiFunction_h_

#include "TriElementPrototype.h"

namespace Tritium{

	class TriRelativisticFermiFunction : public TriElementPrototype<TriRelativisticFermiFunction> {
	private:
		//inputs
		double Z;//<! Charge of the daughter nucleus
		double R;//<! The nuclear Radius in m
		double V0;//<! The Thomas Fermi Potential 

		//outputs
		double S;
		double gamma;
		double beta;
		double eta;
		double p_e;//<! The Electron momentum
		double kinematic_factor;
		double phase_factor;

	public:
		TriRelativisticFermiFunction();

		void SetZ(double x){this->Z = x;}
		void SetR(double x){this->R =x;}
		void SetV0(double x){this->V0 = x;}

		void Init();

		void dNdE(double kE);
		virtual void OnNewFileCreate();

	private:
		REGISTER_DEC_TYPE(TriRelativisticFermiFunction);
	};
}

#endif //TriRelativisticFermiFunction_h_