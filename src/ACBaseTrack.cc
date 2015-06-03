#include "ACBaseTrack.hh"
#include <iostream>

ACBaseTrack::ACBaseTrack() {

}

ACBaseTrack::~ACBaseTrack() {

}



// "get" methods -------------------------------------

TLorentzVector ACBaseTrack::p4() const {
   return _4mom;
}

float ACBaseTrack::E() const {
   return _4mom.E();
}

float ACBaseTrack::p() const {
   return _4mom.P();
}

TVector3 ACBaseTrack::pos() const {
   return _pos;
}

int ACBaseTrack::pid() const {
   return _pid;
}

float ACBaseTrack::time() const {
   return _time;
}

int ACBaseTrack::inc() const {
   return _inc;
}

// "set" methods ---------------------------------------------

void ACBaseTrack::Setp4(TLorentzVector mom) {
   _4mom = mom;
}

void ACBaseTrack::SetInc(int i) {
   _inc = i;
}

void ACBaseTrack::Setp4(float px, float py, float pz, float e) {
   TLorentzVector mom(px, py, pz, e);
   _4mom = mom;
}

void ACBaseTrack::SetPos(float vx, float vy, float vz) {
   TVector3 v3(vx, vy, vz);
   _pos = v3;
}

void ACBaseTrack::SetPid(int id){
   _pid = id;
}

void ACBaseTrack::SetTime(float t) {
   _time = t;
}
