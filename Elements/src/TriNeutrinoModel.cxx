#include "TriNeutrinoModel.h"
#include "TriRootOutput.h"

#include "TMath.h"

namespace Tritium{

	REGISTER_DEF_TYPE(TriNeutrinoModel);

	TriNeutrinoModel::TriNeutrinoModel() : TriElementPrototype<TriNeutrinoModel>() , 
		isInverted(false), currentI(0), currentJ(0), q_value(1.e6), fPMNS(3,3), fMassEigenstates(3),fFlavorMasses(3)
	{
		fPMNS.UnitMatrix(); 
		for(int i=0; i<3;i++){
			fMassEigenstates[i]=1.0;
			fFlavorMasses[i]=1.0;
			individual_factor[i]=0;
		}
		AddValueToMap("mass", &TriNeutrinoModel::setMassOrdered );
		AddValueToMap("pmns", &TriNeutrinoModel::setPMNSOrdered );
		AddValueToMap("endpoint", &TriNeutrinoModel::setQValue );
	}

	void TriNeutrinoModel::OnNewFileCreate(){
		TriRootOutput::GetInstance()->AddTree("TriNeutrinoModel");
		TriRootOutput::GetInstance()->AddBranch<double>("TriNeutrinoModel", "kE",      &kE,                    "D");
		TriRootOutput::GetInstance()->AddBranch<double>("TriNeutrinoModel", "input",   &input,                 "D");
		TriRootOutput::GetInstance()->AddBranch<double>("TriNeutrinoModel", "output",  &output,                "D");
		TriRootOutput::GetInstance()->AddBranch<double>("TriNeutrinoModel", "factor",  &factor,                "D");
		TriRootOutput::GetInstance()->AddBranch<double>("TriNeutrinoModel", "factor1", &(individual_factor[0]),"D");
		TriRootOutput::GetInstance()->AddBranch<double>("TriNeutrinoModel", "factor2", &(individual_factor[1]),"D");
		TriRootOutput::GetInstance()->AddBranch<double>("TriNeutrinoModel", "factor3", &(individual_factor[2]),"D");
	}

	void TriNeutrinoModel::setPMNS(int i, int j, double x){
		fPMNS[i][j]=x;
	}

	void TriNeutrinoModel::setMass(int i, double x){
		fMassEigenstates[i]=x;
	}

	void TriNeutrinoModel::setPMNSOrdered(double x){
		setPMNS(currentI,currentJ,x);
		currentJ++;
		if(currentJ==3){
			currentJ=0;
			currentI++;
		}	
		if(currentI==3){
			currentI=0;
		}
	}
	
	void TriNeutrinoModel::setMassOrdered(double x){
		setMass(currentI, x);
		currentI++;
		if(currentI==3)
			currentI=0;
	}

	void TriNeutrinoModel::dNdE(double kE){
		long double value = 0.0;
		for(int i=0; i<3;i++ ){
			if( ( (q_value-kE)- fMassEigenstates[i]) > 0  ){//this is for the step function required by conservation of energy
				individual_factor[i]=((fPMNS*fPMNS)[0][i])*TMath::Sqrt( (q_value-kE)*(q_value-kE)-fMassEigenstates[i]*fMassEigenstates[i] );
				value+=individual_factor[i];
			}
		}
		this->factor = value;
		this->output = (value)*(this->input);
		TriRootOutput::GetInstance()->FillTree("TriNeutrinoModel");
	}
}