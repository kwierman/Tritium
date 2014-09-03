#ifndef TriSingleton_h_
#define TriSingleton_h_ 1

#include <list>
#include <new>
#include <memory>


namespace TriThreading{


	class LifetimeTrackerPrototype;
	void AtExitFunction();
	typedef void (*atexitfunct_ptr)();

	typedef std::list<LifetimeTrackerPrototype*> TrackerList;
	extern TrackerList* pTrackerList;



	class LifetimeTrackerPrototype{
		unsigned int fLongevity;
	public:
		LifetimeTrackerPrototype(unsigned int x=1e6) : fLongevity(x) {}
		virtual ~LifetimeTrackerPrototype() =0;
		static  bool Compare(const LifetimeTrackerPrototype* lhs, const LifetimeTrackerPrototype* rhs){
			return lhs->fLongevity > rhs->fLongevity;
		}
	};

	inline LifetimeTrackerPrototype::~LifetimeTrackerPrototype() {}

	template<typename T>
	struct Deleter{
		typedef void (*Type)(*T);
		static void Delete(*T obj){delete obj;}
	};

	template<typename T, typename Destructor>
	class LifetimeTracker : public LifetimeTrackerPrototype {
		T* fTracked;
		Destructor fDestructor;
	public:
		LifetimeTracker(T* p, unsigned int longevity, Destructor d) : 	LifetimeTracker(longevity),
		 																fTracked(p),
		 																 Destructor(d){}
		virtual ~LifetimeTracker(){fDestructor(fTracked);}
	};


	template<typename T, typename Destructor>
	void SetLongevity(T* object, unsigned int longevity, Destructor d){
		if(pTrackerList==0)
			pTrackerList = new pTrackerList();

		std::auto_ptr<LifetimeTrackerPrototype> p(new LifetimeTracker<T, Destructor>(object, longevity, d));

		TrackerList::iterator it = std::upper_bound(pTrackerList->begin(), pTrackerList->end(), p.get(), LifetimeTrackerPrototype::Compare);

		pTrackerList->insert(it, p.get() );

		p.release();
		std::atexit( AtExitFunction);
	}

	//default
	template<typename T >
	void SetLongevity(T* object, unsigned int longevity, typename Deleter<T>::Type d = Deleter<T>::Delete){
		SetLongevity<T, typename Deleter<T>::Type >(object, longevity, d);
	}

	template<class T>
	struct CreateUsingNew{
		static T* Create(){return new T;}
		static void Destroy(T* p){delete p;}
	};

    template< template<class> 
    		  class Alloc 
    		>
    struct CreateUsingClass {
        template <class T>
        struct Allocator{

            static Alloc<T> allocator;

            static T* Create(){
                return new (allocator.allocate(1)) T;
            }

            static void Destroy(T* p){
                p->~T();
                allocator.deallocate(p,1);
            }
        };
    };

    template <class T> 
    struct CreateUsingMalloc{
        static T* Create()
        {
            void* p = std::malloc(sizeof(T));
            if (!p) return 0;
            return new(p) T;
        }
        
        static void Destroy(T* p)
        {
            p->~T();
            std::free(p);
        }
    };

    template<class T>
    struct CreateStatic{
    	union MaxAlign{
    		char t_[sizeof(T)];
    		short int shortInt_;
    		int int_;
    		long int longInt_;
    		float float_;
    		double double_;
    		long double longDouble_;
    		struct Test;
    		int Test::* pMember_;
    		int (Test::*pMemberFn_)(int);
    	};

        static T* Create(){
            static MaxAlign staticMemory_;
            return new(&staticMemory_) T;
        }
        
        static void Destroy(T* p){
            p->~T();
        }

    };

    template <class T>
    struct DefaultLifetime{

        static void ScheduleDestruction(T*, atexitfunct_ptr pFun)
        { std::atexit(pFun); }
        
        static void OnDeadReference()
        { throw std::logic_error("Dead Reference Detected"); }
    };


    template <class T>
    class PhoenixSingleton
    {
		static bool destroyedOnce_;

    public:
        static void ScheduleDestruction(T*, atexit_pfn_t pFun){
            if (!destroyedOnce_)
                std::atexit(pFun);
        }
        
        static void OnDeadReference(){
            destroyedOnce_ = true;
        }
        
    };

    template <class T> bool PhoenixSingleton<T>::destroyedOnce_ = false;


    template <class T>
    class DeletableSingleton{

    	static atexit_pfn_t deleter;
        static bool isDead;
        static bool needCallback;
    public:

        static void ScheduleDestruction(T*, atexit_pfn_t pFun)
        {
            static bool firstPass = true;
            isDead = false;
            deleter = pFun;
            if (firstPass || needCallback)
            {
                std::atexit(atexitCallback);
                firstPass = false;
                needCallback = false;
            }
        }
    
        static void OnDeadReference()
        { 
        }
        ///  delete singleton object manually
        static void GracefulDelete()
        {
            if (isDead)
                return;
            isDead = true;
            deleter();
        }
    
    protected:

        
        static void atexitCallback()
        {
            needCallback = true;
            GracefulDelete();
        }
    };

    template <class T> atexit_pfn_t DeletableSingleton<T>::deleter = 0;
    
    template <class T> bool DeletableSingleton<T>::isDead = true;
    
    template <class T> bool DeletableSingleton<T>::needCallback = true;


    template <class T>
    struct Adapter {
    	atexit_pfn_t pFun_;
        void operator()(T*) { return pFun_(); }
        
    };

