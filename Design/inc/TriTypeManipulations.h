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

    template <typename T, typename U>
    struct SameType
    {
        enum { value = false };
    };
    
    template <typename T>
    struct SameType<T,T>
    {
        enum { value = true };
    };
    
}   // namespace TritiumDesign



#endif // end file guardian

