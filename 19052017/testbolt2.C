int testbolt2()

{
	TCanvas *can1 = new TCanvas("can1", "can1", 550, 440);
	TH1F *h1 = new TH1F ("h1", "histogram", 100, 0, 2);

	TRandom3 r;

 r.SetSeed();
	double m=0.938;

 TF1 *momentum = new TF1 ("momentum", "[0]*x*x*exp(-sqrt(x*x+[2]*[2])/[1])", 0, 10); // poniewaz zakres 0-10 to temp w GeV. (do uporzadkowania)
 TF1 *fteta = new TF1 ("fteta", "sin(x)", 0, TMath::Pi()); // nowa funkcja - teta, generujaca sinus x dla pzedzialu 0 do pi


	momentum->SetParameter (0, 1);
 	momentum->SetParameter (1, 0.07);
	momentum->FixParameter (2, m); // poniewaz masa wychodzi ujemna przy SetParameter przy Fit

	double p;  // dlugosc wektora pedu
	double fi;

	double px;
	double py;
	double pz;
	double teta;

	double pt; // poprzeczny
	double E; // energia
	double y; // pospiesznosc (rapidity)

 TH2F* h = new TH2F("h","h",50, -1,1,50,0,1.5);

 for (int i=0 ; i<1000000; i++)
 {

	p=momentum->GetRandom();  // losujemy ped (Boltzmann)
	fi=r.Rndm()*2.*TMath::Pi(); // generujemy wartosc fi w przedziale 0 do 2pi
	teta=fteta->GetRandom();

	px=p*sin(teta)*cos(fi);
	py=p*sin(teta)*sin(fi);
	pz=p*cos(teta);

	pt=sqrt(px*px+py*py);
	E=sqrt(p*p+m*m);
	y=(1/2.)*log((E+pz)/(E-pz));

		h->Fill(y,pt);



// h1->Fill(momentum->GetRandom() );

 }


// h1->Draw();

h->Draw("colz");


//h1->Fit(momentum);
//gaus->Print();

}
