int testguasu()

{
	TCanvas *can1 = new TCanvas("can1", "can1", 550, 440); 	
	TH1F *h1 = new TH1F ("h1", "histogram", 100, -4, 4);

	TRandom3 r; 

 r.SetSeed();
 
 for (int i=0 ; i<100000; i++)
 {

 h1->Fill(r.Gaus());

 }

h1->Draw();
h1->Fit("gaus");
gaus->Print(); 
	
}


