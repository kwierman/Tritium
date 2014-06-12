#include "TritiumMCEngine.h"
#include "TriRootOutput.h"
#include "TriElementPrototype.h"

#include <cstdlib>

#include "TriLogger.h"


Tritium::TritiumMCEngine::TritiumMCEngine() : lowEnergy(0.0), highEnergy(16.1), nBins(100000), elementModel(NULL), name("Default_Tritium"){
	d_config.insert(std::make_pair("lowEnergy", &TritiumMCEngine::setLowEnergy ) );
	d_config.insert(std::make_pair("highEnergy", &TritiumMCEngine::setHighEnergy ) );
	d_config.insert(std::make_pair("nBins", &TritiumMCEngine::setNBins ) );
}

void  Tritium::TritiumMCEngine::Run() const{

	if(!elementModel){
		TriLog(TriLogger::kWarning)<<"element Model is NULL, Exiting..."<<Tritium::endl;
		return;
	}
	TriRootOutput::GetInstance()->CreateNewFile(this->name);

	elementModel->Initialize();

	TriLog(TriLogger::kHeader)<<"TritiumMCEngine is now Running"<<Tritium::endl;
	double binWidth = ((this->highEnergy)-(this->lowEnergy))/(double(nBins) );
	TriLog(TriLogger::kNormal)<<"Bin Widths are: "<<binWidth<<" keV wide"<<Tritium::endl;
	TriLog(TriLogger::kNormal)<<"High Energy: "<<this->highEnergy<<Tritium::endl;
	TriLog(TriLogger::kNormal)<<"Low Energy: "<<this->lowEnergy<<Tritium::endl;
	TriLog(TriLogger::kNormal)<<"NBins: "<<this->nBins<<Tritium::endl;

	for(double kE = lowEnergy ;kE<= highEnergy ;kE+=binWidth ){
		elementModel->Compute(kE, 1.0);
	}
	TriLog(TriLogger::kGood)<<"Finished"<<Tritium::endl;

	elementModel->Close();

	TriLog(TriLogger::kHeader)<<"Closing Output Files"<<Tritium::endl;
	TriRootOutput::GetInstance()->WriteAllTrees();
	TriRootOutput::GetInstance()->Finish();
	TriLog(TriLogger::kGood)<<"Finished"<<Tritium::endl;

	TriLog(TriLogger::kGood)<<"Calculation Closing"<<Tritium::endl;
}

void Tritium::TritiumMCEngine::SetEnergyRange(double const& low, double const& high){
	this->lowEnergy = low;
	this->highEnergy = high;
}

void Tritium::TritiumMCEngine::AddElement(TriElement* element){
	if(elementModel)
		elementModel->setNext(element);
	else
		elementModel = element;
}

void Tritium::TritiumMCEngine::Set(std::string key, std::string value){
	TriLog(TriLogger::kGood)<<"Setting: "<<key<<", "<<value<<Tritium::endl;

	double newValue = std::atof(value.c_str() );

	d_func call = d_config[key];
	if(!call) return;
	(this->*call)(newValue);
}

