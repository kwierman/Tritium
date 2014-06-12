#ifndef TriDimensions_h_
#define TriDimensions_h_

#include "TriSequence.h"

namespace TritiumDesign{

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
	typedef TriSequence<int, IntType<0>,IntType<1>,IntType<-1>,IntType<0>,IntType<0>,IntType<0>,IntType<0> > velocity;
	typedef TriSequence<int, IntType<0>,IntType<1>,IntType<-2>,IntType<0>,IntType<0>,IntType<0>,IntType<0> > acceleration;
	typedef TriSequence<int, IntType<1>,IntType<1>,IntType<-1>,IntType<0>,IntType<0>,IntType<0>,IntType<0> > momentum;
	typedef TriSequence<int, IntType<1>,IntType<1>,IntType<-2>,IntType<0>,IntType<0>,IntType<0>,IntType<0> > force;


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
	struct TriDimensionAdd{
		typedef TriSequence<int, 	IntType< Seq1::Type::Tail::Type::Head::value - Seq2::Type::Tail::Type::Head::value >,
									IntType< Seq1::Type::Tail::Type::Tail::Type::Head::value - Seq2::Type::Tail::Type::Tail::Type::Head::value >,
									IntType< Seq1::Type::Tail::Type::Tail::Type::Tail::Type::Head::value - Seq2::Type::Tail::Type::Tail::Type::Tail::Type::Head::value >,
									IntType< Seq1::Type::Tail::Type::Tail::Type::Tail::Type::Tail::Type::Head::value - Seq2::Type::Tail::Type::Tail::Type::Tail::Type::Tail::Type::Head::value >,
									IntType< Seq1::Type::Tail::Type::Tail::Type::Tail::Type::Tail::Type::Tail::Type::Head::value - Seq2::Type::Tail::Type::Tail::Type::Tail::Type::Tail::Type::Tail::Type::Head::value >,
									IntType< Seq1::Type::Tail::Type::Tail::Type::Tail::Type::Tail::Type::Tail::Type::Tail::Type::Head::value - Seq2::Type::Tail::Type::Tail::Type::Tail::Type::Tail::Type::Tail::Type::Tail::Type::Head::value >,
									IntType< Seq1::Type::Tail::Type::Tail::Type::Tail::Type::Tail::Type::Tail::Type::Tail::Type::Tail::Type::Head::value - Seq2::Type::Tail::Type::Tail::Type::Tail::Type::Tail::Type::Tail::Type::Tail::Type::Tail::Type::Head::value >
		 > Type;
	};
}

#endif //TriDimensions_h_