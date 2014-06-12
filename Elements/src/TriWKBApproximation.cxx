#include "TriWKBApproximation.h"
#include "TriRootOutput.h"

#include "TMath.h"
#include "TriConstants.h"

namespace Tritium{

	REGISTER_DEF_TYPE(TriWKBApproximation);

	TriWKBApproximation::TriWKBApproximation() :  TriElementPrototype<TriWKBApproximation>() , 
	Z(2.0), type(0.0), v0(99.4242){
		AddValueToMap("Z",&TriWKBApproximation::SetZ);
		AddValueToMap("type",&TriWKBApproximation::SetType);
	}

	void TriWKBApproximation::dNdE(double kE){
		if(this->type==0){
			this->factor = (kE+ElectronMasseV-v0 )/(kE+ElectronMasseV);
			if(kE==0)
				this->factor=0;
		}
		if(this->type==1.0){
			this->factor = TMath::Sqrt(TMath::Power(kE,2.0)/TMath::Abs(kE-v0) );
		}

		this->output = (this->factor)*(this->input);

		TriRootOutput::GetInstance()->FillTree("TriWKBApproximation");
	}
	void TriWKBApproximation::OnNewFileCreate(){
		TriRootOutput::GetInstance()->AddTree("TriWKBApproximation");
		TriRootOutput::GetInstance()->AddBranch<double>("TriWKBApproximation", "kE", &kE,"D");
		TriRootOutput::GetInstance()->AddBranch<double>("TriWKBApproximation", "input", &input,"D");
		TriRootOutput::GetInstance()->AddBranch<double>("TriWKBApproximation", "output", &output,"D");
		TriRootOutput::GetInstance()->AddBranch<double>("TriWKBApproximation", "factor", &factor,"D");
	}
}