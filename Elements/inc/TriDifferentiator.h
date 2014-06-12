#ifndef TriDifferentiator_h_
#define TriDifferentiator_h_

#include "TriElementPrototype.h"

namespace Tritium{

	class TriDifferentiator : public TriElementPrototype<TriDifferentiator> {
	private:
		double norm;
		double previousP;

	public:
		TriDifferentiator();

		void SetNorm(double x){this->norm = x;}

		void Init(){this->factor+=0.0;}

		void dNdE(double kE);
		virtual void OnNewFileCreate();

	private:
		REGISTER_DEC_TYPE(TriDifferentiator);
	};
}

#endif //TriDifferentiator_h_