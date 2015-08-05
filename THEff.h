#include <SearchBins.h>

#include <TChain.h>
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TSelector.h>
#include <TTree.h>
#include <TH2F.h>
#include <TH1F.h>
#include "TVector2.h"
#include <cmath>
#include "TCanvas.h"
#include "TString.h"
#include "TEfficiency.h"
#include "TGraphAsymmErrors.h"
#include <iostream>
#include <iomanip> 

class TH1Eff
{
public:
	TH1Eff(){}
	TH1Eff(const char* name, const char* title, Int_t nbinsx, const double* xbins)
	{
		name_=TString(name);
		title_=TString(title);
		PassTH1F_ = new TH1F(name_+"Pass", title_, nbinsx, xbins);
		PassTH1F_->Sumw2();
		TotalTH1F_ = (TH1F*) PassTH1F_->Clone(name_+"Total");		
		RatioTH1F_ = (TH1F*) PassTH1F_->Clone(name_);
		RatioTGraphAsymm_ = new TGraphAsymmErrors();
	}
	TH1Eff(const char* name, const char* title, unsigned int nBins, double startBin, double endBin)
	{
		name_=TString(name);
		title_=TString(title);
		PassTH1F_ = new TH1F(name_+"Pass", title_, nBins, startBin, endBin);
		PassTH1F_->Sumw2();
		TotalTH1F_ = (TH1F*) PassTH1F_->Clone(name_+"Total");	
		RatioTH1F_ = (TH1F*) PassTH1F_->Clone(name_);
		RatioTGraphAsymm_ = new TGraphAsymmErrors();
	}
	TH1Eff(const char* name, TDirectory* MainDirectory)
	{	
		name_=TString(name);
		MainDirectory->cd();
		TDirectory *effDir = (TDirectory*)MainDirectory->Get(name_);
		effDir->cd();
		RatioTH1F_ = (TH1F*) effDir->Get(name_);
		RatioTGraphAsymm_ = (TGraphAsymmErrors*) effDir->Get(name_+"Asymm");
	}
	void SetName(const char* name){
		name_=TString(name);
		PassTH1F_->SetName(name_+" Pass");
		TotalTH1F_->SetName(name_+" Total");
		RatioTH1F_->SetName(name_);
	}
	void SetTitle(const char* title){
		title_=TString(title);
		PassTH1F_->SetTitle(title_);
		TotalTH1F_->SetTitle(title_);
	}
	void Fill(Double_t x, Double_t Weight, bool passOrFail);
	void SaveEff(TDirectory* MainDirectory){ SaveEff(title_, MainDirectory); }
	void SaveEff(const char* title, TDirectory* MainDirectory);
	void OpenEff(const char* name, TDirectory* MainDirectory);
	double GetEff(double xValue){ return GetEff(xValue, false); }
	double GetEff(double xValue, bool asymm);
	~TH1Eff(){}
private:
	TH1F* PassTH1F_;
	TH1F* TotalTH1F_;
	TH1F* RatioTH1F_;
	TGraphAsymmErrors* RatioTGraphAsymm_;
	TString name_;
	TString title_;
};

void TH1Eff::Fill(Double_t x, Double_t Weight, bool passOrFail)
{
	if(passOrFail){
		PassTH1F_->Fill(x, Weight);
		TotalTH1F_->Fill(x, Weight);
	}else{
		TotalTH1F_->Fill(x, Weight);
	}
}

void TH1Eff::SaveEff(const char* title, TDirectory* MainDirectory)
{
	MainDirectory->cd();
	MainDirectory->mkdir(name_);
	TDirectory *effDir = (TDirectory*)MainDirectory->Get(name_);
	effDir->cd();

	RatioTH1F_->Divide(PassTH1F_, TotalTH1F_, 1, 1, "B");
	RatioTH1F_->SetName(name_);
	RatioTH1F_->SetTitle(TString("Simulation, L=4 fb^{-1}, #sqrt{s}=13 TeV ") + TString(title));
	RatioTH1F_->SetMarkerSize(2.0);
  	RatioTH1F_->UseCurrentStyle();

  	gROOT->SetBatch(true);	  
	TCanvas *c1 = new TCanvas(name_,title_,1);
	c1->cd();
	if(RatioTH1F_->GetXaxis()->GetBinCenter(RatioTH1F_->GetXaxis()->GetNbins()) > 100) c1->SetLogx();
	RatioTH1F_->Draw("ColZ,Text,E");
	c1->SaveAs("Efficiencies/"+name_+".pdf");
	delete c1;
	gROOT->SetBatch(false);

	RatioTH1F_->Write();

	RatioTGraphAsymm_->Divide(PassTH1F_, TotalTH1F_, "cl=0.683 b(1,1) mode");
	RatioTGraphAsymm_->SetName(name_+"Asymm");
	RatioTGraphAsymm_->SetTitle(title);
	RatioTGraphAsymm_->Write();
}

