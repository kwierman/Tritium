#ifndef TriAssert_h_
#define TriAssert_h_


template<int> struct CompileTimeError;
template<> struct CompileTimeError<true> {};

#define TRITIUM_STATIC_ASSERT(expr, msg) \
    { CompileTimeError<((expr) != 0)> ERROR_##msg; (void)ERROR_##msg; } 



#endif //TriAssert_h_
