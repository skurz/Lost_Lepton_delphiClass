#!/bin/bash

#echo "Running ST_s-channel"
#root -l -q "run_ApplyBaseline_script.C+(\"ST_s-channel\", \"Spring16.ST_s-channel*.root\")"
#wait

#echo "Running ST_t-channel_antitop"
#root -l -q "run_ApplyBaseline_script.C+(\"ST_t-channel_antitop\", \"Spring16.ST_t-channel_antitop*.root\")"
#wait

echo "Running ST_t-channel_top"
root -l -q "run_ApplyBaseline_script.C+(\"ST_t-channel_top\", \"Spring16.ST_t-channel_top*.root\")"
wait

#echo "Running ST_tW_antitop"
#root -l -q "run_ApplyBaseline_script.C+(\"ST_tW_antitop\", \"Spring16.ST_tW_antitop*.root\")"
#wait

#echo "Running ST_tW_top"
#root -l -q "run_ApplyBaseline_script.C+(\"ST_tW_top\", \"Spring16.ST_tW_top*.root\")"
#wait
