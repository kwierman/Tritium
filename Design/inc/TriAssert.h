#ifndef TriAssert_h_
#define TriAssert_h_

//Let's not lie here, this is a straight up ripoff of Alexandrescui

template<bool> 
struct CompileTimeChecker {
	CompileTimeChecker(...);
};

template<> 
struct CompileTimeChecker<false> { };

#define TRITIUM_STATIC_ASSERT(expr, msg) {class ERROR_##msg {}; (void)sizeof(CompileTimeChecker<(expr) != 0>((ERROR_##msg())));}

#endif //TriAssert_h_
