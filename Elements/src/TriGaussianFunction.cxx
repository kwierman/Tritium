#include "TriGaussianFunction.h"
#include "TriRootOutput.h"

#include "TMath.h"
#include "TriConstants.h"

namespace Tritium{

	TriGaussianFunction::TriGaussianFunction() :  TriElementPrototype<TriGaussianFunction>(), 
	mean(1.0), sigma(1.0), offset(1.0){
		AddValueToMap("mean",&TriGaussianFunction::SetMean);
		AddValueToMap("sigma",&TriGaussianFunction::SetSigma);
		AddValueToMap("offset",&TriGaussianFunction::SetOffset);
	}

	void TriGaussianFunction::dNdE(double kE){
		this-> factor = TMath::Gaus(kE, this->mean,this->sigma) + this->offset;
		this->output = (this->factor)*(this->input);
		TriRootOutput::GetInstance()->FillTree("TriGaussianFunction");
	}
	void TriGaussianFunction::OnNewFileCreate(){
		TriRootOutput::GetInstance()->AddTree("TriGaussianFunction");
		TriRootOutput::GetInstance()->AddBranch<double>("TriGaussianFunction", "kE", &kE,"D");
		TriRootOutput::GetInstance()->AddBranch<double>("TriGaussianFunction", "input", &input,"D");
		TriRootOutput::GetInstance()->AddBranch<double>("TriGaussianFunction", "output", &output,"D");
		TriRootOutput::GetInstance()->AddBranch<double>("TriGaussianFunction", "mean", &mean,"D");
		TriRootOutput::GetInstance()->AddBranch<double>("TriGaussianFunction", "sigma", &sigma,"D");
		TriRootOutput::GetInstance()->AddBranch<double>("TriGaussianFunction", "offset", &offset,"D");
		TriRootOutput::GetInstance()->AddBranch<double>("TriGaussianFunction", "factor", &factor,"D");
	}

	REGISTER_DEF_TYPE(TriGaussianFunction);
}