#ifndef __SWEEPER_RAW_HH
#define __SWEEPER_RAW_HH
#define __UNPACK_SAMPLES 1
#define __WITH_DIAMOND // (un)comment to turn (on)off diamond timing analysis, then re-compile
#define __WITH_HODOSCOPE
static const unsigned short DIA_CH (4);  // number of diamond channels
static const unsigned short HODO_CH (25);
#define __WITH_SEGTARG
static const unsigned short SEGTARG_CH (32);//number of segtarg channels



#include "sweeper_definitions.hh"
#include "sweeper_packets.hh"
#include "detector.hh"
#include "cosy_map.hh"
#include "utils.cc"
#include <vector>
#include <string>

//---------------------------------------//
// raws
namespace raw {

  // Sweeper VME TDC
  class sweeper_vmetdc
  {
  public:
    unsigned short data[32][32];
    unsigned short raw[32];
    signed short hits[32];

  public:
  void reset();
  void unpack(unsigned short* p);
  };


  // trigger packet
  class sweeper_trigger
  {
  public:
    short registr;
    short sweeper;
    short external1;
    short external2;
    short secondary;
    short pattern;
    short timestamp[4];

  public:
    void reset();
    void unpack(unsigned short* pTrig);
  };

  // crdc
  class sweeper_crdc_pads
  {
  public:
    short nsamples[FPCRDC_PADS];
    short raw[FPCRDC_PADS];
#if(__UNPACK_SAMPLES)
    short sample[FPCRDC_PADS][FPCRDC_MAX_WIDTH];
#endif


  public:
    void integrate(std::vector< std::vector<short> >& data,
		   unsigned short sampleWidth,
		   unsigned short id);// THR 22 August 2016: allow for
		   		      // different methods between
				      // CRDC1 and CRDC2
  };

  class sweeper_crdc
  {
  public:
    short anode;
    short tac;
    short sample_width;
    sweeper_crdc_pads pad;

  public:
    void reset();
    void unpack(unsigned short* pCrdc,unsigned short id);
    void unpack_raw_data(unsigned short* pCrdc,
    			 unsigned short id);
  };

  // tcrdc
  class sweeper_track_crdc_pads
  {
  public:
    short nsamples[TCRDC_PADS];
    short raw[TCRDC_PADS];
#if(__UNPACK_SAMPLES)
    short sample[TCRDC_PADS][TCRDC_MAX_WIDTH];
#endif

  public:
    void integrate(std::vector< std::vector<short> >& data,
		   unsigned short sampleWidth);
  };

  class sweeper_track_crdc
  {
  public:
    short anode;
    short tac;
    short sample_width;
    sweeper_track_crdc_pads pad;

  public:
    void reset();
    void unpack(unsigned short* pCrdc);
    void unpack_raw_data(unsigned short* pCrdc);
  };

  // ion chamber
  class sweeper_ion_chamber
  {
  public:
    short raw[IC_CHANNELS];

  public:
    void reset();
    void unpack(unsigned short* pIc);
  };

  // fp scintillator
  class sweeper_fp_scint
  {
  public:
    short qraw[4];
    short traw[4];

  public:
    void reset();
  };

  // beamline scintillator
  class sweeper_scint
  {
  public:
    short traw;
    short qraw;

  public:
    void reset();
  };

  // diamond detector
#ifdef __WITH_DIAMOND
  class sweeper_diamond_detector
  {
  public:
    short traw[DIA_CH];
    short qraw[DIA_CH];

  public:
    void reset();
  };
#endif

  // hodoscope
#ifdef __WITH_HODOSCOPE
  class sweeper_hodoscope
  {
  public:
    short raw[HODO_CH];

  public:
    void reset();
    void unpack(unsigned short* pHs);
  };
#endif

  // segmented target ADC
#ifdef __WITH_SEGTARG
  class sweeper_segtargadc
  {
  public:
    short raw[SEGTARG_CH];

  public:
    void reset();
    void unpack(unsigned short* pHs);
  };
#endif

  // timing detector
  class sweeper_timing_detector
  {
  public:
    short traw;

  public:
    void reset();
  };

  // all raw sweeper parameters
  class sweeper: public detector
  {
  public:

