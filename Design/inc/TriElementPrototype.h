#ifndef TriElementPrototype_h_
#define TriElementPrototype_h_ 1

#include <map>
#include <string>
#include <cstdlib>

#include "TriObject.h"
#include "TriRootOutput.h"

namespace Tritium{



	class TriElementProtoType : public TriConstructable{
		virtual ~TriElementPrototype(){}
		virtual void Set(std::string key, std::string value)=0;
	};

	template<class Derived>
	class TriElement : public TriElementPrototype{
		typedef void (Derived::*d_func)(double);
		typedef std::map<std::string, d_func> func_map;
		func_map d_config;

		void AddValueToMap(std::string value, d_func f){
			d_config.insert(std::make_pair(value, f));
		}
		void Set(std::string key, std::string value){
			double newValue = std::atof(value.c_str() );
			d_func call = d_config[key];
			if(!call) return;
			Derived* d = dynamic_cast<Derived*>(this);
			(d->*call)(newValue);
		}

	};
}

#endif //File Guardian
