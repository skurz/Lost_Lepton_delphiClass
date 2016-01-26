#!/bin/bash
# My first script

echo "->Removing old files"
rm ttbar/Prediction_*.root &> /dev/null &
rm wpj/Prediction_*.root &> /dev/null &
rm singlet/Prediction_*.root &> /dev/null &
rm rare/Prediction_*.root &> /dev/null &
rm ttbar/pred.log &> /dev/null &
rm wpj/pred.log &> /dev/null &
rm singlet/pred.log &> /dev/null &
rm rare/pred.log &> /dev/null &
wait
echo "->Done"

echo "->Prepare Prediction.h for run on MC"
ed -s Prediction.h <<< $'/const bool runOnData/s/true/false/g\nw' &> /dev/null
ed -s Prediction.h <<< $'/const bool runOnStandardModelMC/s/false/true/g\nw' &> /dev/null
ed -s Prediction.h <<< $'/const bool runOnSignalMC/s/true/false/g\nw' &> /dev/null
wait
echo "->Done"

echo "->Running Prediction: ttbar/wpj/singlet/rare - output written to log files!"
root -l -b -q MakePredictionLibraries.C+ # Needed to link libraries
wait
root -l -b -q ttbar/MakePrediction.C+ > ttbar/pred.log&
root -l -b -q wpj/MakePrediction.C+ > wpj/pred.log&
root -l -b -q singlet/MakePrediction.C+ > singlet/pred.log&
root -l -b -q rare/MakePrediction.C+ > rare/pred.log&
wait
echo "->Done"

echo "->Merge files"
hadd -f Prediction.root ttbar/Prediction_*.root wpj/Prediction_*.root singlet/Prediction_*.root rare/Prediction_*.root
wait
echo "->Done"

echo "->Prepare Prediction.h for run on Data"
ed -s Prediction.h <<< $'/const bool runOnData/s/false/true/g\nw' &> /dev/null
ed -s Prediction.h <<< $'/const bool runOnStandardModelMC/s/true/false/g\nw' &> /dev/null
wait
echo "->Done"

echo "->Running Prediction: data"
root -l -b -q MakePrediction_Data.C+
wait
echo "->Done"

echo "->Set back to standard values"
ed -s Prediction.h <<< $'/const bool runOnData/s/true/false/g\nw' &> /dev/null
ed -s Prediction.h <<< $'/const bool runOnStandardModelMC/s/false/true/g\nw' &> /dev/null
wait
echo "->Done"

echo "->Generate output: LLPrediction.root"
root -l -b -q ResultPlot.C+
wait
echo "->Done"