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
    
    template <bool flag, typename T, typename U>
    struct SelectType{
        typedef T result;
    };

    template <typename T, typename U>
    struct SelectType<false, T, U>{
        typedef U result;
    };
    
    template <typename T, typename U>
    struct IsType{
        enum { value = false };
    };
    
    template <typename T>
    struct IsType<T,T>{
        enum { value = true };
    };

    namespace TritiumForbidden
    {
        template <class T, class U>
        struct ConversionExistanceHelper
        {
            typedef char Small;
            struct Big { char dummy[2]; };
            static Big   Test(...);
            static Small Test(U);
            static T MakeT();
        };
    }

    template <class T, class U>
    struct ConversionExistance{
        typedef TritiumForbidden::ConversionExistanceHelper<T, U> H;
        enum { exists = sizeof(typename H::Small) == sizeof((H::Test(H::MakeT()))) };
        enum { exists2Way = exists && ConversionExistance<U, T>::exists };
        enum { sameType = false };
    };
    
    template <class T>
    struct ConversionExistance<T, T> {
        enum { exists = 1, exists2Way = 1, sameType = 1 };
    };
    
    template <class T>
    struct ConversionExistance<void, T> {
        enum { exists = 0, exists2Way = 0, sameType = 0 };
    };
    
    template <class T>
    struct ConversionExistance<T, void> {
        enum { exists = 0, exists2Way = 0, sameType = 0 };
    };
    
    template <>
    struct ConversionExistance<void, void> {
    public:
        enum { exists = 1, exists2Way = 1, sameType = 1 };
    };

    template <class T, class U>
    struct SuperSubclass
    {
        enum { value = (::TritiumDesign::ConversionExistance<const volatile U*, const volatile T*>::exists &&
                      !::TritiumDesign::ConversionExistance<const volatile T*, const volatile void*>::sameType) };
          
        // Dummy enum to make sure that both classes are fully defined.
        enum{ dontUseWithIncompleteTypes = ( sizeof (T) == sizeof (U) ) };
    };

    template <>
    struct SuperSubclass<void, void> 
    {
        enum { value = false };
    };

    template <class U>
    struct SuperSubclass<void, U> 
    {
        enum { value = (::TritiumDesign::ConversionExistance<const volatile U*, const volatile void*>::exists &&
                      !::TritiumDesign::ConversionExistance<const volatile void*, const volatile void*>::sameType) };
          
        // Dummy enum to make sure that both classes are fully defined.
        enum{ dontUseWithIncompleteTypes = ( 0 == sizeof (U) ) };
    };

    template <class T>
    struct SuperSubclass<T, void> 
    {
        enum { value = (::TritiumDesign::ConversionExistance<const volatile void*, const volatile T*>::exists &&
                      !::TritiumDesign::ConversionExistance<const volatile T*, const volatile void*>::sameType) };
          
        // Dummy enum to make sure that both classes are fully defined.
        enum{ dontUseWithIncompleteTypes = ( sizeof (T) == 0 ) };
    };


    template<class T,class U>
    struct SuperSubclassStrict
    {
        enum { value = (::TritiumDesign::ConversionExistance<const volatile U*, const volatile T*>::exists &&
                     !::TritiumDesign::ConversionExistance<const volatile T*, const volatile void*>::sameType &&
                     !::TritiumDesign::ConversionExistance<const volatile T*, const volatile U*>::sameType) };
        
        // Dummy enum to make sure that both classes are fully defined.
        enum{ dontUseWithIncompleteTypes = ( sizeof (T) == sizeof (U) ) };
    };

    template<>
    struct SuperSubclassStrict<void, void> 
    {
        enum { value = false };
    };

    template<class U>
    struct SuperSubclassStrict<void, U> 
    {
        enum { value = (::TritiumDesign::ConversionExistance<const volatile U*, const volatile void*>::exists &&
                     !::TritiumDesign::ConversionExistance<const volatile void*, const volatile void*>::sameType &&
                     !::TritiumDesign::ConversionExistance<const volatile void*, const volatile U*>::sameType) };
        
        // Dummy enum to make sure that both classes are fully defined.
        enum{ dontUseWithIncompleteTypes = ( 0 == sizeof (U) ) };
    };

    template<class T>
    struct SuperSubclassStrict<T, void> 
    {
        enum { value = (::TritiumDesign::ConversionExistance<const volatile void*, const volatile T*>::exists &&
                     !::TritiumDesign::ConversionExistance<const volatile T*, const volatile void*>::sameType &&
                     !::TritiumDesign::ConversionExistance<const volatile T*, const volatile void*>::sameType) };
        
        // Dummy enum to make sure that both classes are fully defined.
        enum{ dontUseWithIncompleteTypes = ( sizeof (T) == 0 ) };
    };


}   // namespace TritiumDesign


#define TritiumDesign_SUPERSUBCLASS(T, U) \
    ::TritiumDesign::SuperSubclass<T,U>::value


#define TritiumDesign_SUPERSUBCLASS_STRICT(T, U) \
    ::TritiumDesign::SuperSubclassStrict<T,U>::value


#endif // end file guardian