double TH1Eff::GetEff(double xValue, bool asymm)
{
  	double result = 0;

  	if(xValue < RatioTH1F_->GetXaxis()->GetXmin()){
	    //std::cout<<"Warning xValue: "<<xValue<<" is smaller than minimum of histo: "<<RatioTH1F_->GetName()<<std::endl;
	    xValue= RatioTH1F_->GetXaxis()->GetXmin()+0.01;
	    //std::cout<<" Setting xValue to: "<<xValue<<std::endl;
	}
	else if(xValue > RatioTH1F_->GetXaxis()->GetXmax()){
	    //std::cout<<"Warning xValue: "<<xValue<<" is bigger than maximum of histo: "<<RatioTH1F_->GetName()<<" which is: "<<RatioTH1F_->GetXaxis()->GetXmax();
	    xValue= RatioTH1F_->GetXaxis()->GetXmax()-0.01;
	    //std::cout<<" Setting xValue to: "<<xValue<<std::endl;
	}

	int nxBin = RatioTH1F_->GetXaxis()->FindBin(xValue);

  	if(!asymm){
		result = RatioTH1F_->GetBinContent(nxBin);
	}else{
		Double_t xValueAsymm;
		RatioTGraphAsymm_->GetPoint(nxBin-1, xValueAsymm, result);
	//	std::cout <<"TH1<->TGraphAsymmErrors:"<< RatioTH1F_->GetBinContent(nxBin) << "; " << result << std::endl;
	}

	if(result<0.01){
		std::cout<<"Warning efficiency is: "<<result<<" is smaller than 0.01 for histo: "<<RatioTH1F_->GetName()<<std::endl;
		result =0.01;
	}
	if(result>1){
		std::cout<<"Warning efficiency is: "<<result<<" is bigger than 1 for histo: "<<RatioTH1F_->GetName()<<std::endl;
		result =0.99;
	}

	return result;
}

