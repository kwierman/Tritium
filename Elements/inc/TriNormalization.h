#ifndef TriNormalization_h_
#define TriNormalization_h_

#include "TriElementPrototype.h"

#include "TMath.h"
#include <iostream>

/**
 * Note that Type=1.0 = Simpson's and Rose's Approximation and 2=Longmire and Brown's Approximation
 **/

namespace Tritium{

	class TriHist;

	class TriNormalization : public TriElementPrototype<TriNormalization>{
	private:
		double norm;
		double total;
		TriHist* hist;

	public:
		TriNormalization();
		void SetNorm(double x){this->norm = x;}

		void Init(){}

		void Close();

		void dNdE(double kE);
		virtual void OnNewFileCreate();

	private:
		REGISTER_DEC_TYPE(TriNormalization);

	};
}

#endif //TriNormalization_h_