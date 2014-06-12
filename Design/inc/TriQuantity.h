#ifndef TriQuantity_h_
#define TriQuantity_h_

#include "TriAssert.h"
#include "TriTypeManipulations.h"

namespace TritiumDesign{
/**
 * Usage:
 * TriQuantity<float,length> l( 1.0f );
 * TriQuantity<float,mass> m( 2.0f );
 * Therefore m=l;//Compile time error
**/

	template <class T, class Dimensions>
	struct TriQuantity{
	    explicit TriQuantity(T x) : fValue(x) {}

	    template<class OtherDimensions>
	    TriQuantity(const OtherDimensions& rhs ) :fValue(rhs.Value()){
	    	STATIC_CHECK(SameType<Dimensions,OtherDimensions>().value, ERROR_QUANTITIES_NOT_EQUAL_DIMENSIONS );
	    }

	    T Value() const { return fValue; }
	 private:
	    T fValue;
	};

	//Addition, Subtraction (only available for the same dimensions)

	template <class T, class D>
	TriQuantity<T,D> operator+(TriQuantity<T,D> x, TriQuantity<T,D> y) {
		return TriQuantity<T,D>(x.Value() + y.Value());
	}

	template <class T, class D>
	TriQuantity<T,D> operator-(TriQuantity<T,D> x, TriQuantity<T,D> y) {
		return TriQuantity<T,D>(x.Value() - y.Value());
	}

	//Multiplication


}

#endif //TriQuantity_h_