    // classes with data
    sweeper_vmetdc	    tdc;
    sweeper_trigger         trigger;
    sweeper_crdc            crdc1;
    sweeper_crdc            crdc2;
    sweeper_track_crdc      tcrdc1;
    sweeper_track_crdc      tcrdc2;
    sweeper_ion_chamber     ic;
    sweeper_fp_scint        thin;
#ifdef __WITH_SEGTARG
    sweeper_segtargadc      st;
#endif
#ifdef __WITH_HODOSCOPE
    sweeper_hodoscope	    hodo;
#else
    sweeper_fp_scint        thick;
#endif
    sweeper_scint           pot;
    sweeper_timing_detector a1900;
    sweeper_timing_detector rf;
#ifdef __WITH_DIAMOND
    sweeper_diamond_detector diamond;
#endif

    // unpackers that don't fit neatly into the event packet structure
    void unpack_fp_scint(unsigned short* pFp);
    void unpack_tof(unsigned short* pTof);
    void unpack_time_stamp(unsigned short* pTs);
#ifdef __WITH_DIAMOND
    void unpack_diamond(unsigned short* pDia);
#endif

    void reset();
    void unpack(unsigned short* pS);
  };

} // namesapce raw


//---------------------------------------//
// variables
namespace var {

  // (t)crdc
  class sweeper_crdc_pads
  {
  public:
    double ped[FPCRDC_PADS];
    double slope[FPCRDC_PADS];
    double offset[FPCRDC_PADS];
    double f_scale[FPCRDC_PADS];
    double f_sigma[FPCRDC_PADS];
    int ref_pad;

  public:
    void write(const char* name, FILE* f);
  };

  class sweeper_track_crdc_pads
  {
  public:
    double ped[TCRDC_PADS];
    double slope[TCRDC_PADS];
    double offset[TCRDC_PADS];
    double f_scale[FPCRDC_PADS];
    double f_sigma[FPCRDC_PADS];
    int ref_pad;

  public:
    void write(const char* name, FILE* f);
  };

  class sweeper_crdc
  {
  public:
    sweeper_crdc_pads pad;

    int gravity_width;
    int fit_width;
    int method; //\ 1 = gravity, 2 = fit
    int badpads;
    int badpad[FPCRDC_PADS];

    double x_offset;
    double x_slope;
    double y_offset;
    double y_slope;
    double z;

  public:
    void write(const char* name, FILE* f);
  };


  class sweeper_track_crdc
  {
  public:
    sweeper_track_crdc_pads pad;

    int gravity_width;
    int fit_width;
    int method; //\ 1 = gravity, 2 = fit
    int badpads;
    int badpad[TCRDC_PADS];

    double x_offset;
    double x_slope;
    double y_offset;
    double y_slope;
    double z;

    bool rotate_spikes;
    bool force_correlation;
    double corr_slope;
    double corr_offset;

  public:
    void write(const char* name, FILE* f);
  };

  // ion chamber
  class sweeper_ion_chamber
  {
  public:
    double slope[IC_CHANNELS];
    double offset[IC_CHANNELS];
    double corr[IC_CHANNELS][IC_CORR_ORDER+1];
    double corr_scale[IC_CHANNELS];
    double de_slope;
    double de_offset;

  public:
    void write(const char* name, FILE* f);
  };

  // fp scint
  class sweeper_fp_scint
  {
  public:
    double t_slope[4];
    double t_offset[4];
    double q_slope[4];
    double q_offset[4];
    int required_pmts;
    double corr_scale;
    double corr_offset;
    double corr[POSCORR_ORDER];
    double z;

  public:
    void write(const char* name, FILE* f);
  };

  // normal scint
  class sweeper_scint
  {
  public:
    double t_slope;
    double t_offset;
    double q_slope;
    double q_offset;
    double z;

  public:
    void write(const char* name, FILE* f);
  };

  // timing detector
  class sweeper_timing_detector
  {
  public:
    double t_slope;
    double t_offset;
    double z;

  public:
    void write(const char* name, FILE* f);
  };

