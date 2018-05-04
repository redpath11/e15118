// data structure declarations for simulation analysis tree
/*
  typedef struct {Double_t beta,gamma,velocity;} BEAM;
  typedef struct {Double_t x,y,de;} SILICON;
  typedef struct {Double_t x,y,tx,ty;} CRDC;
  typedef struct {Double_t x,y;} THIN;
  typedef struct {Double_t x,y,z,dist,t,v,beta,gamma,E,P,light;} NEUTRON;
  typedef struct {Double_t beta,gamma,v,Bp,E,P;} FRAGMENT;
*/

  struct BEAM {Double_t beta,gamma,v;};
  struct SILICON {Double_t x,y,de;};
  struct CRDC {Double_t x,y,tx,ty,path;};
  struct THIN {Double_t x,y;};
  struct NEUTRON {Double_t x,y,z,t,dist,cosTheta,v,beta,gamma,E,P,light;};
  struct FRAGMENT {Double_t dist,beta0,gamma0,v0,ke0,Bp,beta,gamma,v,ke,E,P;};
  struct TOF {
    UShort_t nfired;
    Double_t un,pt,frag;
    Double_t q[4];
    Double_t qx[4];
    Double_t qxy[4];};
/*
  static BEAM beam;
  static SILICON si0;
  static SILICON si1;
  static SILICON si2;
  static SILICON si3;
  static CRDC crdc1;
  static CRDC crdc2;
  static THIN thin;
  static NEUTRON n0;
  static FRAGMENT frag;
*/

