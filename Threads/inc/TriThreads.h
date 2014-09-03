#ifndef TriThreads_h_
#define TriThreads_h_

#include "TriAssert.h"

#include <pthread.h>
#include <cassert>

namespace TritiumThreading{

	//Class to wrap mutexes.
	class Mutex	{
		Mutex(const Mutex&);
		Mutex & operator = (const Mutex &);
		pthread_mutex_t fMtx;
	public:
		Mutex(){pthread_mutex_init(&fMtx, 0);}
		~Mutex(){pthread_mutex_destroy(&fMtx);}
		void Lock(){pthread_mutex_lock(&fMtx);}
		void Unlock(){pthread_mutex_unlock(&fMtx);}
	};


	template<class Derived, class MutexClass=Mutex>
	class InSingleThread{

        typedef Derived DerivedType;
        
		struct Lock{
			Lock(){}
			explicit Lock(const InSingleThread&){}
			explicit Lock(const InSingleThread*){}
		};

        static int ThreadedAdd(volatile int& lhs, const int rhs){ return lhs += rhs; }

        static int ThreadedSubtract(volatile int& lhs, const int rhs){ return lhs -= rhs; }

        static int ThreadedMultiply(volatile int& lhs, const int rhs){ return lhs *= rhs; }

        static int ThreadedDivide(volatile int& lhs, const int rhs){ return lhs /= rhs; }

        static int ThreadedIncrement(volatile int& lhs){ return ++lhs; }

        static int ThreadedDecrement(volatile int& lhs){ return --lhs; }

        static void ThreadedAssign(volatile int & lhs, const int rhs) { lhs = rhs; }

        static void ThreadedAssign(int & lhs, volatile int & rhs) { lhs = rhs; }

        static int ThreadedAdd(volatile int& lhs, const int rhs, const int comp, bool& matches ){
            lhs += rhs;
            matches = ( lhs == comp );
            return lhs;
        }

        static int ThreadedSubtract(volatile int& lhs, const int rhs, const int comp, bool& matches ){
            lhs -= rhs;
            matches = ( lhs == comp );
            return lhs;
        }

        static int ThreadedMultiply(volatile int& lhs, const int rhs, const int comp, bool& matches ){
            lhs *= rhs;
            matches = ( lhs == comp );
            return lhs;
        }

        static int ThreadedDivide(volatile int& lhs, const int rhs, const int comp, bool& matches ){
            lhs /= rhs;
            matches = ( lhs == comp );
            return lhs;
        }

        static int ThreadedIncrement(volatile int& lhs, const int comp, bool& matches ){
            ++lhs;
            matches = ( lhs == comp );
            return lhs;
        }

        static int ThreadedDecrement(volatile int& lhs, const int comp, bool& matches ){
            --lhs;
            matches = ( lhs == comp );
            return lhs;
        }
	};





    template <class Derived, class MutexClass = Mutex>
    class LockByObject{
        mutable MutexClass fMtx;
        //statically lock all of the same objects
        static pthread_mutex_t fMathMutex;
        typedef Derived DerivedType;

    public:
        LockByObject() : fMtx() {}

        LockByObject(const LockByObject&) : fMtx() {}

        ~LockByObject() {}

        class Lock;
        friend class Lock;

        class Lock{
        	Lock();
        	Lock(const Lock&);
        	Lock& operator=(const Lock&);
        	const LockByObject& fOwner;
        public:

            explicit Lock(const LockByObject& own) : fOwner(own) {
                fOwner.fMtx.Lock();
            }

            explicit Lock(const LockByObject* own) : fOwner(*own){
                fOwner.fMtx.Lock();
            }

            ~Lock(){
                fOwner.fMtx.Unlock();
            }
        };                                                
                                
    public:                                                          
        static int ThreadedMultiply(volatile int& lhs, const int rhs) 
        {                                                                
            pthread_mutex_lock( &fMathMutex );                      
            lhs *= rhs;                                                 
            pthread_mutex_unlock( &fMathMutex );                    
            return lhs;                                                 
        }                                                                
                                                                         