  // diamond detector
#ifdef __WITH_DIAMOND
  class sweeper_diamond_detector
  {
  public:
    double t_slope [DIA_CH];
    double t_offset[DIA_CH];
    double q_slope [DIA_CH];
    double q_offset[DIA_CH];
    double z;

  public:
    void write(const char* name, FILE* f);
  };
#endif
  
  // hodoscope
#ifdef __WITH_HODOSCOPE
  class sweeper_hodoscope
  {
  public:
    double slope [HODO_CH];
    double offset [HODO_CH];
    double z;

  public:
    void write(const char* name, FILE* f);
  };
#endif

  // segmented target ADC                     // 12/18/15
#ifdef __WITH_SEGTARG
  class sweeper_segtargadc
  {
  public:
   // slopes and offsets for corners
   // [det:0,1,2,3][corner:LU,RU,RD,LD]
   // det0 is the first Si the beam sees
   double cnr_slope  [4][4];
   double cnr_offset [4][4];
   // slopes and offsets for position
   // calculations after the corners have
   // been gainmatched; [det0,1,2,3]
   // det0 is the first Si the beam sees
   double x_slope [4];
   double x_offset[4];
   double y_slope [4];
   double y_offset[4];
   // slopes and offsets for the energy
   // calibration: [det0,1,2,3]
   // det0 is the first Si the beam sees
   double e_slope [4];
   double e_offset[4];

  public:
   void write(const char* name, FILE* f);
  };
#endif

  // tof
  class sweeper_tofcorr
  {
  public:
    double x;
    double tx;
    double xtx;
    double x2;
    double tx2;

  public:
    void write(const char* name, FILE* f);
  };

  class sweeper_tof
  {
  public:
    sweeper_tofcorr rf;
    sweeper_tofcorr a1900;
    sweeper_tofcorr pot;

  public:
    void write(const char* name, FILE* f);
  };

  // itrack
  class sweeper_itrack
  {
  public:
    double z;
    double tx_offset;
    double ty_offset;
    std::string filename;

  public:
    void write(const char* name, FILE* f);
  };

  // ftrack
  class sweeper_ftrack
  {
  public:
    double z;
    std::string filename;

  public:
    void write(const char* name, FILE* f);
  };

  // focus
  class sweeper_focus
  {
  public:
    double z;

  public:
    void write(const char* name, FILE* f);
  };

  // all of sweeper
  class sweeper
  {
  public:
    int    charge;
    double mass;
    double brho;
    double target_eloss;
    sweeper_crdc            crdc1;
    sweeper_crdc            crdc2;
    sweeper_focus           focus;
    sweeper_track_crdc      tcrdc1;
    sweeper_track_crdc      tcrdc2;
    sweeper_ion_chamber     ic;
    sweeper_fp_scint        thin;
#ifdef __WITH_HODOSCOPE
    sweeper_segtargadc      st;//HL 12/21/2015
#endif

#ifdef __WITH_HODOSCOPE
    sweeper_hodoscope	    hodo;
#else
    sweeper_fp_scint        thick;
#endif
    sweeper_scint           pot;
    sweeper_timing_detector rf;
    sweeper_timing_detector a1900;
    sweeper_tof             tofcorr;
    sweeper_ftrack ftrack;
    sweeper_itrack itrack;
#ifdef __WITH_DIAMOND
    sweeper_diamond_detector diamond;
#endif

  public:
    sweeper() {
#include "sweeper_variables.hh"
    }

    void write(const char* name, const char* filename);
  };

} // namespace var


//---------------------------------------//
// cals
namespace cal {

  // (t)crdcs
  class sweeper_crdc_pads
  {
  public:
    int    fcpy[FPCRDC_PADS];//flag events with duplicate pads THR 4 August 2016
//    int    smpls[FPCRDC_PADS][4];// write out all samples THR 16 August 2016
    double cal[FPCRDC_PADS];

  public:
    void reset();
    void calibrate(const raw::sweeper_crdc_pads& rw,
		   const var::sweeper_crdc_pads& v,
		   const short& sw,
		   const short& pm);
  };

  class sweeper_crdc
  {
  private:
    void gravity_fit(const var::sweeper_crdc& v);
    void gaus_fit(const var::sweeper_crdc& v);

