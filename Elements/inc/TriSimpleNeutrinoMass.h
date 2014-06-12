#ifndef TriSimpleNeutrinoMass_h_
#define TriSimpleNeutrinoMass_h_ 1

#include "TriElementPrototype.h"

#include <string>

namespace Tritium{

	/**
	 * \class TriSimpleNeutrinoMass
	 * Computes the basic beta decay spectrum for a 
	 */
	class TriSimpleNeutrinoMass : public TriElementPrototype<TriSimpleNeutrinoMass> {
	private:
		double q_value;
		double norm;
		double neutrino_mass;

	public:
		TriSimpleNeutrinoMass();

		void SetEndPoint(double x){this->q_value = x;}
		void SetNorm(double x){this->norm = x;}
		void SetNeutrinoMass(double x){this->neutrino_mass = x;}

		void Init(){}

		void dNdE(double kE);

		void OnNewFileCreate();

		REGISTER_DEC_TYPE(TriSimpleNeutrinoMass);
	};

}


#endif /* TriSimpleNeutrinoMass_h_ */