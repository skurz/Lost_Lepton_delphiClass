#include <TH1D.h>
#include <TPad.h>
#include <TCanvas.h>
#include <TList.h>
#include <TStyle.h>
#include <vector>
#include <cstdio>
#include <tdrstyle.C>

using namespace std;

/*

  Usage:

.x Plot_closure.C("delphi","NJet","stacked","Elog377_")
.x Plot_closure.C("delphi","NBtag","stacked","Elog377_")
.x Plot_closure.C("delphi","HT","stacked","Elog377_")
.x Plot_closure.C("delphi","MHT","stacked","Elog377_")
.x Plot_closure.C("delphi","MET","stacked","Elog377_")

root.exe -b -q 'Plot_closure.C("delphi","NJet","stacked","Elog377_",true)'
root.exe -b -q 'Plot_closure.C("delphi","NBtag","stacked","Elog377_",true)'
root.exe -b -q 'Plot_closure.C("delphi","HT","stacked","Elog377_",true)'
root.exe -b -q 'Plot_closure.C("delphi","MHT","stacked","Elog377_",true)'

root.exe -b -q 'Plot_closure.C("mht_200","NJet","stacked","Elog377_",true)'
root.exe -b -q 'Plot_closure.C("isoPion","NJet","stacked","Elog377_",true)'
root.exe -b -q 'Plot_closure.C("delphi","NJet","stacked","Elog377_",true)'
root.exe -b -q 'Plot_closure.C("delphi_NoIso","NJet","stacked","",true)'
root.exe -b -q 'Plot_closure.C("met_500","NJet","stacked","Elog377_",true)'
root.exe -b -q 'Plot_closure.C("J46_HT5001200_MHT500750","NJet","stacked","Elog377_",true)'


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

void Plot_closure(string cutname="nocut", string histname="MHT",string option="",bool zoom=true, bool debug=false){

  //
  ///////////////////////////////////////////////////////////////////////////////////////////
  ////Some cosmetic work for official documents. 
  //
  // Set basic style
  //
  gROOT->LoadMacro("tdrstyle.C");
  setTDRStyle();
  //gROOT->LoadMacro("CMS_lumi_v2.C");

  int W = 600;
  int H = 600;
  int H_ref = 600;
  int W_ref = 800;
  float T = 0.08*H_ref;
  float B = 0.12*H_ref;
  float L = 0.12*W_ref;
  float R = 0.08*W_ref;

  //
  // Various vertical line coordinates
  float ymax_top = 100000.;
  float ymin_top = 0.04.;
  float ymax_bottom = 1.99;
  float ymin_bottom = 0.01;
  float ytext_top = 3200.;
  float x_legend = 10.;
  float y_legend = 4000.;
  float xtext_top;
  
  if (zoom){
    ymax_bottom = 1.7;
    ymin_bottom = 0.45;
  }

  //
  // Luminosity information for scaling
  double lumi = 3.00; // normaliza to 3 (fb-1)

  // true: do closure test (MC prediction vs MC truth)
  // false: do data driven prediction and compare to MC truth
  bool doDataVsMC = false;


  ///////////////////////////////////////////////////////////////////////////////////////////
  //
  // More specific style set, opening input files etc
  //

  gStyle->SetOptStat(0);  ///to avoid the stat. on the plots 
  char tempname[200];
  char xtitlename[200];
  char ytitlename[200];
  
  vector<TFile *> filevec;
  
  if(sample.find("stack")==string::npos)sprintf(tempname,"TauHad/%sGenInfo_HadTauEstimation_%s.root",elogForExp.c_str(),sample.c_str());
  else sprintf(tempname,"TauHad/Stack/%sGenInfo_HadTauEstimation_%s.root",elogForExp.c_str(),sample.c_str());
  filevec.push_back(TFile::Open(tempname,"R"));

  if(sample.find("stack")==string::npos)sprintf(tempname,"TauHad2/%sHadTauEstimation_%s.root",elogForPre.c_str(),sample.c_str());
  else sprintf(tempname,"TauHad2/Stack/%sHadTauEstimation_%s.root",elogForPre.c_str(),sample.c_str());
  // sprintf(tempname,"TauHad2/Storage/HadTauEstimation_TTbar_Feb_17_2015.root");
  filevec.push_back(TFile::Open(tempname,"R"));

  //
  // Define legend
  //
  Float_t legendX1 = .35; //.50;
  Float_t legendX2 = .90; //.70;
  Float_t legendY1 = .76; //.65;
  Float_t legendY2 = .88;

  TLegend* catLeg1 = new TLegend(legendX1,legendY1,legendX2,legendY2);
  catLeg1->SetTextSize(0.032);
  catLeg1->SetTextFont(42);

  catLeg1->SetTextSize(0.042);
  catLeg1->SetTextFont(42);
  catLeg1->SetFillColor(0);
  catLeg1->SetLineColor(0);
  catLeg1->SetBorderSize(0);

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
  canvas->SetRightMargin( 0.2 );
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
  double dw_correction = 1.30; // please tune so that the smaller canvas size will work in your environment
  double font_size_dw  = 0.1;  // please tune the font size parameter for bottom figure
  double dw_height    = (1. - up_height) * dw_correction;
  double dw_height_offset = 0.040; // KH, added to put the bottom one closer to the top panel
 
  // set pad size
  canvas_up->SetPad(0., 1 - up_height, 0.97, 1.);
  canvas_dw->SetPad(0., dw_height_offset, 0.97, dw_height+dw_height_offset);
  canvas_up->SetFrameFillColor(0);
  canvas_up->SetFillColor(0);
  canvas_dw->SetFillColor(0);
  canvas_dw->SetFrameFillColor(0);
  canvas_dw->SetBottomMargin(0.25);
  
  // set top margin 0 for bottom figure
  canvas_dw->SetTopMargin(0);
  
  // draw top figure
  canvas_up->cd();

  THStack * tempstack;
  TH1D * GenHist, * EstHist,* thist;
  TH1D * histTemplate;

  double HT_x_max=2500.;
  double HT_x_min=400.;
  double MHT_x_max=1000.;
  double NJet_x_max=15.;
  double NBtag_x_max=4.;
  double search_x_max=19.;
  double search_x_min=0.;
  double DelPhiN_x_max=20.;
  double Delphi1_x_max=3.2;
  
  TH1D * GenHist_Clone;
  
  for(int i=0; i<filevec.size(); i++){

    if(sample.find("stacked")!=string::npos){

      if(i==0){
        if(histname=="search"){
          sprintf(tempname,"searchH");
          GenHist=(TH1D*) filevec.at(i)->Get(tempname)->Clone();
        }
        else{

          sprintf(tempname,"allEvents/%s/%s_%s_allEvents",cutname.c_str(),histname.c_str(),cutname.c_str());
          tempstack = (THStack*)filevec.at(i)->Get(tempname)->Clone();
          GenHist=(TH1D*) tempstack->GetStack()->Last();
        }
      }
      if(i==1){
        if(histname=="search"){
          sprintf(tempname,"searchH");
          GenHist=(TH1D*) filevec.at(i)->Get(tempname)->Clone();
        }        
        else{
          sprintf(tempname,"allEvents/%s/%s_%s_allEvents",cutname.c_str(),histname.c_str(),cutname.c_str());
          tempstack = (THStack*)filevec.at(i)->Get(tempname)->Clone();
          EstHist=(TH1D*) tempstack->GetStack()->Last();
        }
      }
      tempstack = (THStack*)filevec.at(i)->Get(tempname)->Clone();
      thist=(TH1D*) tempstack->GetStack()->Last();
      thist->SetLineColor(2*i+2);
      thist->SetFillColor(0);
      std::cout << "tempstack print starts" << std::endl;
      tempstack->Print();
      std::cout << "tempstack ends" << std::endl;

    }
    else{
      
      if(i==0){
        if(histname=="search"){
          sprintf(tempname,"searchH");
          GenHist=(TH1D*) filevec.at(i)->Get(tempname)->Clone();
        }
        else{
          sprintf(tempname,"allEvents/%s/%s_%s_allEvents",cutname.c_str(),histname.c_str(),cutname.c_str());
          GenHist=(TH1D*) filevec.at(i)->Get(tempname)->Clone();
        }
      }
      if(i==1){
  //      if(histname=="NBtag")sprintf(tempname,"allEvents/%s/nB_new_%s_allEvents",cutname.c_str(),cutname.c_str());
  //      else sprintf(tempname,"allEvents/%s/%s_%s_allEvents",cutname.c_str(),histname.c_str(),cutname.c_str());
        if(histname=="search"){
          sprintf(tempname,"searchH");
          EstHist=(TH1D*) filevec.at(i)->Get(tempname)->Clone();
        }
        else{
          sprintf(tempname,"allEvents/%s/%s_%s_allEvents",cutname.c_str(),histname.c_str(),cutname.c_str());
          EstHist=(TH1D*) filevec.at(i)->Get(tempname)->Clone();
        }
      }
      //    thist=(TH1D*) filevec.at(i)->Get(tempname)->Clone();
      thist=static_cast<TH1D*>(filevec.at(i)->Get(tempname)->Clone());
      thist->SetLineColor(2*i+2);
      
    }

    thist->SetTitle("");
//    thist->Scale(lumi/lumi_ttbar);

    //
    // Setting style
    //---------------
    if(i==0){
      thist->SetMaximum(1.4);
      //thist->GetXaxis()->SetLabelFont(42);
      //thist->GetXaxis()->SetLabelOffset(0.007);
      //thist->GetXaxis()->SetLabelSize(0.04);
      thist->GetXaxis()->SetTitleSize(0.05);
      thist->GetXaxis()->SetTitleOffset(1.9);
      thist->GetXaxis()->SetTitleFont(42);
      //thist->GetYaxis()->SetLabelFont(42);
      //thist->GetYaxis()->SetLabelOffset(0.007);
      //thist->GetYaxis()->SetLabelSize(0.04);
      thist->GetYaxis()->SetTitleSize(0.05);
      thist->GetYaxis()->SetTitleOffset(1.2);
      thist->GetYaxis()->SetTitleFont(42);
    }
    if(histname=="search"){
      sprintf(xtitlename,"search bins");
      sprintf(ytitlename,"Events");
      thist->SetMaximum(2000);
      thist->SetMinimum(0.);
      thist->GetXaxis()->SetRangeUser(search_x_min,search_x_max);
    }
    
    if(histname=="HT"){
      xtext_top = 1800.;
      //y_legend  = 2000.;
      ymax_top = 300000.;
      ymin_top = 0.2.;
      sprintf(xtitlename,"H_{T} (GeV)");
      sprintf(ytitlename,"Events / 200 GeV");
      thist->SetMaximum(ymax_top);
      thist->SetMinimum(ymin_top);
      thist->GetXaxis()->SetRangeUser(HT_x_min,HT_x_max);
      gPad->SetLogy();
      //thist->GetXaxis()->SetLimits(0.,HT_x_max);
    }
    if(histname=="MHT"){
      xtext_top = 650.;
      //y_legend = 500.;
      ymax_top = 1000000.;
      ymin_top = 0.05;
      sprintf(xtitlename,"#slash{H}_{T} (GeV)");
      sprintf(ytitlename,"Events / 100 GeV");
      thist->SetMaximum(ymax_top);
      thist->SetMinimum(ymin_top);
      thist->GetXaxis()->SetRangeUser(100.,MHT_x_max);
      gPad->SetLogy();
      //thist->GetXaxis()->SetLimits(0.,MHT_x_max);
    } 
    
    if(histname=="NBtag"){
      xtext_top = 2.8;
      //y_legend = 3000.;
      ymax_top = 4000.;
      ymin_top = 0.0;
      ytext_top = 0.65*ymax_top;
      sprintf(xtitlename,"Number of b-tags");
      sprintf(ytitlename,"Events");
      thist->SetMaximum(ymax_top/2.);
      thist->SetMinimum(0.);
      thist->GetXaxis()->SetRangeUser(0.,NBtag_x_max);
    }
    
    if(histname=="NJet"){
      xtext_top = 11.;
      //y_legend = 2000.;
      ymax_top = 300000.;
      ymin_top = 0.04.;
      ytext_top = ymax_top*0.01;
      sprintf(xtitlename,"Number of jets");
      sprintf(ytitlename,"Events");
      thist->SetMaximum(ymax_top);
      thist->SetMinimum(ymin_top);
      thist->GetXaxis()->SetRangeUser(3.,NJet_x_max);
      gPad->SetLogy();
    }
    if(histname=="MET"){
      sprintf(xtitlename,"MET (GeV)");
      sprintf(ytitlename,"Events / 100 GeV");
      thist->SetMaximum(50000);
      thist->GetXaxis()->SetRangeUser(0.,MHT_x_max);
      gPad->SetLogy();
      //thist->GetXaxis()->SetLimits(0.,MHT_x_max);
    }
    if(histname=="DelPhiN"){
      xtext_top = 14.;
      //y_legend = 1300.;
      ymax_top = 600.;
      ymin_top = 0.0;
      ytext_top = ymax_top*0.65;
      sprintf(xtitlename,"DelPhiN");
      sprintf(ytitlename,"Events");
      thist->SetMaximum(ymax_top);
      thist->SetMinimum(ymin_top);
      thist->GetXaxis()->SetRangeUser(0.,DelPhiN_x_max);
    }   
    if(histname=="DelPhi1"){
      xtext_top = 1.2;
      //y_legend = 1300.;
      ymax_top = 10000.;
      ymin_top = 1.;
      ytext_top = ymax_top*0.05;
      sprintf(xtitlename,"DelPhi1");
      sprintf(ytitlename,"Events");
      thist->SetMaximum(ymax_top);
      thist->SetMinimum(ymin_top);
      thist->GetXaxis()->SetRangeUser(0.,Delphi1_x_max);
      gPad->SetLogy();
    }
    if(histname=="DelPhi2"){
      xtext_top = 2.2;
      //y_legend = 1300.;
      ymax_top = 1000.;
      ymin_top = 10.;
      ytext_top = ymax_top*0.2;
      sprintf(xtitlename,"DelPhi2");
      sprintf(ytitlename,"Events");
      thist->SetMaximum(ymax_top);
      thist->SetMinimum(ymin_top);
      thist->GetXaxis()->SetRangeUser(0.,Delphi1_x_max);
      gPad->SetLogy();
    }
    if(histname=="DelPhi3"){
      xtext_top = 2.2;
      //y_legend = 1300.;
      ymax_top = 1000.;
      ymin_top = 10.;
      ytext_top = ymax_top*0.2;
      sprintf(xtitlename,"DelPhi3");
      sprintf(ytitlename,"Events");
      thist->SetMaximum(ymax_top);
      thist->SetMinimum(ymin_top);
      thist->GetXaxis()->SetRangeUser(0.,Delphi1_x_max);
      gPad->SetLogy();
    } 
    if(histname=="DelPhi4"){
      xtext_top = 2.2;
      //y_legend = 1300.;
      ymax_top = 1000.;
      ymin_top = 10.;
      ytext_top = ymax_top*0.2;
      sprintf(xtitlename,"DelPhi4");
      sprintf(ytitlename,"Events");
      thist->SetMaximum(ymax_top);
      thist->SetMinimum(ymin_top);
      thist->GetXaxis()->SetRangeUser(0.,Delphi1_x_max);
      gPad->SetLogy();
    }
    if(histname=="TauJet_MHT_delPhi"){
      xtext_top = 2.2;
      //y_legend = 1300.;
      ymax_top = 1000.;
      ymin_top = 1.;
      ytext_top = ymax_top*0.2;
      sprintf(xtitlename,"DelPhi-TauJet");
      sprintf(ytitlename,"Events");
      thist->Rebin(5);
      thist->SetMaximum(ymax_top);
      thist->SetMinimum(ymin_top);
      thist->GetXaxis()->SetRangeUser(0.,Delphi1_x_max);
      gPad->SetLogy();
    }

    if(histname=="TauJet_MHT_delPhi"){
      xtext_top = 2.2;
      //y_legend = 1300.;
      ymax_top = 100.;
      ymin_top = 0.01;
      ytext_top = ymax_top*0.2;
      sprintf(xtitlename,"#{Phi}(tau,mht)");
      sprintf(ytitlename,"Events");
      thist->SetMaximum(ymax_top);
      thist->SetMinimum(ymin_top);
      thist->GetXaxis()->SetRangeUser(0.,Delphi1_x_max);
      gPad->SetLogy();
    }

    //
    // Drawing plots
    //
    thist->GetXaxis()->SetTitle(xtitlename);
    thist->GetYaxis()->SetTitle(ytitlename);
    if(i==0){
      //thist->Draw();
      /*
      thist->SetFillStyle(3004);
      thist->SetFillColor(kGreen-3);
      */
      thist->SetMarkerStyle(20);
      thist->SetLineColor(1);
      thist->DrawCopy("e");      
      GenHist_Clone   = static_cast<TH1D*>(thist->Clone("GenHist_Clone"));
      std::cout << "thist print starts" << std::endl;
      if (debug) thist->Print("all");
      std::cout << "thist print ends" << std::endl;
    }
    else{
      thist->SetFillStyle(3144);
      thist->SetFillColor(kGreen-3);
      thist->SetMarkerStyle(20);
      thist->SetMarkerSize(0.0001);
      thist->DrawCopy("e2same ");
      thist->DrawCopy("esame ");
      std::cout << "thist print starts" << std::endl;
      if (debug) thist->Print("all");
      std::cout << "thist print ends" << std::endl;
    }

    //
    // Set up canvas
    //
    if(i==0){
      sprintf(tempname,"#tau_{hadronic} BG expectation (MC truth)");
      catLeg1->AddEntry(thist,tempname,"p");
    }
    else if(i==1){
      sprintf(tempname,"Prediction from MC");
      catLeg1->AddEntry(thist,tempname);
    }
  }

  GenHist_Clone->DrawCopy("esame");
  catLeg1->Draw();

  TText * ttext = new TLatex(xtext_top, ytext_top, "Normalized to 3 fb^{-1}");
  ttext->SetTextFont(42);
  ttext->SetTextSize(0.045);
  ttext->SetTextAlign(22);
  ttext->Draw();
  
  //
  // Bottom ratio plot
  //
  // ----------

  //if(choice==1){
    
      GenHist->SetMarkerStyle(20);
      GenHist->SetLineColor(1);

      EstHist->SetFillStyle(3144);
      EstHist->SetFillColor(kGreen-3);
      EstHist->SetMarkerStyle(20);
      EstHist->SetMarkerSize(0.0001);

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

      if(histname=="TauJet_MHT_delPhi"){
	numerator->Rebin(5);
	denominator->Rebin(5);
	GenHist_Clone->Rebin(5);
	EstHist_Clone->Rebin(5);
	EstHist_NoError->Rebin(5);
      }

      numerator->Divide(GenHist_Clone,EstHist_NoError,1,1,"");
      denominator->Divide(EstHist_Clone,EstHist_NoError,1,1,"");

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
      if(histname=="HT"){
        sprintf(xtitlename,"H_{T} (GeV)");
        numerator->GetXaxis()->SetRangeUser(HT_x_min,HT_x_max);
        TLine *tline = new TLine(HT_x_min,1.,HT_x_max,1.);
      }
      if(histname=="MHT"){
        sprintf(xtitlename,"#slash{H}_{T} (GeV)");
        numerator->GetXaxis()->SetRangeUser(100.,MHT_x_max);
        TLine *tline = new TLine(100.,1.,MHT_x_max,1.);
      }   
      if(histname=="NBtag"){
        sprintf(xtitlename,"Number of b-tags");
        numerator->GetXaxis()->SetRangeUser(0.,NBtag_x_max);
        TLine *tline = new TLine(0.,1.,NBtag_x_max,1.);
	//ymax_bottom=1.5;
	//ymin_bottom=0.7;
      }    
      if(histname=="NJet"){
        sprintf(xtitlename,"Number of jets");
        numerator->GetXaxis()->SetRangeUser(3.,NJet_x_max);
        TLine *tline = new TLine(3.,1.,NJet_x_max,1.);
	//ymax_bottom=1.5;
	//ymin_bottom=0.5;
      }
      if(histname=="MET"){
        sprintf(xtitlename,"MET (GeV)");
        numerator->GetXaxis()->SetRangeUser(0.,MHT_x_max);
        TLine *tline = new TLine(0.,1.,MHT_x_max,1.);
      }
      if(histname=="DelPhiN"){
        sprintf(xtitlename,"DelPhiN");
        numerator->GetXaxis()->SetRangeUser(0.,DelPhiN_x_max);
        TLine *tline = new TLine(0.,1.,DelPhiN_x_max,1.);
      }
      if(histname=="DelPhi1"){
        sprintf(xtitlename,"DelPhi1");
        numerator->GetXaxis()->SetRangeUser(0.,Delphi1_x_max);
        TLine *tline = new TLine(0.,1.,Delphi1_x_max,1.);
      } 
      if(histname=="DelPhi2"){
        sprintf(xtitlename,"DelPhi2");
        numerator->GetXaxis()->SetRangeUser(0.,Delphi1_x_max);
        TLine *tline = new TLine(0.,1.,Delphi1_x_max,1.);
      }
      if(histname=="DelPhi3"){
        sprintf(xtitlename,"DelPhi3");
        numerator->GetXaxis()->SetRangeUser(0.,Delphi1_x_max);
        TLine *tline = new TLine(0.,1.,Delphi1_x_max,1.);
      }
      if(histname=="DelPhi4"){
        sprintf(xtitlename,"DelPhi4");
        numerator->GetXaxis()->SetRangeUser(0.,Delphi1_x_max);
        TLine *tline = new TLine(0.,1.,Delphi1_x_max,1.);
      }
      if(histname=="TauJet_MHT_delPhi"){
        sprintf(xtitlename,"#Phi(tau,MHT)");
        numerator->GetXaxis()->SetRangeUser(0.,Delphi1_x_max);
        TLine *tline = new TLine(0.,1.,Delphi1_x_max,1.);
      }

      //
      // Common to all bottom plots
      //
      //      sprintf(ytitlename,"#frac{Estimate - #tau_{had} BG}{#tau_{had} BG} ");
      sprintf(ytitlename,"#frac{Expectation}{Prediction} ");
      numerator->SetMaximum(ymax_bottom);
      numerator->SetMinimum(ymin_bottom);

      // Setting style
      //numerator->SetMaximum(1.4);
      //numerator->GetXaxis()->SetLabelFont(42);
      //numerator->GetXaxis()->SetLabelOffset(0.007);
      //numerator->GetXaxis()->SetLabelSize(0.04);
      numerator->GetXaxis()->SetTitleSize(0.12);
      numerator->GetXaxis()->SetTitleOffset(0.9);
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
      if (zoom) numerator->GetYaxis()->SetNdivisions(510);
      numerator->Draw();
      if (debug) numerator->Print("all");

      denominator->DrawCopy("e2same");
      denominator->DrawCopy("same");

      numerator->DrawCopy("same");

      tline->SetLineStyle(2);
      tline->Draw();

  //}

  sprintf(tempname,"Closure_%s_%s_%s_%sPlot.png",histname.c_str(),cutname.c_str(),sample.c_str(),elogForPre.c_str());
  canvas->Print(tempname);
  sprintf(tempname,"Closure_%s_%s_%s_%sPlot.pdf",histname.c_str(),cutname.c_str(),sample.c_str(),elogForPre.c_str());
  canvas->Print(tempname);

}
