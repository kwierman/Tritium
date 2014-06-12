#include "TriUtilities.h"

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <execinfo.h>
#include <cxxabi.h>
#include <signal.h>

//---------------------------------------------------------------------
void signal_callback_handler(int signum)
{
  std::cout<<"Caught Signal: "<<signum<<std::endl;;
  print_stacktrace();//print out the stack trace.
  exit(-1);
}
//---------------------------------------------------------------------

//---------------------------------------------------------------------
static inline void print_stacktrace(unsigned int stack_depth)
{

	std::cout<<"Stack Trace:"<<std::endl;;

    void* trace_addr[stack_depth+1];//to be used as a list of the 

    unsigned int trace_addr_length = backtrace(trace_addr, sizeof(trace_addr) / sizeof(void*));

    if (!trace_addr_length) 
    {
    	std::cout<<"Stack Empty"<<std::endl;
		return;
    }
    char** trace_symbols = backtrace_symbols(trace_addr, trace_addr_length);

    size_t function_name_size = 256;
    char* function_name = (char*)malloc(function_name_size);


    for (int i = 1; i < trace_addr_length; i++)
    {
		char *begin_name = 0, *begin_offset = 0, *end_offset = 0;
		for (char *p = trace_symbols[i]; *p; ++p)//for (char *p = trace_symbols[i]; *p!=NULL; ++p)
		{
		    if (*p == '(')
				begin_name = p;
		    else if (*p == '+')
				begin_offset = p;
		    else if (*p == ')' && begin_offset) 
		    {
				end_offset = p;
				break;
		    }
		}

		if (begin_name && begin_offset && end_offset && begin_name < begin_offset)
		{
		    *begin_name++ = '\0';
		    *begin_offset++ = '\0';
		    *end_offset = '\0';

	    // mangled name is now in [begin_name, begin_offset) and caller
	    // offset in [begin_offset, end_offset). now apply
	    // __cxa_demangle():

	    	int status;
	    	char* ret = abi::__cxa_demangle(begin_name,
					    function_name, &function_name_size, &status);
	    	if (status == 0) 
	    	{
				function_name = ret; // use possibly realloc()-ed string
				std::cout<<trace_symbols[i]<<" : "<<function_name<<"+"<<begin_offset<<std::endl;;
	    	}
		    else 
		    {
				std::cout<<trace_symbols[i]<<" : "<<function_name<<"()+"<<begin_offset<<std::endl;
	    	}
		}
		else
		{
			std::cout<<trace_symbols[i]<<std::endl;
		}
    }
    free(function_name);
    free(trace_symbols);
}
//---------------------------------------------------------------------
namespace TriForbidden{
	TriUtilities* TriUtilities::instance = TriUtilities::GetInstance();

	TriUtilities* TriUtilities::GetInstance(){
		if(!instance) instance =  new TriUtilities();
		return instance;
	}
	TriUtilities::TriUtilities(){
		signal(SIGINT, signal_callback_handler);
		signal(SIGABRT, signal_callback_handler);
		signal(SIGBUS ,signal_callback_handler);
		signal(SIGSEGV ,signal_callback_handler);
	}
}
//---------------------------------------------------------------------
