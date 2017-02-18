#!/bin/bash

echo "Removing temporary folders"
rm -r /nfs/dust/cms/user/kurzsimo/.proof/*
rm -r /nfs/dust/cms/user/kurzsimo/tmp/*
sleep 5

echo "Running TTJets_HT-600to800"
root -l -q "run_ApplyBaseline_script.C+(\"TTJets_HT-600to800\", \"Summer16.TTJets_HT-600to800*.root\")"
wait
sleep 5
rm -r /nfs/dust/cms/user/kurzsimo/.proof/*
rm -r /nfs/dust/cms/user/kurzsimo/tmp/*
sleep 5

echo "Running TTJets_HT-800to1200"
root -l -q "run_ApplyBaseline_script.C+(\"TTJets_HT-800to1200\", \"Summer16.TTJets_HT-800to1200*.root\")"
wait
sleep 5
rm -r /nfs/dust/cms/user/kurzsimo/.proof/*
rm -r /nfs/dust/cms/user/kurzsimo/tmp/*
sleep 5

echo "Running TTJets_HT-1200to2500"
root -l -q "run_ApplyBaseline_script.C+(\"TTJets_HT-1200to2500\", \"Summer16.TTJets_HT-1200to2500*.root\")"
wait
sleep 5
rm -r /nfs/dust/cms/user/kurzsimo/.proof/*
rm -r /nfs/dust/cms/user/kurzsimo/tmp/*
sleep 5

echo "Running TTJets_HT-2500toInf"
root -l -q "run_ApplyBaseline_script.C+(\"TTJets_HT-2500toInf\", \"Summer16.TTJets_HT-2500toInf*.root\")"
wait
sleep 5
rm -r /nfs/dust/cms/user/kurzsimo/.proof/*
rm -r /nfs/dust/cms/user/kurzsimo/tmp/*
sleep 5
