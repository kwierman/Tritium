#include "TriNormalization.h"
#include "TriRootOutput.h"
#include "TritiumMCEngine.h"
#include "TriHist.h"

#include "TMath.h"
#include "TriConstants.h"

#include "TriLogger.h"

namespace Tritium{

	REGISTER_DEF_TYPE(TriNormalization);

	TriNormalization::TriNormalization() :  TriElementPrototype<TriNormalization>() , 
	norm(1.0), total(0.0){
		AddValueToMap("norm",&TriNormalization::SetNorm);
		//hist = new TriHist(TritiumMCEngine::GetInstance()->getLowEnergy(), TritiumMCEngine::GetInstance()->getHighEnergy(), TritiumMCEngine::GetInstance()->getBinWidth() );

		hist = new TriHist(TritiumMCEngine::GetInstance()->getLowEnergy(), TritiumMCEngine::GetInstance()->getBinWidth() );
	}

	void TriNormalization::dNdE(double kE){
		hist->Put(kE, input);
		total+=input;
		output = input;
	}

	void TriNormalization::Close(){
		TriLog(TriLogger::kHeader)<<"Normalizing..."<<Tritium::endl;
		this->factor = this->norm/total;
		double lo = TritiumMCEngine::GetInstance()->getLowEnergy();
		double hi = TritiumMCEngine::GetInstance()->getHighEnergy();
		double width = TritiumMCEngine::GetInstance()->getBinWidth();
		for(double bin = lo; bin<=hi; bin+= width){
			this->kE = bin;
			this->input = hist->Get(bin);
			this->output = (this->input)*(this->factor);
			TriRootOutput::GetInstance()->FillTree("TriNormalization");			
		}
		TriLog(TriLogger::kGood)<<"Finished"<<Tritium::endl;
	}

	void TriNormalization::OnNewFileCreate(){
		TriRootOutput::GetInstance()->AddTree("TriNormalization");
		TriRootOutput::GetInstance()->AddBranch<double>("TriNormalization", "kE", &kE,"D");
		TriRootOutput::GetInstance()->AddBranch<double>("TriNormalization", "input", &input,"D");
		TriRootOutput::GetInstance()->AddBranch<double>("TriNormalization", "output", &output,"D");
		TriRootOutput::GetInstance()->AddBranch<double>("TriNormalization", "factor", &factor,"D");
	}


}