class TH2Eff
{
public:
	TH2Eff(){}
	TH2Eff(const char* name, const char* title, Int_t nbinsx, const double* xbins, Int_t nbinsy, const double* ybins)
	{
		name_=TString(name);
		title_=TString(title);
		nBinsy_=nbinsy;

		PassTH2F_ = new TH2F(name_+"Pass", title_, nbinsx, xbins, nbinsy, ybins);
		PassTH2F_->Sumw2();

		TotalTH2F_ = (TH2F*) PassTH2F_->Clone(name_+"Total");		
		RatioTH2F_ = (TH2F*) PassTH2F_->Clone(name_);

		for(int i = 0; i < nbinsy; ++i){
			PassTH1Fvec_.push_back(new TH1F(name_+"Pass_yBin"+std::to_string(i), title_, nbinsx, xbins));
			TotalTH1Fvec_.push_back(new TH1F(name_+"Total_yBin"+std::to_string(i), title_, nbinsx, xbins));
			RatioTGraphAsymmVec_.push_back(new TGraphAsymmErrors());
		}
	}
	TH2Eff(const char* name, const char* title, unsigned int nBinsx, double startBinx, double endBinx, unsigned int nBinsy, double startBiny, double endBiny)
	{
		name_=TString(name);
		title_=TString(title);
		nBinsy_=nBinsy;

		PassTH2F_ = new TH2F(name_+"Pass", title_, nBinsx, startBinx, endBinx, nBinsy, startBiny, endBiny);
		PassTH2F_->Sumw2();
		TotalTH2F_ = (TH2F*) PassTH2F_->Clone(name_+"Total");
		RatioTH2F_ = (TH2F*) PassTH2F_->Clone(name_);

		for(unsigned int i = 0; i < nBinsy; ++i){
			PassTH1Fvec_.push_back(new TH1F(name_+"Pass_yBin"+std::to_string(i+1), title_, nBinsx, startBinx, endBinx));
			TotalTH1Fvec_.push_back(new TH1F(name_+"Total_yBin"+std::to_string(i+1), title_, nBinsx, startBinx, endBinx));
			RatioTGraphAsymmVec_.push_back(new TGraphAsymmErrors());
		}
	}
	TH2Eff(const char* name, TDirectory* MainDirectory)
	{	
		name_=TString(name);
		MainDirectory->cd();
		TDirectory *effDir = (TDirectory*)MainDirectory->Get(name_);
		effDir->cd();
		RatioTH2F_ = (TH2F*) effDir->Get(name_);

		for(int i = 0; i < RatioTH2F_->GetYaxis()->GetNbins(); ++i){
			RatioTGraphAsymmVec_.push_back((TGraphAsymmErrors*) effDir->Get(name_+"_yBin"+std::to_string(i+1)));
		}	
		
	}
	void SetName(const char* name){
		name_=TString(name);
		PassTH2F_->SetName(name_+" Pass");
		TotalTH2F_->SetName(name_+" Total");
		RatioTH2F_->SetName(name_);
	}
	void SetTitle(const char* title){
		title_=TString(title);
		PassTH2F_->SetTitle(title_);
		TotalTH2F_->SetTitle(title_);
	}
	void Fill(Double_t x, Double_t y, Double_t Weight, bool passOrFail);
	void SaveEff(TDirectory* MainDirectory){ SaveEff(title_, MainDirectory); }
	void SaveEff(const char* title, TDirectory* MainDirectory);
	void OpenEff(const char* name, TDirectory* MainDirectory);
	double GetEff(double xValue, double yValue){ return GetEff(xValue, yValue, false); }
	double GetEff(double xValue, double yValue, bool asymm);
	~TH2Eff(){}
private:
	TH2F* PassTH2F_;
	TH2F* TotalTH2F_;
	TH2F* RatioTH2F_;

	std::vector<TH1F*> PassTH1Fvec_;
	std::vector<TH1F*> TotalTH1Fvec_;
	std::vector<TGraphAsymmErrors*> RatioTGraphAsymmVec_;

	TString name_;
	TString title_;

	int nBinsy_;
};

void TH2Eff::Fill(Double_t x, Double_t y, Double_t Weight, bool passOrFail)
{
	int nyBin = RatioTH2F_->GetYaxis()->FindBin(y);

	if(passOrFail){
		PassTH2F_->Fill(x, y, Weight);
		TotalTH2F_->Fill(x, y, Weight);
		
		if(nyBin > 0 && nyBin <= nBinsy_){
			PassTH1Fvec_.at(nyBin-1)->Fill(x, Weight);
			TotalTH1Fvec_.at(nyBin-1)->Fill(x, Weight);
		}

	}else{
		TotalTH2F_->Fill(x, y, Weight);

		if(nyBin > 0 && nyBin <= nBinsy_){
			TotalTH1Fvec_.at(nyBin-1)->Fill(x, Weight);
		}
	}
}

void TH2Eff::SaveEff(const char* title, TDirectory* MainDirectory)
{
	MainDirectory->cd();
	MainDirectory->mkdir(name_);
	TDirectory *effDir = (TDirectory*)MainDirectory->Get(name_);
	effDir->cd();

	RatioTH2F_->Divide(PassTH2F_, TotalTH2F_, 1, 1, "B");
	RatioTH2F_->SetName(name_);
	RatioTH2F_->SetTitle(TString("Simulation, L=4 fb^{-1}, #sqrt{s}=13 TeV ") + TString(title));
	RatioTH2F_->SetMarkerSize(2.0);
  	RatioTH2F_->UseCurrentStyle();

  	gROOT->SetBatch(true);	  
	TCanvas *c1 = new TCanvas(name_,title_,1);
	c1->cd();
	if(RatioTH2F_->GetXaxis()->GetBinCenter(RatioTH2F_->GetXaxis()->GetNbins()) > 100) c1->SetLogx();
	if(RatioTH2F_->GetYaxis()->GetBinCenter(RatioTH2F_->GetYaxis()->GetNbins()) > 100) c1->SetLogy();
	RatioTH2F_->SetMinimum(0.);
	RatioTH2F_->SetMaximum(1.);
	RatioTH2F_->Draw("ColZ,Text,E");
	c1->SaveAs("Efficiencies/"+name_+".pdf");
	delete c1;
	gROOT->SetBatch(false);

	RatioTH2F_->Write();

	for(int i = 0; i < nBinsy_; ++i){
		RatioTGraphAsymmVec_.at(i)->Divide(PassTH1Fvec_.at(i), TotalTH1Fvec_.at(i), "cl=0.683 b(1,1) mode");
		RatioTGraphAsymmVec_.at(i)->SetName(name_+"_yBin"+std::to_string(i+1));
		RatioTGraphAsymmVec_.at(i)->SetTitle(title);
		RatioTGraphAsymmVec_.at(i)->Write();
	}
}

