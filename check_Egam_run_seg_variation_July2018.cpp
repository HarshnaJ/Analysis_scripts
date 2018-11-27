//***********************************************************************************************//
//Code to check the variation in the 24Mg 1.368 MeV Gamma peak between runs for each segment.	 //
//	19 July 2018										 //
//***********************************************************************************************//
{


  //Read in runlist
  vector<int> runlist;
  ifstream input;
  input.open("Mg24_runs_Col.dat");
    while(!input.eof())
	{
	 int dummy = 0;
	 input >> dummy;
	 runlist.push_back(dummy);	
	 //if(dummy!=0)  cout << "LIST:run number " << dummy << endl;
	 }

  Int_t nrofruns=(int)runlist.size()-1; 


  //Defining fit 
  Double_t xmin=1320,xmax=1420;
  TF1 *fit = new TF1("fit","gaus(0) + pol1(3)",xmin,xmax);
  //TF1 *fit = new TF1("fit","gaus(0)",xmin,xmax);
  Float_t height,position,sigm,intercept,slope;
  height = 30;
  position = 1366;
  sigm = 2;
  intercept = 0;
  slope = 0;
  fit->SetParameters(height,position,sigm,intercept,slope);
  //fit->SetParameters(height,position,sigm); 
  Double_t par[5];
  gStyle->SetOptFit(10001);



  //creating output file 
  int Clover = 1;
  char buffer[256];
  TString rebuffer= "Egam_Variation/Run_variation.dat";
  cout << rebuffer << endl;
  ofstream mOutput;
  mOutput.open(rebuffer);


  //variables
  double PeakPos[nrofruns], Variation[nrofruns], Resolution[nrofruns];
  char buffer[256];
  TCanvas *c1 = new TCanvas("c1","c1",800,600);
   char DetectorOption[256];
   char HistoName[256];
   char Filename1[256];
   char Filename2[256];

/*  //loop over clovers
  for(int j=Clover;j<Clover+1;j++)
    {
	//loop over segments
	for(int i=1;i<5;i++)
       {
	  mOutput << " " <<   endl;
 	  mOutput << " " <<   endl;
	  mOutput << "Variation data for Clover " << j << " Segment " << i<< endl;
	  mOutput << " " <<   endl;
*/	  mOutput << "Run #" << "\tPeak Position" << "\tVariation from first run" << "\tFWHM (keV)"<< endl;

	  //loop over runs
	  for(int k=0;k<nrofruns;k++)
	  {
	      sprintf(buffer,"16Jul_Sorted_1_CsCo/sorted0%d.root",runlist[k]);
	      //cout << buffer << endl;
	      TFile *f = TFile::Open(buffer);
	        if(f){ 
			//sprintf(HistoName,"Run%d_Clover%i_Segment%i",runlist[k],j,i);	
			sprintf(HistoName,"Run%d",runlist[k]);	
			TH1F *h = new TH1F("h",HistoName,300,1200,1500);
			//sprintf(DetectorOption,"X1flag==0 &&U1flag==0 &&Y1>-25 &&Y1<30 &&GammaDetectorType==\"Clover\" && GammaDetectorLabel==%d && GammaDetectorSegm==%d &&GammaTime>4000 &&GammaTime<5000",j,i);
			//sprintf(DetectorOption,"GammaDetectorType==\"Clover\" && GammaDetectorLabel==%d && GammaDetectorSegm==%d",j,i);

			//DATA->Draw("GammaEnergy>>h",DetectorOption,"");
			DATA->Draw("GammaEnergy>>h","GammaDetectorType==\"Clover\"","");
			//h->GetXaxis()->SetTitle("^{152}Eu Calibrated Gamma Energy (keV)");
			h->GetXaxis()->SetTitle("^{137}Cs-^{60}Co Calibrated Gamma Energy (keV)");
			h->GetYaxis()->SetTitle("Counts/1 keV");			
			
		        int entries = h->GetEntries();
			  if(entries==0) 
			   {PeakPos[k] = 0; Variation[k] = 0; Resolution[k] = 0;}
			  else{
			      h->Fit(fit,"R","",xmin,xmax);
			      fit->GetParameters(par);
			      PeakPos[k] = par[1];
			      Variation[k] = PeakPos[k]-PeakPos[0];
			      Resolution[k] = par[2]*2.35;
	    		      }
			c1->Modified(); c1->Update();
     			mOutput << runlist[k] << "\t" << PeakPos[k] << "\t" << Variation[k] << "\t" << Resolution[k] << endl;
			//sprintf(Filename1,"Egam_Variation/Run_%d_Clover%i_Segment%i.png",runlist[k],j,i);
			sprintf(Filename1,"Egam_Variation/Run_%d.png",runlist[k]);
			cout << " " << endl;
			cout << Filename1 << endl;
			cout << " " << endl;
			c1->SaveAs(Filename1);
     			c1->Clear();

		     }

	  } //run loop


//	} //seg loop
//    } //clover loop

  mOutput.close();

}
