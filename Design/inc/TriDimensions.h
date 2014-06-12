#ifndef TriDimensions_h_
#define TriDimensions_h_

#include "TriSequence.h"

namespace TritiumDesign{

	//For Multiplying Quantities, add dimensions
	
	template<class Seq1, class Seq2>
	struct TriDimensionAdd{
		typedef typename TriSequence<int, 	IntType< Seq1::Tail::Head::value + Seq2::Tail::Head::value >,
									IntType< Seq1::Tail::Tail::Head::value + Seq2::Tail::Tail::Head::value >,
									IntType< Seq1::Tail::Tail::Tail::Head::value + Seq2::Tail::Tail::Tail::Head::value >,
									IntType< Seq1::Tail::Tail::Tail::Tail::Head::value + Seq2::Tail::Tail::Tail::Tail::Head::value >,
									IntType< Seq1::Tail::Tail::Tail::Tail::Tail::Head::value + Seq2::Tail::Tail::Tail::Tail::Tail::Head::value >,
									IntType< Seq1::Tail::Tail::Tail::Tail::Tail::Tail::Head::value + Seq2::Tail::Tail::Tail::Tail::Tail::Tail::Head::value >,
									IntType< Seq1::Tail::Tail::Tail::Tail::Tail::Tail::Tail::Head::value + Seq2::Tail::Tail::Tail::Tail::Tail::Tail::Tail::Head::value >
		 >::Type Type;
	};
	//For Dividing Quantities, subtract dimensions
	template<class Seq1, class Seq2>
	struct TriDimensionSubtract{
		typedef typename TriSequence<int, 	IntType< Seq1::Tail::Head::value - Seq2::Tail::Head::value >,
									IntType< Seq1::Tail::Tail::Head::value - Seq2::Tail::Tail::Head::value >,
									IntType< Seq1::Tail::Tail::Tail::Head::value - Seq2::Tail::Tail::Tail::Head::value >,
									IntType< Seq1::Tail::Tail::Tail::Tail::Head::value - Seq2::Tail::Tail::Tail::Tail::Head::value >,
									IntType< Seq1::Tail::Tail::Tail::Tail::Tail::Head::value - Seq2::Tail::Tail::Tail::Tail::Tail::Head::value >,
									IntType< Seq1::Tail::Tail::Tail::Tail::Tail::Tail::Head::value - Seq2::Tail::Tail::Tail::Tail::Tail::Tail::Head::value >,
									IntType< Seq1::Tail::Tail::Tail::Tail::Tail::Tail::Tail::Head::value - Seq2::Tail::Tail::Tail::Tail::Tail::Tail::Tail::Head::value >
		 >::Type Type;
	};
	


	//base dimensions
	typedef TriSequence<int, IntType<0>,IntType<0>,IntType<0>,IntType<0>,IntType<0>,IntType<0>,IntType<0> >::Type scalar;
	typedef TriSequence<int, IntType<0>,IntType<0>,IntType<0>,IntType<1>,IntType<0>,IntType<0>,IntType<0> >::Type charge;
	typedef TriSequence<int, IntType<1>,IntType<0>,IntType<0>,IntType<0>,IntType<0>,IntType<0>,IntType<0> >::Type mass;
	typedef TriSequence<int, IntType<0>,IntType<1>,IntType<0>,IntType<0>,IntType<0>,IntType<0>,IntType<0> >::Type length;
	typedef TriSequence<int, IntType<0>,IntType<0>,IntType<1>,IntType<0>,IntType<0>,IntType<0>,IntType<0> >::Type time;
	typedef TriSequence<int, IntType<0>,IntType<0>,IntType<0>,IntType<0>,IntType<1>,IntType<0>,IntType<0> >::Type temperature;
	typedef TriSequence<int, IntType<0>,IntType<0>,IntType<0>,IntType<0>,IntType<0>,IntType<1>,IntType<0> >::Type intensity;
	typedef TriSequence<int, IntType<0>,IntType<0>,IntType<0>,IntType<0>,IntType<0>,IntType<0>,IntType<1> >::Type angle;

	//derived dimensions
	
	typedef TriDimensionSubtract<scalar, time>::Type 					rate;
	typedef TriDimensionSubtract<length, time>::Type 					velocity;
	typedef TriDimensionSubtract<velocity, time>::Type 					acceleration;
	typedef TriDimensionAdd<acceleration, mass >::Type 					force;
	typedef TriDimensionAdd<mass, velocity>::Type 						momentum;
	typedef TriDimensionAdd<force, length>::Type 						energy;
	typedef TriDimensionAdd<energy, time>::Type 						action;
	typedef TriDimensionSubtract<
			TriDimensionSubtract<scalar, energy>::Type, energy>::Type 	fermiDimension;
	typedef TriDimensionSubtract<charge, time>::Type 					current;
	typedef TriDimensionSubtract< 
			TriDimensionSubtract<force, current>::Type, current>::Type 	magneticFluxDensity;
	typedef TriDimensionSubtract<scalar, 
			TriDimensionAdd<magneticFluxDensity, 
			TriDimensionAdd<velocity, velocity>::Type>::Type  >::Type 	electricFluxDensity;
}

#endif //TriDimensions_h_