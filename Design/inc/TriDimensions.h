#ifndef TriDimensions_h_
#define TriDimensions_h_

#include "TriSequence.h"

namespace TritiumDesign{

	//For Multiplying Quantities, add dimensions
	/*
	template<class Seq1, class Seq2>
	struct TriDimensionAdd{
		typedef TriSequence<int, 	IntType< Seq1::Type::Tail::Type::Head::value + Seq2::Type::Tail::Type::Head::value >,
									IntType< Seq1::Type::Tail::Type::Tail::Type::Head::value + Seq2::Type::Tail::Type::Tail::Type::Head::value >,
									IntType< Seq1::Type::Tail::Type::Tail::Type::Tail::Type::Head::value + Seq2::Type::Tail::Type::Tail::Type::Tail::Type::Head::value >,
									IntType< Seq1::Type::Tail::Type::Tail::Type::Tail::Type::Tail::Type::Head::value + Seq2::Type::Tail::Type::Tail::Type::Tail::Type::Tail::Type::Head::value >,
									IntType< Seq1::Type::Tail::Type::Tail::Type::Tail::Type::Tail::Type::Tail::Type::Head::value + Seq2::Type::Tail::Type::Tail::Type::Tail::Type::Tail::Type::Tail::Type::Head::value >,
									IntType< Seq1::Type::Tail::Type::Tail::Type::Tail::Type::Tail::Type::Tail::Type::Tail::Type::Head::value + Seq2::Type::Tail::Type::Tail::Type::Tail::Type::Tail::Type::Tail::Type::Tail::Type::Head::value >,
									IntType< Seq1::Type::Tail::Type::Tail::Type::Tail::Type::Tail::Type::Tail::Type::Tail::Type::Tail::Type::Head::value + Seq2::Type::Tail::Type::Tail::Type::Tail::Type::Tail::Type::Tail::Type::Tail::Type::Tail::Type::Head::value >
		 >::Type Type;
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
		 >::Type Type;
	};
	*/


	//base dimensions
	typedef TriSequence<int, IntType<0>,IntType<0>,IntType<0>,IntType<0>,IntType<0>,IntType<0>,IntType<0> >::Type scalar;
	/*
	typedef TriSequence<int, IntType<1>,IntType<0>,IntType<0>,IntType<0>,IntType<0>,IntType<0>,IntType<0> >::Type mass;
	typedef TriSequence<int, IntType<0>,IntType<1>,IntType<0>,IntType<0>,IntType<0>,IntType<0>,IntType<0> >::Type length;
	typedef TriSequence<int, IntType<0>,IntType<0>,IntType<1>,IntType<0>,IntType<0>,IntType<0>,IntType<0> >::Type time;
	typedef TriSequence<int, IntType<0>,IntType<0>,IntType<0>,IntType<1>,IntType<0>,IntType<0>,IntType<0> >::Type charge;
	typedef TriSequence<int, IntType<0>,IntType<0>,IntType<0>,IntType<0>,IntType<1>,IntType<0>,IntType<0> >::Type temperature;
	typedef TriSequence<int, IntType<0>,IntType<0>,IntType<0>,IntType<0>,IntType<0>,IntType<1>,IntType<0> >::Type intensity;
	typedef TriSequence<int, IntType<0>,IntType<0>,IntType<0>,IntType<0>,IntType<0>,IntType<0>,IntType<1> >::Type angle;

	//derived dimensions
	/*
	typedef typename TriDimensionSubtract<scalar, time>::Type rate;
	typedef typename TriDimensionSubtract<length, time>::Type velocity;
	typedef typename TriDimensionSubtract<velocity, time>::Type acceleration;
	typedef typename TriDimensionAdd<acceleration, mass >::Type force;
	typedef typename TriDimensionAdd<mass, velocity>::Type momentum;
	typedef typename TriDimensionAdd<force, length>::Type energy;
	typedef typename TriDimensionAdd<energy, time>::Type action;
	typedef typename TriDimensionSubtract<TriDimensionSubtract<scalar, energy>::Type, energy>::Type fermiDimension;
	typedef typename TriDimensionSubtract<charge, time>::Type current;
	typedef typename TriDimensionSubtract< TriDimensionSubtract<force, current>::Type, current>::Type magneticFluxDensity;
	typedef typename TriDimensionSubtract<scalar, TriDimensionAdd<magneticFluxDensity, TriDimensionAdd<velocity, velocity>::Type>::Type  >::Type electricFluxDensity;
	*/
}

#endif //TriDimensions_h_