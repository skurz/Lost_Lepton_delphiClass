#!/bin/bash

root -l -b -q "Plot_closure.C(\"baseline\", \"HT\", \"ExpVsPre\")"
wait

root -l -b -q "Plot_closure.C(\"baseline\", \"MHT\", \"ExpVsPre\")"
wait

root -l -b -q "Plot_closure.C(\"baseline\", \"NJets\", \"ExpVsPre\")"
wait

root -l -b -q "Plot_closure.C(\"baseline\", \"NBtag\", \"ExpVsPre\")"
wait


root -l -b -q "Plot_closure.C(\"baseline\", \"HT\", \"ExpVsCS\")"
wait

root -l -b -q "Plot_closure.C(\"baseline\", \"MHT\", \"ExpVsCS\")"
wait

root -l -b -q "Plot_closure.C(\"baseline\", \"NJets\", \"ExpVsCS\")"
wait

root -l -b -q "Plot_closure.C(\"baseline\", \"NBtag\", \"ExpVsCS\")"
wait

root -l -b -q "Plot_closure.C(\"baseline\", \"search\", \"ExpVsCS\")"
wait