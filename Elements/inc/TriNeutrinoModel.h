#ifndef TriNeutrinoModel_h_
#define TriNeutrinoModel_h_

#include "TMatrixD.h" //!< For the 
#include "TVectorD.h"
#include "TriElementPrototype.h"

#include "TriLogger.h"

namespace Tritium{

	/**
	 * \param m the span of neutrino flavor space
 	 */
	class TriNeutrinoModel : public TriElementPrototype<TriNeutrinoModel> {
	private:
		TMatrixD fPMNS; //!< The PMNS Matrix
		TVectorD fMassEigenstates; //!< the mass eigenstates (Want this in eV in order to jive with the )
		TVectorD fFlavorMasses;
		bool isInverted; //!< Indicates inverted or non-inverted mass hierarchy

		int currentI;
		int currentJ;

		double oldMass;
		double q_value;

		double individual_factor[3];

	public:
		TriNeutrinoModel(); //!< For now, no other constructor.

		void setQValue(double x){this->q_value = x;}
		void setPMNSOrdered(double x);
		void setMassOrdered(double x);

		void setPMNS(int i, int j, double x);
		void setMass(int i, double x);

		void dNdE(double kE);

		void Init(){
			TriLog(TriLogger::kHeader)<<"Neutrino Model Configuring"<<Tritium::endl;
			TriLog(TriLogger::kNormal)<<" PMNS Matrix:"<<Tritium::endl;
			for(Int_t i=0; i<3;i++){
				for (Int_t j=0; j<3;j++)
					TriLog(TriLogger::kNormal)<<fPMNS[i][j]<<" ";
				TriLog(TriLogger::kNormal)<<Tritium::endl;
			}
			TriLog(TriLogger::kNormal)<<"  Mass fMassEigenstates:"<<Tritium::endl;
			for(Int_t i=0; i<3;i++)
				TriLog(TriLogger::kNormal)<<fMassEigenstates[i]<<" ";
			TriLog(TriLogger::kNormal)<<Tritium::endl;
		};

		void OnNewFileCreate();

		REGISTER_DEC_TYPE(TriNeutrinoModel);

	};
}


#endif //TriNeutrinoModel_h_