#include <vector>
#include <cstdio>
#include <iostream>   // std::cout
#include <string>     // std::string, std::to_string
#include "TCanvas.h"
#include "TH1.h"
#include "TExec.h"
#include "TDirectory.h"
#include "TLegend.h"
#include "TFile.h"
#include <tdrstyle.C>
#include <CMS_lumi.C>


using namespace std;

void Plot_1D_Closure(std::string infileName="LLPrediction.root", std::string plotName="Closure_vs_MHT.pdf", std::string expHist="totalExp_MHT_LL", std::string predHist="totalPred_MHT_LL_MC"){ 


  // do closure test (MC prediction vs MC truth)

  // Add systematics in quadrature to stat. uncertainty on prediction
  // Non-closure systematic not included yet!
  bool showSystematics = false;

  ///////////////////////////////////////////////////////////////////////////////////////////
  ////Some cosmetic work for official documents.
  //
  // Set basic style
  //
  setTDRStyle();
  gStyle->SetPalette(1) ; // for better color output

  //
  // Canvas size
  int W = 1200;
  int H = 1000;
  int H_ref = 740;
  int W_ref = 800;
  float T = 0.10*H_ref;
  float B = 0.06*H_ref;
  float L = 0.16*W_ref;
  float R = 0.04*W_ref;

  //
  // Various vertical line coordinates
  float ymax_top = 40000.;
  float ymin_top = 0.015;

  float ymax2_top = 1000.;
  float ymax3_top = 200.;
  float ymax4_top = 30.;

  float ymax_bottom = 1.99;
  float ymin_bottom = 0.01;

  float ymax2_bottom = 2.15;
  float ymax3_bottom = 2.15;
  float ymax4_bottom = 2.15;

  //
  // Luminosity information for scaling
  double lumi     = 2.3; // normaliza to this lumi (fb-1)
  double lumi_ref = 2.3; // normaliza to 3 (fb-1)
  
  ///////////////////////////////////////////////////////////////////////////////////////////
  //
  // More specific style set, opening input files etc

  gStyle->SetOptStat(0);  ///to avoid the stat. on the plots
  //gStyle->SetErrorX(0);
  //  char xtitlename[200];
  char ytitlename[200];

  TFile * LLFile = new TFile(infileName.c_str(),"R");
  printf("Opened %s\n",infileName.c_str());

  //
  // Define legend
  //
  Float_t legendX1 = .55; //.50;
  Float_t legendX2 = .95; //.70;
  Float_t legendY1 = .60; //.65;
  Float_t legendY2 = .85;

  TLegend* catLeg1 = new TLegend(legendX1,legendY1,legendX2,legendY2);
  //catLeg1->SetTextSize(0.060);
  catLeg1->SetTextSize(0.04);
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
  canvas->SetTickx(0);
  canvas->SetTicky(0);

  canvas->Divide(1, 2);
  
  //
  // Define pads
  //
  TPad* canvas_up = (TPad*) canvas->GetListOfPrimitives()->FindObject("canvas_1");
  TPad* canvas_dw = (TPad*) canvas->GetListOfPrimitives()->FindObject("canvas_2");

  //
  // define the size
  double up_height     = 0.8;  // please tune so that the upper figures size will meet your requirement
  double dw_correction = 1.30; // please tune so that the smaller canvas size will work in your environment
  double font_size_dw  = 0.1*0.7;  // please tune the font size parameter for bottom figure
  double dw_height     = (1. - up_height) * dw_correction;
  double dw_height_offset = 0.04; // KH, added to put the bottom one closer to the top panel

  //
  // set pad size
  canvas_up->SetPad(0., 1 - up_height,    1., 1.00);
  canvas_dw->SetPad(0., 0.,               1., dw_height+dw_height_offset);
  //
  canvas_up->SetFrameFillColor(0);
  canvas_up->SetFillColor(0);
  canvas_up->SetTopMargin(0.12);
  canvas_up->SetLeftMargin(0.1);
  //
  canvas_dw->SetFillColor(0);
  canvas_dw->SetFrameFillColor(0);
  canvas_dw->SetBottomMargin(0.35);
  canvas_dw->SetTopMargin(0);
  canvas_dw->SetLeftMargin(0.1);
  
  //
  // draw top figure
  canvas_up->cd();

  TH1D * GenHist, * EstHist,* thist;
  TH1D * GenHistTemp, * EstHistTemp;
  TH1D * GenHistD, * EstHistD;
  TH1D * GenHistDTemp, * EstHistDTemp;
  TH1D * EstSystematics;
  TH1D * histTemplate;

  double HT_x_max=2500.;
  double HT_x_min=400.;
  double MHT_x_max=1000.;
  double NJet_x_max=15.;
  double NBtag_x_max=4.;
  double search_x_max=73.-0.5;
  double search_x_min=1.-0.5;

  TDirectory *dPre = 0;
  TDirectory *dExp = (TDirectory*)LLFile->Get("SearchVariables");


  dPre = (TDirectory*)LLFile->Get("SearchVariables");
  EstHistTemp=(TH1D*) dPre->Get(predHist.c_str())->Clone();
  EstHistDTemp=(TH1D*) dPre->Get(predHist.c_str())->Clone();


  GenHistTemp=(TH1D*) dExp->Get(expHist.c_str())->Clone();
  string xtitlename=GenHistTemp->GetXaxis()->GetTitle();
  GenHistDTemp=(TH1D*) dExp->Get(expHist.c_str())->Clone();

  if(showSystematics){
    TDirectory *dSys = (TDirectory*)LLFile->Get("AdditionalContent");
    EstSystematics=(TH1D*) dSys->Get("totalPropSysUp_LL_MC")->Clone();
  }

  if(EstHistTemp->GetNbinsX() != GenHistTemp->GetNbinsX()) std::cout<<"NbinsX of Expectation and Prediction don't agree!"<<std::endl;

  EstHist = new TH1D("Exp", "Exp", EstHistTemp->GetNbinsX(), EstHistTemp->GetBinLowEdge(1), EstHistTemp->GetBinLowEdge(EstHistTemp->GetNbinsX()+1));
  EstHistD = new TH1D("ExpD", "ExpD", EstHistDTemp->GetNbinsX(), EstHistTemp->GetBinLowEdge(1), EstHistTemp->GetBinLowEdge(EstHistTemp->GetNbinsX()+1));
  GenHist = new TH1D("Pred", "Pred", GenHistTemp->GetNbinsX(), EstHistTemp->GetBinLowEdge(1), EstHistTemp->GetBinLowEdge(EstHistTemp->GetNbinsX()+1));
  GenHistD = new TH1D("PredD", "PredD", GenHistDTemp->GetNbinsX(), EstHistTemp->GetBinLowEdge(1), EstHistTemp->GetBinLowEdge(EstHistTemp->GetNbinsX()+1));

  for(int i = 0; i <= EstHistTemp->GetNbinsX()+1; i++){
    EstHist->SetBinContent(i, EstHistTemp->GetBinContent(i));    
    EstHistD->SetBinContent(i, EstHistDTemp->GetBinContent(i));

    if(showSystematics){
      EstHist->SetBinError(i, std::sqrt(EstHistTemp->GetBinError(i)*EstHistTemp->GetBinError(i)+EstSystematics->GetBinContent(i)*EstSystematics->GetBinContent(i)*EstHistTemp->GetBinError(i)*EstHistTemp->GetBinError(i)));
      EstHistD->SetBinError(i, std::sqrt(EstHistDTemp->GetBinError(i)*EstHistDTemp->GetBinError(i)+EstSystematics->GetBinContent(i)*EstSystematics->GetBinContent(i)*EstHistDTemp->GetBinError(i)*EstHistDTemp->GetBinError(i)));
    }else{
      EstHist->SetBinError(i, EstHistTemp->GetBinError(i));
      EstHistD->SetBinError(i, EstHistDTemp->GetBinError(i));
    }    

    GenHist->SetBinContent(i, GenHistTemp->GetBinContent(i));
    GenHist->SetBinError(i, GenHistTemp->GetBinError(i));
    GenHistD->SetBinContent(i, GenHistDTemp->GetBinContent(i));
    GenHistD->SetBinError(i, GenHistDTemp->GetBinError(i));
  }

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
  GenHist->GetYaxis()->SetTitleSize(0.06);
  GenHist->GetYaxis()->SetTitleOffset(0.75);
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
  //  sprintf(xtitlename,);
  sprintf(ytitlename,"Events");
  gPad->SetLogy();
  GenHist->SetMaximum(ymax_top);
  GenHist->SetMinimum(ymin_top);
  //GenHist->GetXaxis()->SetRangeUser(search_x_min,search_x_max);

  //GenHist->GetYaxis()->SetTickLength(0.015);
  //GenHist->GetXaxis()->SetTickLength(0.02);

  //gPad->SetGridx(1);
  TExec *ex1 = new TExec("ex1","gStyle->SetErrorX(0);");
  TExec *ex2 = new TExec("ex2","gStyle->SetErrorX(0.5);");

  GenHist->SetTitle("");
  GenHist->SetMarkerStyle(20);
  GenHist->SetMarkerSize(1.2);
  GenHist->SetLineColor(1);
  GenHist->GetXaxis()->SetTitle(xtitlename.c_str());
  GenHist->GetYaxis()->SetTitle(ytitlename);
  GenHist->Scale(lumi/lumi_ref);
  EstHist->Scale(lumi/lumi_ref);
  TH1D * GenHist_Normalize = static_cast<TH1D*>(GenHist->Clone("GenHist_Normalize"));
  GenHist_Normalize->SetMaximum(ymax_top);
  GenHist_Normalize->SetMinimum(ymin_top);
  ex1->Draw();
  //GenHist_Normalize->GetListOfFunctions()->Add(ex1);
  GenHist_Normalize->DrawCopy("e");

  EstHist->SetFillStyle(3144);
  EstHist->SetFillColor(kRed-10);
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

  GenHist->Print("all");
  EstHist->Print("all");
  
  //
  // Re-draw to have "expectation" on top of "prediction"
  ex1->Draw();
  GenHist_Normalize->DrawCopy("esame");
  //

  TString line = Form("%8.1f",lumi);
  line+=" fb^{-1} (13 TeV)";
  
  int iPeriod = 0;    // 1=7TeV, 2=8TeV, 3=7+8TeV, 7=7+8+13TeV, 0=free form (uses lumi_sqrtS)
  int iPos=0;
    
  writeExtraText = true;  
  extraText   = "        Simulation";
  //float extraTextFont = 52;  // default is helvetica-italics

  // text sizes and text offsets with respect to the top frame
  // in unit of the top margin size
  //lumiTextSize     = 0.5;
  //float lumiTextOffset   = 0.2;
  //cmsTextSize      = 0.65;
  //float cmsTextOffset    = 0.1;  // only used in outOfFrame version
  
  //relPosX    = 0.045;
  //relPosY    = 0.035;
  //relExtraDY = 1.2;
  
  // ratio of "CMS" and extra text size
  //float extraOverCmsTextSize  = 0.76;
    
  //TString lumi_13TeV = "20.1 fb^{-1}";
  //TString lumi_8TeV  = "19.7 fb^{-1}";
  //TString lumi_7TeV  = "5.1 fb^{-1}";
  TString lumi_sqrtS = line;

   // Legend & texts
  catLeg1->SetHeader("Lost-lepton background");
  catLeg1->AddEntry(GenHist,"Direct from simulation","p");
  catLeg1->AddEntry(EstHist,"Treat simulation like data");
  catLeg1->Draw();

  gPad->RedrawAxis();

  //
  // Bottom ratio plot
  //
  // ----------

  //
  // Preparing ratio histograms
  TH1D * numerator   = static_cast<TH1D*>(GenHist->Clone("numerator"));
  TH1D * numerator_fullstaterr   = static_cast<TH1D*>(GenHist->Clone("numerator_fullstaterr"));
  TH1D * denominator = static_cast<TH1D*>(EstHist->Clone("denominator"));

  TH1D * GenHist_Clone = static_cast<TH1D*>(GenHist->Clone("GenHist_Clone"));
  TH1D * EstHist_Clone = static_cast<TH1D*>(EstHist->Clone("EstHist_Clone"));
  TH1D * EstHist_NoError = static_cast<TH1D*>(EstHist->Clone("EstHist_NoError"));
  TH1D * One_NoError = static_cast<TH1D*>(EstHist->Clone("EstHist_NoError"));
  for (int ibin=0; ibin<EstHist_NoError->GetNbinsX()+2; ibin++){ // scan including underflow and overflow bins
    EstHist_NoError->SetBinError(ibin,0.);
    One_NoError->SetBinContent(ibin,1.);
    One_NoError->SetBinError(ibin,0.);
  }

  //EstHistD->Add(GenHistD,-1);
  numerator->Divide(GenHist_Clone,EstHist_NoError,1,1,"");
  denominator->Divide(EstHist_Clone,EstHist_NoError,1,1,"");

  numerator_fullstaterr->Divide(GenHist_Clone,EstHist_Clone,1,1,"");  // Expectation/Prediction
  numerator_fullstaterr->Add(One_NoError,-1.);                        // Expectation/Prediction-1

  // draw bottom figure
  canvas_dw->cd();
  // font size
  numerator->GetXaxis()->SetLabelSize(font_size_dw);
  numerator->GetXaxis()->SetTitleSize(font_size_dw*0.85);
  numerator->GetYaxis()->SetLabelSize(font_size_dw);
  numerator->GetYaxis()->SetTitleSize(font_size_dw);

  //
  // Horizontal Lines
  TLine *tline  = new TLine(search_x_min,1.,search_x_max,1.);
  TLine *tline0 = new TLine(search_x_min,0.,search_x_max,0.);

  //
  // Common to all bottom plots
  //
  //sprintf(ytitlename,"#frac{Estimate - #tau_{had} BG}{#tau_{had} BG} ");
  sprintf(ytitlename,"#frac{Direct}{Prediction} ");
  numerator->SetMaximum(ymax_bottom);
  numerator->SetMinimum(ymin_bottom);

  //
  // Specific to each bottom plot
  //
  // Setting style
  //numerator->SetMaximum(1.4);
  //numerator->GetXaxis()->SetLabelFont(42);
  //numerator->GetXaxis()->SetLabelOffset(0.007);
  numerator->GetXaxis()->SetLabelSize(0.18*0.045/0.06);
  numerator->GetXaxis()->SetTitleSize(0.18*0.85);
  numerator->GetXaxis()->SetTitleOffset(0.9);
  numerator->GetXaxis()->SetTitleFont(42);
  //numerator->GetYaxis()->SetLabelFont(42);
  //numerator->GetYaxis()->SetLabelOffset(0.007);
  numerator->GetYaxis()->SetLabelSize(0.18*0.035/0.06);
  numerator->GetYaxis()->SetTitleSize(0.1);
  //numerator->GetYaxis()->SetTitleOffset(0.5);
  numerator->GetYaxis()->SetTitleOffset(0.45);
  numerator->GetYaxis()->SetTitleFont(42);

  numerator->GetXaxis()->SetTitle(xtitlename.c_str());
  numerator->GetYaxis()->SetTitle(ytitlename);

  //gPad->SetGridx(1);


  //
  // Plotting
  numerator->GetYaxis()->SetNdivisions(505);
  numerator->GetYaxis()->SetTickLength(0.015);
  numerator->GetXaxis()->SetTickLength(0.08);
  numerator->SetTitle("");
  ex1->Draw();
  numerator->DrawCopy();

  ex2->Draw();
  denominator->DrawCopy("e2same");
  //denominator->DrawCopy("same");

  TH1D *denominator_Clone = (TH1D*)denominator->Clone();
  denominator_Clone->SetFillColor(kWhite);
  denominator_Clone->Draw("hist same");

  ex1->Draw();
  numerator->DrawCopy("same");

  numerator->Print("all");
  denominator->Print("all");
  numerator_fullstaterr->Print("all");

  //
  // Drawing lines
  tline->SetLineStyle(2);
  //tline->Draw();

  
      

  //
   

  gPad->RedrawAxis();

  //
  //

  CMS_lumi(canvas, iPeriod, iPos, lumi_sqrtS);

  canvas->Print( Form("Closure/%s",plotName.c_str()) );

}

