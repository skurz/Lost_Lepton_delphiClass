#!/bin/bash

#echo "Running TTJets_SingleLeptFromT"
#root -l -q "run_topPt_script.C+(\"TTJets_SingleLeptFromT_topPt\", \"Spring16.TTJets_SingleLeptFromT_*.root\")"
#wait

echo "Running TTJets_SingleLeptFromTbar"
root -l -q "run_topPt_script.C+(\"TTJets_SingleLeptFromTbar_topPt\", \"Spring16.TTJets_SingleLeptFromTbar_*.root\")"
wait

echo "Running TTJets_DiLept"
root -l -q "run_topPt_script.C+(\"TTJets_DiLept_topPt\", \"Spring16.TTJets_DiLept*.root\")"
wait