  public:
    // fitted
    sweeper_crdc_pads pad;
    int    padmax;
    double padsum;
    double sigma;
    double x_gravity;
    double x_fit;
    double x_chi2;
    // calibrated
    double x;
    double tx;
    double y;
    double ty;

  public:
    void reset();
    void calibrate(const raw::sweeper_crdc& rw,
		   const var::sweeper_crdc& v);
    void calculate_image(const sweeper_crdc& p1, const var::sweeper_crdc& v1,
			 const sweeper_crdc& p2, const var::sweeper_crdc& v2);
  };

  class sweeper_track_crdc_pads
  {
  public:
    double cal[TCRDC_PADS];

  public:
    void reset();
    void calibrate(const raw::sweeper_track_crdc_pads& rw,
		   const var::sweeper_track_crdc_pads& v,
		   const short& sw,
		   const short& pm);
  };

  class sweeper_track_crdc
  {
  private:
    void gravity_fit(const var::sweeper_track_crdc& v);
    void gaus_fit(const var::sweeper_track_crdc& v);

  public:
    // fitted
    sweeper_track_crdc_pads pad;
    int    padmax;
    double padsum;
    double sigma;
    double x_gravity;
    double x_fit;
    double x_chi2;
    // calibrated
    double x;
    double tx;
    double y;
    double ty;

  public:
    void reset();
    void calibrate(const raw::sweeper_track_crdc& rw,
		   const var::sweeper_track_crdc& v);
    void calculate_image(const cal::sweeper_track_crdc& p1, const var::sweeper_track_crdc& v1,
			 const cal::sweeper_track_crdc& p2, const var::sweeper_track_crdc& v2);
    double rotate_spikes(double x1, double x2);
    void force_correlation(const cal::sweeper_track_crdc& other_tcrdc,
			   const var::sweeper_track_crdc& v);
    void calibrate_y(const raw::sweeper_track_crdc& rw,
		     const var::sweeper_track_crdc& v);

  };

  // ion chamber
  class sweeper_ion_chamber
  {
  public:
    double cal[IC_CHANNELS];
    double sum;
    double de;
    double corr[IC_CHANNELS];
    double de_corr;

  public:
    void reset();
    void calibrate(const raw::sweeper_ion_chamber& rw,
		   const var::sweeper_ion_chamber& v);
    void correct(const var::sweeper_ion_chamber& v,
		 const double& x_corr);

  };

#ifdef __WITH_HODOSCOPE
  // hodoscope
  class sweeper_hodoscope
  {
  public:
    double cal[HODO_CH];
    double sum;
    int maxcrystal;
    int mult;
    double x;
    double tx;
    double y;
    double ty;

  public:
    void reset();
    void calibrate(const raw::sweeper_hodoscope& rw,
		   const var::sweeper_hodoscope& v);
    void calculate_image(const cal::sweeper_crdc& p1, const var::sweeper_crdc& v1,
			 const cal::sweeper_crdc& p2, const var::sweeper_crdc& v2,
			 const double& z);
  };
#endif

#ifdef __WITH_SEGTARG
  class sweeper_segtargadc
  {
  public:
//    double cal[SEGTARG_CH];
    // arrays to hold raw anode, gainmatched
    // corner, calculated x,y and calibrated
    // energy signals
    double anode[4];
    double corner[4][4];
    double x[4];
    double y[4];
    double ecal[4];

  public:
    void reset();
    void calibrate(const raw::sweeper_segtargadc& rw,
		   const var::sweeper_segtargadc& v);
//    void position_correct(const var::sweeper_segtargadc& v);
//    void energy_calibration(const var::sweeper_segtargadc& v);
  };

#endif


  // fp scint
  class sweeper_fp_scint
  {
  public:
    double tcal[4];
    double qcal[4];
    double e;
    double ecorr;
    double t;
    double xpos;
    double ypos;
    double x;
    double tx;
    double y;
    double ty;
 
  public:
    void reset();
    void calibrate(const raw::sweeper_fp_scint& rw,
		   const var::sweeper_fp_scint& v,
		   const double& jittersub);
    void calculate_image(const cal::sweeper_crdc& p1, const var::sweeper_crdc& v1,
			 const cal::sweeper_crdc& p2, const var::sweeper_crdc& v2,
			 const double& z);
    void position_correct(const var::sweeper_fp_scint& v);
  }; 

