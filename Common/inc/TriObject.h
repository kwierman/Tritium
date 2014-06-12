/**	\file Triobject.h
 *
 *	\brief Virtual base object definitions
 */
#ifndef TriObject_h_
#define TriObject_h_

#include <vector>
#include <map>
#include <string>
#include "TString.h"


namespace Tritium
{
	/**	\struct TriObject
	 *  \author Kevin Wierman
	 *	\brief Pure virtual base class for objects to be constructed from serialization
	 */
	struct TriObject
	{
		TriObject(){}
		virtual ~TriObject(){}
	};

	/**	\class TriBaseFactory
	 *  \author Kevin Wierman
	 *	\brief A base factory that utilizes a static map to create objects of different classes from strings
	 */
	struct TriBaseFactory
	{
		typedef std::map<std::string, TriObject*(*)()> map_type;

		static TriObject* createInstance(std::string const& s, TriObject* (*creator)() = 0 ) {
			map_type::iterator it = getMap()->find(s);
			if(it==getMap()->end() ){
				return NULL;
			}
			return it->second();
		}

	protected:
		static map_type* getMap(){
			static map_type* map = new map_type();
			return map;
		}	

	private:
		//static map_type* map;
	};

	//Tritium::TriBaseFactory::map_type* Tritium::TriBaseFactory::map;


	template<typename T>
	struct TriDerivedRegister : TriBaseFactory { 
		
		static TriObject* create() { return ( new T() );}

    	TriDerivedRegister(std::string const& s) { 
       		getMap()->insert(std::make_pair(s, &create ) );
    	}
	};

}

#define REGISTER_DEC_TYPE(NAME) \
    static TriDerivedRegister<NAME> reg;

#define REGISTER_DEF_TYPE(NAME) \
    TriDerivedRegister<NAME> NAME::reg(#NAME);


#endif /* TriObject_h_ */