double TH2Eff::GetEff(double xValue, double yValue, bool asymm)
{
  double result = 0;
  double resultAsymm = 0;

  if(xValue < RatioTH2F_->GetXaxis()->GetXmin() )
  {
    //std::cout<<"Warning xValue: "<<xValue<<" is smaller than minimum of histo: "<<RatioTH2F_->GetName()<<std::endl;
    xValue= RatioTH2F_->GetXaxis()->GetXmin()+0.01;
    //std::cout<<" Setting xValue to: "<<xValue<<std::endl;
  }
  else if(xValue > RatioTH2F_->GetXaxis()->GetXmax() )
  {
    //std::cout<<"Warning xValue: "<<xValue<<" is bigger than maximum of histo: "<<RatioTH2F_->GetName()<<" which is: "<<RatioTH2F_->GetXaxis()->GetXmax();
    xValue= RatioTH2F_->GetXaxis()->GetXmax()-0.01;
    //std::cout<<" Setting xValue to: "<<xValue<<std::endl;
  }
  
  if(yValue < RatioTH2F_->GetYaxis()->GetXmin() )
  {
    //std::cout<<"Warning yValue: "<<yValue<<" is smaller than minimum of histo: "<<RatioTH2F_->GetName()<<std::endl;
    yValue= RatioTH2F_->GetYaxis()->GetXmin()+0.01;
    //std::cout<<" Setting yValue to: "<<yValue<<std::endl;
  }
  else if(yValue > RatioTH2F_->GetYaxis()->GetXmax() )
  {
    //std::cout<<"Warning yValue: "<<yValue<<" is bigger than maximum of histo: "<<RatioTH2F_->GetName()<<std::endl;
    yValue= RatioTH2F_->GetYaxis()->GetXmax()-0.01;
    //std::cout<<" Setting yValue to: "<<yValue<<std::endl;
  }

  int nxBin = RatioTH2F_->GetXaxis()->FindBin(xValue);
  int nyBin = RatioTH2F_->GetYaxis()->FindBin(yValue);

  result = RatioTH2F_->GetBinContent(nxBin, nyBin);

  if(result<0.01)
  {
    std::cout<<"Warning efficiency is: "<<result<<" is smaller than 0.01 for histo: "<<RatioTH2F_->GetName()<<std::endl;
    result =0.01;
  }
  if(result>1)
  {
    std::cout<<"Warning efficiency is: "<<result<<" is bigger than 1 for histo: "<<RatioTH2F_->GetName()<<std::endl;
    result =0.99;
  }

  if(asymm && result>0.01){
  	Double_t xValueAsymm;
  	RatioTGraphAsymmVec_.at(nyBin-1)->GetPoint(nxBin-1, xValueAsymm, resultAsymm);
  	return resultAsymm;
  }

  return result;
}


class TH1Feff
{
public:
	TH1Feff(){}
	TH1Feff(const char* name, const char* title, Int_t nbinsx, const double* xbins)
	{
		RefTH1F_ = new 	TH1F(name, title, nbinsx, xbins);
		RefTH1F_->Sumw2();
		name_=name;
		title_=title;
	}
	TH1Feff(const char* name, const char* title, unsigned int nBins, double startBin, double endBin)
	{
		RefTH1F_ = new 	TH1F(name, title, nBins, startBin,endBin);
		RefTH1F_->Sumw2();
		name_=name;
		title_=title;
	}
	TH1F* Clone(){return RefTH1F_;}
	void SetName(const char* title){RefTH1F_->SetName(title); }
	void SetTitle(const char* title){RefTH1F_->SetTitle(title);}
	void Fill(Double_t x,Double_t Weight,bool passOrFail);
	TGraphAsymmErrors* GetEfficiency();
	TH1F* GetSanityCheckTH1F(){return RefTH1F_;}
	void saveResults(TDirectory* MainDirectory);
	~TH1Feff(){}
private:
	TH1F* RefTH1F_;
	vector<Double_t> weights_;
	vector<TH1F*> TH1FFail_, TH1FPass_;
	const char* name_;
	const char* title_;
};

