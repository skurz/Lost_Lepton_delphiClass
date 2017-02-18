#!/bin/bash

echo "Removing temporary folders"
rm -r /nfs/dust/cms/user/kurzsimo/.proof/*
rm -r /nfs/dust/cms/user/kurzsimo/tmp/*
sleep 5

echo "Running TTJets_SingleLeptFromT"
root -l -q "run_ApplyBaseline_script.C+(\"TTJets_SingleLeptFromT\", \"Summer16.TTJets_SingleLeptFromT_*.root\")"
wait
sleep 5
rm -r /nfs/dust/cms/user/kurzsimo/.proof/*
rm -r /nfs/dust/cms/user/kurzsimo/tmp/*
sleep 5

echo "Running TTJets_SingleLeptFromTbar"
root -l -q "run_ApplyBaseline_script.C+(\"TTJets_SingleLeptFromTbar\", \"Summer16.TTJets_SingleLeptFromTbar_*.root\")"
wait
sleep 5
rm -r /nfs/dust/cms/user/kurzsimo/.proof/*
rm -r /nfs/dust/cms/user/kurzsimo/tmp/*
sleep 5

echo "Running TTJets_DiLept"
root -l -q "run_ApplyBaseline_script.C+(\"TTJets_DiLept\", \"Summer16.TTJets_DiLept*.root\")"
wait
sleep 5
rm -r /nfs/dust/cms/user/kurzsimo/.proof/*
rm -r /nfs/dust/cms/user/kurzsimo/tmp/*
sleep 5
