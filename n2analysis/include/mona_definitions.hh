/*
This file contains definitions for mona parameters which may
need to be edited on occasion.  Changes here should propogate
to all .h and .cpp files when re-compiling.

Please note that everything set here is just a default value.
One can still change the actual value SpecTcl uses by editing
the tcl TreeVariable.
*/

#ifndef __HAVE_MONA_DEFINITIONS
#define __HAVE_MONA_DEFINITIONS

// Some useful constants
#ifndef __STD_CONSTANTS
#define __STD_CONSTANTS
static const double PI(3.14159);
static const double C(29.9792458); //\cm/ns
static const double N_MASS(939.565560); //\MeV/c^2
static const double AMU_MASS(931.494088); //MeV/c^2
#endif

// Structure/layout of MoNA.

static const unsigned short MONA_HITS   (  10  );
static const unsigned short MONA_WALLS  (   18  );
static const unsigned short WALL_BARS   (  16  );

// Conversion to linear algebra position calculation: THR 12/20/2016
static const unsigned short Jinv_R      (  3  );
static const unsigned short Jinv_C      (  3  );

static const double         MONA_XPOS   (  0.0 );
static const double         MONA_YPOS   (-82.08); //from beam->cntr of row 0
static const double         MONA_ZPOS   ( 653.0);

//the parameter on which we sort hit values (1=t, 2=v)
static const unsigned short SORT_PARAM( 1 );

// Default slopes, offsets, etc.
//tdcs
static const double TDC_RANGE     (  320.0 );
static const double TDC_OFFSET    (  0.0   );
static const double TDC_SLOPE     (TDC_RANGE / 4096.);
//xpos
static const double XPOS_SLOPE    (  8.0  );
static const double XPOS_OFFSET   (  0.0  );

//qdcs
static const double QDC_SLOPE     (  0.028 );
static const double QDC_OFFSET    ( -100.0 );
static const double QDC_THRESHOLD (  10.0  );

//tmean
static const double TMEAN_OFFSET  ( 400.0 );

//neutron window for calculating e_decay, etc.
static const double NWINDOW_LO    (  50.0 );
static const double NWINDOW_HI    ( 400.0 );


// Definitions for spectrum ranges
// format:
//    #define SOME_BINS     nbins, low_bin, high_bin

#define RAW_BINS     4096,   0, 4095
#define TCAL_BINS    100,  -50,  350
#define VCAL_BINS    100,    0,   40
#define QCAL_BINS    100,    0,  100
#define XCAL_BINS    100, -100,  100
#define YCAL_BINS     16,  -70,   70
#define ZCAL_BINS     30, MONA_ZPOS, MONA_ZPOS+300.
#define RHO_BINS     100,    0,   20
#define ANGLE_BINS   100,  -PI,   PI



// Mask definitions for CAEN ADCs (i.e. the MoNA tdcs and qdcs)
// (from /usr/opt/spectcl/3.2/contrib/scripted/src/CCAENDigitizerModule.cpp)
// In general these values should not be touched unless the type
// of TDC or QDC in use has changed.
    
static const unsigned int ALLH_TYPEMASK(0x700);
static const unsigned int ALLH_TYPESHIFT(8);
static const unsigned int ALLH_GEOMASK(0xf800);
static const unsigned int ALLH_GEOSHIFT(11);

    // High part of header.
    
static const unsigned int HDRH_CRATEMASK(0x00ff);
static const unsigned int HDRH_CRATESHIFT(0);

    // Low part of header.
    
static const unsigned int HDRL_COUNTMASK(0X3f00);
static const unsigned int HDRL_COUNTSHIFT(8);

    // High part of data:
    
static const unsigned int DATAH_CHANMASK(0x3f);
static const unsigned int DATAH_CHANSHIFT(0);

    // Low part of data:
    
static const unsigned int DATAL_UNBIT(0x2000);
static const unsigned int DATAL_OVBIT(0x1000);
static const unsigned int DATAL_VBIT(0x40000);
static const unsigned int DATAL_DATAMASK(0x0fff);

    //  High part of trailer:
    
static const unsigned int TRAILH_EVHIMASK(0x00ff);

    // Word types:
    
static const unsigned int HEADER(2);
static const unsigned int DATA(0);
static const unsigned int TRAILER(4);
static const unsigned int INVALID(6);



#endif
