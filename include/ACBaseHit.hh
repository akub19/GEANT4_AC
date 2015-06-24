#ifndef _ACBASEHIT_H
#define _ACBASEHIT_H

#include "TObject.h"
#include "TLorentzVector.h"
#include "TVector3.h"

class ACBaseHit : public TObject {
private:
    TVector3 _pos;
    int _pid;
    float _edep;
    int _detID;
    float _time;
    int _inc;
    int _pre;
    int _post;

public:
    ACBaseHit();
    virtual ~ACBaseHit();

    // "get" methods -----------

    TVector3 pos() const;
    int pid() const;
    float Edep() const;
    int detID() const;
    float time() const;
    int inc() const;
    int preproc() const;
    int postproc() const;

    // "set" methods ---------
    void SetPos(float vx, float vy, float vz);
    void SetEdep(float e);
    void SetPid(int id);
    void SetDetID(int d);
    void SetTime(float t);
    void SetInc(int i);
    void SetPreProcess(int p);
    void SetPostProcess(int p);

    ClassDef(ACBaseHit, 1);


};

#endif  /* _ACBASEHIT_H */
