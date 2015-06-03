#ifndef _ACBASETRACK_H
#define _ACBASETRACK_H

#include "TObject.h"
#include "TLorentzVector.h"
#include "TVector3.h"

class ACBaseTrack : public TObject {
private:
    TLorentzVector _4mom;
    TVector3 _pos;
    int _pid;
    float _time;
    int _inc;

public:
    ACBaseTrack();
    virtual ~ACBaseTrack();

    // "get" methods -----------

    TLorentzVector p4() const;
    TVector3 pos() const;
    int pid() const;
    float p() const;
    float E() const;
    float time() const;
    int inc() const;

    // "set" methods ---------
    void Setp4(TLorentzVector mom);
    void Setp4(float px, float py, float pz, float e);
    void SetPos(float vx, float vy, float vz);
    void SetPid(int id);
    void SetTime(float t);
    void SetInc(int i);

    ClassDef(ACBaseTrack, 1);


};

#endif  /* _ACBASETRACK_H */
