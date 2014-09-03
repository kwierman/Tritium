#ifndef TriVector_h_
#define TriVector_h_

#include <cmath>

namespace Tritium{

	struct TriVector{
		double fX;
		double fY;
		double fZ;

		TriVector& operator=(const TriVector& rhs){
			if(this == &rhs) return *this;
			this->fX = rhs->fX;
			this->fY = rhs->fY;
			this->fZ = rhs->fZ;
			return *this;
		}


    double Norm(){
      return sqrt(this*this);
    }

		TriVector& TriVector::operator+=(const TriVector& rhs) {
   			this->fX += rhs->fX;
			this->fY += rhs->fY;
			this->fZ += rhs->fZ; 		
    		return *this;
  		}
		TriVector& TriVector::operator*=(const TriVector& rhs) {
   			this->fX *= rhs->fX;
			this->fY *= rhs->fY;
			this->fZ *= rhs->fZ; 		
    		return *this;
  		}
		TriVector& TriVector::operator-=(const TriVector& rhs) {
   			this->fX -= rhs->fX;
			 this->fY -= rhs->fY;
			this->fZ -= rhs->fZ; 		
    		return *this;
  		}

  		const TriVector TriVector::operator+(const TriVector &other) const {
    		return TriVector(*this) += other;
  		}
  		const TriVector TriVector::operator-(const TriVector &other) const {
    		return TriVector(*this) -= other;
  		}
  		const TriVector TriVector::operator*(const TriVector &other) const {
    		return (this->fX*rhs->fX)+(this->fY*rhs->fY)+(this->fZ*rhs->fZ);
  		}
  		bool TriVector::operator==(const TriVector &other) const {
    		return (this->fX == rhs->fX) && (this->fY == rhs->fY) && (this->fZ == rhs->fZ);
  		}
	  	bool TriVector::operator!=(const TriVector &other) const {
    		return !(*this == other);
  		}
	};



}


#endif //TriVector_h_