#include "TVector2.h"
#include <iostream>
#include <vector>
#include <utility>

class Bin
{
public:
	Bin(){}
	Bin(double HTmin, double HTmax, double MHTmin, double MHTmax, int NJetsmin, int NJetsmax, int BTagsmin, int BTagsmax)
	{
		HTmin_=HTmin;
		HTmax_=HTmax;
		MHTmin_=MHTmin;
		MHTmax_=MHTmax;
		NJetsmin_=NJetsmin;
		NJetsmax_=NJetsmax;
		BTagsmin_=BTagsmin;
		BTagsmax_=BTagsmax;
	}
	double HTmin_, HTmax_, MHTmin_, MHTmax_;
	int NJetsmin_, NJetsmax_, BTagsmin_, BTagsmax_;
	~Bin(){}
private:
};

class SearchBins
{
public:
  SearchBins() : SearchBins(false) {}
  SearchBins(bool useQCDbinning);
  unsigned int GetBinNumber(double HT, double MHT, int NJets, int BTags);
  void PrintUsed();
  Bin* GetSearchBin(int i);
  
  ~SearchBins(){}
protected:
  std::vector<Bin> bins_;
  std::vector<int> usedBin_;

  std::vector<std::pair<double, double>> HT_bins;
  std::vector<std::pair<double, double>> MHT_bins;
  std::vector<std::pair<int, int>> NJets_bins;
  std::vector<std::pair<int, int>> BTags_bins_NJets3Inf;
  std::vector<std::pair<int, int>> BTags_bins_NJets2;

};


SearchBins::SearchBins(bool useQCDbinning)
{
	if(!useQCDbinning){
		// 10 HTMHT bins
		// [HT range]
		HT_bins.push_back(std::make_pair(250, 500));
		HT_bins.push_back(std::make_pair(500, 1000));
		HT_bins.push_back(std::make_pair(1000, 99999));
		HT_bins.push_back(std::make_pair(350, 500));
		HT_bins.push_back(std::make_pair(500, 1000));
		HT_bins.push_back(std::make_pair(1000, 99999));
		HT_bins.push_back(std::make_pair(500, 1000));
		HT_bins.push_back(std::make_pair(1000, 99999));
		HT_bins.push_back(std::make_pair(750, 1500));
		HT_bins.push_back(std::make_pair(1500, 99999));

		// [MHT range]
		MHT_bins.push_back(std::make_pair(250, 350));
		MHT_bins.push_back(std::make_pair(250, 350));
		MHT_bins.push_back(std::make_pair(250, 350));
		MHT_bins.push_back(std::make_pair(350, 500));
		MHT_bins.push_back(std::make_pair(350, 500));
		MHT_bins.push_back(std::make_pair(350, 500));
		MHT_bins.push_back(std::make_pair(500, 750));
		MHT_bins.push_back(std::make_pair(500, 750));
		MHT_bins.push_back(std::make_pair(750, 99999));
		MHT_bins.push_back(std::make_pair(750, 99999));

		// NJets
		NJets_bins.push_back(std::make_pair(2, 2));
		NJets_bins.push_back(std::make_pair(3, 4));
		NJets_bins.push_back(std::make_pair(5, 6));
		NJets_bins.push_back(std::make_pair(7, 8));
		NJets_bins.push_back(std::make_pair(9, 999));

		// BTags (different for NJets==2)
		BTags_bins_NJets3Inf.push_back(std::make_pair(0, 0));
		BTags_bins_NJets3Inf.push_back(std::make_pair(1, 1));
		BTags_bins_NJets3Inf.push_back(std::make_pair(2, 2));
		BTags_bins_NJets3Inf.push_back(std::make_pair(3, 99));

		BTags_bins_NJets2.push_back(std::make_pair(0, 0));
		BTags_bins_NJets2.push_back(std::make_pair(1, 1));
		BTags_bins_NJets2.push_back(std::make_pair(2, 99));
	}else{
		// 10 HTMHT bins
		// [HT range]
		HT_bins.push_back(std::make_pair(250, 500));
		HT_bins.push_back(std::make_pair(500, 1000));
		HT_bins.push_back(std::make_pair(1000, 99999));
		HT_bins.push_back(std::make_pair(350, 500));
		HT_bins.push_back(std::make_pair(500, 1000));
		HT_bins.push_back(std::make_pair(1000, 99999));
		HT_bins.push_back(std::make_pair(500, 1000));
		HT_bins.push_back(std::make_pair(1000, 99999));
		HT_bins.push_back(std::make_pair(750, 1500));
		HT_bins.push_back(std::make_pair(1500, 99999));

		// [MHT range]
		MHT_bins.push_back(std::make_pair(250, 350));
		MHT_bins.push_back(std::make_pair(250, 350));
		MHT_bins.push_back(std::make_pair(250, 350));
		MHT_bins.push_back(std::make_pair(350, 500));
		MHT_bins.push_back(std::make_pair(350, 500));
		MHT_bins.push_back(std::make_pair(350, 500));
		MHT_bins.push_back(std::make_pair(500, 750));
		MHT_bins.push_back(std::make_pair(500, 750));
		MHT_bins.push_back(std::make_pair(750, 99999));
		MHT_bins.push_back(std::make_pair(750, 99999));

		// NJets
		NJets_bins.push_back(std::make_pair(2, 2));
		NJets_bins.push_back(std::make_pair(3, 4));
		NJets_bins.push_back(std::make_pair(5, 6));
		NJets_bins.push_back(std::make_pair(7, 8));
		NJets_bins.push_back(std::make_pair(9, 999));

		// BTags (different for NJets==2)
		BTags_bins_NJets3Inf.push_back(std::make_pair(0, 0));
		BTags_bins_NJets3Inf.push_back(std::make_pair(1, 1));
		BTags_bins_NJets3Inf.push_back(std::make_pair(2, 2));
		BTags_bins_NJets3Inf.push_back(std::make_pair(3, 99));

		BTags_bins_NJets2.push_back(std::make_pair(0, 0));
		BTags_bins_NJets2.push_back(std::make_pair(1, 1));
		BTags_bins_NJets2.push_back(std::make_pair(2, 99));

	}

	if(HT_bins.size() != MHT_bins.size())	std::cout << "SearchBins.h: No valid definition of HTMHT bins!" << std::endl;

	for(unsigned i_NJets = 0; i_NJets < NJets_bins.size(); ++i_NJets){
		// distinguish between BTag multiplicities
		if(i_NJets == 0){
			for(unsigned i_bTags = 0; i_bTags < BTags_bins_NJets2.size(); ++i_bTags){
				for(unsigned i_HTMHT = 0; i_HTMHT < HT_bins.size(); ++i_HTMHT){
					bins_.push_back(Bin(HT_bins[i_HTMHT].first, HT_bins[i_HTMHT].second,
										MHT_bins[i_HTMHT].first, MHT_bins[i_HTMHT].second,
										NJets_bins[i_NJets].first, NJets_bins[i_NJets].second,
										BTags_bins_NJets2[i_bTags].first, BTags_bins_NJets2[i_bTags].second));
				}
			}
		}else{
			for(unsigned i_bTags = 0; i_bTags < BTags_bins_NJets3Inf.size(); ++i_bTags){
				for(unsigned i_HTMHT = 0; i_HTMHT < HT_bins.size(); ++i_HTMHT){
					bins_.push_back(Bin(HT_bins[i_HTMHT].first, HT_bins[i_HTMHT].second,
										MHT_bins[i_HTMHT].first, MHT_bins[i_HTMHT].second,
										NJets_bins[i_NJets].first, NJets_bins[i_NJets].second,
										BTags_bins_NJets3Inf[i_bTags].first, BTags_bins_NJets3Inf[i_bTags].second));
				}
			}
		}

	}

	std::cout<<"Loaded bins: "<<bins_.size()<<std::endl;
	for(unsigned int i=0; i<bins_.size();i++)
	{
		//std::cout<<"Bin["<<i<<"]: HT["<<bins_[i].HTmin_<<","<<bins_[i].HTmax_<<"] MHT["<<bins_[i].MHTmin_<<","<<bins_[i].MHTmax_<<"] NJets["<<bins_[i].NJetsmin_<<","<<bins_[i].NJetsmax_<<"] BTags["<<bins_[i].BTagsmin_<<","<<bins_[i].BTagsmax_<<"]\n";
	    usedBin_.push_back(0); 
	}
}