    template <class T>
    class SingletonWithLongevity{
    public:
        static void ScheduleDestruction(T* pObj, atexit_pfn_t pFun){
            Adapter<T> adapter = { pFun };
            SetLongevity(pObj, GetLongevity(pObj), adapter);
        }
        
        static void OnDeadReference()
        { throw std::logic_error("Dead Reference Detected"); }
    };

    template <class T>
    struct NoDestroy{
        static void ScheduleDestruction(T*, atexit_pfn_t)
        {}
        
        static void OnDeadReference()
        {}
    };

    template <unsigned int Longevity, class T>
    class SingletonFixedLongevity
    {
    public:
        virtual ~SingletonFixedLongevity() {}
        
        static void ScheduleDestruction(T* pObj, atexit_pfn_t pFun)
        {
            Adapter<T> adapter = { pFun };
            SetLongevity(pObj, Longevity , adapter);
        }
        
        static void OnDeadReference()
        { throw std::logic_error("Dead Reference Detected"); }
    };

    template <class T>
    struct DieLast  : SingletonFixedLongevity<0xFFFFFFFF ,T> {};

    template <class T>
    struct DieDirectlyBeforeLast  : SingletonFixedLongevity<0xFFFFFFFF-1 ,T> {};

    template <class T>
    struct DieFirst : SingletonFixedLongevity<0,T>{};

    template<class T>
    struct DieAfterFirst : SingletonFixedLongevity<1,T>{};


    class FollowIntoDeath {
        template<class T>
        class Followers{
            typedef std::vector<atexit_pfn_t> Container;
            typedef typename Container::iterator iterator;
            static Container* followers_;
        
        public:
            static void Init(){
                static bool done = false;
                if(!done){
                    followers_ = new Container;
                    done = true;
                }
            }

            static void AddFollower(atexit_pfn_t ae){
                Init();
                followers_->push_back(ae);
            }

            static void DestroyFollowers(){
                Init();
                for(iterator it = followers_->begin();it != followers_->end();++it)
                    (*it)();    
                delete followers_;
            }
        };

    public:

        ///  \struct With
        ///  Template for the master 
        ///  \param Lifetime Lifetime policy for the master
        template<template <class> class Lifetime>
        struct With{
            ///  \struct AsMasterLifetime
            ///  Policy for master
            template<class Master>
            struct AsMasterLifetime{
                static void ScheduleDestruction(Master* pObj, atexit_pfn_t pFun)
                {
                    Followers<Master>::Init();
                    Lifetime<Master>::ScheduleDestruction(pObj, pFun);

                    // use same policy for the followers and force a new 
                    // template instantiation,  this adds a additional atexit entry
                    // does not work with SetLonlevity, but there you can control
                    // the lifetime with the GetLongevity function.
                    Lifetime<Followers<Master> >::ScheduleDestruction(0,Followers<Master>::DestroyFollowers);
                }

                static void OnDeadReference(){ 
                    throw std::logic_error("Dead Reference Detected"); 
                }
            };
        };

        ///  \struct AfterMaster
        ///  Template for the follower
        ///  \param Master Master to follow into death
        template<class Master>
        struct AfterMaster{
            ///  \struct IsDestroyed
            ///  Policy for followers 
            template<class F>
            struct IsDestroyed {
                static void ScheduleDestruction(F*, atexit_pfn_t pFun){
                    Followers<Master>::AddFollower(pFun);
                }
      
                static void OnDeadReference(){ 
                    throw std::logic_error("Dead Reference Detected"); 
                }
            };
        };
    };

    template<class T>
    typename FollowIntoDeath::Followers<T>::Container* 
    FollowIntoDeath::Followers<T>::followers_ = 0;

 	template<
        	typename T,
        	template <class> class CreationPolicy = CreateUsingNew,
        	template <class> class LifetimePolicy = DefaultLifetime,
        	template <class, class> class ThreadingModel = LOKI_DEFAULT_THREADING_NO_OBJ_LEVEL,
        	class MutexPolicy = LOKI_DEFAULT_MUTEX
    		>
    class SingletonHolder
    {
    public:

        ///  Type of the singleton object
        typedef T ObjectType;

        ///  Returns a reference to singleton object
        static T& Instance();
        
    private:
        // Helpers
        static void MakeInstance();
        static void DestroySingleton();
        
        // Protection
        SingletonHolder();
        
        // Data
        typedef typename ThreadingModel<T*,MutexPolicy>::DerivedType PtrInstanceType;
        static PtrInstanceType pInstance_;
        static bool destroyed_;
    };

    template<
        class T,
        template <class> class C,
        template <class> class L,
        template <class, class> class M,
        class X
    >
    typename SingletonHolder<T, C, L, M, X>::PtrInstanceType
        SingletonHolder<T, C, L, M, X>::pInstance_ = 0;

    template<
        class T,
        template <class> class C,
        template <class> class L,
        template <class, class> class M,
        class X
    >
    bool SingletonHolder<T, C, L, M, X>::destroyed_ = false;


    template
    <
        class T,
        template <class> class CreationPolicy,
        template <class> class LifetimePolicy,
        template <class, class> class ThreadingModel,
        class MutexPolicy
    >
    inline T& SingletonHolder<T, CreationPolicy, 
        LifetimePolicy, ThreadingModel, MutexPolicy>::Instance()
    {
        if (!pInstance_)
        {
            MakeInstance();
        }
        return *pInstance_;
    }

}


#endif //TriSingleton_h_