#ifndef TriConfigReader_h_
#define TriConfigReader_h_

#include "boost/property_tree/detail/rapidxml.hpp"
#include "boost/filesystem.hpp"
#include "boost/filesystem/fstream.hpp"

#include <iostream>
#include <sstream>
#include <string>

#include "TritiumMCEngine.h"
#include "TriObject.h"
#include "TriElementPrototype.h"
#include "TriLogger.h"

namespace Tritium{

	namespace xml =boost::property_tree::detail::rapidxml;
	namespace fs = boost::filesystem;

	class TriConfigReader{

		fs::path fPath;//!< for storing the path to the configuration file

	public:
		TriConfigReader(char* filename) : fPath(filename){
         TriLogger::GetInstance()->SetOutputFile("Tritium.log");

			try{
				if( fs::exists(fPath) && fs::is_regular_file(fPath) )
					TriLog(TriLogger::kGood)<<"File Exists"<<Tritium::endl;
				}
			catch (const fs::filesystem_error& ex) {
				TriLog(TriLogger::kFail)<<ex.what()<<Tritium::endl;
			}
		}

		void read(){
			TriLog(TriLogger::kNormal)<<"Reading in config File"<<Tritium::endl;

			fs::ifstream file( fPath );
			std::stringstream buffer;
			buffer<<file.rdbuf();
			file.close();
			std::string content(buffer.str());

			xml::xml_document<> doc;
            try{
   			   doc.parse<0>(&content[0]); 
            }
            catch (boost::property_tree::detail::rapidxml::parse_error& e ){
               TriLog(TriLogger::kFail)<<"Malformed XML: "<<e.what()<<Tritium::endl<<"Exiting..."<<Tritium::endl;
               return;
            }

   			for(xml::xml_node<>* config = doc.first_node(); config; config = config->next_sibling() ){
   				std::string name="";
   				if( config->first_attribute() )
   					name = config->first_attribute()->value();
               TriLogger::GetInstance()->SetOutputFile(name+".log");
               TritiumMCEngine::GetInstance()->SetName(name);
               TriLogger::GetInstance()->SetOutputFile("TritiumMC.log");
               TriLog(TriLogger::kNormal)<<"Now parsing config: "<<name<<Tritium::endl;
               

   				for(xml::xml_node<>* child = config->first_node();child;child = child->next_sibling() ){
   					name = child->name();
   					if(name=="set" && child->first_attribute()){
   						TritiumMCEngine::GetInstance()->Set(child->first_attribute()->name(),child->first_attribute()->value() );
   					}
   					else if(name =="element"){
   						if(! (child->first_attribute() ) ){ 
   							TriLog(TriLogger::kWarning)<<"Element has no Name Attributes"<<Tritium::endl;
   							continue;
   						}
   						name = child->first_attribute()->value();
   						TriLog(TriLogger::kNormal)<<"Constructing new Element: "<<name<<Tritium::endl;
   						TriBaseFactory factory;
   						TriObject* object = factory.createInstance(name);
                     TriLog(TriLogger::kGood)<<"Successfully created Object"<<Tritium::endl;
                     if(!object){
                        TriLog(TriLogger::kWarning)<<"Factory Created NULL Object."<<Tritium::endl;
                        continue;
                     }
                     TriElement* newElement = (TriElement*)(object);
                     TriLog(TriLogger::kGood)<<"Successfully converted object to a Element"<<Tritium::endl;
   						if(!newElement){
                        TriLog(TriLogger::kWarning)<<"Object will not convert to Element "<<Tritium::endl;
                        continue;
                     }
   						for(xml::xml_node<>* pNode = child->first_node();pNode;pNode = pNode->next_sibling() ){
   							if( std::string(pNode->name()) == "set" && (pNode->first_attribute() )) 
	   							newElement->Set(pNode->first_attribute()->name(), pNode->first_attribute()->value() );
   						}
   						TritiumMCEngine::GetInstance()->AddElement(newElement);
   					}
   				}
               
   			}
            TritiumMCEngine::GetInstance()->Run();

		}
	};
}

#endif //TriConfigReader_h_

