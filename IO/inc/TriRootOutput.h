
#ifndef TriRootOutput_hh_
#define TriRootOutput_hh_

#include "TFile.h"
#include "TTree.h"

#include <string>
#include <vector>
#include <cstring>


namespace Tritium
{

	/*!
		\class TriOutputtingComponent
		\brief Virtual Class for defining methods to be called on new output file creation

		\warning This class makes it impossible to output to multiple files at once
		\note The importance of using this in tandem with the TriRootOutput class makes output isolated to each Simulation component
	*/
	class TriOutputtingComponent{
	public:
		TriOutputtingComponent();
		virtual ~TriOutputtingComponent(){}
		virtual void OnNewFileCreate() =0;
	};

	/*!
		\class TriRootOutput
		\brief Singleton Root Output Manager
		\group Tritium

		This static time class is meant to be a manager for output to the root file
	*/

	class TriRootOutput{

	private:
	    TriRootOutput()
	    {
			fOutput = NULL;
			dataTakingFlag = true;
	    }
	    TriRootOutput(TriRootOutput const&){}
   		TriRootOutput& operator=(TriRootOutput const&){return *this;}

	    std::vector<TTree*> fTrees; //!< Vector of lcoally known trees in the output file
	    TFile* fOutput; 		//!< Current output file. Note that when the output file 

	    bool dataTakingFlag;//!< Data taking flag
	public:

		//! The Singleton creation/get method for this class
		/*!
			\return The Pointer to the singleton instance of this class
		*/
	    static TriRootOutput* GetInstance(){
	    	static TriRootOutput* single = new TriRootOutput();
			return single;
		}

		bool IsTakingData(){return dataTakingFlag;}
		void SetDataTakingFlag(bool flag){dataTakingFlag = flag;}
	    

	    virtual ~TriRootOutput()
	    {
	        if(fOutput){
        		fOutput->Close();
        		fOutput=NULL;
        	}
	    }

	    //! Creates a new root file.
	    /*!
	    	\param std::string name The name of the File
	    	\return bool indicator of file validity 
	    */
	    bool CreateNewFile(std::string name)
	    {
	    	fTrees.clear();
	    	if(fOutput)
	    	{
	    		fOutput->Close();
	    		fOutput=NULL;
	    	}
	    	fOutput = new TFile(name.c_str(), "RECREATE");
	    	if(fOutput->IsZombie())
	    		return false;

	    	for(std::vector<TriOutputtingComponent*>::iterator it = fComponents.begin(); it!= fComponents.end(); ++it)
	    		(*it)->OnNewFileCreate();

	    	return true;
	    }

	    //! Adds a new tree to the current file
	    /*!
	    	\param std::string name The name of the file
	    	\return Indicator for tree creation success
	    */ 

	    bool AddTree(std::string name )
	    {
	    	if(!fOutput)
	    		return false;
	    	TTree* tmpTree = new TTree( name.c_str(), name.c_str() );
			fTrees.push_back(tmpTree);
	    	return true;
	    }

		template<typename XType>
	    bool AddBranch(std::string treeName, std::string branchName, XType* address, std::string )
	    {
	    	return this->AddBranch<XType>(treeName, branchName, address);
	    }

	    //!	Adds a Branch to the Current File
	    /*!
	    	\param std::string treeName The Name of the mother tree
			\param std::string branchName the name of the branch
			\param XType address the address for a double holding
			\return Indicator of success 
	    */

		template<typename XType>
	    bool AddBranch(std::string treeName, std::string branchName, XType* address )
	    {
	    	for(std::vector<TTree*>::iterator it = fTrees.begin(); it!= fTrees.end(); ++it )
	    	{
	    		if( std::string( (*it)->GetName() ) == treeName )//std::strcmp ( (*it)->GetName() , treeName.c_str() ) )
	    		{
	    			//(*it)->Branch(branchName.c_str(), address, variable.c_str());//branchName.c_str());
	    			(*it)->Branch(branchName.c_str(), address, 32000,0);//variable.c_str());
	    			return true;
	    		}
	    	}
	    	return false;
	    }

	    //! Fills a given tree
	    /*!
			\param std::string name The name of the tree to fill
			\return Indicator of success
	    */

	    bool FillTree(std::string name)
	    {
	    	if(!dataTakingFlag) return false;
	    	for(std::vector<TTree*>::iterator it = fTrees.begin(); it!= fTrees.end(); ++it )
	    	{
	    		if( std::string( (*it)->GetName() ) == name )
	    		{
	    			(*it)->Fill();
	    			return true;
	    		}
	    	}
	    	return false;
	    }

	    //! Writes all trees
	    /*!
	    	\return Indicator of success
	    */
	    bool WriteAllTrees()
	    {
	    	if(!fOutput)
	    		return false;
	    	//for(std::vector<TTree*>::iterator it = fTrees.begin(); it!= fTrees.end(); ++it )
	    	//{
	    	//	(*it)->Write();
	    	//}
	    	fOutput->Write(0,TObject::kOverwrite);
	    	fTrees.clear();
	    	return true;
	    }

	    //! Closes the output
	    void Finish()
	    {
	    	if(fOutput)
		    	fOutput->Close();
	    	fOutput=NULL;
	    	fComponents.clear();
	    }

	    std::vector<Tritium::TriOutputtingComponent*> fComponents;

	    //!Registers a new file component
	    void RegisterNewFileComponent( Tritium::TriOutputtingComponent* component )
	    {
	    	fComponents.push_back(component);
	    }
	};



}



#endif

