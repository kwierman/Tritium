#ifndef TriWKBApproximation_h_
#define TriWKBApproximation_h_

#include "TriElementPrototype.h"
#include "TriConstants.h"

#include "TMath.h"
#include "TriLogger.h"

/**
 * Note that Type=1.0 = Simpson's and Rose's Approximation and 2=Longmire and Brown's Approximation
 **/

namespace Tritium{

	class TriWKBApproximation : public TriElementPrototype<TriWKBApproximation>{
	private:
		double Z;
		double type;
		double v0;

	public:
		TriWKBApproximation();
		void SetZ(double x){this->Z = x;}
		void SetType(double x){this->type = x;}

		void Init(){
			this->v0 = 1.45*TMath::Power(Z,4.0/3.0)*TMath::Power(Alpha,2.0)*ElectronMasseV;
			TriLog(TriLogger::kNormal)<<"Thomson-Fermi Potential: "<<v0<<Tritium::endl;
		}

		void dNdE(double kE);
		virtual void OnNewFileCreate();

	private:
		REGISTER_DEC_TYPE(TriWKBApproximation);

	};
}

#endif //TriWKBApproximation_h_