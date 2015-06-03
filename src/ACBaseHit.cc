#include "ACBaseHit.hh"
#include <iostream>

ACBaseHit::ACBaseHit() {

}

ACBaseHit::~ACBaseHit() {

}



// "get" methods -------------------------------------


TVector3 ACBaseHit::pos() const {
   return _pos;
}

int ACBaseHit::pid() const {
   return _pid;
}

float ACBaseHit::Edep() const {
   return _edep;
}

int ACBaseHit::detID() const {
   return _detID;
}

float ACBaseHit::time() const {
   return _time;
}

int ACBaseHit::inc() const {
   return _inc;
}

// "set" methods ---------------------------------------------

void ACBaseHit::SetInc(int i) {
   _inc = i;
}

void ACBaseHit::SetPos(float vx, float vy, float vz) {
   TVector3 v3(vx, vy, vz);
   _pos = v3;
}

void ACBaseHit::SetPid(int id){
   _pid = id;
}

void ACBaseHit::SetDetID(int d) {
   _detID = d;
}

void ACBaseHit::SetTime(float t) {
   _time = t;
}

void ACBaseHit::SetEdep(float e) {
   _edep = e;
}

