#ifndef TriTypeManipulations_h_
#define TriTypeManipulations_h_

// $Id: TypeManip.h 749 2006-10-17 19:49:26Z syntheticpp $


namespace TritiumDesign
{
    template <int v>
    struct IntType{
        enum { value = v };
    };
    
    template <typename T>
    struct TypeType{
        typedef T OType;
    };
    
}   // namespace TritiumDesign



#endif // end file guardian

