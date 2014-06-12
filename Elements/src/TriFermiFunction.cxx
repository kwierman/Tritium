#include "TriFermiFunction.h"
#include "TriRootOutput.h"

#include "TMath.h"
#include "TriConstants.h"

namespace Tritium{

	REGISTER_DEF_TYPE(TriFermiFunction);

	TriFermiFunction::TriFermiFunction() :  TriElementPrototype<TriFermiFunction>() , 
	eta(0.0), beta(0.0), gamma(0.0), Z(2.0){
		AddValueToMap("Z",&TriFermiFunction::SetZ);
	}

	void TriFermiFunction::dNdE(double kE){
		this->gamma = 1.0 + (this->kE)/(ElectronMasseV);
		this->beta = TMath::Sqrt(1.0 - 1.0/(gamma*gamma));
		this->eta = (Z*Alpha)/(beta);
		this->factor = 2.0*eta*TMath::Pi()/(1.0 - TMath::Exp(-2.0*eta*TMath::Pi()) );
		if(1.0 - TMath::Exp(-2.0*eta*TMath::Pi())<=0 || this->gamma<=0 || this->beta<=0)
			this->factor=0.0;
		this->output = (this->factor)*(this->input);

		TriRootOutput::GetInstance()->FillTree("TriFermiFunction");
	}
	void TriFermiFunction::OnNewFileCreate(){
		TriRootOutput::GetInstance()->AddTree("TriFermiFunction");
		TriRootOutput::GetInstance()->AddBranch<double>("TriFermiFunction", "kE", &kE,"D");
		TriRootOutput::GetInstance()->AddBranch<double>("TriFermiFunction", "input", &input,"D");
		TriRootOutput::GetInstance()->AddBranch<double>("TriFermiFunction", "output", &output,"D");
		TriRootOutput::GetInstance()->AddBranch<double>("TriFermiFunction", "eta", &eta,"D");
		TriRootOutput::GetInstance()->AddBranch<double>("TriFermiFunction", "beta", &beta,"D");
		TriRootOutput::GetInstance()->AddBranch<double>("TriFermiFunction", "gamma", &gamma,"D");
		TriRootOutput::GetInstance()->AddBranch<double>("TriFermiFunction", "factor", &factor,"D");
	}


}