#!/bin/bash

echo "Running TTJets_HT-600to800"
root -l -q "run_ApplyBaseline_script.C+(\"TTJets_HT-600to800\", \"/eos/uscms/store/user/lpcsusyhad/SusyRA2Analysis2015/Run2ProductionV9/Spring16.TTJets_HT-600to800*.root\")"
wait

echo "Running TTJets_HT-800to1200"
root -l -q "run_ApplyBaseline_script.C+(\"TTJets_HT-800to1200\", \"/eos/uscms/store/user/lpcsusyhad/SusyRA2Analysis2015/Run2ProductionV9/Spring16.TTJets_HT-800to1200*.root\")"
wait

echo "Running TTJets_HT-1200to2500"
root -l -q "run_ApplyBaseline_script.C+(\"TTJets_HT-1200to2500\", \"/eos/uscms/store/user/lpcsusyhad/SusyRA2Analysis2015/Run2ProductionV9/Spring16.TTJets_HT-1200to2500*.root\")"
wait

echo "Running TTJets_HT-2500toInf"
root -l -q "run_ApplyBaseline_script.C+(\"TTJets_HT-2500toInf\", \"/eos/uscms/store/user/lpcsusyhad/SusyRA2Analysis2015/Run2ProductionV9/Spring16.TTJets_HT-2500toInf*.root\")"
wait
