#ifndef  TriSaenzJonsellTail_h_
#define  TriSaenzJonsellTail_h_

#include "TriElementPrototype.h"

/**
* Phys. Rev. Lett. Vol. 84 Num. 2 (2000)                                        
* equation (1)  
*/

namespace Tritium{

	class TriSaenzJonsellTail : public TriElementPrototype<TriSaenzJonsellTail> {
	private:
		//data
		double N;
		double a;
		double b;
		double low_cutoff;
		double high_cutoff;
		double norm;

	public:
		TriSaenzJonsellTail();

		void SetN(double x){this->N = x;}
		void SetA(double x){this->a = x;}
		void SetB(double x){this->b = x;}
		void SetLowCutoff(double x){this->low_cutoff = x;}
		void SetHighCutoff(double x){this->high_cutoff = x;}
		void SetNorm(double x){this->norm = x;}

		void Init();

		void dNdE(double kE);
		virtual void OnNewFileCreate();	

		REGISTER_DEC_TYPE(TriSaenzJonsellTail);
	};
}




#endif //TriSaenzJonsellTail_h_
