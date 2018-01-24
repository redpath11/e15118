#ifndef __HAVE_SWEEPER_DEFINITIONS
#define __HAVE_SWEEPER_DEFINITIONS

/*
This file contains definitions for sweeper parameters which may
need to be edited on occasion.  Changes here should propogate
to all .h and .cpp files when re-compiling.

Please note that things set here are just default values.
One can still change the actual value SpecTcl uses by editing
the tcl TreeVariable.
*/


// Some useful constants
#ifndef __STD_CONSTANTS
#define __STD_CONSTANTS
static const double PI(3.14159);
static const double C(29.9792458); //\cm/ns
static const double N_MASS(939.565560); //\MeV/c^2
static const double AMU_MASS(931.494088); //MeV/c^2
#endif

//order of the thick/thin energy position correction
static const unsigned int POSCORR_ORDER(6);
static const unsigned int IC_CORR_ORDER(3);

//mapping of ToF channels-> detector
//static const unsigned short CH_A1900 (12); - during Dec 2010 exp, switched wire from scaler 12 to scaler 15 - JKS, 18 June 2011
//experiment e10023c - runs<=1056(2056 & 3056) have CH_A1900 (12). runs>1056 have CH_A1900 (15). see page 81 of logbook.
static const unsigned short CH_A1900 (15);
static const unsigned short CH_RF    (13);
static const unsigned short CH_POT   (14);


//no of channels for various detectors
static const unsigned short FPCRDC_PADS          (128);
static const unsigned short TCRDC_PADS           (64);
static const unsigned short IC_CHANNELS          (16);
static const unsigned short FPCRDC_MAX_WIDTH     (32);
static const unsigned short TCRDC_MAX_WIDTH      (32);
static const unsigned short TRACK_PARAMETERS      (6);
static const unsigned short TRACK_COEFFICIENTS    (200);
static const unsigned short II_TRACK_PARAMETERS   (6);
static const unsigned short II_TRACK_COEFFICIENTS (200);


//where things are (in meters, relative to trgt)
static const double CRDC1POS      (  1.0 );
static const double CRDC2POS      (  2.0 );
static const double TCRDC2POS     ( -2.0 );
static const double TCRDC1POS     ( -3.0 );
static const double QUAD_ENTRANCE ( -1.8 );
static const double FOCUSPOS      (  1.0 );
static const double THINPOS       (  5.002);
static const double THICKPOS      (  5.002);

//slopes, offsets
static const double DEFAULT_SLOPE (1.);
static const double DEFAULT_OFFSET(0.);

static const double S_TDC_SLOPE     (-0.1);

static const double CRDC1_XSLOPE  ( 2.54);
static const double CRDC2_XSLOPE  (-2.54);
static const double CRDC1_XOFFSET (-175.);
static const double CRDC2_XOFFSET ( 175.);

static const double CRDC_YSLOPE  (-0.065);
static const double CRDC_YOFFSET ( 125. );

static const double TCRDC_XSLOPE  ( 2.54);
static const double TCRDC_XOFFSET (-125.);

static const double TCRDC_YSLOPE  (-0.05);
static const double TCRDC_YOFFSET ( 30. );


//default bins
#ifndef __HAVE_RAW_BINS
#define __HAVE_RAW_BINS
#define RAW_BINS   4096, 0, 4095
#endif
#define S_TCAL_BINS   100, 0, 100
#define S_QCAL_BINS   100, 0, 100
#define S_TOF_BINS    100, 0, 100
#define S_POSN_BINS   300, -300, 300
#define S_ANGLE_BINS  300, -300, 300
#define S_CRDC_BINS   300, -300, 300


#endif
