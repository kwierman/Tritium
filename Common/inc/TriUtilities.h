#ifndef TriUtilies_h_
#define TriUtilies_h_ 1

//---------------------------------------------------------------------
void signal_callback_handler(int signum);
static inline void print_stacktrace(unsigned int stack_depth = 100);
//---------------------------------------------------------------------

namespace TriForbidden{

	class TriUtilities{
	public:
		static TriUtilities* GetInstance();
	protected:
		static TriUtilities* instance;

	private:
		TriUtilities() ;
		TriUtilities(TriUtilities& other){}
		const TriUtilities& operator=(const TriUtilities& other);
		~TriUtilities(){}
	};

}


#endif //TriUtilies_h_

