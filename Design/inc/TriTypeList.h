#ifndef TriTypeList_h_
#define TriTypeList_h_


#include "TriNullTypes.h"
#include "TriTypeManipulations.h"


namespace TritiumDesign{

    template <class T, class U>
    struct TriTypelist{
       typedef T Head;
       typedef U Tail;
    };        
}   // namespace TritiumDesign


#endif // end file guardian