        static int ThreadedDivide(volatile int& lhs, const int rhs) 
        {                                                                
            pthread_mutex_lock( &fMathMutex );                      
            lhs /= rhs;                                                 
            pthread_mutex_unlock( &fMathMutex );                    
            return lhs;                                                 
        }                                                                
                                                                         
        static int ThreadedIncrement(volatile int& lhs)           
        {                                                                
            pthread_mutex_lock( &fMathMutex );                      
            ++lhs;                                                      
            pthread_mutex_unlock( &fMathMutex );                    
            return lhs;                                                 
        }                                                                
                                                                         
        static int ThreadedDecrement(volatile int& lhs)           
        {                                                                
            pthread_mutex_lock( &fMathMutex );                      
            --lhs;                                                      
            pthread_mutex_unlock( &fMathMutex );                    
            return lhs;                                                 
        }                                                                
                                                                         
        static void ThreadedAssign(volatile int& lhs, const int rhs) 
        {                                                                
            pthread_mutex_lock( &fMathMutex );                      
            lhs = rhs;                                                  
            pthread_mutex_unlock( &fMathMutex );                    
            return lhs;                                                 
        }                                                                
                                                                         
        static void ThreadedAssign(int& lhs, volatile const int& rhs) 
        {                                                                
            pthread_mutex_lock( &fMathMutex );                      
            lhs = rhs;                                                  
            pthread_mutex_unlock( &fMathMutex );                    
            return lhs;                                                 
        }                                                                
                                                                         
        static int ThreadedIncrement(volatile int& lhs, const int compare, bool& matches ) 
        {                                                                
            pthread_mutex_lock( &fMathMutex );                      
            ++lhs;                                                      
            matches = ( compare == lhs );                               
            pthread_mutex_unlock( &fMathMutex );                    
            return lhs;                                                 
        }                                                                
                                                                         
        static int ThreadedDecrement(volatile int& lhs, const int compare, bool& matches ) 
        {                                                                
            pthread_mutex_lock( &fMathMutex );                      
            --lhs;                                                      
            matches = ( compare == lhs );                               
            pthread_mutex_unlock( &fMathMutex );                    
            return lhs;                                                 
        }                                                                
        static int ThreadedMultiply(volatile int& lhs, const int rhs, const int compare, bool& matches ) 
        {                                                               
            pthread_mutex_lock( &fMathMutex );                     
            lhs *= rhs;                                                
            matches = ( lhs == compare );                              
            pthread_mutex_unlock( &fMathMutex );                   
            return lhs;                                                
        }                                                               
                                                                        
        static int ThreadedDivide(volatile int& lhs, const int rhs, const int compare, bool& matches ) 
        {                                                               
            pthread_mutex_lock( &fMathMutex );                     
            lhs /= rhs;                                                
            matches = ( lhs == compare );                              
            pthread_mutex_unlock( &fMathMutex );                   
            return lhs;                                                
        }

    };

	template <class Derived, class MutexClass>
    pthread_mutex_t LockByObject<Derived, MutexClass>::fMathMutex = PTHREAD_MUTEX_INITIALIZER;



   template <class Derived, class MutexClass = Mutex >
    class ClassLevelLockable
    {
        struct Initializer{
            bool fIsInit;
            MutexClass fMtx;

            Initializer() : fIsInit(false), fMtx()
            {
                fIsInit = true;
            }

            ~Initializer()
            {
                assert(fIsInit);
            }
        };

        static Initializer fInit;
        static pthread_mutex_t fMathMutex;
        typedef Derived DerivedType;


    public:

        class Lock;
        friend class Lock;

        ///  \struct Lock
        ///  Lock class to lock on class level
        class Lock
        {
        public:

