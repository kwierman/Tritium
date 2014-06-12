#ifndef TriBetaKinematics_h_
#define TriBetaKinematics_h_ 1

#include "TriElementPrototype.h"

#include <string>

namespace Tritium{

	/**
	 * \class TriBetaKinematics
	 * Computes the basic beta decay spectrum for a 
	 */
	class TriBetaKinematics : public TriElementPrototype<TriBetaKinematics> {
	private:
		double q_value;
		double norm;

		double gamma;
		double beta;
		double c_factor;
		double P_e;
		double E_e;
		double delta_E;

	public:
		TriBetaKinematics();

		void SetEndPoint(double x){this->q_value = x;}
		void SetNorm(double x){this->norm = x;}

		void Init();


		void dNdE(double kE);

		void OnNewFileCreate();

		REGISTER_DEC_TYPE(TriBetaKinematics);

	};

}


#endif /* TriBetaKinematics_h_ */