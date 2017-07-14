int testbolt()

{
	TCanvas *can1 = new TCanvas("can1", "can1", 550, 440); 	
	TH1F *h1 = new TH1F ("h1", "histogram", 100, 0, 5);

	TRandom3 r; 

 r.SetSeed();

 TF1 *fun = new TF1 ("fun", "[0]*x*x*exp(-sqrt(x*x+[2]*[2])/[1])", 0, 10);
 
 for (int i=0 ; i<100000; i++)
 {

 h1->Fill(fun->GetRandom() );

 }

h1->Draw();
h1->Fit("[0]*x*x*exp(-sqrt(x*x+[2]*[2])/[1])");
gaus->Print(); 
	
}