            /// Lock class
            Lock()
            {
                assert(fInit.fIsInit);
                fInit.fMtx.Lock();
            }

            /// Lock class
            explicit Lock(const ClassLevelLockable&)
            {
                assert(fInit.fIsInit);
                fInit.fMtx.Lock();
            }

            /// Lock class
            explicit Lock(const ClassLevelLockable*)
            {
                assert(fInit.fIsInit);
                fInit.fMtx.Lock();
            }

            /// Unlock class
            ~Lock()
            {
                assert(fInit.fIsInit);
                fInit.fMtx.Unlock();
            }

        private:
            Lock(const Lock&);
            Lock& operator=(const Lock&);
        };


    public:
        static int ThreadedMultiply(volatile int& lhs, const int rhs) 
        {                                                                
            pthread_mutex_lock( &fMathMutex );                      
            lhs *= rhs;                                                 
            pthread_mutex_unlock( &fMathMutex );                    
            return lhs;                                                 
        }                                                                
                                                                         
        static int ThreadedDivide(volatile int& lhs, const int rhs) 
        {                                                                
            pthread_mutex_lock( &fMathMutex );                      
            lhs /= rhs;                                                 
            pthread_mutex_unlock( &fMathMutex );                    
            return lhs;                                                 
        }                                                                
                                                                         
        static int ThreadedIncrement(volatile int& lhs)           
        {                                                                
            pthread_mutex_lock( &fMathMutex );                      
            ++lhs;                                                      
            pthread_mutex_unlock( &fMathMutex );                    
            return lhs;                                                 
        }                                                                
                                                                         
        static int ThreadedDecrement(volatile int& lhs)           
        {                                                                
            pthread_mutex_lock( &fMathMutex );                      
            --lhs;                                                      
            pthread_mutex_unlock( &fMathMutex );                    
            return lhs;                                                 
        }                                                                
                                                                         
        static void ThreadedAssign(volatile int& lhs, const int rhs) 
        {                                                                
            pthread_mutex_lock( &fMathMutex );                      
            lhs = rhs;                                                  
            pthread_mutex_unlock( &fMathMutex );                    
            return lhs;                                                 
        }                                                                
                                                                         
        static void ThreadedAssign(int& lhs, volatile const int& rhs) 
        {                                                                
            pthread_mutex_lock( &fMathMutex );                      
            lhs = rhs;                                                  
            pthread_mutex_unlock( &fMathMutex );                    
            return lhs;                                                 
        }                                                                
                                                                         
        static int ThreadedIncrement(volatile int& lhs, const int compare, bool& matches ) 
        {                                                                
            pthread_mutex_lock( &fMathMutex );                      
            ++lhs;                                                      
            matches = ( compare == lhs );                               
            pthread_mutex_unlock( &fMathMutex );                    
            return lhs;                                                 
        }                                                                
                                                                         
        static int ThreadedDecrement(volatile int& lhs, const int compare, bool& matches ) 
        {                                                                
            pthread_mutex_lock( &fMathMutex );                      
            --lhs;                                                      
            matches = ( compare == lhs );                               
            pthread_mutex_unlock( &fMathMutex );                    
            return lhs;                                                 
        }                                                                
        static int ThreadedMultiply(volatile int& lhs, const int rhs, const int compare, bool& matches ) 
        {                                                               
            pthread_mutex_lock( &fMathMutex );                     
            lhs *= rhs;                                                
            matches = ( lhs == compare );                              
            pthread_mutex_unlock( &fMathMutex );                   
            return lhs;                                                
        }                                                               
                                                                        
        static int ThreadedDivide(volatile int& lhs, const int rhs, const int compare, bool& matches ) 
        {                                                               
            pthread_mutex_lock( &fMathMutex );                     
            lhs /= rhs;                                                
            matches = ( lhs == compare );                              
            pthread_mutex_unlock( &fMathMutex );                   
            return lhs;                                                
        }

    };




}


#endif //TriThreads_h_