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
}   // namespace TritiumDesign


#endif // end file guardian

