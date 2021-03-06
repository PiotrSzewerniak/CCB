
TFile *f1 = new TFile("KRATTA_histos_7334_7345.root");//0.2 nA
TFile *f2 = new TFile("KRATTA_histos_7043_7048.root");//2. nA
TFile *f3 = new TFile("KRATTA_histos_230MeV.root");


TH1F * h_protEn1, *h_protEn2, *h_protEn3;
TH2F *p10_vs_p12p13st1, *p10_vs_p12p13st3;
TH2F *p10_vs_p12p13stCut1, *p10_vs_p12p13stCut3;
TH2F *am1_vs_am2_1, *am1_vs_am2_Cut1;
TH2F *am1_vs_am2_3, *am1_vs_am2_Cut3;



void kratta_draw_bkg_mod0(){
    
  //Float_t scale=10.68;
  
  f1->cd();
  h_protEn1=(TH1F*)f1->Get("en_prot_mod0")->Clone();
  p10_vs_p12p13st1=(TH2F*)f1->Get("p10_vs_p12p13st_mod0")->Clone();
  p10_vs_p12p13stCut1=(TH2F*)f1->Get("p10_vs_p12p13stCut_mod0")->Clone();
  am1_vs_am2_1=(TH2F*)f1->Get("am1_vs_am2_mod0")->Clone();
  am1_vs_am2_Cut1=(TH2F*)f1->Get("am1_vs_am2_Cut_mod0")->Clone();

  f2->cd();
  h_protEn2=(TH1F*)f2->Get("en_prot_mod0")->Clone(); 


  f3->cd();
  h_protEn3=(TH1F*)f3->Get("en_prot_mod0")->Clone(); 
  p10_vs_p12p13st3=(TH2F*)f3->Get("p10_vs_p12p13st_mod0")->Clone();
  p10_vs_p12p13stCut3=(TH2F*)f3->Get("p10_vs_p12p13stCut_mod0")->Clone();
  am1_vs_am2_3=(TH2F*)f3->Get("am1_vs_am2_mod0")->Clone();
  am1_vs_am2_Cut3=(TH2F*)f3->Get("am1_vs_am2_Cut_mod0")->Clone();
  

  h_protEn1->SetLineColor(4);
  h_protEn2->SetLineColor(2);
 
  //h_protEn_empty->Scale(scale);
  //h_protEn_new->Add(h_protEn,h_protEn_empty,1.,-1.);
 

 //************************************************
 
 TCanvas *c1a = new TCanvas("bkg_comp_mod0","bkg_comp_mod0");
 c1a->Divide(1,0);

 c1a->cd(1);
 //gPad->SetLogy();
 h_protEn2->Draw(); 
 h_protEn1->Draw("same"); 
 
//###############################
 
 TCanvas *c2 = new TCanvas("2D_comp1_mod0","2D_comp1_mod0");
 c2->Divide(3,1);

 c2->cd(1);
 p10_vs_p12p13st1->Draw("colz"); 

 c2->cd(2);
 p10_vs_p12p13st3->Draw("colz"); 
  
 c2->cd(3);
 p10_vs_p12p13st3->Draw("colz"); 
 p10_vs_p12p13st1->Draw("same"); 

 
//###############################
 
 TCanvas *c3 = new TCanvas("2D_comp2_mod0","2D_comp2_mod0");
 c3->Divide(2,1);

 c3->cd(1);
 am1_vs_am2_1->Draw("colz"); 

 c3->cd(2);
 am1_vs_am2_3->Draw("colz"); 
  
 // c3->cd(3);
 //am1_vs_am2_3->Draw("colz"); 
 //am1_vs_am2_1->Draw("same"); 



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
