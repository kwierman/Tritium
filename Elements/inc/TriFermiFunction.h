#ifndef TriFermiFunction_h_
#define TriFermiFunction_h_

#include "TriElementPrototype.h"

namespace Tritium{

	class TriFermiFunction : public TriElementPrototype<TriFermiFunction> {
	private:
		double eta;
		double beta;
		double gamma;
		double Z;

	public:
		TriFermiFunction();

		void SetZ(double x){this->Z = x;}

		void Init(){}

		void dNdE(double kE);
		virtual void OnNewFileCreate();

	private:
		REGISTER_DEC_TYPE(TriFermiFunction);
	};
}

#endif //TriFermiFunction_h_