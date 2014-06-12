#ifndef TriNode_h_
#define TriNode_h_

namespace Tritium{


	class TriNode{
		TriNode* fNext;//!<Holder for the next node in a linked list of like nodes
	public:
		const TriNode* GetNext() const {return fNext;}
		bool RemoveNext(){
			if(fNext) delete fNext;
			else return false;
			return true;
		}
		bool InsertNext(TriNode& rhs){
			rhs.InsertNext(fNext);
			fNext = *rhs;
		}

	};

}

#endif //TriNode_h_
