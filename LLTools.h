#include "TVector2.h"
#include <cmath>

static double deltaR(double eta1, double phi1, double eta2, double phi2)
{
  double deta = eta1-eta2;
  double dphi = TVector2::Phi_mpi_pi(phi1-phi2);
  return sqrt(deta * deta + dphi *dphi); 
}

static double MTWCalculator(double metPt,double  metPhi,double  lepPt,double  lepPhi)
{
  double deltaPhi =TVector2::Phi_mpi_pi(lepPhi-metPhi);
  return sqrt(2*lepPt*metPt*(1-cos(deltaPhi)) );
}

static double PTWCalculator(double metPt,double  metPhi,double  lepPt,double  lepPhi)
{
  TVector2 Wvec(metPt*cos(metPhi)+lepPt*cos(lepPhi), metPt*sin(metPhi)+lepPt*sin(lepPhi));
  return Wvec.Mod();
}
