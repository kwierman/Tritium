#ifndef TriGaussianFunction_h_
#define TriGaussianFunction_h_


#include "TriElementPrototype.h"

namespace Tritium{

	class TriGaussianFunction : public TriElementPrototype<TriGaussianFunction> {
	private:
		double mean;
		double sigma;
		double offset;

	public:
		TriGaussianFunction();

		void SetMean(double x){this->mean = x;}
		void SetSigma(double x){this->sigma = x;}
		void SetOffset(double x){this->offset=x;}

		void Init(){}

		void dNdE(double kE);
		virtual void OnNewFileCreate();

	private:
		REGISTER_DEC_TYPE(TriGaussianFunction);
	};
}

#endif //TriGaussianFunction_h_