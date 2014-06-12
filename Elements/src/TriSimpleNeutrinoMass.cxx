#include "TriSimpleNeutrinoMass.h"
#include "TriConstants.h"
#include "TriRootOutput.h"

#include "TMath.h"


namespace Tritium{
	REGISTER_DEF_TYPE(TriSimpleNeutrinoMass);

	TriSimpleNeutrinoMass::TriSimpleNeutrinoMass() :   TriElementPrototype<TriSimpleNeutrinoMass>(), 
		q_value(1.e6), norm(1.0), neutrino_mass(0.0) {
			AddValueToMap("endpoint", &TriSimpleNeutrinoMass::SetEndPoint );
			AddValueToMap("norm",&TriSimpleNeutrinoMass::SetNorm );
			AddValueToMap("neutrino_mass",&TriSimpleNeutrinoMass::SetNeutrinoMass);
	} 

	void TriSimpleNeutrinoMass::dNdE(double kE){
		//This is the simple treatment of the non-positive neutrino mass
		this->factor= TMath::Power(q_value-kE, 2) - TMath::Sign(1.0, neutrino_mass)*TMath::Power(neutrino_mass, 2);	
		if(this->factor>0)
			this->factor = TMath::Sqrt(this->factor);
		this->factor *= norm*Vud*Vud;
		this->output = (double) (this->input)*(this->factor);
		if(this->output<0.0)
			this->output=0.0;
		TriRootOutput::GetInstance()->FillTree("TriSimpleNeutrinoMass");
	}

	void TriSimpleNeutrinoMass::OnNewFileCreate() {
		TriRootOutput::GetInstance()->AddTree("TriSimpleNeutrinoMass");
		TriRootOutput::GetInstance()->AddBranch<double>("TriSimpleNeutrinoMass", "kE", &kE,"D");
		TriRootOutput::GetInstance()->AddBranch<double>("TriSimpleNeutrinoMass", "input", &input,"D");
		TriRootOutput::GetInstance()->AddBranch<double>("TriSimpleNeutrinoMass", "output", &output,"D");
		TriRootOutput::GetInstance()->AddBranch<double>("TriSimpleNeutrinoMass", "factor", &factor,"D");
	}
}