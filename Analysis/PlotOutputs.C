void PlotOutputs(){

	TFile* input = new TFile("SimpleModel.root","READ");
	TTree* t1 = (TTree*) input->Get("TriBetaDecayKinematics");

	TH1D* inputHist = new TH1D("BetaDecayKinematics","BetaDecayKinematics",10000,0,20000);

	Double_t kE, factor;

	TBranch* kB = t1->GetBranch("kE");
	kB->SetAddress(&kE);
	TBranch* iB = t1->GetBranch("factor");
	iB->SetAddress(&factor);

	for(Int_t i=0; i<t1->GetEntries(); i++){
		t1->GetEvent(i);
		inputHist->Fill(kE,factor);
		std::cout<<kE<<","<<factor<<std::endl;
	}

	TCanvas* c1 = new TCanvas();
	inputHist->Draw("APL");
	c1->Update();

}