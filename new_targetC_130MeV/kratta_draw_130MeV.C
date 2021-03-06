
TFile *f1 = new TFile("KRATTA_histos_130MeV.root");
TFile *f2 = new TFile("KRATTA_histos_emptyTar130MeV.root");
TFile *f3 = new TFile("myCuts_130MeV.root");


TH1F *h_protEn4, *h_protEn11, *h_protEn3;
TH1F *h_protEn4bkg, *h_protEn3bkg;

TH2F *p10_vs_p12p13st4, *p10_vs_p12p13st11;
TH2F *p10_vs_p12p13stCut4, *p10_vs_p12p13stCut11;
TH2F *p10_vs_p12p13st3,*p10_vs_p12p13stCut3;
TH2F *am1_vs_am2_4, *am1_vs_am2_Cut4;
TH2F *am1_vs_am2_11, *am1_vs_am2_Cut11;
TH2F *am1_vs_am2_3, *am1_vs_am2_Cut3;
TCutG *cut1_4, *cut2_4;
TCutG *cut1_11, *cut2_11;

void kratta_draw_130MeV(){
    
  Float_t scale=20.;
  
  f1->cd();
  h_protEn4=(TH1F*)f1->Get("en_prot_mod4")->Clone();
  h_protEn4c=(TH1F*)f1->Get("en_prot_mod4")->Clone();
  p10_vs_p12p13st4=(TH2F*)f1->Get("p10_vs_p12p13st_mod4")->Clone();
  p10_vs_p12p13stCut4=(TH2F*)f1->Get("p10_vs_p12p13stCut_mod4")->Clone();
  am1_vs_am2_4=(TH2F*)f1->Get("am1_vs_am2_mod4")->Clone();
  am1_vs_am2_Cut4=(TH2F*)f1->Get("am1_vs_am2_Cut_mod4")->Clone();

  h_protEn11=(TH1F*)f1->Get("en_prot_mod11")->Clone();
  h_protEn11c=(TH1F*)f1->Get("en_prot_mod11")->Clone();
  p10_vs_p12p13st11=(TH2F*)f1->Get("p10_vs_p12p13st_mod11")->Clone();
  p10_vs_p12p13stCut11=(TH2F*)f1->Get("p10_vs_p12p13stCut_mod11")->Clone();
  am1_vs_am2_11=(TH2F*)f1->Get("am1_vs_am2_mod11")->Clone();
  am1_vs_am2_Cut11=(TH2F*)f1->Get("am1_vs_am2_Cut_mod11")->Clone();

  h_protEn3=(TH1F*)f1->Get("en_prot_mod3")->Clone();
  h_protEn3c=(TH1F*)f1->Get("en_prot_mod3")->Clone();
  p10_vs_p12p13st3=(TH2F*)f1->Get("p10_vs_p12p13st_mod3")->Clone();
  p10_vs_p12p13stCut3=(TH2F*)f1->Get("p10_vs_p12p13stCut_mod3")->Clone();
  am1_vs_am2_3=(TH2F*)f1->Get("am1_vs_am2_mod3")->Clone();
  am1_vs_am2_Cut3=(TH2F*)f1->Get("am1_vs_am2_Cut_mod3")->Clone();

 f2->cd();
 h_protEn4bkg=(TH1F*)f2->Get("en_prot_mod4")->Clone();
 h_protEn3bkg=(TH1F*)f2->Get("en_prot_mod3")->Clone();


  f3->cd();
  cut1_4=(TCutG*)f3->Get("cut_p10_vs_p12p13st_mod4")->Clone(); 
  cut2_4=(TCutG*)f3->Get("cut_am1_vs_am2_mod4")->Clone(); 
  cut1_11=(TCutG*)f3->Get("cut_p10_vs_p12p13st_mod11")->Clone(); 
  cut2_11=(TCutG*)f3->Get("cut_am1_vs_am2_mod11")->Clone(); 

  //h_protEn4->SetLineColor(4);
  //h_protEn11->SetLineColor(2);
 
  h_protEn4bkg->SetLineColor(2);
  h_protEn3bkg->SetLineColor(2);
  h_protEn4bkg->Scale(scale);
  h_protEn3bkg->Scale(scale);

  //h_protEn_empty->Scale(scale);
  //h_protEn_new->Add(h_protEn,h_protEn_empty,1.,-1.);
 
 
//###############################
  TCanvas *c2 = new TCanvas("Ctarget_130MeV_mod4","Ctarget_130MeV_mod4");
 c2->Divide(2,2);

 c2->cd(1);
 gPad->SetLogz();
 p10_vs_p12p13st4->Draw("colz"); 
 cut1_4->Draw("same");
 
  c2->cd(2);
 gPad->SetLogz();
 am1_vs_am2_4->Draw("colz"); 
 cut2_4->Draw("same");

 c2->cd(3);
 h_protEn4->Draw();
 h_protEn4bkg->Draw("same");

 c2->cd(4);
 h_protEn4c->GetXaxis()->SetRangeUser(80,140);
 h_protEn4c->Draw();
//###############################
 
 TCanvas *c1 = new TCanvas("Ctarget_130MeV_mod11","Ctarget_130MeV_mod11");
 c1->Divide(2,2);

 c1->cd(1);
 gPad->SetLogz();
 p10_vs_p12p13st11->Draw("colz"); 
 cut1_11->Draw("same");
 
  c1->cd(2);
 gPad->SetLogz();
 am1_vs_am2_11->Draw("colz"); 
 cut2_11->Draw("same");

 c1->cd(3);
 h_protEn11->Draw();

 c1->cd(4);
 h_protEn11c->GetXaxis()->SetRangeUser(80,140);
 h_protEn11c->Draw();
 //########################################

TCanvas *c3 = new TCanvas("Ctarget_130MeV_mod3","Ctarget_130MeV_mod3");
 c3->Divide(2,2);

 c3->cd(1);
 gPad->SetLogz();
 p10_vs_p12p13st3->Draw("colz"); 
 //cut1_4->Draw("same");
 
  c3->cd(2);
 gPad->SetLogz();
 am1_vs_am2_3->Draw("colz"); 
 //cut2_4->Draw("same");

 c3->cd(3);
 h_protEn3->Draw();
 h_protEn3bkg->Draw("same");

 c3->cd(4);
 h_protEn3c->GetXaxis()->SetRangeUser(80,140);
 h_protEn3c->Draw();
//###############################
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