class TH2Feff
{
public:
	TH2Feff(){}
	TH2Feff(const char* name, const char* title, Int_t nbinsx, const Double_t* xbins, Int_t nbinsy, const Double_t* ybins)
	{
		RefTH2F_ = new 	TH2F(name, title, nbinsx, xbins,nbinsy,ybins);
		RefTH2F_->Sumw2();
		nbinsx_=nbinsx; xbins_=xbins;
		nbinsy_=nbinsy; ybins_=ybins;
		name_=name;
		title_=title;
	}
	TH2F* Clone(){return RefTH2F_;}
	void SetName(const char* title){RefTH2F_->SetName(title);}
	void Fill(Double_t x, Double_t y, Double_t Weight,bool passOrFail);
	std::vector<TGraphAsymmErrors*> GetEfficiency();
	TH2F* GetSanityCheckTH2F(){return RefTH2F_;}
	void saveResults(TDirectory* MainDirectory);
	~TH2Feff(){}
private:
	TH2F* RefTH2F_;
	vector<Double_t> weights_;
	vector<TH2F*> TH2FFail_, TH2FPass_;
	Int_t nbinsx_, nbinsy_;
	const Double_t* xbins_;
	const Double_t* ybins_;
	const char* name_;
	const char* title_;
};
class Efficiency : public SearchBins
{
public:
	Efficiency(){}
	Efficiency(const char* name, const char* title);

	void Fill(double HT, double MHT, int NJets, int BTags, double Weight, bool passOrFail);

	void saveResults(TDirectory* MainDirectory);
	~Efficiency(){}
private:	
	const char* name_;
	const char* title_;
	TH1Feff* TH1FSearchBins_;
	std::vector<TH1Feff*> TH1FSearchBinsSplit_;
	unsigned int splitAfter_;
	
};
class SearchBinEventCount : public SearchBins
{
public:
	SearchBinEventCount(){}
	SearchBinEventCount(const char*);
	void Fill(double HT, double MHT, int NJets, int BTags, double Weight);
	void saveResults(TDirectory* MainDirectory);
	TH1F* getFullTH1F(){return fullTH1F_;}
	~SearchBinEventCount(){}
private:
	TH1F* fullTH1F_;
	std::vector<TH1F*> splitTH1F_;
	unsigned int splitAfter_;
	const char* name_;
};


