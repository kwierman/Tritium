#include "TriIntegrator.h"
#include "TriRootOutput.h"

#include "TMath.h"
#include "TriConstants.h"

namespace Tritium{

	REGISTER_DEF_TYPE(TriIntegrator);

	TriIntegrator::TriIntegrator() :  TriElementPrototype<TriIntegrator>(), norm(1.0) {
		AddValueToMap("norm",&TriIntegrator::SetNorm);
	}

	void TriIntegrator::dNdE(double kE){
		this->factor += this->input;
		this->output = (this->factor)*(this->norm);

		TriRootOutput::GetInstance()->FillTree("TriIntegrator");
	}
	void TriIntegrator::OnNewFileCreate(){
		TriRootOutput::GetInstance()->AddTree("TriIntegrator");
		TriRootOutput::GetInstance()->AddBranch<double>("TriIntegrator", "kE", &kE,"D");
		TriRootOutput::GetInstance()->AddBranch<double>("TriIntegrator", "input", &input,"D");
		TriRootOutput::GetInstance()->AddBranch<double>("TriIntegrator", "output", &output,"D");
		TriRootOutput::GetInstance()->AddBranch<double>("TriIntegrator", "factor", &factor,"D");
		TriRootOutput::GetInstance()->AddBranch<double>("TriIntegrator", "norm", &norm,"D");
	}


}