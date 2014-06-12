#include "TriSaenzJonsellTail.h"

#include "TMath.h"

namespace Tritium{
	REGISTER_DEF_TYPE(TriSaenzJonsellTail);

	TriSaenzJonsellTail::TriSaenzJonsellTail() : TriElementPrototype<TriSaenzJonsellTail>(),
		N(14.7) , low_cutoff(240), high_cutoff(2240) , a(45), b(13.606), norm(100.0) {

		AddValueToMap("N", &TriSaenzJonsellTail::SetN);
		AddValueToMap("a", &TriSaenzJonsellTail::SetA);
		AddValueToMap("b", &TriSaenzJonsellTail::SetB);
		AddValueToMap("lowCutOff", &TriSaenzJonsellTail::SetLowCutoff);
		AddValueToMap("HighCutoff", &TriSaenzJonsellTail::SetHighCutoff);
		AddValueToMap("norm", &TriSaenzJonsellTail::SetNorm);
	}

	void TriSaenzJonsellTail::dNdE(double kE){
		this->input +=1.0;
		if(kE<=low_cutoff){
			this->factor = 1.0;
		}
		else if(kE<high_cutoff) {

			double kappa = TMath::Sqrt( (kE-a)/b );
			this->factor = N;
			this->factor *= 8*TMath::Exp((-4.0*TMath::ATan(kappa))/kappa);
			this->factor *= 8*TMath::Exp((-4.0*TMath::ATan(kappa))/kappa);
			this->factor /= TMath::Sqrt(1 - TMath::Exp(-4.0*TMath::Pi()/kappa)  )*(1 + kappa*kappa)*(1 + kappa*kappa);
			this->factor /= TMath::Sqrt(1 - TMath::Exp(-4.0*TMath::Pi()/kappa)  )*(1 + kappa*kappa)*(1 + kappa*kappa);
			this->factor *=(this->norm);
		}

		this->output = (this->factor+1.0)*(this->input);

		TriRootOutput::GetInstance()->FillTree("TriSaenzJonsellTail");
	}

	void TriSaenzJonsellTail::Init(){
		this->kE = low_cutoff;
		double kappa = TMath::Sqrt( (kE-a)/b );
		this->factor = N;
		this->factor *= 8*TMath::Exp((-4.0*TMath::ATan(kappa))/kappa);
		this->factor *= 8*TMath::Exp((-4.0*TMath::ATan(kappa))/kappa);
		this->factor /= TMath::Sqrt(1 - TMath::Exp(-4.0*TMath::Pi()/kappa)  )*(1 + kappa*kappa)*(1 + kappa*kappa);
		this->factor /= TMath::Sqrt(1 - TMath::Exp(-4.0*TMath::Pi()/kappa)  )*(1 + kappa*kappa)*(1 + kappa*kappa);
		this->norm = 1.0/(this->factor);

	}

	void TriSaenzJonsellTail::OnNewFileCreate(){
		TriRootOutput::GetInstance()->AddTree("TriSaenzJonsellTail");
		TriRootOutput::GetInstance()->AddBranch<double>("TriSaenzJonsellTail", "kE", &kE,"D");
		TriRootOutput::GetInstance()->AddBranch<double>("TriSaenzJonsellTail", "input", &input,"D");
		TriRootOutput::GetInstance()->AddBranch<double>("TriSaenzJonsellTail", "output", &output,"D");
		TriRootOutput::GetInstance()->AddBranch<double>("TriSaenzJonsellTail", "factor", &factor,"D");
		TriRootOutput::GetInstance()->AddBranch<double>("TriSaenzJonsellTail", "N", &N,"D");
		TriRootOutput::GetInstance()->AddBranch<double>("TriSaenzJonsellTail", "a", &a,"D");
		TriRootOutput::GetInstance()->AddBranch<double>("TriSaenzJonsellTail", "b", &b,"D");
		TriRootOutput::GetInstance()->AddBranch<double>("TriSaenzJonsellTail", "low_cutoff", &low_cutoff,"D");
		TriRootOutput::GetInstance()->AddBranch<double>("TriSaenzJonsellTail", "high_cutoff", &high_cutoff,"D");
		TriRootOutput::GetInstance()->AddBranch<double>("TriSaenzJonsellTail", "norm", &norm,"D");
	}
}