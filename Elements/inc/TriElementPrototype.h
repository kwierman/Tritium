#ifndef TriElementPrototype_h_
#define TriElementPrototype_h_ 1

#include <map>
#include <string>
#include <cstdlib>

#include "TriObject.h"
#include "TriRootOutput.h"

namespace Tritium{

	/**
	 *	\class TriElement
	 *	\author Kevin Wierman
	 *	\brief Common Base Class to be used as a constructable.
	 *
	 */
	class TriElement : public TriObject{
	public:
		/**
		 * Use this to set variables for each doughter Decay
		 */
		virtual void Set(std::string key, std::string value)=0;
		virtual ~TriElement(){delete next;}

	private:
		TriElement* next; //!< Holds the next decay in the computation chain

	protected:
		double kE;
		double input;
		double output;
		double factor;

	public:
		TriElement() : TriObject(), next(NULL), kE(0.0),input(0.0),output(0.0),factor(0.0) {}
		bool hasNext(){ return (next != NULL); } //!< Check to see if the next element in the chain exists
		/**
		 * Adds a decay onto the chain
		 **/
		void setNext(TriElement* decay){ 
			if(next)
				next->setNext(decay);
			else
				next=decay; 
		} //!< Extend the decay computation chain
		TriElement* getNext(){return next;} //<! Get the next element in the decay computation chain
		virtual void Compute(double kE, double prevValue )=0; //<! Compute the next element in the decay computation chain.
		virtual void Init()=0;
		virtual void Close() {
			if( hasNext()) getNext()->Close();
		}
		virtual void Initialize(){
			if( hasNext()) getNext()->Initialize();
			this->Init();
		}

	protected:
		virtual void dNdE(double kE)=0;//<! Compute this element in the decay Chain
	};

	/**
		\class TriElementPrototype
		\author Kevin Wierman
		\breif Prototyping for Decay Modules To be used in order for all doughter classes to create their own 
	*/
	template<class T>
	class TriElementPrototype : public TriElement, public TriOutputtingComponent {
	private:
		/**
		*	Declare types of functions to use as pointers.
		*	\warning There is no other way to do this. Do not erase this typedef.
		*/
		typedef void (T::*d_func)(double);
		typedef std::map<std::string, d_func> func_map; //<! Declare the type of map to be used here
		func_map d_config; //<! a map of strings to functions for each type of daughet class

	public:
		TriElementPrototype() : TriElement(),TriOutputtingComponent() {}
		virtual ~TriElementPrototype(){}

		virtual void Compute(double kE, double prevValue){
			this->input = prevValue;
			this->kE = kE;
			this->dNdE(kE);
			if( hasNext() )	getNext()->Compute(kE, this->output);
		}

		void AddValueToMap(std::string value, d_func f ){
			d_config.insert(std::make_pair( value , f) );
		}

		virtual void Set(std::string key, std::string value){
			double newValue = std::atof(value.c_str() );
			d_func call = d_config[key];
			if(!call) return;
			T* derived = dynamic_cast<T*>(this);
			(derived->*call)(newValue);
		}


	};

}

#endif //TriElementPrototype_h_