Bin* SearchBins::GetSearchBin(int i){
	return &(bins_.at(i));
}

unsigned int SearchBins::GetBinNumber(double HT, double MHT, int NJets, int BTags)
{
  unsigned int result =999;
  int match =-1;
  for(unsigned int i=0; i<bins_.size();i++)
  {
	  if(HT>=bins_[i].HTmin_ && 
	      HT<bins_[i].HTmax_ &&
	      MHT>=bins_[i].MHTmin_ && 
	      MHT<bins_[i].MHTmax_ &&
	      NJets+0.1> bins_[i].NJetsmin_ && 
	      NJets-0.1< bins_[i].NJetsmax_ &&
	      BTags+0.1> bins_[i].BTagsmin_ && 
	      BTags-0.1< bins_[i].BTagsmax_){
		      	result=i;
		      	match++;
		      	usedBin_[i]=usedBin_[i]+1;
	  }
  }
  if(match==-1)
  {
    std::cout<<"Error event fits in no bin! HT: "<<HT<<", MHT: "<<MHT<<", NJets: "<<NJets<<", BTags: "<<BTags<<std::endl;
  }
  if(match>0)
  {
    std::cout<<"Error event fits in more than one bin! HT: "<<HT<<", MHT: "<<MHT<<", NJets: "<<NJets<<", BTags: "<<BTags<<std::endl;
  }
  return result+1; // to not use the 0 bin but start counting at 1
}

void SearchBins::PrintUsed()
{
  int total = 0;
  for(unsigned int i=0; i< usedBin_.size();i++){
  	std::cout<<"Bin["<<i+1<<"] has been used: "<<usedBin_[i]<<std::endl;
  	total+=usedBin_[i];;
  }
  std::cout<<"Total: "<<total<<std::endl;
}