void TH1Feff::Fill(Double_t x,Double_t Weight, bool passOrFail)
{
	int matched=-1;
	for(unsigned int i=0; i < weights_.size();i++)
	{
		if(std::abs(weights_[i]-Weight)/Weight<0.0001 ) matched=i;
	}
	if(matched==-1)
	{
		TH1F* tempPass = (TH1F*) RefTH1F_->Clone();
		TH1F* tempFail = (TH1F*) RefTH1F_->Clone();
		TH1FPass_.push_back(tempPass );
		TH1FFail_.push_back(tempFail );

		if(passOrFail)
		{
			TH1FPass_[weights_.size()]->Fill(x);
		}
		else TH1FFail_[weights_.size()]->Fill(x);
		weights_.push_back(Weight);
// 		std::cout<<"Weight: "<<Weight<<"added"<<std::endl;
	}
	else
	{
		if(passOrFail) TH1FPass_[matched]->Fill(x);
		else TH1FFail_[matched]->Fill(x);
	}
}
TGraphAsymmErrors* TH1Feff::GetEfficiency()
{
	TList* myList = new TList(); 
	// compute th1 for sanity check
	TH1F* sumRef = (TH1F*) RefTH1F_->Clone();
	sumRef->Sumw2();
	for(unsigned int i=0; i< TH1FFail_.size();i++)
	{
		sumRef->Add(TH1FPass_[i],weights_[i]);
		RefTH1F_->Add(TH1FPass_[i],weights_[i]);
		sumRef->Add(TH1FFail_[i],weights_[i]);
	}
	RefTH1F_->Divide(RefTH1F_,sumRef,1,1,"B");
	for(unsigned int i=0; i<weights_.size();i++)
	{
		TH1FFail_[i]->Sumw2();
		TH1F *sum = (TH1F*)TH1FFail_[i]->Clone();
		TH1FPass_[i]->Sumw2();
		
		sum->Add(TH1FPass_[i]);
		TEfficiency* myEff = new TEfficiency(*TH1FPass_[i],*sum);
// 		std::cout<<"Eff["<<i<<"]: "<<myEff->GetEfficiency(14)<<" +"<<myEff->GetEfficiencyErrorUp(14)<<" - "<<myEff->GetEfficiencyErrorLow(14)<<" passed: "<<myEff->GetPassedHistogram()->GetBinContent(14)<<" totalN: "<<myEff->GetTotalHistogram()->GetBinContent(14)<<" Weight: "<<weights_[i]<<" xCenter: "<<myEff->GetPassedHistogram()->GetBinCenter(14)<<"\n";
// 		myEff->SetWeight(weights_[i]);
		myList->Add(myEff);
	}
	const Int_t size=weights_.size();
	Double_t weightArray[size];
	for(int i=0; i<size;i++)weightArray[i]=weights_[i];
	
	TGraphAsymmErrors* result= TEfficiency::Combine ((TCollection*)&*myList,(Option_t*)"kBUniform",(Int_t)weights_.size(),weightArray);
// 	std::cout<<"Total Eff: "<<result->GetY()[13]<<" + "<<result->GetEYhigh()[13]<<" - "<<result->GetErrorYlow(13)<<" x value: "<<result->GetX()[13]<<"\n";
// 	std::cout<<"-----------------------------------------------------------------Name: "<<name_ <<"\n";
	result->SetName(name_);
	result->SetTitle(title_);
	return result;
}

void TH1Feff::saveResults(TDirectory* MainDirectory)
{
// 	MainDirectory->mkdir(name_);
// 	std::cout<<"name: "<<name_<<std::endl;
// 	TDirectory *dir = (TDirectory*)MainDirectory->Get(name_);
// 	dir->cd();
	MainDirectory->cd();
	TGraphAsymmErrors* result = GetEfficiency();
	result->SetName(RefTH1F_->GetName());
	result->SetTitle(RefTH1F_->GetTitle());
	result->Write();
	TString tempName = RefTH1F_->GetName();
	tempName+="_SanityCheck";
	MainDirectory->mkdir(tempName);
	// 	std::cout<<"name: "<<name_<<std::endl;
	TDirectory *sanityDir = (TDirectory*)MainDirectory->Get(tempName);
	sanityDir->cd();
	RefTH1F_->Write();
	
}


