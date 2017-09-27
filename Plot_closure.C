#include <TH1D.h>
#include <TPad.h>
#include <TCanvas.h>
#include <TList.h>
#include <TStyle.h>
#include <vector>
#include <cstdio>
#include <tdrstyle2.C>
#include "CMS_lumi.C"

using namespace std;

/*

  Usage:

.x Plot_closure.C("delphi","NJets","stacked","Elog377_")
.x Plot_closure.C("delphi","NBtag","stacked","Elog377_")
.x Plot_closure.C("delphi","HT","stacked","Elog377_")
.x Plot_closure.C("delphi","MHT","stacked","Elog377_")
.x Plot_closure.C("delphi","MET","stacked","Elog377_")

root.exe -b -q 'Plot_closure.C("delphi","NJets","stacked","Elog377_",true)'
root.exe -b -q 'Plot_closure.C("delphi","NBtag","stacked","Elog377_",true)'
root.exe -b -q 'Plot_closure.C("delphi","HT","stacked","Elog377_",true)'
root.exe -b -q 'Plot_closure.C("delphi","MHT","stacked","Elog377_",true)'

root.exe -b -q 'Plot_closure.C("mht_200","NJets","stacked","Elog377_",true)'
root.exe -b -q 'Plot_closure.C("isoPion","NJets","stacked","Elog377_",true)'
root.exe -b -q 'Plot_closure.C("delphi","NJets","stacked","Elog377_",true)'
root.exe -b -q 'Plot_closure.C("delphi_NoIso","NJets","stacked","",true)'
root.exe -b -q 'Plot_closure.C("met_500","NJets","stacked","Elog377_",true)'
root.exe -b -q 'Plot_closure.C("J46_HT5001200_MHT500750","NJets","stacked","Elog377_",true)'


.x Plot_closure.C("delphi","DelPhiN","stacked","Elog365_")
.x Plot_closure.C("delphi","DelPhi1","stacked","Elog365_")
.x Plot_closure.C("delphi","DelPhi2","stacked","Elog365_")
.x Plot_closure.C("delphi","DelPhi3","stacked","Elog365_")

root.exe -b -q 'Plot_closure.C("mht_200","DelPhi1","stacked","Elog377_",true,true)'
root.exe -b -q 'Plot_closure.C("mht_200","DelPhi2","stacked","Elog377_",true,true)'
root.exe -b -q 'Plot_closure.C("mht_200","DelPhi3","stacked","Elog377_",true,true)'
root.exe -b -q 'Plot_closure.C("mht_200","DelPhi4","stacked","Elog377_",true,true)'
root.exe -b -q 'Plot_closure.C("mht_200","TauJet_MHT_delPhi","stacked","Elog377_",true,true)'

root.exe -b -q 'Plot_closure.C("mht_500","DelPhi1","stacked","Elog377_",true,true)'
root.exe -b -q 'Plot_closure.C("mht_500","DelPhi2","stacked","Elog377_",true,true)'
root.exe -b -q 'Plot_closure.C("mht_500","DelPhi3","stacked","Elog377_",true,true)'
root.exe -b -q 'Plot_closure.C("mht_500","DelPhi4","stacked","Elog377_",true,true)'

root.exe -b -q 'Plot_closure.C("J46_HT5001200_MHT500750","DelPhi1","stacked","Elog377_",true)'
root.exe -b -q 'Plot_closure.C("J46_HT5001200_MHT500750","DelPhi2","stacked","Elog377_",true)'
root.exe -b -q 'Plot_closure.C("J46_HT5001200_MHT500750","DelPhi3","stacked","Elog377_",true)'
root.exe -b -q 'Plot_closure.C("J46_HT5001200_MHT500750","DelPhi4","stacked","Elog377_",true)'

 */

