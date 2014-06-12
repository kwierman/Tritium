#include "TriDifferentiator.h"
#include "TriRootOutput.h"

#include "TMath.h"
#include "TriConstants.h"

namespace Tritium{

	REGISTER_DEF_TYPE(TriDifferentiator);

	TriDifferentiator::TriDifferentiator() :  TriElementPrototype<TriDifferentiator>(), norm(1.0),previousP(0.0) {
		AddValueToMap("norm",&TriDifferentiator::SetNorm);
	}

	void TriDifferentiator::dNdE(double kE){
		this->factor = this->input-this->previousP;
		this->previousP= this->input;
		this->output = (this->factor)*(this->norm);
		TriRootOutput::GetInstance()->FillTree("TriDifferentiator");
	}
	void TriDifferentiator::OnNewFileCreate(){
		TriRootOutput::GetInstance()->AddTree("TriDifferentiator");
		TriRootOutput::GetInstance()->AddBranch<double>("TriDifferentiator", "kE", &kE,"D");
		TriRootOutput::GetInstance()->AddBranch<double>("TriDifferentiator", "input", &input,"D");
		TriRootOutput::GetInstance()->AddBranch<double>("TriDifferentiator", "output", &output,"D");
		TriRootOutput::GetInstance()->AddBranch<double>("TriDifferentiator", "factor", &factor,"D");
		TriRootOutput::GetInstance()->AddBranch<double>("TriDifferentiator", "norm", &norm,"D");
	}


}