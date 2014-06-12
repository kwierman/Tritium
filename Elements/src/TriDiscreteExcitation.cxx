#include "TriDiscreteExcitation.h"
#include "TriRootOutput.h"

namespace Tritium{

	REGISTER_DEF_TYPE(TriDiscreteExcitation);

	TriDiscreteExcitation::TriDiscreteExcitation() : TriElementPrototype<TriDiscreteExcitation>(),
	 fCurrentEInput(NULL), fCurrentPInput(NULL),fLowEnergy(0.0),fHighEnergy(1.e6), fBinWidth(1.0) {
			AddValueToMap("energy", &TriDiscreteExcitation::setEnergy);
			AddValueToMap("prob", &TriDiscreteExcitation::setProbability);
			AddValueToMap("binWidth", &TriDiscreteExcitation::setBinWidth);
			AddValueToMap("lowEnergy", &TriDiscreteExcitation::setLowEnergy);
			AddValueToMap("highEnergy", &TriDiscreteExcitation::setHighEnergy);
	}

	void TriDiscreteExcitation::OnNewFileCreate(){
		TriRootOutput* rootOutput =  TriRootOutput::GetInstance();
		rootOutput->AddTree("TriDiscreteExcitation");
		rootOutput->AddBranch<double>("TriDiscreteExcitation", "kE", &kE,"D");
		rootOutput->AddBranch<double>("TriDiscreteExcitation", "output", &output,"D");
		rootOutput->AddBranch<double>("TriDiscreteExcitation", "input", &input,"D");
		rootOutput->AddBranch<double>("TriDiscreteExcitation", "factor", &factor,"D");
	}

	void TriDiscreteExcitation::setEnergy(double x){
		this->fCurrentEInput = new double(x);
		if(fCurrentEInput && fCurrentPInput){
			fEToP[*fCurrentEInput] = *fCurrentPInput;
			delete fCurrentEInput;
			fCurrentEInput=NULL;
			delete fCurrentPInput;
			fCurrentPInput=NULL;
		}
	}

	void TriDiscreteExcitation::setProbability(double x){
		this->fCurrentPInput = new double(x);
		if(fCurrentEInput && fCurrentPInput){
			fEToP[*fCurrentEInput] = *fCurrentPInput;
			delete fCurrentEInput;
			fCurrentEInput=NULL;
			delete fCurrentPInput;
			fCurrentPInput=NULL;
		}
	}

	//This is being overriden in order to send the right functions on to another
	void TriDiscreteExcitation::Compute(double kE, double prevValue){
			this->input = prevValue;
			this->kE = kE;
			this->dNdE(kE);
		}

	void TriDiscreteExcitation::dNdE(double kE){
		//this should be 
		if(kE<fLowEnergy){
			this->factor=1.0;
			this->output = (this->factor) * (this->input);
			TriRootOutput::GetInstance()->FillTree("TriDiscreteExcitation");
			if( hasNext() )	getNext()->Compute(this->kE, this->output);
			return;
		}

		for(double adjust = fLowEnergy; adjust<=fHighEnergy; adjust+= fBinWidth){
				//the information we need here: to calculate out each energy loss and the probability of it happenning
			double newKe = kE-adjust;
			if(newKe<0) return;
			std::map<double,double>::iterator it = fEToP.lower_bound(adjust);
			if((it) != fEToP.end() ){
				this->kE = newKe;
				this->factor = (it->second);
				this->output = (it->second) * (this->input);
				TriRootOutput::GetInstance()->FillTree("TriDiscreteExcitation");
				if( hasNext() )	getNext()->Compute(this->kE, this->output);	
			}
		}
	}
}