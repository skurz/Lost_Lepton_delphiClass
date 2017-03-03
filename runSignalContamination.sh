#!/bin/bash

echo "Running T2tt"
root -l -q "SignalContamination.C+(\"Prediction_Scan_T2tt.root\", \"LLContamination_T2tt.root\")"
wait

echo "Running T1tttt"
root -l -q "SignalContamination.C+(\"Prediction_Scan_T1tttt.root\", \"LLContamination_T1tttt.root\")"
wait

echo "Running T5qqqqVV"
root -l -q "SignalContamination.C+(\"Prediction_Scan_T5qqqqVV.root\", \"LLContamination_T5qqqqVV.root\")"
wait


echo "Running T2tt_genMHT"
root -l -q "SignalContamination.C+(\"Prediction_Scan_genMHT_T2tt.root\", \"LLContamination_genMHT_T2tt.root\")"
wait

echo "Running T1tttt_genMHT"
root -l -q "SignalContamination.C+(\"Prediction_Scan_genMHT_T1tttt.root\", \"LLContamination_genMHT_T1tttt.root\")"
wait

echo "Running T5qqqqVV_genMHT"
root -l -q "SignalContamination.C+(\"Prediction_Scan_genMHT_T5qqqqVV.root\", \"LLContamination_genMHT_T5qqqqVV.root\")"
wait
