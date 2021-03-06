{
  gROOT->Reset();
  printf("ROOT initialization starting\n");

  gStyle->SetOptStat(11);
  gStyle->SetPalette(1);
 
  gStyle->SetMarkerStyle(20);
  gStyle->SetMarkerSize(.9);
  gStyle->SetMarkerColor(2);
  Int_t font = 132; 
  gStyle->SetTickLength(0.02,"xy");
  gStyle->SetLabelSize(0.06,"xyz");
  gStyle->SetLabelFont(font,"xyz");
  //gStyle->SetLabelOffset(0.01,"xyz");
  gStyle->SetTitleFont(font,"xyz");
  gStyle->SetTitleOffset(1.03,"xyz");
  gStyle->SetTitleSize(0.06,"xyz");
  gStyle->SetNdivisions(410,"xy");
  gStyle->SetTitleAlign(22); 
  //gStyle->SetPadBottomMargin(2.9);
 // gStyle->SetPadTopMargin(0.2);
 //gStyle->SetPadLeftMargin(1.3);
 //gStyle->SetPadRightMargin(0.1);


  //gStyle->SetTitleSize(0.04);
  //gStyle->SetEndErrorSize(3);
  //gStyle->SetMarkerSize(1.2);
  //gStyle->SetPalette(1,0);
 //gStyle->SetPadTickX(1);
  //gStyle->SetPadTickY(1);
  //gStyle->SetLineWidth(1);

  gROOT->ForceStyle(true);
  return;   
    

}







