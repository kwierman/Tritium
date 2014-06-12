#include "TriRelativisticFermiFunction.h"
#include "TriRootOutput.h"

#include "TMath.h"
#include "TriConstants.h"
#include "TriLogger.h"

namespace Tritium{

	REGISTER_DEF_TYPE(TriRelativisticFermiFunction);

	TriRelativisticFermiFunction::TriRelativisticFermiFunction() :  
		TriElementPrototype<TriRelativisticFermiFunction>() , 
		eta(0.0), beta(0.0), gamma(0.0), Z(2.0), R(1.87e-15), V0(0){
		AddValueToMap("Z",&TriRelativisticFermiFunction::SetZ);
		AddValueToMap("R",&TriRelativisticFermiFunction::SetR);
		AddValueToMap("V0",&TriRelativisticFermiFunction::SetV0);
	}

	void TriRelativisticFermiFunction::Init(){
		S = TMath::Sqrt(1.0-( (Z*Alpha) * (Z*Alpha) ) )-1.0;
		TriLog(TriLogger::kNormal)<<"Initializing Relativistic Fermi Function: "<<S<<Tritium::endl;
	}

	void TriRelativisticFermiFunction::dNdE(double kE){
		double adjusted_Energy = kE-V0;


		this->gamma = 1.0 + (adjusted_Energy)/(ElectronMasseV);
		this->beta = TMath::Sqrt(1.0 - 1.0/(gamma*gamma) );
		this->eta = Z*Alpha/(beta);
		this->p_e = beta*gamma*ElectronMasseV/(C);

		this->factor = 2.0*(S+2.0);
		double interior_factor = 2.0*(this->p_e)*ElectronMasseV*C*R/(HBar);
		this->kinematic_factor = TMath::Power(interior_factor, 2.0*S );
		this->factor *= this->kinematic_factor;
		this->factor *= TMath::Exp(TMath::Pi() * this->eta );

		this->phase_factor = TMath::Power( TMath::Abs(TMath::Gamma(1+S+eta)),2.0)/TMath::Power( TMath::Abs(TMath::Gamma(3.0+2.0*S)),2.0 );

		this->factor *=phase_factor;
		if(adjusted_Energy<=0 || 1+S+eta==0 ){
			this->factor=0;
		}
		this->output = (this->factor) * (this->input);

		TriRootOutput::GetInstance()->FillTree("TriRelativisticFermiFunction");
	}
	void TriRelativisticFermiFunction::OnNewFileCreate(){
		TriRootOutput::GetInstance()->AddTree("TriRelativisticFermiFunction");
		TriRootOutput::GetInstance()->AddBranch<double>("TriRelativisticFermiFunction", "kE", &kE,"D");
		TriRootOutput::GetInstance()->AddBranch<double>("TriRelativisticFermiFunction", "input", &input,"D");
		TriRootOutput::GetInstance()->AddBranch<double>("TriRelativisticFermiFunction", "output", &output,"D");
		TriRootOutput::GetInstance()->AddBranch<double>("TriRelativisticFermiFunction", "factor", &factor,"D");
		TriRootOutput::GetInstance()->AddBranch<double>("TriRelativisticFermiFunction", "eta", &eta,"D");
		TriRootOutput::GetInstance()->AddBranch<double>("TriRelativisticFermiFunction", "beta", &beta,"D");
		TriRootOutput::GetInstance()->AddBranch<double>("TriRelativisticFermiFunction", "gamma", &gamma,"D");
		TriRootOutput::GetInstance()->AddBranch<double>("TriRelativisticFermiFunction", "p_e", &p_e,"D");
		TriRootOutput::GetInstance()->AddBranch<double>("TriRelativisticFermiFunction", "kinematic_factor", &kinematic_factor,"D");
		TriRootOutput::GetInstance()->AddBranch<double>("TriRelativisticFermiFunction", "phase_factor", &phase_factor,"D");
	}
}