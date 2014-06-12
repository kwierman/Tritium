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

    template
    <typename T1  = TriNullType, typename T2  = TriNullType, typename T3  = TriNullType,
        typename T4  = TriNullType, typename T5  = TriNullType, typename T6  = TriNullType,
        typename T7  = TriNullType, typename T8  = TriNullType, typename T9  = TriNullType,
        typename T10 = TriNullType, typename T11 = TriNullType, typename T12 = TriNullType,
        typename T13 = TriNullType, typename T14 = TriNullType, typename T15 = TriNullType,
        typename T16 = TriNullType, typename T17 = TriNullType, typename T18 = TriNullType
    > 
    struct MakeTriTypelist{
    private:
        typedef typename MakeTriTypelist
        <
            T2 , T3 , T4 , 
            T5 , T6 , T7 , 
            T8 , T9 , T10, 
            T11, T12, T13,
            T14, T15, T16, 
            T17, T18
        >
        ::Result TailResult;

    public:
        typedef TriTypelist<T1, TailResult> Result;
    };

    template<>
    struct MakeTriTypelist<>{
        typedef TriNullType Result;
    };

    template <class TList> 
    struct Length;

    template <> 
    struct Length<TriNullType>{
        enum { value = 0 };
    };
    
    template <class T, class U>
    struct Length< TriTypelist<T, U> > {
        enum { value = 1 + Length<U>::value };
    };

    template <class TList, unsigned int index> 
    struct TypeAt;
    
    template <class Head, class Tail>
    struct TypeAt<TriTypelist<Head, Tail>, 0> {
        typedef Head Result;
    };

    template <class Head, class Tail, unsigned int i>
    struct TypeAt<TriTypelist<Head, Tail>, i> {
        typedef typename TypeAt<Tail, i - 1>::Result Result;
    };

    template <class TList, unsigned int index, typename DefaultType = TriNullType>
    struct TypeAtNonStrict
    {
        typedef DefaultType Result;
    };
    
    template <class Head, class Tail, typename DefaultType>
    struct TypeAtNonStrict<TriTypelist<Head, Tail>, 0, DefaultType> {
        typedef Head Result;
    };
    
    template <class Head, class Tail, unsigned int i, typename DefaultType>
    struct TypeAtNonStrict<TriTypelist<Head, Tail>, i, DefaultType> {
        typedef typename TypeAtNonStrict<Tail, i - 1, DefaultType>::Result Result;
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
    struct IndexOf<TriTypelist<Head, Tail>, T>{
    private:
        enum { temp = IndexOf<Tail, T>::value };
    public:
        enum { value = (temp == -1 ? -1 : 1 + temp) };
    };

    template <class TList, class T> 
    struct Append;
    
    template <> struct Append<TriNullType, TriNullType>{
        typedef TriNullType Result;
    };
    
    template <class T> struct Append<TriNullType, T>{
        typedef TriTypelist<T,TriNullType> Result;
    };

    template <class Head, class Tail>
    struct Append<TriNullType, TriTypelist<Head, Tail> >{
        typedef TriTypelist<Head, Tail> Result;
    };
    
    template <class Head, class Tail, class T>
    struct Append<TriTypelist<Head, Tail>, T>{
        typedef TriTypelist<Head, typename Append<Tail, T>::Result>
            Result;
    };
    
    template <class TList, class T> 
    struct Erase;
    
    template <class T>                         // Specialization 1
    struct Erase<TriNullType, T> {
        typedef TriNullType Result;
    };

    template <class T, class Tail>             // Specialization 2
    struct Erase<TriTypelist<T, Tail>, T>{
        typedef Tail Result;
    };

    template <class Head, class Tail, class T> // Specialization 3
    struct Erase<TriTypelist<Head, Tail>, T> {
        typedef TriTypelist<Head, typename Erase<Tail, T>::Result>
            Result;
    };

    template <class TList, class T> 
    struct EraseAll;
    
    template <class T>
    struct EraseAll<TriNullType, T>{
        typedef TriNullType Result;
    };
    
    template <class T, class Tail>
    struct EraseAll<TriTypelist<T, Tail>, T> {
        typedef typename EraseAll<Tail, T>::Result Result;
    };


    template <class Head, class Tail, class T>
    struct EraseAll<TriTypelist<Head, Tail>, T>{
        typedef TriTypelist<Head, 
                typename EraseAll<Tail, T>::Result>
            Result;
    };

    template <class TList> 
    struct NoDuplicates;
    
    template <> struct NoDuplicates<TriNullType> {
        typedef TriNullType Result;
    };

    template <class Head, class Tail>
    struct NoDuplicates< TriTypelist<Head, Tail> > {
    private:
        typedef typename NoDuplicates<Tail>::Result L1;
        typedef typename Erase<L1, Head>::Result L2;
    public:
        typedef TriTypelist<Head, L2> Result;
    };

    template <class TList, class T, class U> 
    struct Replace;
    
    template <class T, class U>
    struct Replace<TriNullType, T, U>{
        typedef TriNullType Result;
    };

    template <class T, class Tail, class U>
    struct Replace<TriTypelist<T, Tail>, T, U>{
        typedef TriTypelist<U, Tail> Result;
    };

    template <class Head, class Tail, class T, class U>
    struct Replace<TriTypelist<Head, Tail>, T, U> {
        typedef TriTypelist<Head,
                typename Replace<Tail, T, U>::Result>
            Result;
    };

////////////////////////////////////////////////////////////////////////////////
// class template ReplaceAll
// Replaces all occurences of a type in a Tritypelist, with another type
// Invocation (TList is a Tritypelist, T, U are types):
// Replace<TList, T, U>::Result
// returns a Tritypelist in which all occurences of T is replaced with U
////////////////////////////////////////////////////////////////////////////////

        template <class TList, class T, class U> struct ReplaceAll;
        
        template <class T, class U>
        struct ReplaceAll<TriNullType, T, U>
        {
            typedef TriNullType Result;
        };
        
        template <class T, class Tail, class U>
        struct ReplaceAll<TriTypelist<T, Tail>, T, U>
        {
            typedef TriTypelist<U, typename ReplaceAll<Tail, T, U>::Result> Result;
        };
        
        template <class Head, class Tail, class T, class U>
        struct ReplaceAll<TriTypelist<Head, Tail>, T, U>
        {
            typedef TriTypelist<Head,
                    typename ReplaceAll<Tail, T, U>::Result>
                Result;
        };

////////////////////////////////////////////////////////////////////////////////
// class template Reverse
// Reverses a Tritypelist
// Invocation (TList is a Tritypelist):
// Reverse<TList>::Result
// returns a Tritypelist that is TList reversed
////////////////////////////////////////////////////////////////////////////////

        template <class TList> struct Reverse;
        
        template <>
        struct Reverse<TriNullType>
        {
            typedef TriNullType Result;
        };
        
        template <class Head, class Tail>
        struct Reverse< TriTypelist<Head, Tail> >
        {
            typedef typename Append<
                typename Reverse<Tail>::Result, Head>::Result Result;
        };

////////////////////////////////////////////////////////////////////////////////
// class template MostDerived
// Finds the type in a Tritypelist that is the most derived from a given type
// Invocation (TList is a Tritypelist, T is a type):
// MostDerived<TList, T>::Result
// returns the type in TList that's the most derived from T
////////////////////////////////////////////////////////////////////////////////

        template <class TList, class T> struct MostDerived;
        
        template <class T>
        struct MostDerived<TriNullType, T>
        {
            typedef T Result;
        };
        
        template <class Head, class Tail, class T>
        struct MostDerived<TriTypelist<Head, Tail>, T>
        {
        private:
            typedef typename MostDerived<Tail, T>::Result Candidate;
        public:
            typedef typename Select<
                SuperSubclass<Candidate,Head>::value,
                    Head, Candidate>::Result Result;
        };

////////////////////////////////////////////////////////////////////////////////
// class template DerivedToFront
// Arranges the types in a Tritypelist so that the most derived types appear first
// Invocation (TList is a Tritypelist):
// DerivedToFront<TList>::Result
// returns the reordered TList 
////////////////////////////////////////////////////////////////////////////////

        template <class TList> struct DerivedToFront;
        
        template <>
        struct DerivedToFront<TriNullType>
        {
            typedef TriNullType Result;
        };
        
        template <class Head, class Tail>
        struct DerivedToFront< TriTypelist<Head, Tail> >
        {
        private:
            typedef typename MostDerived<Tail, Head>::Result
                TheMostDerived;
            typedef typename Replace<Tail,
                TheMostDerived, Head>::Result Temp;
            typedef typename DerivedToFront<Temp>::Result L;
        public:
            typedef TriTypelist<TheMostDerived, L> Result;
        };
        
}   // namespace TritiumDesign


#endif // end file guardian