void TH2Feff::Fill(Double_t x, Double_t y, Double_t Weight, bool passOrFail)
{
	int matched=-1;
	for(unsigned int i=0; i < weights_.size();i++)
	{
		if(std::abs(weights_[i]-Weight)/Weight<0.0001 ) matched=i;
	}
	if(matched==-1)
	{
		TH2F* tempPass = (TH2F*) RefTH2F_->Clone();
		tempPass->Sumw2();
		TH2F* tempFail = (TH2F*) RefTH2F_->Clone();
		tempFail->Sumw2();
		TH2FPass_.push_back(tempPass );
		TH2FFail_.push_back(tempFail );
		
		if(passOrFail)	TH2FPass_[weights_.size()]->Fill(x,y);
		else TH2FFail_[weights_.size()]->Fill(x,y);
		weights_.push_back(Weight);
// 		std::cout<<"Weight: "<<Weight<<" added"<<std::endl;
	}
	else
	{
		if(passOrFail) TH2FPass_[matched]->Fill(x,y);
		else TH2FFail_[matched]->Fill(x,y);
	}
}
std::vector<TGraphAsymmErrors*> TH2Feff::GetEfficiency()
{ 
	const Int_t nBinsY = RefTH2F_->GetNbinsY();
	std::cout<<"Number of binsY: "<<nBinsY<<std::endl;
	std::vector<std::vector<TH1F*> > th1PassVec, th1FailVec;
	std::vector<TList*> myLists;
	// reference sum th2f
	TH2F* sumTH2ftemp = (TH2F*) RefTH2F_->Clone();
	sumTH2ftemp->Sumw2();

	for(unsigned int i=0; i < TH2FPass_.size();i++)
	{
		RefTH2F_->Add(TH2FPass_[i],weights_[i]);
		sumTH2ftemp->Add(TH2FPass_[i],weights_[i]);
		sumTH2ftemp->Add(TH2FFail_[i],weights_[i]);
	}
	RefTH2F_->Divide(RefTH2F_,sumTH2ftemp,1,1,"B");
	for(int i=0; i<nBinsY;i++)
	{
		myLists.push_back(new TList());
		TString temp1 ( Form ("%d", i));
		temp1= (TString)name_+"Bin"+temp1;
		TString temp2 (Form ("_%f.0-%f.0",ybins_[i],ybins_[i+1]));
		temp2= (TString)title_+temp2;
		std::vector<TH1F*> tt;
		th1PassVec.push_back(tt);
		th1FailVec.push_back(tt);
	for(unsigned int ii=0; ii<weights_.size();ii++)
	{
		TString temp3 ( Form ("%d", ii));
		temp1= temp1+"_"+temp3;
		temp3=temp1+"pass";
		th1PassVec[i].push_back(new TH1F(temp3,temp2,nbinsx_, xbins_));
		temp3=temp1+"fail";
		th1FailVec[i].push_back(new TH1F(temp3,temp2,nbinsx_, xbins_));
		for(int iii=0; iii<nbinsx_+1;iii++)
		{
			th1PassVec[i][ii]->SetBinContent(iii,TH2FPass_[ii]->GetBinContent(iii,i+1) );
// 			std::cout<<"P:BinContent["<<i<<"]["<<ii<<"]["<<iii<<"]: "<<TH2FPass_[ii]->GetBinContent(iii,i+1)<<" +- "<<TH2FPass_[ii]->GetBinError(iii,i+1)<<std::endl;
			th1PassVec[i][ii]->SetBinError(iii,TH2FPass_[ii]->GetBinError(iii,i+1) );
			th1FailVec[i][ii]->SetBinContent(iii,TH2FFail_[ii]->GetBinContent(iii,i+1) );
// 			std::cout<<"F:BinContent["<<i<<"]["<<ii<<"]["<<iii<<"]: "<<TH2FFail_[ii]->GetBinContent(iii,i)<<" +- "<<TH2FFail_[ii]->GetBinError(iii,i+1)<<std::endl;
			th1FailVec[i][ii]->SetBinError(iii,TH2FFail_[ii]->GetBinError(iii,i+1) );
		}
		TH1F *sum = (TH1F*)th1FailVec[i][ii]->Clone();
// 		sum->SetTitle()
		sum->Add(th1PassVec[i][ii]);
		TEfficiency* myEff = new TEfficiency(*th1PassVec[i][ii],*sum);
		// 		myEff->SetWeight(weights_[i]);
		myLists[i]->Add(myEff);
	}
	}
	const Int_t size=weights_.size();
	Double_t weightArray[size];
	for(int i=0; i<size;i++)weightArray[i]=weights_[i];
	std::vector<TGraphAsymmErrors*> result; //= TEfficiency::Combine ((TCollection*)&*myList,(Option_t*)"kFCP",(Int_t)weights_.size(),weightArray);
	for(int i=0; i<nBinsY;i++)
	{
		result.push_back(TEfficiency::Combine ((TCollection*)&*myLists[i],(Option_t*)"kBUniform",(Int_t)weights_.size(),weightArray) );
	}
	
	return result;
}

