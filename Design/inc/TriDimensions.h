#ifndef TriDimensions_h_
#define TriDimensions_h_

#include "TriSequence.h"

namespace TritiumDesign{

	//For Multiplying Quantities, add dimensions
	template<class Seq1, class Seq2>
	struct TriDimensionAdd{
		typedef TriSequence<int, 	IntType< Seq1::Type::Tail::Type::Head::value + Seq2::Type::Tail::Type::Head::value >,
									IntType< Seq1::Type::Tail::Type::Tail::Type::Head::value + Seq2::Type::Tail::Type::Tail::Type::Head::value >,
									IntType< Seq1::Type::Tail::Type::Tail::Type::Tail::Type::Head::value + Seq2::Type::Tail::Type::Tail::Type::Tail::Type::Head::value >,
									IntType< Seq1::Type::Tail::Type::Tail::Type::Tail::Type::Tail::Type::Head::value + Seq2::Type::Tail::Type::Tail::Type::Tail::Type::Tail::Type::Head::value >,
									IntType< Seq1::Type::Tail::Type::Tail::Type::Tail::Type::Tail::Type::Tail::Type::Head::value + Seq2::Type::Tail::Type::Tail::Type::Tail::Type::Tail::Type::Tail::Type::Head::value >,
									IntType< Seq1::Type::Tail::Type::Tail::Type::Tail::Type::Tail::Type::Tail::Type::Tail::Type::Head::value + Seq2::Type::Tail::Type::Tail::Type::Tail::Type::Tail::Type::Tail::Type::Tail::Type::Head::value >,
									IntType< Seq1::Type::Tail::Type::Tail::Type::Tail::Type::Tail::Type::Tail::Type::Tail::Type::Tail::Type::Head::value + Seq2::Type::Tail::Type::Tail::Type::Tail::Type::Tail::Type::Tail::Type::Tail::Type::Tail::Type::Head::value >
		 > Type;
	};
	//For Dividing Quantities, subtract dimensions
	template<class Seq1, class Seq2>
	struct TriDimensionSubtract{
		typedef TriSequence<int, 	IntType< Seq1::Type::Tail::Type::Head::value - Seq2::Type::Tail::Type::Head::value >,
									IntType< Seq1::Type::Tail::Type::Tail::Type::Head::value - Seq2::Type::Tail::Type::Tail::Type::Head::value >,
									IntType< Seq1::Type::Tail::Type::Tail::Type::Tail::Type::Head::value - Seq2::Type::Tail::Type::Tail::Type::Tail::Type::Head::value >,
									IntType< Seq1::Type::Tail::Type::Tail::Type::Tail::Type::Tail::Type::Head::value - Seq2::Type::Tail::Type::Tail::Type::Tail::Type::Tail::Type::Head::value >,
									IntType< Seq1::Type::Tail::Type::Tail::Type::Tail::Type::Tail::Type::Tail::Type::Head::value - Seq2::Type::Tail::Type::Tail::Type::Tail::Type::Tail::Type::Tail::Type::Head::value >,
									IntType< Seq1::Type::Tail::Type::Tail::Type::Tail::Type::Tail::Type::Tail::Type::Tail::Type::Head::value - Seq2::Type::Tail::Type::Tail::Type::Tail::Type::Tail::Type::Tail::Type::Tail::Type::Head::value >,
									IntType< Seq1::Type::Tail::Type::Tail::Type::Tail::Type::Tail::Type::Tail::Type::Tail::Type::Tail::Type::Head::value - Seq2::Type::Tail::Type::Tail::Type::Tail::Type::Tail::Type::Tail::Type::Tail::Type::Tail::Type::Head::value >
		 > Type;
	};



	//base dimensions
	typedef TriSequence<int, IntType<0>,IntType<0>,IntType<0>,IntType<0>,IntType<0>,IntType<0>,IntType<0> > scalar;
	typedef TriSequence<int, IntType<1>,IntType<0>,IntType<0>,IntType<0>,IntType<0>,IntType<0>,IntType<0> > mass;
	typedef TriSequence<int, IntType<0>,IntType<1>,IntType<0>,IntType<0>,IntType<0>,IntType<0>,IntType<0> > length;
	typedef TriSequence<int, IntType<0>,IntType<0>,IntType<1>,IntType<0>,IntType<0>,IntType<0>,IntType<0> > time;
	typedef TriSequence<int, IntType<0>,IntType<0>,IntType<0>,IntType<1>,IntType<0>,IntType<0>,IntType<0> > charge;
	typedef TriSequence<int, IntType<0>,IntType<0>,IntType<0>,IntType<0>,IntType<1>,IntType<0>,IntType<0> > temperature;
	typedef TriSequence<int, IntType<0>,IntType<0>,IntType<0>,IntType<0>,IntType<0>,IntType<1>,IntType<0> > intensity;
	typedef TriSequence<int, IntType<0>,IntType<0>,IntType<0>,IntType<0>,IntType<0>,IntType<0>,IntType<1> > angle;

	//derived dimensions
	typedef TriDimensionSubtract<scalar, time>::Type rate;
	typedef TriDimensionSubtract<length, time>::Type velocity;
	typedef TriDimensionSubtract<velocity, time>::Type acceleration;
	typedef TriDimensionAdd<acceleration, mass >::Type force;
	typedef TriDimensionAdd<mass, velocity>::Type momentum;
	typedef TriDimensionAdd<force, length>::Type energy;
	typedef TriDimensionAdd<energy, time>::Type action;
	typedef TriDimensionSubtract<TriDimensionSubtract<scalar, energy>::Type, energy>::Type fermiDimension;
	typedef TriDimensionSubtract<charge, time>::Type current;
	typedef TriDimensionSubtract< TriDimensionSubtract<force, current>::Type, current>::Type magneticFluxDensity;
	typedef TriDimensionSubtract<scalar, TriDimensionAdd<magneticFluxDensity, TriDimensionAdd<velocity, velocity>::Type>::Type  >::Type electricFluxDensity;
}

#endif //TriDimensions_h_