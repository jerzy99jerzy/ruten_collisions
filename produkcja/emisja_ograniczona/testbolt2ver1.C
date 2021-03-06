
Double_t funPt_Y_pmax (Double_t *arg, Double_t *par)

{
	Double_t y=arg[0];
	Double_t pmax=par[1];
	Double_t mpi=par[0];
	Double_t pt;

	double x = mpi*sinh(y);
	double z = cosh(y);

			if (z >= 0. )
				pt= ( TMath::Sqrt(((pmax*pmax)-(x*x))))/z ;
					else
					pt = -1;
						cout << pmax*pmax - x*x << endl;

			return pt;


}

Double_t funPt_Y_teta (Double_t *xval, Double_t *par)

{
	Double_t y=xval[0];
	Double_t mpi=par[0];
	Double_t teta=par[1];

	double x=sinh(y)*tan(teta);
	Double_t pt;

	if (1. - x*x >= 0. )
	pt = mpi* x / TMath::Sqrt(1. - x*x);
    else pt = -1;
			//cout << teta << endl;
			//cout << y << endl; // coutowalem te wartosci w celu debuggingu
			cout << 1 - x*x << endl;

return pt;
}

int testbolt2ver1()

{
	TCanvas *can1 = new TCanvas("can1", "can1", 550, 440);
	TH1F *h1 = new TH1F ("h1", "histogram", 100, 0, 2);

	TRandom3 r;

 r.SetSeed(); // tworzę r czyli obiekt klasy TRandom3

	double m = 0.938; //masa protonu(nukleonu)
 	double mpi = 0.139; // masa pionu
	double mn = m;
	double T_beam = 1.65; // ENERGIA kinetyczna wiązki (cząstek)
	double p_beam = 2.41; 	// pęd wiązki wyznaczony z relatywistycznej zależnosci pędu, masy, energii

 TF1 *momentum = new TF1 ("momentum", "[0]*x*x*exp(-sqrt(x*x+[2]*[2])/[1])", 0, 10); // poniewaz zakres 0-10 to temp w GeV.
 TF1 *fteta = new TF1 ("fteta", "sin(x)", 0, TMath::Pi()); // nowa funkcja - teta, generujaca sinus x dla pzedzialu 0 do pi

 TF1 *fpmax = new TF1 ("fpmax", funPt_Y_pmax, 0, 1.8, 2 ); //pierwszy parametr/wartosc parametru/ilosc parametrow
fpmax->SetNpx(1000);

 TF1 *fteta20 = new TF1 ("fteta20", funPt_Y_teta, 0, 2 ,2);
 TF1 *fteta85 = new TF1 ("fteta85", funPt_Y_teta, 0, 0.2, 2);
 fteta20->SetNpx(1000); // SetNpx ustawienie liczby punktow probkowania funkcji
 fteta85->SetNpx(1000);

	fteta20->SetParameter(0,mpi); // numer parametru/wartosc parametru
	fteta20->SetParameter(1,20.*(M_PI/180));
	fteta85->SetParameter(0,mpi);
	fteta85->SetParameter(1, 85.*(M_PI/180));

	fpmax->SetParameter(0, mpi);
	fpmax->SetParameter(1,1.5);


	momentum->SetParameter (0, 1); // przepisujemy rozklad boltzmana dla generacji rozkladu pionow - nie protonow (uprzednio przykladowo pracowalem na protonach)
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
	double plab; // pęd w układzie LAB (dodano 22.06.2017)
	double teta;

	double pt; // poprzeczny
	double E; // energia (kinetyczna)
	double y; // pospiesznosc (rapidity)
	double Elab; // energia w LAB
	double ylab; // rapidity w LAB
	double tetalab; // wartość kąta theta w LAB (dodano 22.06.2017)
	double filab;



 TH1F* htemp;
 TH2F* h = new TH2F("h","h",50, -1,1,50,0,1.5);  //wyrysowuję histogram
 TH2F* h_w_lab = new TH2F("h_w_lab","h_w_lab",100, -1,3,50,0,1.5); // docelowo histogram w LAB (zmiana parametrów?)
 TH2F* hpty_ok = new TH2F("hpty_ok", "hpty_ok",100, -1,3,50,0,1.5); // tymczasowo skopiowałem wartości parammetrów z linii powyzej (!) należałoby je doprecyzować.

 for (int i=0 ; i<1000000; i++) // pętla dla przykładowego miliona cząstek

 {

	p=momentum->GetRandom();  // losuję ped (Boltzmann)
	fi=r.Rndm()*2.*TMath::Pi(); // generuję wartosc fi w przedziale od 0 do 2pi
	teta=fteta->GetRandom();

	px=p*sin(teta)*cos(fi);
	py=p*sin(teta)*sin(fi);
	pz=p*cos(teta);
			E=sqrt(p*p+mpi*mpi);
 			Elab=gammaCM*(E+betaCM*pz);
			pzlab=gammaCM*(pz+betaCM*E);

			ylab=0.5*log((Elab+pzlab)/(Elab-pzlab));
			// cout<<"betaCM = <<betaCM <<endl;

				plab=sqrt(px*px+py*py+pzlab*pzlab); // pęd w LAB
				tetalab=(acos(pzlab/plab))*(180./M_PI); // kąt theta w LAB - M_PI to PI z maths.h


								if( tetalab < 20 || tetalab > 85 ) continue;

												if(plab >= 1.5) continue;

								pt=sqrt(px*px+py*py);

														if(pt <= 0.1) continue;

	y=(1/2.)*log((E+pz)/(E-pz));

	//	h->Fill(y,pt);

							h_w_lab->Fill(ylab,pt);

// h1->Fill(momentum->GetRandom() );

 }


h->Draw("colz");

h_w_lab->Draw("colz");

fteta20 -> Draw("same"); // wyrysowują funPt_Y_teta
fteta85 -> Draw("same");

fpmax -> Draw("same"); // wyrysowuję funPt_Y_pmax

Double_t NbinsX = h_w_lab -> GetXaxis() -> GetNbins(); //liczba binow
Double_t Xmin = h_w_lab -> GetXaxis() -> GetXmin();
Double_t Xmax = h_w_lab -> GetXaxis() -> GetXmax();
Double_t Xbinwidth = (Xmax-Xmin)/NbinsX; //szerokosc słupka bin
Double_t Ymin = Xmin;
Double_t Yi; // wartosc pospiesznosci w itym kroku

	// for (int i=1; i<=NbinsX; i++)
	//{
		//htemp = (TH1F*) h_w_lab -> ProjectionY("p",i,i,"e"); //bin od i do i, nazwa "p", e to option errors
		//htemp -> Draw();
		//can1 -> Update();
		//cin.ignore();
		//Yi = Ymin + 0.5*Xbinwidth + Xbinwidth*(i-1);
		//cout << Yi << endl;

	//}
//h1->Fit(momentum);
//gaus->Print();

return 0;
}
