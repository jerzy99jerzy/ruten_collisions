int testbolt2()
{
	TCanvas *can1 = new TCanvas("can1", "can1", 550, 440); 	
	TH1F *h1 = new TH1F ("h1", "histogram", 100, 0, 2);

	TRandom3 r; 

 r.SetSeed();

 TF1 *fun = new TF1 ("fun", "[0]*x*x*exp(-sqrt(x*x+[2]*[2])/[1])", 0, 10); // poniewaz zakres 0-10 to temp w GeV. 
 
 fun->SetParameter (0, 1);
 fun->SetParameter (1, 0.07); 
 fun->FixParameter (2, 0.938); // poniewaz masa wychodzi ujemna przy SetParameter przy Fit


 for (int i=0 ; i<1000000; i++)
 {

 h1->Fill(fun->GetRandom() );

 }

h1->Draw();

h1->Fit(fun);
//gaus->Print(); 
	
return(0);
}




