#ifndef TriNode_h_
#define TriNode_h_

#include "TriProcessEvent.h"

namespace TritiumDesign{

	template<class TGroup>
	class TriNode{
		TriNode* fNext;
		//This part should hold all of the information regarding the node system
	public:
		TriNode() : fNext(0){}
		virtual ~TriNode(){
			if(fNext)
				delete fNext;
			fNext = NULL;
		}

		template<class Event>
		virtual void OnEvent(const Event& ev)=0;

		template<class Event>
		virtual void Process(const Event& ev){
			this->OnEvent(ev);
			if(this->fNext)
				if(this->fNext->Processes<Event>())
					this->fNext->Process(ev);
		}

		template<class Event>
		bool Processes(){
			return IndexOf<TGroup, Event>::value;
		}

	};


	class TriEverythingProcessor : public TriNode<AllEvents>{
		template<>
		virtual void OnEvent<TriBeginNewConfig>(const TriBeginNewConfig& ev){
			return;
		}

	};
}


#endif //TriNode_h_