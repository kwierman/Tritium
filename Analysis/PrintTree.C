void PrintTree(){
	//TApplication* theApp = new TApplication("App", NULL, NULL);

	TFile* input = new TFile("RelativisticFermiFunctionTest.root","READ");
	TTree* t1 = (TTree*) input->Get("TriRelativisticFermiFunction");

	Double_t kE, iP,oP, kF;

	TBranch* kB = t1->GetBranch("kE");
	kB->SetAddress(&kE);
	TBranch* iB = t1->GetBranch("input");
	iB->SetAddress(&iP);
	TBranch* oB = t1->GetBranch("output");
	oB->SetAddress(&oP);
	TBranch* fB = t1->GetBranch("factor");
	fB->SetAddress(&kF);
	for(Int_t i=0; i<20; i++){

	//for(Int_t i=0; i<t1->GetEntries(); i++){
		t1->GetEvent(i);
		std::cout<<"Event: "<<i<<" Energy: "<<kE<<" Input: "<<iP<<" Output: "<<oP<<" Factor: "<<kF<<std::endl;
	}
}