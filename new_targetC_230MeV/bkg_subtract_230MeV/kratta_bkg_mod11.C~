
TFile *f1 = new TFile("/home/ciepal/Main/KRATTA/spall-2017-06/myRoot_C/KRATTA_histos.root");
TFile *f2 = new TFile("/home/ciepal/Main/KRATTA/spall-2017-06/myRoot_emptyTar/KRATTA_histos_7043_7048.root");


TH1F * h_protEn;
TH1F * h_protEn_empty;


TH1F * h_protEnc1;
TH1F * h_protEn_emptyc1;
TH1F * h_protEn_emptyc2;

TH1F *h_protEn_new=new TH1F("a","a",250,0,250);

void kratta_bkg_mod11(){
  
  //Float_t scale=1.42;
  Float_t scale=10.68;
  
  f1->cd();
  h_protEn=(TH1F*)f1->Get("en_prot_mod11")->Clone();
  //h_protEn_empty->SetName("elastic_said");
  h_protEnc1=(TH1F*)f1->Get("en_prot_mod11")->Clone();

  f2->cd();
  h_protEn_empty=(TH1F*)f2->Get("en_prot_mod11")->Clone(); 
  h_protEn_emptyc1=(TH1F*)f2->Get("en_prot_mod11")->Clone();
  h_protEn_emptyc2=(TH1F*)f2->Get("en_prot_mod11")->Clone();
  //h_protEn_emptyc2=(TH1F*)h_protEn_emptyc1->Clone();
  h_protEn_emptyc2->Scale(scale);
  

  h_protEn_emptyc1->SetLineColor(2);
  h_protEn_emptyc2->SetLineColor(2);
 //_p - after  subtracting (only protons)
 
h_protEn_empty->Scale(scale);
h_protEn_new->Add(h_protEn,h_protEn_empty,1.,-1.);
 

 //************************************************
 
 TCanvas *c1a = new TCanvas("c1a","c1a");
 c1a->Divide(3,1);

 
 c1a->cd(1);
 gPad->SetLogy();
 h_protEnc1->Draw(); 
 h_protEn_emptyc1->Draw("same"); 
 
 c1a->cd(2);
 gPad->SetLogy();
 h_protEnc1->Draw(); 
 h_protEn_emptyc2->Draw("same"); 
 
 c1a->cd(3);
 gPad->SetLogy();
 h_protEn_new->Draw(); 
 
 


 //p0=1.30434 +/- 6.62878e-03

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

 

/*
TCanvas *c5 = new TCanvas("c5","c5 656 MeV/c SEC 03");
h_theta_cm_p_corr->SetLabelSize(0.05,"X");
h_theta_cm_p_corr->SetLabelSize(0.05,"Y");
h_theta_cm_p_corr->GetXaxis()->SetRangeUser(48,108);
h_theta_cm_p_corr->SetMarkerStyle(20);
h_theta_cm_p_corr->SetMaximum(420000);
h_theta_cm_p_corr->Draw();
h_theta_cm_p_corr->Sumw2();
h_elastic_said->GetXaxis()->SetRangeUser(48,115);
//h_elastic_said->Scale(2.69e5);
h_elastic_said->Scale(2.e5);
h_elastic_said->Draw("same"); 
*/


/*
 TCanvas *c5 = new TCanvas("c5","c5 656 MeV/c SEC 03 ");
c5->SetLogy();
h_ppim_miss2_p_PT->SetLabelSize(0.05,"X");
h_ppim_miss2_p_PT->SetLabelSize(0.05,"Y");
h_ppim_miss2_p_PT->SetMinimum(1.0);
h_ppim_miss2_p_PT->Draw();
h_ppim_miss2_p_sim->SetLineColor(3);
h_ppim_miss2_p_sim->Draw("same");
h_ppim_miss2_p_sim->Draw("same");
//

*/

}
