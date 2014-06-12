#include "TriConfigReader.h"
#include "TriUtilities.h"
#include "TriLogger.h"

using namespace Tritium;
int main(int argc, char* argv[]){
	if(argc <2){
		TriLog(TriLogger::kFail)<<"Usage: ComputeTritium <path to configuration file>"<<endl;
		TriLog(TriLogger::kFail)<<"  No configuration file found"<<endl;
		return -1;
	}
	TriConfigReader config(argv[1]);
	config.read();
}