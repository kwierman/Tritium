#ifndef TriSmallObjectAllocation_h_
#define TriSmallObjectAllocation_h_

#include "TriThreads.h"
#include "Singleton.h"

#include <cstddef>

#define TRITIUM_CHUNK_SIZE 4096
#define TRITIUM_OBJECT_ALIGN 4
#define TRITIUM_MAX_SMALL_OBJECT_SIZE 256


#define TRITIUM_DEFAULT_SMALLOBJ_LIFETIME ::TritiumThreads::LongevityLifetime::DieAsSmallObjectParent




namespace TritiumThreading{

	namespace LifetimeLongevity{

		template<class T>
		struct DieAsSmallObjectParent : DieLast<T> {};

		template<class T>
		struct DieAsSmllObjcetChild : DieDirectlyBeforeLast<T>{};

	}

	class FixedAllocator;


	class SmallObjAllocator{
	protected:
		SmallObjAllocator(std::size_t pagesize, std::size_t maxObjectSize, std::size_t objectAlignSize);
	};
}


