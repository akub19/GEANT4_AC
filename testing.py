#! /usr/bin/env python

import ROOT
ROOT.PyConfig.IgnoreCommandLineOptions = True
import sys
from ROOT import *
#from math import fabs,pi,sqrt
from math import *
from array import array
import profile
import time
import copy
#sys.setcheckinterval(1000)
import numpy as n

TH1.SetDefaultSumw2(kTRUE)
TH2.SetDefaultSumw2(kTRUE)
TH3.SetDefaultSumw2(kTRUE)


gROOT.LoadMacro("/home/andy/HistManager/HistManager.cc+")
gROOT.LoadMacro("/home/andy/HistManager/ACStuff/ACBaseHit.cc+")
gROOT.LoadMacro("/home/andy/HistManager/ACStuff/ACBaseTrack.cc+")
from ROOT import HistManager
from ROOT import ACBaseHit
from ROOT import ACBaseTrack

saveFile = TFile("analysis.root","RECREATE")

hists = HistManager(saveFile)
f1DH = hists.fill1DHist
f1DHU = hists.fill1DHistUnevenBins
f2DH = hists.fill2DHist
f2DHU = hists.fill2DHistUnevenBins
fProf = hists.fillProfile


treeFile = TFile.Open('hits.root')
theTree = treeFile.Get('theTree')

saveFile.cd()

hits = TClonesArray("ACBaseHit",10)
theTree.SetBranchAddress("sHits",hits)

trks = TClonesArray("ACBaseTrack",10)
theTree.SetBranchAddress("sTracks",trks)

nHits = 0
nVetos = 0
events = 0

#points = TH3D("hitpos","hitpos",300,-100,100,300,-100,100,300,-100,100)

eff_den = TH1D("phoE_den","Incident photon Energy spectrum",30,0,3)
eff_num = TH1D("phoE_num","Incident photon Energy spectrum",30,0,3)
eff = TH1D("eff_vs_incE","; Incident Photon E (MeV); Veto Efficiency",30,0,3)

for evt in theTree:

   events += 1
   if events%1000 == 0: print events
   detHit = false
   vetoHitIn = false
   vetoHitOut = false

   detE = 0.
   vetoEin = 0.
   vetoEout = 0.

   eTime = 99999.


   incE = 0.
   outT = 0.
   outE = 0.
   for trk in evt.sTracks:
      if trk.time() > outT:
          outT = trk.time()
          outE = trk.p()
      if trk.inc() == 0:
          f1DH(trk.p(),"phoE","Incident photon Energy spectrum",100,0,4,1.,"")
          incE = trk.p()


   for hit in evt.sHits:
      #points.Fill(hit.pos().x(),hit.pos().y(),hit.pos().z())
      if hit.detID() == 0: # and hit.pid() == 22:
          detHit = true
          detE += hit.Edep()
          if hit.time() < eTime:
              eTime = hit.time()

   for hit in evt.sHits:
      if hit.detID() != 0: # and hit.pid() == 22:
         if hit.time() > eTime:
            vetoHitOut = true
            vetoEout += hit.Edep()
         else:
            vetoHitIn = true
            vetoEin += hit.Edep()


   #print incE, (incE - detE - vetoEin)

   if detHit:
      f1DH(detE,"detE","E dep. (incoming veto hit)",100,0,3,1.,"")
      if vetoHitIn:
          f1DH(detE,"detE_vetoHitIn","E dep. (incoming veto hit)",100,0,3,1.,"") 
      if vetoHitOut:
          f1DH(detE,"detE_vetoHitOut","E dep. (outgoing veto hit)",100,0,3,1.,"")
      if not vetoHitIn and not vetoHitOut:
          f1DH(detE,"detE_noVeto","E dep. (no veto hit)",100,0,3,1.,"")


   

   if detHit and not vetoHitIn and (incE - detE) > 0.00001:
      nHits += 1
      eff_den.Fill(incE)
      if vetoHitOut:
          nVetos += 1
          eff_num.Fill(incE)
          f1DH(incE-detE,"edeposit_veto","E dep. veto",100,-3,3,1.,"")
      else:
          f1DH(incE-detE,"edeposit_noveto","E dep. no veto",100,-3,3,1.,"")



eff.Divide(eff_num,eff_den,1.,1.,"B")

print "Done"
print "Total Events: ", nHits
print "Total Events vetoed: ", nVetos
saveFile.Write()
saveFile.Close()
del hists
