#ifndef TriTypeList_h_
#define TriTypeList_h_


#include "TriNullTypes.h"
#include "TriTypeManipulations.h"


namespace TritiumDesign{

    template <class H, class T>
    struct TriTypelist{
       typedef H Head;
       typedef T Tail;
    };        


	template <class TList, class T> 
	struct IndexOf;

	template <class T>
	struct IndexOf<TriNullType, T>{
	    enum { value = -1 };
	};

	template <class T, class Tail>
	struct IndexOf<TriTypelist<T, Tail>, T>{
	    enum { value = 0 };
	};

	template <class Head, class Tail, class T>
	struct IndexOf<TriTypelist<Head, Tail>, T>
	{
	private:
	    enum { temp = IndexOf<Tail, T>::value };
	public:
	    enum { value = (temp == -1 ? -1 : 1 + temp) };
	};

}   // namespace TritiumDesign


#endif // end file guardian

