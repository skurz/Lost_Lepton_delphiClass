#!/bin/bash

echo "Running WJetsToLNu_HT-100to200"
root -l -q "run_ApplyBaseline_script.C+(\"WJetsToLNu_HT-100to200\", \"Summer16.WJetsToLNu_HT-100To200*.root\")"
wait

echo "Running WJetsToLNu_HT-200to400"
root -l -q "run_ApplyBaseline_script.C+(\"WJetsToLNu_HT-200to400\", \"Summer16.WJetsToLNu_HT-200To400*.root\")"
wait

echo "Running WJetsToLNu_HT-400to600"
root -l -q "run_ApplyBaseline_script.C+(\"WJetsToLNu_HT-400to600\", \"Summer16.WJetsToLNu_HT-400To600*.root\")"
wait

echo "Running WJetsToLNu_HT-600to800"
root -l -q "run_ApplyBaseline_script.C+(\"WJetsToLNu_HT-600to800\", \"Summer16.WJetsToLNu_HT-600To800*.root\")"
wait

echo "Running WJetsToLNu_HT-800to1200"
root -l -q "run_ApplyBaseline_script.C+(\"WJetsToLNu_HT-800to1200\", \"Summer16.WJetsToLNu_HT-800To1200*.root\")"
wait

echo "Running WJetsToLNu_HT-1200to2500"
root -l -q "run_ApplyBaseline_script.C+(\"WJetsToLNu_HT-1200to2500\", \"Summer16.WJetsToLNu_HT-1200To2500*.root\")"
wait

echo "Running WJetsToLNu_HT-2500toInf"
root -l -q "run_ApplyBaseline_script.C+(\"WJetsToLNu_HT-2500toInf\", \"Summer16.WJetsToLNu_HT-2500ToInf*.root\")"
wait
