#ifndef TriPhaseSpace_h_
#define TriPhaseSpace_h_

namespace Tritium{

	//Defines a single "Element" in phase space. i.e,. one 
	struct TriPhaseSpaceElement{
		double kE;//!< energy
		TriVector fMomentum;//<! Momentum
		TriVector fPosition;//<! Position
		double kWeight;//<! Weighting of that phase space element
	};

	//Defines out the phase space to be spanned by this
	struct TriPhaseSpaceSpan{
		TriPhaseSpaceElement fBegin;
		TriPhaseSpaceElement fEnd;
	};
}

#endif //TriPhaseSpace_h_