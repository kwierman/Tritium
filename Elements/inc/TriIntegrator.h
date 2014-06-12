#ifndef TriIntegrator_h_
#define TriIntegrator_h_

#include "TriElementPrototype.h"

namespace Tritium{

	class TriIntegrator : public TriElementPrototype<TriIntegrator> {
	private:
		double norm;

	public:
		TriIntegrator();

		void SetNorm(double x){this->norm = x;}

		void Init(){this->factor+=0.0;}

		void dNdE(double kE);
		virtual void OnNewFileCreate();

	private:
		REGISTER_DEC_TYPE(TriIntegrator);
	};
}

#endif //TriIntegrator_h_