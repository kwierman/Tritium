#include "TriBetaKinematics.h"
#include "TriConstants.h"
#include "TriRootOutput.h"

#include "TMath.h"


namespace Tritium{
	REGISTER_DEF_TYPE(TriBetaKinematics);

	TriBetaKinematics::TriBetaKinematics() :   TriElementPrototype<TriBetaKinematics>(), 
		q_value(1.e6), norm(1.0) {
			AddValueToMap("endpoint", &TriBetaKinematics::SetEndPoint );
			AddValueToMap("norm",&TriBetaKinematics::SetNorm );
		} 

	void TriBetaKinematics::Init(){
		c_factor = cos_theta_c*NuclearMatrixElementSquared*Gf*Gf/(2.0*TMath::Pi()*TMath::Pi()*TMath::Pi());
	}


	void TriBetaKinematics::dNdE(double kE){
		this->kE = kE;
		this->factor=0.0;
		gamma = 1.0+(kE)/(ElectronMasseV);
		beta = TMath::Sqrt( (1.0)- (1.0/(gamma*gamma)) );

		P_e = beta*gamma*ElectronMasseV/(C);
		E_e = gamma*ElectronMasseV;
		delta_E = q_value - kE;
		if(delta_E>0)
			this->factor = c_factor*P_e*E_e*delta_E;
		this->factor *=this->norm;
		this->output = (this->input)*(this->factor);
		TriRootOutput::GetInstance()->FillTree("TriBetaKinematics");
	}

	void TriBetaKinematics::OnNewFileCreate() {
		TriRootOutput::GetInstance()->AddTree("TriBetaKinematics");
		TriRootOutput::GetInstance()->AddBranch<double>("TriBetaKinematics", "kE", &kE,"D");
		TriRootOutput::GetInstance()->AddBranch<double>("TriBetaKinematics", "input", &input,"D");
		TriRootOutput::GetInstance()->AddBranch<double>("TriBetaKinematics", "output", &output,"D");
		TriRootOutput::GetInstance()->AddBranch<double>("TriBetaKinematics", "factor", &factor,"D");
		TriRootOutput::GetInstance()->AddBranch<double>("TriBetaKinematics","gamma", &gamma,"D");
		TriRootOutput::GetInstance()->AddBranch<double>("TriBetaKinematics","beta", &beta,"D");
		TriRootOutput::GetInstance()->AddBranch<double>("TriBetaKinematics","c_factor", &c_factor,"D");
		TriRootOutput::GetInstance()->AddBranch<double>("TriBetaKinematics","P_e", &P_e,"D");
		TriRootOutput::GetInstance()->AddBranch<double>("TriBetaKinematics","E_e", &E_e,"D");
		TriRootOutput::GetInstance()->AddBranch<double>("TriBetaKinematics","delta_E", &delta_E,"D");
	}
}