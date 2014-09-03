#ifndef TriAssert_h_
#define TriAssert_h_

#include <stdlib.h>
#include <iostream>


template<int> struct CompileTimeError;
template<> struct CompileTimeError<true> {};

#define TRITIUM_STATIC_ASSERT(expr, msg) \
    { CompileTimeError<((expr) != 0)> ERROR_##msg; (void)ERROR_##msg; } 
    

#define TRITIUM_RUNTIME_ASSERT(expr, msg)\
    {if(!expr) std::cerr<<##msg<<std::endl; abort();}

#endif //TriAssert_h_
