#ifndef TriSqeuence_h_
#define TriSequence_h_

#include "TriTypeList.h"

namespace TritiumDesign{

    template<	class T1=TriNullType,
    			class T2=TriNullType,
    			class T3=TriNullType,
    			class T4=TriNullType,
    			class T5=TriNullType,
        		class T6=TriNullType,
    			class T7=TriNullType,
    			class T8=TriNullType,
    			class T9=TriNullType,
    			class T10=TriNullType,
		        class T11=TriNullType,
      			class T12=TriNullType,
       			class T13=TriNullType,
       			class T14=TriNullType,
       			class T15=TriNullType,
       			class T16=TriNullType,
    			class T17=TriNullType,
    			class T18=TriNullType,
    			class T19=TriNullType,
    			class T20=TriNullType
  			>
    struct TriSequence{
    private:
        typedef typename TriSequence<	T2,
        			 					T3,
        			 					T4,
        			 					T5,
        			 					T6,
        			 					T7,
        			 					T8,
        			 					T9,
        			 					T10,
        			 					T11,
										T12,
										T13,
										T14,
										T15,
										T16,
										T17,
										T18,
										T19,
                             			T20	>::Type TailResult;
    public:
        typedef TriTypelist<T1, TailResult> Type;
    };
        
    template<>
    struct TriSequence<>{
        typedef TriNullType Type;
    };

}

#endif //TriSequence_h_
