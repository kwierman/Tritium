#ifndef TriNodeElement_h_
#define TriNodeElement_h_

#include "TriNullTypes.h"

namespace Tritium{

	//Usage Should be something like class  TriSomething : public TriNodeElement<TriSomething, TriEventGroup>

	template<class Group = , class Element>
	class TriNodeElement : public TriElement<Element>, public TriNode<Group>{

	};
	
}

#endif //TriNodeElement_h_