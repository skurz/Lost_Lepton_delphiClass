#!/bin/bash

echo "Running T1tbtt"
root -l -q "SignalContamination.C+(\"Prediction_Scan_T1tbtt.root\", \"LLContamination_T1tbtt.root\")"
wait

echo "Running T1tbtb"
root -l -q "SignalContamination.C+(\"Prediction_Scan_T1tbtb.root\", \"LLContamination_T1tbtb.root\")"
wait

echo "Running T1tbbb"
root -l -q "SignalContamination.C+(\"Prediction_Scan_T1tbbb.root\", \"LLContamination_T1tbbb.root\")"
wait

echo "Running T1bbtt"
root -l -q "SignalContamination.C+(\"Prediction_Scan_T1bbtt.root\", \"LLContamination_T1bbtt.root\")"
wait


echo "Running T1tbtt_genMHT"
root -l -q "SignalContamination.C+(\"Prediction_Scan_genMHT_T1tbtt.root\", \"LLContamination_genMHT_T1tbtt.root\")"
wait

echo "Running T1tbtb_genMHT"
root -l -q "SignalContamination.C+(\"Prediction_Scan_genMHT_T1tbtb.root\", \"LLContamination_genMHT_T1tbtb.root\")"
wait

echo "Running T1tbbb_genMHT"
root -l -q "SignalContamination.C+(\"Prediction_Scan_genMHT_T1tbbb.root\", \"LLContamination_genMHT_T1tbbb.root\")"
wait

echo "Running T1bbtt_genMHT"
root -l -q "SignalContamination.C+(\"Prediction_Scan_genMHT_T1bbtt.root\", \"LLContamination_genMHT_T1bbtt.root\")"
wait