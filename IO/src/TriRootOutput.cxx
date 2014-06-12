#include "TriRootOutput.h"


Tritium::TriOutputtingComponent::TriOutputtingComponent(){
	TriRootOutput::GetInstance()->RegisterNewFileComponent(this);
}

