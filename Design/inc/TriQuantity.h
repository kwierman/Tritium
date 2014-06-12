#ifndef TriQuantity_h_
#define TriQuantity_h_

#include "TriAssert.h"
#include "TriTypeManipulations.h"
#include "TriDimensions.h"

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
	    	TRITIUM_STATIC_ASSERT( (SameType< Dimensions , OtherDimensions >::value) , ERROR_QUANTITIES_NOT_EQUAL_DIMENSIONS );
	    }

	    T Value() const { return fValue; }

	    //NOTE THAT THIS IS ONLY NECESSARY FOR THE ROOT OUTPUT. DECOUPLING ROOT
	    #pragma mark ROOT_COUPLED
	    T* ValueByPointer() { return &fValue; }
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
	/*
	
	template <class T, class D1, class D2>
	TriQuantity< T, typename TriDimensionAdd<D1,D2>::Type >  operator*(TriQuantity<T,D1> x, TriQuantity<T,D2> y) {
    	typedef typename TriDimensionAdd<D1,D2>::Type dim;
    	return TriQuantity<T,dim>( x.Value() * y.Value() );
	}

	//Division
	template <class T, class D1, class D2>
	TriQuantity< T, typename TritiumDesign::TriDimensionSubtract<D1,D2>::Type > operator/(TriQuantity<T,D1> x, TriQuantity<T,D2> y) {
    	typedef typename TritiumDesign::TriDimensionSubtract<D1,D2>::Type dim;
    	return TriQuantity<T,dim>( x.Value() * y.Value() );
	}
	*/
	
	

}

namespace Tritium{
	//everything in double, since that's the limit that we're calculating to
	typedef TritiumDesign::TriQuantity<double, TritiumDesign::scalar> TriScalar;
	/*
	typedef TritiumDesign::TriQuantity<double, TritiumDesign::mass> TriMass;
	typedef TritiumDesign::TriQuantity<double, TritiumDesign::length> TriLength;
	typedef TritiumDesign::TriQuantity<double, TritiumDesign::time> TriTime;
	typedef TritiumDesign::TriQuantity<double, TritiumDesign::charge> TriCharge;
	/*
	typedef TritiumDesign::TriQuantity<double, TritiumDesign::rate> TriRate;
	typedef TritiumDesign::TriQuantity<double, TritiumDesign::temperature> TriTemperature;
	typedef TritiumDesign::TriQuantity<double, TritiumDesign::intensity> TriIntensity;
	typedef TritiumDesign::TriQuantity<double, TritiumDesign::angle> TriAngle;
	typedef TritiumDesign::TriQuantity<double, TritiumDesign::energy> TriEnergy;
	typedef TritiumDesign::TriQuantity<double, TritiumDesign::action> TriAction;
	typedef TritiumDesign::TriQuantity<double, TritiumDesign::fermiDimension> TriFermiQuantity;
	typedef TritiumDesign::TriQuantity<double, TritiumDesign::magneticFluxDensity> TriMagneticFluxDensity;
	typedef TritiumDesign::TriQuantity<double, TritiumDesign::electricFluxDensity> TriElectricFluxDensity;
	*/
}

#endif //TriQuantity_h_