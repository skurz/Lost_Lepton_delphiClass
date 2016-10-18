#!/bin/bash

echo "Running TTJets_HT-600to800"
root -l -q "run_ApplyBaseline_script.C+(\"TTJets_HT-600to800\", \"Spring16.TTJets_HT-600to800*.root\")"
wait

echo "Running TTJets_HT-800to1200"
root -l -q "run_ApplyBaseline_script.C+(\"TTJets_HT-800to1200\", \"Spring16.TTJets_HT-800to1200*.root\")"
wait

echo "Running TTJets_HT-1200to2500"
root -l -q "run_ApplyBaseline_script.C+(\"TTJets_HT-1200to2500\", \"Spring16.TTJets_HT-1200to2500*.root\")"
wait

echo "Running TTJets_HT-2500toInf"
root -l -q "run_ApplyBaseline_script.C+(\"TTJets_HT-2500toInf\", \"Spring16.TTJets_HT-2500toInf*.root\")"
wait
