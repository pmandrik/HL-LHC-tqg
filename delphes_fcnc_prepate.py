#! /usr/bin/python

import sys
import re
import os
from os.path import isfile, join
import argparse

## old settings
delphespath="/afs/cern.ch/user/p/pmandrik/public/analysis/TDR_tqgamma/1_delphi/CMSSW_8_0_4/src/delphes"
delphespath="/afs/cern.ch/user/p/pmandrik/public/analysis/TDR_tqgamma/1_delphi/CMSSW_8_0_4/src/delphes"

delphespath="/afs/cern.ch/user/p/pmandrik/public/analysis/TDR_tqgamma/2_delphi/delphes-3.4.2pre03"
cmsswbase="/afs/cern.ch/user/p/pmandrik/public/analysis/TDR_tqgamma/2_delphi/CMSSW_9_1_0_pre3"

delphespath="/afs/cern.ch/user/p/pmandrik/public/analysis/TDR_tqgamma/3_delphi/delphes"
cmsswbase="/afs/cern.ch/user/p/pmandrik/public/analysis/TDR_tqgamma/3_delphi/CMSSW_9_1_0_pre3/src"

## new settings
delphespath="/eos/user/p/pmandrik/lsf_delphy_samples/delphes"
cmsswbase=""

## its ku
outputpath = "/eos/user/p/pmandrik/lsf_delphy_samples/ku_results"
scriptpath = "/afs/cern.ch/work/p/pmandrik/tdr_tqgamma/delphy_samples/ku_cmd"
lhepath = "/afs/cern.ch/work/p/pmandrik/tdr_tqgamma/delphy_samples/ku_split"

## its ku for Alexey
outputpath = "/eos/user/b/baskakov/delphe/ku_results"
scriptpath = "/afs/cern.ch/work/p/pmandrik/tdr_tqgamma/delphy_samples/ku_cmd_backakov"
lhepath = "/afs/cern.ch/work/p/pmandrik/tdr_tqgamma/delphy_samples/ku_split"

## its kc
outputpath = "/eos/user/p/pmandrik/lsf_delphy_samples/kc_results_new"
scriptpath = "/afs/cern.ch/work/p/pmandrik/tdr_tqgamma/delphy_samples/kc_cmd"
lhepath = "/afs/cern.ch/work/p/pmandrik/tdr_tqgamma/delphy_samples/kc_split"

# we need a directory with prepared lhc files
inputs = [f for f in os.listdir(lhepath) if isfile(join(lhepath, f)) and f[-4:]==".lhe"]

# we know it
#nevents = [5000 for f in inputs]
nevents = [10000 for f in inputs]