void TH2Feff::saveResults(TDirectory* MainDirectory)
{
	MainDirectory->mkdir(name_);
// 	std::cout<<"name: "<<name_<<std::endl;
	TDirectory *dir = (TDirectory*)MainDirectory->Get(name_);
	dir->cd();
	RefTH2F_->SetName(name_);
	RefTH2F_->Write();
	std::vector<TGraphAsymmErrors*> result = GetEfficiency();
	for(unsigned int i=0; i<result.size();i++) 
	{
		TString temp2 (Form ("_%d-%d",(int)ybins_[i],(int)ybins_[i+1]));
		temp2= (TString)title_+temp2;
		TString temp3 ( Form ("%d", i));
		temp3= (TString)name_+temp3;
		result[i]->SetName(temp3);
		result[i]->SetTitle(temp2);
		result[i]->Write();
	}
	dir->mkdir("SanityCheck");
	// 	std::cout<<"name: "<<name_<<std::endl;
	TDirectory *sanityDir = (TDirectory*)dir->Get("SanityCheck");
	sanityDir->cd();
	RefTH2F_->Write();
}


SearchBinEventCount::SearchBinEventCount(const char* name)
{
	fullTH1F_ = new 	TH1F(name, name, bins_.size(),0,bins_.size()+1);
	fullTH1F_->Sumw2();
	name_=name;
/*	splitAfter_=18;
	unsigned int plotsNumber= bins_.size()/splitAfter_;
	// 	std::cout<<"Efficiency::Efficiency plotsNumber="<<plotsNumber<<" number of bins: "<<bins_.size()<<std::endl;
	if(plotsNumber * splitAfter_<bins_.size() )
	{
		
		plotsNumber++;
		for(unsigned int i=0; i < plotsNumber;i++)
		{
			
			TString temp2 (Form ("_%d",(int)i+1));
			TString temp1 = name;
			temp1+=temp2;
			temp2 = name + temp2;
			const char* name1=temp1;
			const char* title1=temp2;
			
			if(i+1==plotsNumber)
			{
				// 				std::cout<<"titlelast["<<i<<"]: "<<temp1<<std::endl;
				unsigned int tempBins = bins_.size() - plotsNumber * splitAfter_;
				splitTH1F_.push_back( new TH1F (name1,title1,tempBins,0,tempBins+1) );
				splitTH1F_[i]->Sumw2();
				continue;
			}
			// 			std::cout<<"title["<<i<<"]: "<<temp1<<std::endl;
			splitTH1F_.push_back( new TH1F (name1,title1,splitAfter_,0,splitAfter_+1) );
			splitTH1F_[i]->Sumw2();
		}
	}
	else
	{
		for(unsigned int i=0; i < plotsNumber;i++)
		{
			
			TString temp2 (Form ("_%d",(int)i+1));
			TString temp1 = name;
			temp1+=temp2;

			const char* name1=temp1;
			TH1F* tempeff2 = new  TH1F (name1,name1,splitAfter_,0,splitAfter_+1);
			splitTH1F_.push_back( tempeff2 );
			splitTH1F_[i]->Sumw2();
		}
	}
*/}


void SearchBinEventCount::Fill(double HT, double MHT, int NJets, int BTags, double Weight)
{
	double bin = GetBinNumber(HT,MHT,NJets,BTags);
	
	if(bin<bins_.size()+2) 
	{
		fullTH1F_->Fill(bin-0.01, Weight);
	/*	unsigned int splitHist=0;
		// 	std::cout<<"bin before split: "<<bin<<std::endl;
		for(int ii=0;bin>splitAfter_;ii++)
		{
			splitHist++;
			bin = bin-splitAfter_;
		}
		// 		if(splitHist==3)std::cout<<"BinForSplit: "<<bin<<" with splitHistNumber "<<splitHist<<" and TH1FSearchBinsSplit_.size(): "<<TH1FSearchBinsSplit_.size()<<std::endl;
		
		splitTH1F_[splitHist]->Fill(bin-0.1, Weight);
	*/}
}
void SearchBinEventCount::saveResults(TDirectory* MainDirectory)
{
	MainDirectory->mkdir(name_);
	// 	std::cout<<"name: "<<name_<<std::endl;
	TDirectory *dir = (TDirectory*)MainDirectory->Get(name_);
	dir->cd();
	fullTH1F_->Write();
/*	for(unsigned int i=0; i<splitTH1F_.size();i++) 
	{
		TString temp2 (Form ("_%d",(int)i+1));
		TString temp1 = name_;
		temp1+=temp2;
		temp2 = name_ + temp2;
		const char* name1=temp1;
		const char* title1=temp2;
		splitTH1F_[i]->SetTitle(title1);
		splitTH1F_[i]->SetName(name1);
		splitTH1F_[i]->Write();
	}
*/}