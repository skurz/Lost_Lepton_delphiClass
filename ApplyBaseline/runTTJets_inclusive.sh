#!/bin/bash

#echo "Running TTJets_SingleLeptFromT"
#root -l -q "run_ApplyBaseline_script.C+(\"TTJets_SingleLeptFromT\", \"Spring16.TTJets_SingleLeptFromT_*.root\")"
#wait

echo "Running TTJets_SingleLeptFromTbar"
root -l -q "run_ApplyBaseline_script.C+(\"TTJets_SingleLeptFromTbar\", \"Spring16.TTJets_SingleLeptFromTbar_*.root\")"
wait

#echo "Running TTJets_DiLept"
#root -l -q "run_ApplyBaseline_script.C+(\"TTJets_DiLept\", \"Spring16.TTJets_DiLept*.root\")"
#wait
