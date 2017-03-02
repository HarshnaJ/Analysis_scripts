///////////////////////////////////////////////////////////////////////////
// Macro for extrapolating line shape correction parameters	  	 //
//									 //
//  The run file of interest should be read in to root			 //
//  before implementing this script 					 //
//									 //
///////////////////////////////////////////////////////////////////////////

{

 //ToF vs X1 histogram
  TH2F *htofvsX1pos = new TH2F("htofvsX1pos","tof vs X1pos",700,100,800,100,1900,2000);
  TCanvas *C2 = new TCanvas;
  DATA->Draw("tof:X1pos>> htofvsX1pos","X1flag==0 &&U1flag==0 &&CUTpad1tof","col");
   htofvsX1pos->GetXaxis()->SetTitle("X1 position (mm)");
   htofvsX1pos->GetYaxis()->SetTitle("ToF");
   C2 -> Update();
   C2 -> Modified();

/////////////////////////////////////////////////////////////////////////////////////////////////


  TH2F *hPeakofInterest = new TH2F("hPeakofInterest","tof vs X1pos",20,-10,10,61,1930,1990);//I used th prominent peak in Run2232

  TCanvas *C4 = new TCanvas;
  DATA->Draw("tof:X1pos-694>> hPeakofInterest","X1flag==0 &&U1flag==0 &&CUTpad1tof","col"); //694 was the mean Xposition of the peak I used
   hPeakofInterest->GetXaxis()->SetTitle("X1-X1mean (mm)");
   hPeakofInterest->GetYaxis()->SetTitle("ToF");
   C4 -> Update();
   C4 -> Modified();


   TCanvas *C5 = new TCanvas;
   hPeakofInterest->FitSlicesX(0,2,69,0,"Q",0); //Fits each slice and creates histograms for each fit variable
   hPeakofInterest_1->Draw(); //histoname_1 is the histogram of the centroid parameters for each slice 
   hPeakofInterest_1->Fit("pol3");



 //implement lineshaping correction
  DATA->SetAlias("shapedX1","X1pos-(45027.1+(-65.0117*tof)+(0.031113*pow(tof,2))+(-4.93094e-6*pow(tof,3)))");


  TH2F *htofvsX1corr = new TH2F("htofvsX1corr","tof vs X1corr",700,100,800,100,1900,2000);
   TCanvas *C6 = new TCanvas;
   DATA->Draw("tof:shapedX1>> htofvsX1corr","X1flag==0 &&U1flag==0 &&CUTpad1tof","col");

   htofvsX1corr->GetXaxis()->SetTitle("Corrected X1 position (mm)");
   htofvsX1corr->GetYaxis()->SetTitle("ToF");
   C6 -> Update();
   C6 -> Modified();







}


# Analysis_scripts
# Analysis_scripts
