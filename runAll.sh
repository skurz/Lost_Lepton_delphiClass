#!/bin/bash
# My first script

echo "->Removing old files"
rm Efficiencies/*.pdf&
#rm *.root&
rm ttbar/*.root&
rm wpj/*.root&
rm singlet/*.root&
rm rare/*.root&
rm ttbar/*.log&
rm wpj/*.log&
rm singlet/*.log&
rm rare/*.log&
wait
echo "->Done"

echo "->Running Expectation: ttbar/wpj/singlet/rare - output written to log files!"
root -l ExpecMaker.C+ # Needed to link libraries
wait
root -l -b -q ttbar/MakeExpectation.C++ > ttbar/expec.log&
root -l -b -q wpj/MakeExpectation.C++ > wpj/expec.log&
root -l -b -q singlet/MakeExpectation.C++ > singlet/expec.log&
root -l -b -q rare/MakeExpectation.C++ > rare/expec.log&
wait
echo "->Done"

echo "->Merge files"
hadd -f Expectation.root ttbar/Expectation_*.root wpj/Expectation_*.root singlet/Expectation_*.root rare/Expectation_*.root
wait
echo "->Done"

echo "->Create efficiency maps"
root -l -b -q MakeEff.C++&
wait
echo "->Done"

echo "->Prepare Prediction.h for run on MC"
root -l Prediction.C+ # Needed to link libraries
wait
ed -s Prediction.h <<< $'/const bool runOnData/s/true/false/g\nw' &> /dev/null
ed -s Prediction.h <<< $'/const bool runOnStandardModelMC/s/false/true/g\nw' &> /dev/null
ed -s Prediction.h <<< $'/const bool runOnSignalMC/s/true/false/g\nw' &> /dev/null
wait
echo "->Done"

echo "->Running Prediction: ttbar/wpj/singlet/rare - output written to log files!"
root -l -b -q ttbar/MakePrediction.C++ > ttbar/pred.log&
root -l -b -q wpj/MakePrediction.C++ > wpj/pred.log&
root -l -b -q singlet/MakePrediction.C++ > singlet/pred.log&
root -l -b -q rare/MakePrediction.C++ > rare/pred.log&
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
root -l Prediction.C+ # Needed to link libraries
wait
root -l -b -q MakePrediction_Data.C++
wait
echo "->Done"

echo "->Set back to standard values"
ed -s Prediction.h <<< $'/const bool runOnData/s/true/false/g\nw' &> /dev/null
ed -s Prediction.h <<< $'/const bool runOnStandardModelMC/s/false/true/g\nw' &> /dev/null
wait
echo "->Done"

echo "->Generate output: LLPrediction.root"
root -l -b -q ResultPlot.C++
wait
echo "->Done"