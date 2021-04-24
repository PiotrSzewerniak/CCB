
TFile *f1 = new TFile("KRATTA_histos_230MeV.root");
TFile *f2 = new TFile("KRATTA_histos_7043_7048.root");
TFile *f3 = new TFile("myCuts_230MeV.root");


TH1F *h_protEn1, *h_protEn2;
TH2F *p10_vs_p12p13st1, *p10_vs_p12p13st2;
TH2F *p10_vs_p12p13stCut1, *p10_vs_p12p13stCut2;
TH2F *am1_vs_am2_1, *am1_vs_am2_Cut1;
TH2F *am1_vs_am2_2, *am1_vs_am2_Cut2;

TCutG *cut1, *cut2;

void kratta_draw_cuts_mod4_230MeV(){
    
  //Float_t scale=10.68;
  
  f1->cd();
  h_protEn1=(TH1F*)f1->Get("en_prot_mod4")->Clone();
  p10_vs_p12p13st1=(TH2F*)f1->Get("p10_vs_p12p13st_mod4")->Clone();
  p10_vs_p12p13stCut1=(TH2F*)f1->Get("p10_vs_p12p13stCut_mod4")->Clone();
  am1_vs_am2_1=(TH2F*)f1->Get("am1_vs_am2_mod4")->Clone();
  am1_vs_am2_Cut1=(TH2F*)f1->Get("am1_vs_am2_Cut_mod4")->Clone();

  f2->cd();
  h_protEn2=(TH1F*)f2->Get("en_prot_mod4")->Clone(); 
  p10_vs_p12p13st2=(TH2F*)f2->Get("p10_vs_p12p13st_mod4")->Clone();
  p10_vs_p12p13stCut2=(TH2F*)f2->Get("p10_vs_p12p13stCut_mod4")->Clone();
  am1_vs_am2_2=(TH2F*)f2->Get("am1_vs_am2_mod4")->Clone();
  am1_vs_am2_Cut2=(TH2F*)f2->Get("am1_vs_am2_Cut_mod4")->Clone();
  
  f3->cd();
  cut1=(TCutG*)f3->Get("cut_p10_vs_p12p13st_mod4")->Clone(); 
  cut2=(TCutG*)f3->Get("cut_am1_vs_am2_mod4")->Clone(); 


  h_protEn1->SetLineColor(4);
  h_protEn2->SetLineColor(2);
 
  //h_protEn_empty->Scale(scale);
  //h_protEn_new->Add(h_protEn,h_protEn_empty,1.,-1.);
 

 //************************************************
 
 
 
//###############################
 
 TCanvas *c2 = new TCanvas("cuts_Ctarget_mod4","cuts_Ctarget_mod4");
 c2->Divide(3,2);

 c2->cd(1);
 gPad->SetLogz();
 p10_vs_p12p13st1->Draw("colz"); 
 cut1->Draw("same");
 
 c2->cd(2);
 gPad->SetLogz();
 p10_vs_p12p13stCut1->Draw("colz"); 

 c2->cd(3);
 gPad->SetLogz();
 am1_vs_am2_1->Draw("colz"); 
 cut2->Draw("same");

 c2->cd(4);
 gPad->SetLogz();
 am1_vs_am2_Cut1->Draw("colz"); 


 c2->cd(5);
 h_protEn1->Draw();
 
//###############################
 
  TCanvas *c1 = new TCanvas("cuts_noTarget_mod4","cuts_noTarget_mod4");
  c1->Divide(3,2);

 c1->cd(1);
 //gPad->SetLogz();
 p10_vs_p12p13st2->Draw("colz"); 
 cut1->Draw("same");
 
 c1->cd(2);
 //gPad->SetLogz();
 p10_vs_p12p13stCut2->Draw("colz"); 

 c1->cd(3);
 //gPad->SetLogz();
 am1_vs_am2_2->Draw("colz"); 
 cut2->Draw("same");

 c1->cd(4);
 //gPad->SetLogz();
 am1_vs_am2_Cut2->Draw("colz"); 


 c1->cd(5);
 h_protEn2->Draw();


 //************************************************
 float x1=0.4, y1=0.8, x2=0.5, y2=0.85;
 //float a1=0.3, b1=0.8, a2=0.8, b2=0.89;
 char aa[100];
 char aa1[100];

 TPaveText *pt1 = new TPaveText(x1,y1,x2,y2,"NDC");
 pt1->SetFillColor(0);
 pt1->SetBorderSize(0);
 //pt1->SetTextFont(82);
 pt1->SetTextSize(0.06);
 pt1->SetTextColor(1);

 


}
