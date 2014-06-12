#ifndef TriPhaseSpaceGenerator_h_
#define TriPhaseSpaceGenerator_h_	




namespace Tritium{

	//for holding small bits of phase space
	struct TriPhaseSpaceElement{
		std::string fName;
		double fValue;
	};

	//For holding 
	struct TriPhaseSpaceComposite{
		std::vector<TriPhaseSpaceElement> fElements;
	};


	class TriPhaseSpaceGenerator{

	};
}

#endif //TriPhaseSpaceGenerator_h_