// option="ExpVsPre" (= closure)
// option="ExpVsCS"
void Plot_closure(string cutname="baseline", string histname="MHT",string option="ExpVsPre",bool zoom=true, bool debug=false){

  //
  ///////////////////////////////////////////////////////////////////////////////////////////
  ////Some cosmetic work for official documents. 
  //
  // Set basic style
  //
  setTDRStyle();
  gStyle->SetPalette(1) ; // for better color output

  int W = 600;
  int H = 600;
  int H_ref = 600;
  int W_ref = 1000;
  float T = 0.10*H_ref;
  float B = 0.06*H_ref;
  float L = 0.16*W_ref;
  float R = 0.08*W_ref;

  //
  // Various vertical line coordinates
  float ymax_top = 300000.;
  float ymin_top = 0.015;

  float ymax_bottom = 1.99;
  float ymin_bottom = 0.01;
  float ytext_top = 3200.;
  float x_legend = 10.;
  float y_legend = 4000.;
  float xtext_top;
  
  if (zoom){
   ymax_bottom = 1.49;
   ymin_bottom = 0.51;

   if(option.find("ExpVsCS")!=string::npos){
      ymax_bottom = 9.99;
      ymin_bottom = 0.01;
   }
  }

  //
  // Luminosity information for scaling
  double lumi = 35.9; // normaliza to 3 (fb-1)

  // true: do closure test (MC prediction vs MC truth)
  // false: do data driven prediction and compare to MC truth
  bool doDataVsMC = false;


  ///////////////////////////////////////////////////////////////////////////////////////////
  //
  // More specific style set, opening input files etc
  //

  gStyle->SetOptStat(0);  ///to avoid the stat. on the plots 
  char tempname[200];
  std::string tempnameString;
  char xtitlename[200];
  char ytitlename[200];
  
  sprintf(tempname,"LLPrediction.root");
  TFile * LLFile = new TFile(tempname,"R");
  printf("Opened %s\n",tempname);

  //
  // Define legend
  //
  Float_t legendX1 = .55; //.50;
  Float_t legendX2 = .93; //.70;
  Float_t legendY1 = .73; //.65;
  Float_t legendY2 = .91;


  TLegend* catLeg1 = new TLegend(legendX1,legendY1,legendX2,legendY2);
  catLeg1->SetTextSize(0.038);
  catLeg1->SetTextFont(42);
  catLeg1->SetFillColor(0);
  catLeg1->SetLineColor(1);
  catLeg1->SetBorderSize(1);

  //
  // Define canvas
  //
  TCanvas *canvas = new TCanvas("canvas","canvas",10,10,W,H);

  canvas->SetFillColor(0);
  canvas->SetBorderMode(0);
  canvas->SetFrameFillStyle(0);
  canvas->SetFrameBorderMode(0);
  canvas->SetLeftMargin( L/W );
  canvas->SetRightMargin( R/W );
  canvas->SetTopMargin( T/H );
  canvas->SetBottomMargin( B/H );
  //canvas->SetTickx(0);
  //canvas->SetTicky(0);

  canvas->Divide(1, 2);

  //
  // Define pads
  //
  TPad* canvas_up = (TPad*) canvas->GetListOfPrimitives()->FindObject("canvas_1");
  TPad* canvas_dw = (TPad*) canvas->GetListOfPrimitives()->FindObject("canvas_2");
 
  // define the size
  double up_height     = 0.8;  // please tune so that the upper figures size will meet your requirement
  double dw_correction = 1.25; // please tune so that the smaller canvas size will work in your environment
  double font_size_dw  = 0.1;  // please tune the font size parameter for bottom figure
  double dw_height     = (1. - up_height) * dw_correction;
  double dw_height_offset = 0.04; // KH, added to put the bottom one closer to the top panel
 
  // set pad size
  canvas_up->SetPad(0., 1 - up_height,    1., 0.94);
  canvas_dw->SetPad(0., 0.,               1., dw_height+dw_height_offset);
  
  canvas_up->SetFrameFillColor(0);
  canvas_up->SetFillColor(0);
  canvas_dw->SetFillColor(0);
  canvas_dw->SetFrameFillColor(0);
  canvas_dw->SetBottomMargin(0.3);
  
  // set top margin 0 for bottom figure
  canvas_dw->SetTopMargin(0);
  
  // draw top figure
  canvas_up->cd();

  TH1D * GenHist, * EstHist,* thist;
  TH1D * GenHistTemp, * EstHistTemp;
  TH1D * GenHistD, * EstHistD;
  TH1D * GenHistDTemp, * EstHistDTemp;
  TH1D * EstSystematics;
  TH1D * histTemplate;

  double HT_x_max=3000.;
  double HT_x_min=250.;
  double MHT_x_min=250.;
  double MHT_x_max=1500.;
  double NJet_x_min=1.5;
  double NJet_x_max=12.5;
  double NBtag_x_min=-0.5;
  double NBtag_x_max=3.5;

  double search_x_max=174.+0.5;
  if(option.find("QCD")!=string::npos)search_x_max=223.+0.5;
  double search_x_min=1.-0.5;

  double DelPhiN_x_max=20.;
  double DelPhiN_x_min=0.;
  double Delphi1_x_min=0.;
  double Delphi1_x_max=3.2;

  
  TDirectory *dPre = (TDirectory*)LLFile->Get("Plotting");
  TDirectory *dExp = (TDirectory*)LLFile->Get("Plotting");

  if(option.find("ExpVsPre")!=string::npos){
    tempnameString = "Pre";
	printf("Doing histograms: ExpVsPre\n");
  }else if(option.find("ExpVsCS")!=string::npos){
    tempnameString = "CS";
	printf("Doing histograms: ExpVsCS\n");    
  }

  if(histname=="search"){
    EstHist=(TH1D*) dExp->Get("totalExpCombined_LL_MC")->Clone();
    sprintf(tempname,"total%sCombined_LL_MC",tempnameString.data());
    GenHist=(TH1D*) dPre->Get(tempname)->Clone();
    sprintf(xtitlename,"search bins");
    sprintf(ytitlename,"Events");
    GenHist->SetMaximum(2000);
    GenHist->SetMinimum(0.);
    GenHist->GetXaxis()->SetRangeUser(search_x_min,search_x_max);
    GenHist->GetXaxis()->SetNdivisions(510);
    gPad->SetLogy();
  }
  if(histname=="HT"){
  	EstHist=(TH1D*) dExp->Get("totalExpCombined_LL_HT_MC")->Clone();
    sprintf(tempname,"total%sCombined_LL_HT_MC",tempnameString.data());
    GenHist=(TH1D*) dPre->Get(tempname)->Clone();
    xtext_top = 1800.;
    //y_legend  = 2000.;
    ymax_top = 300000.;
    ymin_top = 0.2;
    sprintf(xtitlename,"H_{T} [GeV]");
    sprintf(ytitlename,"Events / 250 GeV");
    GenHist->SetMaximum(ymax_top);
    GenHist->SetMinimum(ymin_top);
    GenHist->GetXaxis()->SetRangeUser(HT_x_min,HT_x_max);
    GenHist->GetXaxis()->SetNdivisions(510);
    gPad->SetLogy();
  }
  if(histname=="MHT"){
  	EstHist=(TH1D*) dExp->Get("totalExpCombined_LL_MHT_MC")->Clone();
    sprintf(tempname,"total%sCombined_LL_MHT_MC",tempnameString.data());
    GenHist=(TH1D*) dPre->Get(tempname)->Clone();
    xtext_top = 650.;
    //y_legend = 500.;
    ymax_top = 300000.;
    ymin_top = 0.2;
    sprintf(xtitlename,"#slash{H}_{T} [GeV]");
    sprintf(ytitlename,"Events / 125 GeV");
    GenHist->SetMaximum(ymax_top);
    GenHist->SetMinimum(ymin_top);
    GenHist->GetXaxis()->SetRangeUser(MHT_x_min,MHT_x_max);
    GenHist->GetXaxis()->SetNdivisions(-505);
    gPad->SetLogy();
  } 
  
  if(histname=="NBtag"){
  	EstHist=(TH1D*) dExp->Get("totalExpCombined_LL_NBTags_MC")->Clone();
    sprintf(tempname,"total%sCombined_LL_NBTags_MC",tempnameString.data());
    GenHist=(TH1D*) dPre->Get(tempname)->Clone();
    xtext_top = 2.8;
    //y_legend = 3000.;
    ymax_top = 300000.;
    ymin_top = 0.2;
    ytext_top = 0.65*ymax_top;
    sprintf(xtitlename,"N_{b-jet}");
    sprintf(ytitlename,"Events");
    GenHist->SetMaximum(ymax_top/2.);
    GenHist->SetMinimum(0.);
    GenHist->GetXaxis()->SetRangeUser(NBtag_x_min,NBtag_x_max);
    GenHist->GetXaxis()->SetNdivisions(205);
    gPad->SetLogy();
  }
  
  if(histname=="NJets"){
  	EstHist=(TH1D*) dExp->Get("totalExpCombined_LL_NJets_MC")->Clone();
    sprintf(tempname,"total%sCombined_LL_NJets_MC",tempnameString.data());
    GenHist=(TH1D*) dPre->Get(tempname)->Clone();
    xtext_top = 11.;
    //y_legend = 2000.;
    ymax_top = 300000.;
    ymin_top = 0.2;
    ytext_top = ymax_top*0.01;
    sprintf(xtitlename,"N_{jet}");
    sprintf(ytitlename,"Events");
    GenHist->SetMaximum(ymax_top);
    GenHist->SetMinimum(ymin_top);
    GenHist->GetXaxis()->SetRangeUser(NJet_x_min,NJet_x_max);
    GenHist->GetXaxis()->SetNdivisions(212);
    gPad->SetLogy();
  }
  if(histname=="MET"){
  	EstHist=(TH1D*) dExp->Get("totalExpCombined_LL_MET_MC")->Clone();
    sprintf(tempname,"total%sCombined_LL_MET_MC",tempnameString.data());
    GenHist=(TH1D*) dPre->Get(tempname)->Clone();
    ymax_top = 300000.;
    ymin_top = 0.2;
    sprintf(xtitlename,"MET [GeV]");
    sprintf(ytitlename,"Events / 125 GeV");
    GenHist->SetMaximum(ymax_top);
    GenHist->SetMinimum(ymin_top);
    gPad->SetLogy();
  }
  if(histname=="DelPhiN"){
  	EstHist=(TH1D*) dExp->Get("totalExpCombined_LL_DelPhiN_MC")->Clone();
    sprintf(tempname,"total%sCombined_LL_DelPhiN_MC",tempnameString.data());
    GenHist=(TH1D*) dPre->Get(tempname)->Clone();
    xtext_top = 14.;
    //y_legend = 1300.;
    ymax_top = 600.;
    ymin_top = 0.0;
    ytext_top = ymax_top*0.65;
    sprintf(xtitlename,"DelPhiN");
    sprintf(ytitlename,"Events");
    GenHist->SetMaximum(ymax_top);
    GenHist->SetMinimum(ymin_top);
    GenHist->GetXaxis()->SetRangeUser(DelPhiN_x_min,DelPhiN_x_max);
  }   
  if(histname=="DelPhi1"){
  	EstHist=(TH1D*) dExp->Get("totalExpCombined_LL_DelPhi1_MC")->Clone();
    sprintf(tempname,"total%sCombined_LL_DelPhi1_MC",tempnameString.data());
    GenHist=(TH1D*) dPre->Get(tempname)->Clone();
    xtext_top = 1.2;
    //y_legend = 1300.;
    ymax_top = 10000.;
    ymin_top = 1.;
    ytext_top = ymax_top*0.05;
    sprintf(xtitlename,"DelPhi1");
    sprintf(ytitlename,"Events");
    GenHist->SetMaximum(ymax_top);
    GenHist->SetMinimum(ymin_top);
    GenHist->GetXaxis()->SetRangeUser(Delphi1_x_min,Delphi1_x_max);
    gPad->SetLogy();
  }
  if(histname=="DelPhi2"){
  	EstHist=(TH1D*) dExp->Get("totalExpCombined_LL_DelPhi2_MC")->Clone();
    sprintf(tempname,"total%sCombined_LL_DelPhi2_MC",tempnameString.data());
    GenHist=(TH1D*) dPre->Get(tempname)->Clone();
    xtext_top = 2.2;
    //y_legend = 1300.;
    ymax_top = 1000.;
    ymin_top = 10.;
    ytext_top = ymax_top*0.2;
    sprintf(xtitlename,"DelPhi2");
    sprintf(ytitlename,"Events");
    GenHist->SetMaximum(ymax_top);
    GenHist->SetMinimum(ymin_top);
    GenHist->GetXaxis()->SetRangeUser(Delphi1_x_min,Delphi1_x_max);
    gPad->SetLogy();
  }
  if(histname=="DelPhi3"){
  	EstHist=(TH1D*) dExp->Get("totalExpCombined_LL_DelPhi3_MC")->Clone();
    sprintf(tempname,"total%sCombined_LL_DelPhi3_MC",tempnameString.data());
    GenHist=(TH1D*) dPre->Get(tempname)->Clone();
    xtext_top = 2.2;
    //y_legend = 1300.;
    ymax_top = 1000.;
    ymin_top = 10.;
    ytext_top = ymax_top*0.2;
    sprintf(xtitlename,"DelPhi3");
    sprintf(ytitlename,"Events");
    GenHist->SetMaximum(ymax_top);
    GenHist->SetMinimum(ymin_top);
    GenHist->GetXaxis()->SetRangeUser(Delphi1_x_min,Delphi1_x_max);
    gPad->SetLogy();
  } 
  if(histname=="DelPhi4"){
  	EstHist=(TH1D*) dExp->Get("totalExpCombined_LL_DelPhi4_MC")->Clone();
    sprintf(tempname,"total%sCombined_LL_DelPhi4_MC",tempnameString.data());
    GenHist=(TH1D*) dPre->Get(tempname)->Clone();
    xtext_top = 2.2;
    //y_legend = 1300.;
    ymax_top = 1000.;
    ymin_top = 10.;
    ytext_top = ymax_top*0.2;
    sprintf(xtitlename,"DelPhi4");
    sprintf(ytitlename,"Events");
    GenHist->SetMaximum(ymax_top);
    GenHist->SetMinimum(ymin_top);
    GenHist->GetXaxis()->SetRangeUser(Delphi1_x_min,Delphi1_x_max);
    gPad->SetLogy();
  }

  printf("Opened histograms\n");

  if(EstHist->GetNbinsX() != GenHist->GetNbinsX()) std::cout<<"NbinsX of Expectation and Prediction don't agree!"<<std::endl;


  GenHist->SetLineColor(4);
  EstHist->SetLineColor(4);
  //GenHist->GetXaxis()->SetLabelFont(42);
  //GenHist->GetXaxis()->SetLabelOffset(0.007);
  //GenHist->GetXaxis()->SetLabelSize(0.04);
  //GenHist->GetXaxis()->SetTitleSize(0.05);
  //GenHist->GetXaxis()->SetTitleOffset(0.9);
  //GenHist->GetXaxis()->SetTitleOffset(0.5);
  //GenHist->GetXaxis()->SetTitleFont(42);
  //GenHist->GetYaxis()->SetLabelFont(42);
  //GenHist->GetYaxis()->SetLabelOffset(0.007);
  //GenHist->GetYaxis()->SetLabelSize(0.04);
  GenHist->GetYaxis()->SetLabelSize(0.045*1.15);
  GenHist->GetYaxis()->SetTitleSize(0.06*1.15*0.7);
  GenHist->GetYaxis()->SetTitleOffset(1.5);
  GenHist->GetYaxis()->SetTitleFont(42);

  //EstHist->GetXaxis()->SetLabelFont(42);
  //EstHist->GetXaxis()->SetLabelOffset(0.007);
  //EstHist->GetXaxis()->SetLabelSize(0.04);
  //EstHist->GetXaxis()->SetTitleSize(0.05);
  //EstHist->GetXaxis()->SetTitleOffset(0.9);
  //EstHist->GetXaxis()->SetTitleFont(42);
  //EstHist->GetYaxis()->SetLabelFont(42);
  //EstHist->GetYaxis()->SetLabelOffset(0.007);
  //EstHist->GetYaxis()->SetLabelSize(0.04);
  //EstHist->GetYaxis()->SetTitleSize(0.08);
  //EstHist->GetYaxis()->SetTitleOffset(2.0);
  //EstHist->GetYaxis()->SetTitleFont(42);


  //GenHist->GetYaxis()->SetTickLength(0.015);
  //GenHist->GetXaxis()->SetTickLength(0.02);

  //gPad->SetGridx(1);
  TExec *ex1 = new TExec("ex1","gStyle->SetErrorX(0.5);");
  TExec *ex2 = new TExec("ex2","gStyle->SetErrorX(0.5);");

  GenHist->SetTitle("");
  GenHist->SetMarkerStyle(20);
  GenHist->SetMarkerSize(0.6);
  GenHist->SetLineColor(1);
  GenHist->GetXaxis()->SetTitle(xtitlename);
  GenHist->GetYaxis()->SetTitle(ytitlename);
  TH1D * GenHist_Normalize = static_cast<TH1D*>(GenHist->Clone("GenHist_Normalize"));
  GenHist_Normalize->SetMaximum(ymax_top);
  GenHist_Normalize->SetMinimum(ymin_top);
  ex1->Draw();
  //GenHist_Normalize->GetListOfFunctions()->Add(ex1);
  GenHist_Normalize->DrawCopy("e");

  EstHist->SetFillStyle(1001);
  EstHist->SetFillColor(kRed-9);
  EstHist->SetMarkerStyle(20);
  EstHist->SetMarkerSize(0.0001);
  TH1D * EstHist_Normalize = static_cast<TH1D*>(EstHist->Clone("EstHist_Normalize"));
  ex2->Draw();
  //EstHist_Normalize->GetListOfFunctions()->Add(ex2);
  EstHist_Normalize->DrawCopy("e2same");
  //EstHist_Normalize->DrawCopy("esame");

  TH1D *EstHist_Normalize_Clone = (TH1D*)EstHist_Normalize->Clone();
  for(int i=1; i<EstHist_Normalize_Clone->GetNbinsX(); i++) {
    EstHist_Normalize_Clone->SetBinError(i,0);
  }
  EstHist_Normalize_Clone->SetFillColor(kWhite);
  EstHist_Normalize_Clone->Draw("esame");

  //GenHist->Print("all");
  //EstHist->Print("all");
  
  //
  // Re-draw to have "expectation" on top of "prediction"
  ex1->Draw();
  GenHist_Normalize->DrawCopy("esame");

    // Legend & texts
  if(option.find("ExpVsPre")!=string::npos){
    sprintf(tempname,"Lost-lepton background");
    catLeg1->SetHeader(tempname);
    sprintf(tempname,"Direct from simulation");
    catLeg1->AddEntry(GenHist,tempname,"pe");
    sprintf(tempname,"Treat simulation like data");
    catLeg1->AddEntry(EstHist,tempname);
  }else if(option.find("ExpVsCS")!=string::npos){
    sprintf(tempname,"Lost-lepton background");
    catLeg1->SetHeader(tempname);
    sprintf(tempname,"MC: lost-lepton events");
    catLeg1->AddEntry(GenHist,tempname,"pe");
    sprintf(tempname,"MC: control sample (e+#mu)");
    catLeg1->AddEntry(EstHist,tempname);
  }
  catLeg1->Draw();

  gPad->RedrawAxis();

  //
  //
  // Bottom ratio plot
  //
  // ----------

      TH1D * numerator   = static_cast<TH1D*>(GenHist->Clone("numerator"));
      TH1D * denominator = static_cast<TH1D*>(EstHist->Clone("denominator"));

      TH1D * GenHist_Clone = static_cast<TH1D*>(GenHist->Clone("GenHist_Clone"));
      TH1D * EstHist_Clone = static_cast<TH1D*>(EstHist->Clone("EstHist_Clone"));
      TH1D * EstHist_NoError = static_cast<TH1D*>(EstHist->Clone("EstHist_NoError"));
      for (int ibin=0; ibin<EstHist_NoError->GetNbinsX()+2; ibin++){ // scan including underflow and overflow bins
		EstHist_NoError->SetBinError(ibin,0.);
      }

      /*
      TH1D * denominator = static_cast<TH1D*>(EstHist->Clone("denominator"));
      EstHist->Add(GenHist,-1);
      denominator->Divide(EstHist,GenHist,1,1,"");
      */

    if(option.find("ExpVsCS")==string::npos){
      numerator->Divide(GenHist_Clone,EstHist_NoError,1,1,"");
      denominator->Divide(EstHist_Clone,EstHist_NoError,1,1,"");
    }else{
      numerator->Divide(GenHist_Clone,EstHist,1,1,"");
      denominator->Divide(EstHist_Clone,EstHist_NoError,1,1,"");
    }

      // draw bottom figure
      canvas_dw->cd();
      // font size
      numerator->GetXaxis()->SetLabelSize(font_size_dw);
      numerator->GetXaxis()->SetTitleSize(font_size_dw);
      numerator->GetYaxis()->SetLabelSize(font_size_dw);
      numerator->GetYaxis()->SetTitleSize(font_size_dw);
      //
      // Specific to each bottom plot
      //
      TLine *tline = 0;

      if(histname=="search"){
        sprintf(xtitlename,"Search bin");
        numerator->GetXaxis()->SetRangeUser(search_x_min,search_x_max);
        tline = new TLine(search_x_min,1.,search_x_max,1.);
      }
      if(histname=="HT"){
        sprintf(xtitlename,"H_{T} [GeV]");
        numerator->GetXaxis()->SetRangeUser(HT_x_min,HT_x_max);
        tline = new TLine(HT_x_min,1.,HT_x_max,1.);
      }
      if(histname=="MHT"){
        sprintf(xtitlename,"#slash{H}_{T} [GeV]");
        numerator->GetXaxis()->SetRangeUser(MHT_x_min,MHT_x_max);
        tline = new TLine(MHT_x_min,1.,MHT_x_max,1.);
      }   
      if(histname=="NBtag"){
        sprintf(xtitlename,"N_{b-jet}");
        numerator->GetXaxis()->SetRangeUser(NBtag_x_min,NBtag_x_max);
        tline = new TLine(NBtag_x_min,1.,NBtag_x_max,1.);
	//ymax_bottom=1.5;
	//ymin_bottom=0.7;
      }    
      if(histname=="NJets"){
        sprintf(xtitlename,"N_{jet}");
        numerator->GetXaxis()->SetRangeUser(NJet_x_min,NJet_x_max);
        tline = new TLine(NJet_x_min,1.,NJet_x_max,1.);
	//ymax_bottom=1.5;
	//ymin_bottom=0.5;
      }
      if(histname=="MET"){
        sprintf(xtitlename,"MET [GeV]");
        numerator->GetXaxis()->SetRangeUser(MHT_x_min,MHT_x_max);
        tline = new TLine(MHT_x_min,1.,MHT_x_max,1.);
      }
      if(histname=="DelPhiN"){
        sprintf(xtitlename,"DelPhiN");
        numerator->GetXaxis()->SetRangeUser(DelPhiN_x_min,DelPhiN_x_max);
        tline = new TLine(DelPhiN_x_min,1.,DelPhiN_x_max,1.);
      }
      if(histname=="DelPhi1"){
        sprintf(xtitlename,"DelPhi1");
        numerator->GetXaxis()->SetRangeUser(Delphi1_x_min,Delphi1_x_max);
        tline = new TLine(Delphi1_x_min,1.,Delphi1_x_max,1.);
      } 
      if(histname=="DelPhi2"){
        sprintf(xtitlename,"DelPhi2");
        numerator->GetXaxis()->SetRangeUser(Delphi1_x_min,Delphi1_x_max);
        tline = new TLine(Delphi1_x_min,1.,Delphi1_x_max,1.);
      }
      if(histname=="DelPhi3"){
        sprintf(xtitlename,"DelPhi3");
        numerator->GetXaxis()->SetRangeUser(Delphi1_x_min,Delphi1_x_max);
        tline = new TLine(Delphi1_x_min,1.,Delphi1_x_max,1.);
      }
      if(histname=="DelPhi4"){
        sprintf(xtitlename,"DelPhi4");
        numerator->GetXaxis()->SetRangeUser(Delphi1_x_min,Delphi1_x_max);
        tline = new TLine(Delphi1_x_min,1.,Delphi1_x_max,1.);
      }

      //
      // Common to all bottom plots
      //
      if(option.find("ExpVsPre")!=string::npos) sprintf(ytitlename,"#frac{Expectation}{Prediction} ");
      if(option.find("ExpVsCS")!=string::npos) sprintf(ytitlename,"#frac{Expectation}{ControlSample} ");

      numerator->SetMaximum(ymax_bottom);
      numerator->SetMinimum(ymin_bottom);

      // Setting style
      //numerator->SetMaximum(1.4);
      //numerator->GetXaxis()->SetLabelFont(42);
      numerator->GetXaxis()->SetLabelOffset(0.03);
      //numerator->GetXaxis()->SetLabelSize(0.04);
      numerator->GetXaxis()->SetTitleSize(0.12);
      numerator->GetXaxis()->SetTitleOffset(1.2);
      numerator->GetXaxis()->SetTitleFont(42);
      //numerator->GetYaxis()->SetLabelFont(42);
      //numerator->GetYaxis()->SetLabelOffset(0.007);
      //numerator->GetYaxis()->SetLabelSize(0.04);
      numerator->GetYaxis()->SetTitleSize(0.13);
      numerator->GetYaxis()->SetTitleOffset(0.5);
      numerator->GetYaxis()->SetTitleFont(42);

      numerator->GetXaxis()->SetTitle(xtitlename);
      numerator->GetYaxis()->SetTitle(ytitlename);

      numerator->GetXaxis()->SetTickSize(0.08);
      numerator->SetTitle("");
      if (zoom) numerator->GetYaxis()->SetNdivisions(505);
      ex1->Draw();
      numerator->Draw("");
      if (debug) numerator->Print("all");

    if(option.find("ExpVsCS")==string::npos){
      ex2->Draw();
      denominator->DrawCopy("e2same");
    
      TH1D *denominator_Clone = (TH1D*)denominator->Clone();
      denominator_Clone->SetFillColor(kWhite);
      denominator_Clone->Draw("hist same");
    }

      ex1->Draw();
      numerator->DrawCopy("same");
      gPad->RedrawAxis();

      //tline->SetLineStyle(2);
      //tline->Draw();

  //}
  

        TString line = "";
  sprintf(tempname,"%8.1f",lumi);
  line+=tempname;
  line+=" fb^{-1} (13 TeV)";
  
  int iPeriod = 0;    // 1=7TeV, 2=8TeV, 3=7+8TeV, 7=7+8+13TeV, 0=free form (uses lumi_sqrtS)
  int iPos = 0;
    
  TString lumi_sqrtS = line;

  writeExtraText = true;
  extraOverCmsTextSize = 0.6;
  extraText   = "        Simulation Supplementary ";

  lumiTextSize = 0.4;
  cmsTextSize = 0.6;

  relX1 = 0.16;
  relX2 = 0.22;
  relX3 = 0.97;

  CMS_lumi(canvas, iPeriod, iPos, lumi_sqrtS);

  TString arXivText = "arXiv:1704.07781";
  
  TLatex latexArXiv;
  latexArXiv.SetNDC();
  latexArXiv.SetTextAngle(0);
  latexArXiv.SetTextColor(kBlack);    

  latexArXiv.SetTextFont(42);
  latexArXiv.SetTextAlign(31); 
  latexArXiv.SetTextSize(lumiTextSize*extraOverCmsTextSize*canvas->GetTopMargin());    
  latexArXiv.DrawLatex(0.38,0.85,arXivText);


//  sprintf(tempname,"Closure_%s_%s_%s_Plot.png",histname.c_str(),cutname.c_str(),option.c_str());
//  canvas->Print(tempname);
  sprintf(tempname,"%s_%s_%s_Plot.pdf",option.c_str(),histname.c_str(),cutname.c_str());
  canvas->Print(tempname);

}