# cms path
myfinalfile = open( scriptpath + "/SubmitDelphes.sh","w")
lineDelphes = ""
for i, lhefile in enumerate(inputs):
  line = ""
  cmdname ="splitCmnd"+str(i)+".cmnd"
  jobname ="submitJob"+str(i)+".sh"
  outname ="result"+str(i)+".root"

  mycmnd = open(scriptpath+"/"+cmdname,'w')

  dict={'NEVENTS':nevents[i], 'LHEFILE':lhefile}
  line = """! COPY ME TO YOUR DELPHES DIRECTORY 
! 1) Settings used in the main program.

Main:numberOfEvents = %(NEVENTS)s    ! number of events to generate
Main:timesAllowErrors = 3          ! how many aborts before run stops

! 2) Settings related to output in init(), next() and stat().

Init:showChangedSettings = on      ! list changed settings
Init:showChangedParticleData = on  ! list changed particle data
Next:numberCount = 1000            ! print message every n events
Next:numberShowInfo = 1            ! print event information n times
Next:numberShowProcess = 1         ! print process record n times
Next:numberShowEvent = 1           ! print event record n times

! 3) Set the input LHE file

Beams:frameType = 4
Beams:LHEF = %(LHEFILE)s

! 6) Other settings. Can be expanded as desired. ! Pythia8CUEP8M1Settings_cfi
Tune:pp = 14                            ! https://arxiv.org/pdf/1404.5630.pdf
Tune:ee = 7                             ! https://arxiv.org/pdf/1404.5630.pdf
MultipartonInteractions:pT0Ref=2.4024   ! http://home.thep.lu.se/~torbjorn/pythia81html/MultipartonInteractions.html Its value is intimately tied to a number of other choices, such as that of colour flow description, so unfortunately it is difficult to give an independent meaning to pT0Ref.
MultipartonInteractions:ecmPow=0.25208  ! The actual pT0 parameter used at a given CM energy scale, ecmNow, is obtained as pT0 = pT0(ecmNow) = pT0Ref * (ecmNow / ecmRef)^ecmPow 
MultipartonInteractions:expPow=1.6      ! 

Tune:preferLHAPDF = 2                     ! Tunes made by experimental collaborations typically use the LHAPDF package to obtain their PDF values, and so PYTHIA has to be linked accordingly. 
Main:timesAllowErrors = 10000             ! 
Check:epTolErr = 0.01                     ! http://home.thep.lu.se/~torbjorn/pythia81html/ErrorChecks.html Maximum allowed summed deviation of E, p_x, p_y and p_z between the incoming beams and the final state, as a fraction of the initial energy, above which the event is counted as aborted.
Beams:setProductionScalesFromLHEF = off   ! If enabled, production scales for all particles in an input Les Houches event will be set by using auxiliary information provided in the input event.
SLHA:keepSM = on                          ! if you switch off this flag then also SM particles are modified by SLHA input. 
SLHA:minMassSM = 1000.                    ! This parameter provides an alternative possibility to ignore SLHA input for all particles with identity codes below
ParticleDecays:limitTau0 = on             ! When on, only particles with tau0 < tau0Max are decayed.
ParticleDecays:tau0Max = 10               ! 
ParticleDecays:allowPhotonRadiation = on  ! 

JetMatching:setMad = off
JetMatching:merge  = off
  """%dict

  mycmnd.write(line)

  dict={'DELPHYPATH':delphespath, 'CMSSWPATH':cmsswbase, 'CMDNAME':cmdname, 'CMDPATH':scriptpath, 'OUTFILENAME':outname, 'OUTPATH':outputpath, 'LHEFILE': lhepath + "/" + lhefile}
  line = """#!/bin/sh
workdir=`pwd`

source /cvmfs/cms.cern.ch/cmsset_default.sh
export SCRAM_ARCH=slc6_amd64_gcc530
scram project CMSSW_9_1_0_pre3
cd CMSSW_9_1_0_pre3/src
eval `scram runtime -sh`

cd $workdir
cp -r %(DELPHYPATH)s $workdir/delphy
cd delphy
cp %(CMDPATH)s/%(CMDNAME)s .
cp %(LHEFILE)s .

./DelphesPythia8 cards/CMS_PhaseII/CMS_PhaseII_200PU_v02.tcl %(CMDNAME)s %(OUTFILENAME)s
mv %(OUTFILENAME)s %(OUTPATH)s/.

"""%dict

  mycsh = open(scriptpath+"/" + jobname,'w')
  mycsh.write(line)

  if i : 
    lineDelphes = lineDelphes + "bsub -q 1nd -o /dev/null -e /dev/null < "+scriptpath+"/submitJob" + str(i) + ".sh" + "\n"
    pass
  else : lineDelphes = lineDelphes + "bsub -q 1nd "+scriptpath+"/submitJob" + str(i) + ".sh" + "\n"

  os.system("chmod +x " + scriptpath+"/"+jobname)

print lineDelphes
myfinalfile.write(lineDelphes)
os.system("chmod +x " + scriptpath + "/SubmitDelphes.sh")

"""

myfinalfile = open("SubmitDelphes.sh","w")
lineDelphes = ""

for i in range(args.nJobs):
  line = ""
  mycsh = open(args.submissionDir+"/submitJob"+str(i)+".sh",'w')
  line = line + "#!/bin/sh" + "\n" + "\n"
  line = line + "cd " + cmsswbase + "\n"
  line = line + "eval `scramv1 runtime -sh`" + "\n"
  line = line + "cd " + delphespath +"\n" 
  line = line + "export PYTHONPATH=`pwd`/python:$PYTHONPATH\nexport LD_LIBRARY_PATH=`pwd`:$LD_LIBRARY_PATH\n"
  line = line + "cd " + location +"\n"
  if args.scenario=="0PU":
     line = line + delphespath + "/DelphesPythia8 "+delphespath +"/cards/CMS_PhaseII/CMS_PhaseII_0PU.tcl " +args.submissionDir+"/splitCmnd" + str(i) + ".cmnd "  +args.outputDir+"/delphes_lhe_batch" + str(i) + ".root" + "\n"
  elif args.scenario=="200PU":
     line = line + delphespath + "/DelphesPythia8 "+delphespath +"/cards/CMS_PhaseII/CMS_PhaseII_200PU.tcl " +args.submissionDir+"/splitCmnd" + str(i) + ".cmnd " +args.outputDir+"/delphes_lhe_batch" + str(i) + ".root" + "\n"
  mycsh.write(line)
  if i : lineDelphes = lineDelphes + "bsub -q 1nd -o /dev/null -e /dev/null < "+args.submissionDir+"/submitJob" + str(i) + ".sh" + "\n"
  else : lineDelphes = lineDelphes + "bsub -q 1nd -C 0 "+args.submissionDir+"/submitJob" + str(i) + ".sh" + "\n"

myfinalfile.write(lineDelphes)
os.system("chmod +x SubmitDelphes.sh")
"""




