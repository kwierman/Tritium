#ifndef TriDiscreteExcitation_h_
#define TriDiscreteExcitation_h_

#include "TriElementPrototype.h"

#include <map>

namespace Tritium{
	class TriDiscreteExcitation : public TriElementPrototype<TriDiscreteExcitation>{
	private:
		std::map<double, double> fEToP;
		double fLowEnergy;
		double fHighEnergy;
		double fBinWidth;//<! The width of the bins being examined by this module

		double* fCurrentEInput;
		double* fCurrentPInput;

	public:
		TriDiscreteExcitation();
		void setEnergy(double x);
		void setProbability(double x);
		void setBinWidth(double x){this->fBinWidth =x;}
		void setLowEnergy(double x){this->fLowEnergy =x;}
		void setHighEnergy(double x){this->fHighEnergy =x;}

		void Init(){}
		/// The compute function is getting
		virtual void Compute(double kE, double prevValue);

		void dNdE(double kE);

		void OnNewFileCreate();

		REGISTER_DEC_TYPE(TriDiscreteExcitation);
	};
}

#endif //TriDiscreteExcitation_h_