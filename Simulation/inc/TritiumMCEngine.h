#ifndef TritiumMCEngine_h_
#define TritiumMCEngine_h_ 1

#include <iostream>
#include "TriElementPrototype.h"

#include <string>
#include <map>

namespace Tritium{

	class TritiumMCEngine {

		//fields
	private:
		double lowEnergy;
		double highEnergy;
		double nBins;
		TriElement* elementModel;
		std::string name;

		typedef void (TritiumMCEngine::*d_func)(double);
		std::map<std::string, d_func > d_config;

	public:
		static TritiumMCEngine* GetInstance(){
			static TritiumMCEngine* instance = new TritiumMCEngine();
			return instance;
		}

		void Run() const;

		void SetEnergyRange(double const& low, double const& high);
		void AddElement(TriElement* decay);

		void setLowEnergy(double x){
			this->lowEnergy=x;
		}
		void setHighEnergy(double x){
			this->highEnergy=x;
		}
		void setNBins(double x){
			this->nBins=x;
		}
		double getBinWidth(){return (highEnergy-lowEnergy)/(nBins);}
		double getLowEnergy(){return lowEnergy;}
		double getHighEnergy(){return highEnergy;}

		void SetName(std::string name){ 
			if(elementModel)
				this->Run();
			delete elementModel;
			elementModel=NULL;
			name+=".root";
			this->name = name; 
		}
		void Set(std::string key, std::string value);

	private:
		TritiumMCEngine() ;
		TritiumMCEngine(TritiumMCEngine& other){}
		const TritiumMCEngine& operator=(const TritiumMCEngine& other);
		~TritiumMCEngine(){}
	};
}

#endif //TritiumMCEngine_h_