  // normal scint
  class sweeper_scint
  {
  public:
    double tcal;
    double qcal;

  public:
    void reset();
    void calibrate(const raw::sweeper_scint& rw,
		   const var::sweeper_scint& v,
		   const double& jittersub);
  };

  // timing detector
  class sweeper_timing_detector
  {
  public:
    double tcal;

  public:
    void reset();
    void calibrate(const raw::sweeper_timing_detector& rw,
		   const var::sweeper_timing_detector& v,
		   const double& jittersub);
  };

#ifdef __WITH_DIAMOND
  class sweeper_diamond_detector
  {
  public:
    double tcal[DIA_CH];
    double qcal[DIA_CH];
    double t_hit;
    short strip;
    short nhits;

  public:
    void reset();
    void calibrate(const raw::sweeper_diamond_detector& rw,
		   const var::sweeper_diamond_detector& v,
		   const double& jittersub);
  };
#endif

  // focus
  class sweeper_focus
  {
  public:
    double x;
    double tx;
    double y;
    double ty;

  public:
    void reset();
    void calculate_image(const cal::sweeper_crdc& p1, const var::sweeper_crdc& v1,
			 const cal::sweeper_crdc& p2, const var::sweeper_crdc& v2,
			 const var::sweeper_focus& v);
  };

  // tof
  class sweeper_tof
  {
  public:
    double rf_a1900;
    double rf_pot;
    double rf_thin;
    double a1900_pot;
    double a1900_thin;
    double pot_thin;
#ifdef __WITH_DIAMOND
    double rf_diamond;
    double a1900_diamond;
    double pot_diamond;
    double diamond_thin;
#endif

  public:
    void reset();
#ifdef __WITH_DIAMOND
    void calculate(const double& rf,  const double& a1900,
		   const double& pot, const double& thin,
		   const double& dia);
#else
    void calculate(const double& rf,  const double& a1900,
		   const double& pot, const double& thin);
#endif
  };

  class sweeper_tofcorr
  {
  public:
    double rf_thin;
    double a1900_thin;
    double pot_thin;

  public:
    void reset();
    void calculate(const cal::sweeper_tof& tof,
		   const var::sweeper_tof& v,
		   const cal::sweeper_focus& focus);
  };

  // maps
  class sweeper_ftrack
  {
  public:
    double x;
    double tx;
    double y;
    double ty;

  public:
    void reset();
    void calculate(const cal::sweeper_track_crdc& tcrdc1,
		   const var::sweeper_ftrack& v);
  };

  class sweeper_itrack
  {
  public:
    double x;
    double tx;
    double y;
    double ty;
    double len;
    double de;
    double e;
    double p;

  public:
    void reset();
    void calculate(const cal::sweeper_crdc& crdc1,
		   const double& trgt_x,
		   const var::sweeper& v);
  };

// all of sweeper
  class sweeper
  {
  public:
    double v;
    double e;
    double p;
    sweeper_crdc crdc1;
    sweeper_crdc crdc2;
    sweeper_track_crdc tcrdc1;
    sweeper_track_crdc tcrdc2;
    sweeper_ion_chamber ic;
    sweeper_fp_scint thin;
#ifdef __WITH_SEGTARG
    sweeper_segtargadc st;
#endif
#ifdef __WITH_HODOSCOPE
    sweeper_hodoscope hodo;
#else
    sweeper_fp_scint thick;
#endif
    sweeper_scint pot;
    sweeper_timing_detector rf;
    sweeper_timing_detector a1900;
    sweeper_tof tof;
    sweeper_tofcorr tofcorr;
    sweeper_focus focus;
    sweeper_ftrack ftrack;
    sweeper_itrack itrack;
    //    sweeper_target target;
#ifdef __WITH_DIAMOND
    sweeper_diamond_detector diamond;
#endif

  public:
    void reset();
    void calculate_energy(const var::sweeper& v);
    void calibrate(const raw::sweeper* rw,
		   const var::sweeper& v);
  };

} //namespace cal


#endif
