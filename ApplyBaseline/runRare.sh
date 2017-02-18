#!/bin/bash

echo "Removing temporary folders"
rm -r /nfs/dust/cms/user/kurzsimo/.proof/*
rm -r /nfs/dust/cms/user/kurzsimo/tmp/*
sleep 5

echo "Running WWTo1L1Nu2Q"
root -l -q "run_ApplyBaseline_script.C+(\"WWTo1L1Nu2Q\", \"Summer16.WWTo1L1Nu2Q_*.root\")"
wait
sleep 5
rm -r /nfs/dust/cms/user/kurzsimo/.proof/*
rm -r /nfs/dust/cms/user/kurzsimo/tmp/*
sleep 5

echo "Running WWTo2L2Nu"
root -l -q "run_ApplyBaseline_script.C+(\"WWTo2L2Nu\", \"Summer16.WWTo2L2Nu*.root\")"
wait
sleep 5
rm -r /nfs/dust/cms/user/kurzsimo/.proof/*
rm -r /nfs/dust/cms/user/kurzsimo/tmp/*
sleep 5

echo "Running WZTo1L1Nu2Q"
root -l -q "run_ApplyBaseline_script.C+(\"WZTo1L1Nu2Q\", \"Summer16.WZTo1L1Nu2Q*.root\")"
wait
sleep 5
rm -r /nfs/dust/cms/user/kurzsimo/.proof/*
rm -r /nfs/dust/cms/user/kurzsimo/tmp/*
sleep 5

echo "Running WZTo1L3Nu"
root -l -q "run_ApplyBaseline_script.C+(\"WZTo1L3Nu\", \"Summer16.WZTo1L3Nu*.root\")"
wait
sleep 5
rm -r /nfs/dust/cms/user/kurzsimo/.proof/*
rm -r /nfs/dust/cms/user/kurzsimo/tmp/*
sleep 5

echo "Running ZZTo2L2Q"
root -l -q "run_ApplyBaseline_script.C+(\"ZZTo2L2Q\", \"Summer16.ZZTo2L2Q*.root\")"
wait
sleep 5
rm -r /nfs/dust/cms/user/kurzsimo/.proof/*
rm -r /nfs/dust/cms/user/kurzsimo/tmp/*
sleep 5

##echo "Running ZZTo2Q2Nu"
##root -l -q "run_ApplyBaseline_script.C+(\"ZZTo2Q2Nu\", \"Summer16.ZZTo2Q2Nu*.root\")"
##wait
##sleep 5
##rm -r /nfs/dust/cms/user/kurzsimo/.proof/*
##rm -r /nfs/dust/cms/user/kurzsimo/tmp/*
##sleep 5

echo "Running WWZ"
root -l -q "run_ApplyBaseline_script.C+(\"WWZ\", \"Summer16.WWZ*.root\")"
wait
sleep 5
rm -r /nfs/dust/cms/user/kurzsimo/.proof/*
rm -r /nfs/dust/cms/user/kurzsimo/tmp/*
sleep 5

echo "Running WZZ"
root -l -q "run_ApplyBaseline_script.C+(\"WZZ\", \"Summer16.WZZ*.root\")"
wait
sleep 5
rm -r /nfs/dust/cms/user/kurzsimo/.proof/*
rm -r /nfs/dust/cms/user/kurzsimo/tmp/*
sleep 5

echo "Running ZZZ"
root -l -q "run_ApplyBaseline_script.C+(\"ZZZ\", \"Summer16.ZZZ*.root\")"
wait
sleep 5
rm -r /nfs/dust/cms/user/kurzsimo/.proof/*
rm -r /nfs/dust/cms/user/kurzsimo/tmp/*
sleep 5

echo "Running TTTT"
root -l -q "run_ApplyBaseline_script.C+(\"TTTT\", \"Summer16.TTTT*.root\")"
wait
sleep 5
rm -r /nfs/dust/cms/user/kurzsimo/.proof/*
rm -r /nfs/dust/cms/user/kurzsimo/tmp/*
sleep 5

echo "Running TTGJets"
root -l -q "run_ApplyBaseline_script.C+(\"TTGJets\", \"Summer16.TTGJets*.root\")"
wait
sleep 5
rm -r /nfs/dust/cms/user/kurzsimo/.proof/*
rm -r /nfs/dust/cms/user/kurzsimo/tmp/*
sleep 5

echo "Running TTWJetsToLNu"
root -l -q "run_ApplyBaseline_script.C+(\"TTWJetsToLNu\", \"Summer16.TTWJetsToLNu*.root\")"
wait
sleep 5
rm -r /nfs/dust/cms/user/kurzsimo/.proof/*
rm -r /nfs/dust/cms/user/kurzsimo/tmp/*
sleep 5

echo "Running TTWJetsToQQ"
root -l -q "run_ApplyBaseline_script.C+(\"TTWJetsToQQ\", \"Summer16.TTWJetsToQQ*.root\")"
wait
sleep 5
rm -r /nfs/dust/cms/user/kurzsimo/.proof/*
rm -r /nfs/dust/cms/user/kurzsimo/tmp/*
sleep 5

echo "Running TTZToLLNuNu"
root -l -q "run_ApplyBaseline_script.C+(\"TTZToLLNuNu\", \"Summer16.TTZToLLNuNu*.root\")"
wait
sleep 5
rm -r /nfs/dust/cms/user/kurzsimo/.proof/*
rm -r /nfs/dust/cms/user/kurzsimo/tmp/*
sleep 5

echo "Running TTZToQQ"
root -l -q "run_ApplyBaseline_script.C+(\"TTZToQQ\", \"Summer16.TTZToQQ*.root\")"
wait
sleep 5
rm -r /nfs/dust/cms/user/kurzsimo/.proof/*
rm -r /nfs/dust/cms/user/kurzsimo/tmp/*
sleep 5
