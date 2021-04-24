
TFile *f1 = new TFile("KRATTA_histos_7334_7345.root");//0.2 nA
TFile *f2 = new TFile("KRATTA_histos_7043_7048.root");//2. nA
//TFile *f3 = new TFile("KRATTA_histos_230MeV.root");


TH1F * h_protEn0_1, *h_protEn7_1;
TH1F * h_protEn0_2, *h_protEn7_2;
TH1F * h_protEn4_1, *h_protEn4_1;
TH1F * h_protEn11_2, *h_protEn11_2;


void kratta_empty_LRasym(){
    
    
  f1->cd();
  h_protEn0_1=(TH1F*)f1->Get("en_prot_mod0")->Clone();
  h_protEn7_1=(TH1F*)f1->Get("en_prot_mod7")->Clone();
  h_protEn4_1=(TH1F*)f1->Get("en_prot_mod4")->Clone();
  h_protEn11_1=(TH1F*)f1->Get("en_prot_mod11")->Clone();

  f2->cd();
  h_protEn0_2=(TH1F*)f2->Get("en_prot_mod0")->Clone();
  h_protEn7_2=(TH1F*)f2->Get("en_prot_mod7")->Clone();
  h_protEn4_2=(TH1F*)f2->Get("en_prot_mod4")->Clone();
  h_protEn11_2=(TH1F*)f2->Get("en_prot_mod11")->Clone();
  /*  
  h_protEn0_1->SetLineColor(1);
  h_protEn7_1->SetLineColor(2);

  h_protEn4_1->SetLineColor(3);
  h_protEn11_1->SetLineColor(4);

  h_protEn0_2->SetLineColor(1);
  h_protEn7_2->SetLineColor(2);
  h_protEn4_2->SetLineColor(3);
  h_protEn11_2->SetLineColor(4);
  */
  
  h_protEn0_1->SetLineColor(1);
  h_protEn7_1->SetLineColor(2);
  h_protEn0_2->SetLineColor(1);
  h_protEn0_2->SetLineStyle(7);

  h_protEn7_2->SetLineColor(2);
  h_protEn7_2->SetLineStyle(7);


  h_protEn4_1->SetLineColor(1);
  h_protEn11_1->SetLineColor(2);
  h_protEn4_2->SetLineColor(1);
  h_protEn11_2->SetLineColor(2);
  h_protEn4_2->SetLineStyle(7);
  h_protEn11_2->SetLineStyle(7);

 

 

  //h_protEn_empty->Scale(scale);
  //h_protEn_new->Add(h_protEn,h_protEn_empty,1.,-1.);
 

 //************************************************

 /*
 TCanvas *c1 = new TCanvas("empty_LRasym","empty_LRasym");
 c1->Divide(2,2);

 c1->cd(1);
 h_protEn7_1->Draw(); 
 h_protEn0_1->Draw("same"); 

 c1->cd(2);
 h_protEn7_2->Draw(); 
 h_protEn0_2->Draw("same");
 
 c1->cd(3);
 h_protEn4_1->Draw(); 
 h_protEn11_1->Draw("same");
 
 c1->cd(4);
 h_protEn4_2->Draw(); 
 h_protEn11_2->Draw("same");

 */
//###############################
  TCanvas *c1 = new TCanvas("empty_02_2nA","empty_02_2nA");
  c1->Divide(2,1);

 c1->cd(1);
 h_protEn7_1->Draw(); 
 h_protEn7_2->Draw("same");
 h_protEn0_1->Draw("same"); 
 h_protEn0_2->Draw("same"); 
 
 
 c1->cd(2);
 h_protEn4_1->Draw(); 
 h_protEn11_1->Draw("same");
 h_protEn4_2->Draw("same"); 
 h_protEn11_2->Draw("same");

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
