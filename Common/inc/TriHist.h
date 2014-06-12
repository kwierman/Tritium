#ifndef TriHist_h_
#define TriHist_h_

#include <map>

namespace Tritium{

	class TriHist{
		std::map<double,double> fMap;
		double low;
		double high;
		double binwidth;

	public:
		TriHist(double lo, double hi, double width) : low(lo), high(hi), binwidth(width) {
			for(double bin = lo; bin<= hi; bin+=width)
				fMap[bin]=0.0;
		}
		TriHist(double x, double width) : low(x), binwidth(width){
			high = x+width;
			fMap[x]=0.0;
		}

		double GetLow(){return low;}
		double GetHigh(){return high;}
		double GetBinWidth(){return binwidth;}

		void Put(double x, double y=1.0){
			if(x> high){
				for(double bin=high;bin<=x;bin+=binwidth){
					fMap[bin]=0.0;
				}
				high=x;
			}
			std::map<double,double>::iterator it = fMap.lower_bound(x);
			if(it!= fMap.end() ){
				(*it).second += y;
			}
		}
		double Get(double x){
			std::map<double,double>::iterator it = fMap.lower_bound(x);
			if( it!= fMap.end() )
				return (*it).second;
			return 0.0;
		}
	};
}

#endif //TriHist_h_