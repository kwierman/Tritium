#ifndef TriProcessEvent_h_
#define TriProcessEvent_h_

#include <string>
#include "TriSequence.h"

namespace Tritium{

	struct TriProcessEvent{
		std:string EventType()=0;
	};

	struct TriBeginNewConfig: public TriProcessEvent {
		std::string EventType() {return "BeginNewConfig";}
		std::string configName;
	};

	struct TriEndNewConfig : public TriProcessEvent {
		std::string EventType(){ return "EndNewConfig";}
	};

	struct TriBeginNewCalculation : public TriProcessEvent{
		std::string EventType() {return "BeginNewCalculation";}
	};

	struct TriEndNewCalculation : public TriProcessEvent{
		std::string EventType() {return "EndNewCalculation";}
	};
	
	struct TriNewDataInStream : public TriNewDataInStream{
		std::string EventType() {return "NewDataInStream";}
		std::string Owner;
		std::string Name;
		enum type{
			Unsigned,
			Signed,
			Double,
			String,
			Float,
		};
		void* address;
	};

	struct TriDataUpdate : public TriNewDataInStream{
		std::string EventType() {return "DataUpdate";}
		std::string Owner;
		std::string Name;
	};

	typedef TriDesign::TriSequence<	TriProcessEvent, 
									TriBeginNewConfig, 
									TriEndNewConfig, 
									TriBeginNewCalculation
									TriEndNewCalculation
									TriNewDataInStream>::Type AllEvents;
}

#endif //TriProcessEvent_h_