int testbolt2ver1()

{
	TCanvas *can1 = new TCanvas("can1", "can1", 550, 440);
	TH1F *h1 = new TH1F ("h1", "histogram", 100, 0, 2);

	TRandom3 r;

 r.SetSeed();

	double m = 0.938; //masa nukleonu
 	double mpi = 0.139; // masa pionu
	double mn = m;
	double T_beam = 1.65; // ENERGIA kinetyczna wiązki
	double p_beam = 2.41; 	// pęd wiązki wyznaczony z relatywistycznej zależnosci pędu, masy, energii

 TF1 *momentum = new TF1 ("momentum", "[0]*x*x*exp(-sqrt(x*x+[2]*[2])/[1])", 0, 10); // poniewaz zakres 0-10 to temp w GeV.
 TF1 *fteta = new TF1 ("fteta", "sin(x)", 0, TMath::Pi()); // nowa funkcja - teta, generujaca sinus x dla pzedzialu 0 do pi



	momentum->SetParameter (0, 1); // przepisujemy rozklad boltzmana dla generacji rozkladu pionow nie protonw
 	momentum->SetParameter (1, 0.07);
	momentum->FixParameter (2, mpi); // poniewaz masa wychodzi ujemna przy SetParameter przy Fit

	double betaCM = p_beam/(2*m+T_beam);
	double gammaCM = 1./sqrt(1-pow(betaCM ,2));
	double p;  // dlugosc wektora pedu
	double fi;

	double px;
	double py;
	double pz;
	double pzlab;
	double teta;

	double pt; // poprzeczny
	double E; // energia (kinetyczna)
	double y; // pospiesznosc (rapidity)
	double Elab; // energia w LAB
	double ylab; // rapidity w LAB




 TH2F* h = new TH2F("h","h",50, -1,1,50,0,1.5);  //histogram
 TH2F* h_w_lab = new TH2F("h_w_lab","h_w_lab",100, -1,3,50,0,1.5); // docelowo histogram w LAB (zmiana parametrów?)

 for (int i=0 ; i<1000000; i++)

 {

	p=momentum->GetRandom();  // losujemy ped (Boltzmann)
	fi=r.Rndm()*2.*TMath::Pi(); // generujemy wartosc fi w przedziale 0 do 2pi
	teta=fteta->GetRandom();

	px=p*sin(teta)*cos(fi);
	py=p*sin(teta)*sin(fi);
	pz=p*cos(teta);
			E=sqrt(p*p+mpi*mpi);
 			Elab=gammaCM*(E+betaCM*pz);
			pzlab=gammaCM*(pz+betaCM*E);

			ylab=0.5*log((Elab+pzlab)/(Elab-pzlab));
			// cout<<"betaCM =" <<betaCM<<endl;

	pt=sqrt(px*px+py*py);
	y=(1/2.)*log((E+pz)/(E-pz));

		h->Fill(y,pt);
			h_w_lab->Fill(ylab,pt);


// h1->Fill(momentum->GetRandom() );

 }


// h1->Draw();

h->Draw("colz");
h_w_lab->Draw("colz");

//h1->Fit(momentum);
//gaus->Print();

}
