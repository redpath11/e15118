#ifndef __HAVE_CAESAR_RAW_HH
#define __HAVE_CAESAR_RAW_HH

#include "caesar_definitions.hh"
#include "detector.hh"
#include "sweeper.hh"
#include "utils.cc" //\ for custom 2d gates
#include <iostream>
#include <utility>
#include <vector>
#include <map>
#include <stdlib.h>

#define __CAESAR_ECAL_ORDER 1 // order of caesar energy calibration
#define __CAESAR_TCAL_ORDER 1 // order of caesar energy calibration
// #define CAESAR_RINGS        10
// #define CAESAR_AB_PSPEC 

typedef std::pair<int, int> pair_t;
typedef std::map<pair_t, pair_t> pmap_t;

static int caesar_det_per_ring[CAESAR_RINGS] = {
  CAESAR_N_RING_A, CAESAR_N_RING_B, CAESAR_N_RING_C, CAESAR_N_RING_D, 
  CAESAR_N_RING_E, CAESAR_N_RING_F, CAESAR_N_RING_G, CAESAR_N_RING_H, 
  CAESAR_N_RING_I, CAESAR_N_RING_J
}; 

static int caesar_det_offset[CAESAR_RINGS] = {
  0 , 
  CAESAR_N_RING_A, 
  CAESAR_N_RING_A+CAESAR_N_RING_B, 
  CAESAR_N_RING_A+CAESAR_N_RING_B+CAESAR_N_RING_C, 
  CAESAR_N_RING_A+CAESAR_N_RING_B+CAESAR_N_RING_C+CAESAR_N_RING_D, 
  CAESAR_N_RING_A+CAESAR_N_RING_B+CAESAR_N_RING_C+CAESAR_N_RING_D+CAESAR_N_RING_E, 
  CAESAR_N_RING_A+CAESAR_N_RING_B+CAESAR_N_RING_C+CAESAR_N_RING_D+
  CAESAR_N_RING_E+CAESAR_N_RING_F, 
  CAESAR_N_RING_A+CAESAR_N_RING_B+CAESAR_N_RING_C+CAESAR_N_RING_D+
  CAESAR_N_RING_E+CAESAR_N_RING_F+CAESAR_N_RING_G, 
  CAESAR_N_RING_A+CAESAR_N_RING_B+CAESAR_N_RING_C+CAESAR_N_RING_D+
  CAESAR_N_RING_E+CAESAR_N_RING_F+CAESAR_N_RING_G+CAESAR_N_RING_H, 
  CAESAR_N_RING_A+CAESAR_N_RING_B+CAESAR_N_RING_C+CAESAR_N_RING_D+
  CAESAR_N_RING_E+CAESAR_N_RING_F+CAESAR_N_RING_G+CAESAR_N_RING_H+CAESAR_N_RING_I
}; 


// Raw caesar components
namespace raw {

  // Special class to hold the mappings from vsn -> ring
  class caesar_detector_map
  {
  private:
    pmap_t the_map;

  public:
    caesar_detector_map()
    {
      // Read in mappings. They are "hard coded", so a re-compile
      // is needed if one wants to change them.
      // n.b. Here I do not allow for mapping differences between
      // energy and time branches. If at some point in the future
      // separation is needed it wil have to be added.
#include "caesar_map.hh" //\file that specifies {vsn, ch} -> {ring, det}
    };

    short ring(short vsn, short ch)
    {
      pair_t p_vsn(vsn, ch);
      pair_t p_ring = the_map[p_vsn];
      return short(p_ring.first);
    }

    short ch(short vsn, short ch)
    {
      pair_t p_vsn(vsn, ch);
      pair_t p_ring = the_map[p_vsn];
      return short(p_ring.second);
    }
  };

  // Raw FERA module
  class fera
  {
  public:
    short eraw[FERA_MAX_VSN][FERA_N_PER_VSN];
    short traw[FERA_MAX_VSN][FERA_N_PER_VSN];

    void reset();
  };

  // Raw CAESAR rings
  class caesar_ring10
  {
  public:
    short eraw[10];
    short traw[10];

    void reset();
  };

  class caesar_ring14
  {
  public:
    short eraw[14];
    short traw[14];

    void reset();
  };

  class caesar_ring24
  {
  public:
    short eraw[24];
    short traw[24];

    void reset();
  };

  // All of CAESAR
  class caesar: public detector
  {
  private:
    void insert_ring(short edata, short tdata, short vsn, short ch);

  public:
    short trigbit;
    short evtlength;
    short e_hit;
    short t_hit;
    fera vsn;
    caesar_ring10 ring_a; //\0
    caesar_ring14 ring_b; //\1
    caesar_ring24 ring_c; //\2
    caesar_ring24 ring_d; //\3
    caesar_ring24 ring_e; //\4
    caesar_ring24 ring_f; //\5
    caesar_ring24 ring_g; //\6
    caesar_ring24 ring_h; //\7
    caesar_ring14 ring_i; //\8
    caesar_ring10 ring_j; //\9

  public:
    void reset();
    void unpack(unsigned short* pC);


    // for conversion of ring number -> 'name'
    caesar_ring10& get_ring10(int nring);
    caesar_ring14& get_ring14(int nring);
    caesar_ring24& get_ring24(int nring);

    // functions which allow us to get ring values by specifying a number
    double get_eraw(int nring, int ndet);
    double get_traw(int nring, int ndet);

  };

}

namespace var {

  // ring variables
  class caesar_ring10
  {
  public:
    int neighbor_ring[10][CAESAR_MAX_NEIGHBORS];
    int neighbor_det [10][CAESAR_MAX_NEIGHBORS];

    double evar[10][__CAESAR_ECAL_ORDER+1];
    double tvar[10][__CAESAR_TCAL_ORDER+1];
    double doppler[10];

    double t_sl1[10];
    double t_sl2[10];
    double t_xoff[10];

    double pos_x[10];
    double pos_y[10];
    double pos_z[10];

    void set_posn(int ndet, double xpos, double ypos, double zpos) {
      if(ndet < 10 && ndet >=0) {
	pos_x[ndet] = xpos;
	pos_y[ndet] = ypos;
	pos_z[ndet] = zpos;
      }
      else {
	std::cerr << "Invalid detector number "<<ndet<<" specified for set_pos.\n\n";
      }
    }
  };

  class caesar_ring14
  {
  public:
    int neighbor_ring[14][CAESAR_MAX_NEIGHBORS];
    int neighbor_det [14][CAESAR_MAX_NEIGHBORS];

    double evar[14][__CAESAR_ECAL_ORDER+1];
    double tvar[14][__CAESAR_TCAL_ORDER+1];
    double doppler[14];

    double t_sl1[14];
    double t_sl2[14];
    double t_xoff[14];

    double pos_x[14];
    double pos_y[14];
    double pos_z[14];

    void set_posn(int ndet, double xpos, double ypos, double zpos) {
      if(ndet < 14 && ndet >=0) {
	pos_x[ndet] = xpos;
	pos_y[ndet] = ypos;
	pos_z[ndet] = zpos;
      }
      else {
	std::cerr << "Invalid detector number "<<ndet<<" specified for set_pos.\n\n";
      }
    }
  };

  class caesar_ring24
  {
  public:
    int neighbor_ring[24][CAESAR_MAX_NEIGHBORS];
    int neighbor_det [24][CAESAR_MAX_NEIGHBORS];

    double evar[24][__CAESAR_ECAL_ORDER+1];
    double tvar[24][__CAESAR_TCAL_ORDER+1];
    double doppler[24];

    double t_sl1[24];
    double t_sl2[24];
    double t_xoff[24];

    double pos_x[24];
    double pos_y[24];
    double pos_z[24];

    void set_posn(int ndet, double xpos, double ypos, double zpos) {
      if(ndet < 24 && ndet >=0) {
	pos_x[ndet] = xpos;
	pos_y[ndet] = ypos;
	pos_z[ndet] = zpos;
      }
      else {
	std::cerr << "Invalid detector number "<<ndet<<" specified for set_posn.\n\n";
      }
    }
  };

  // addback
  class caesar_addback
  {
  public:
    double n1_offset;
  };

  // target
  class caesar_target
  {
  private:
    // beam beta is made private so that caesar can only access
    // it through set_beam_beta() which also calls calc_dop_coeff()
    double beam_beta;
    // same thing for target positions now
    double x; //\target position
    double y;
    double z;

  public:
    void set_beta(double b) {
      beam_beta = b;
    }
    double get_beta() {
      return beam_beta;
    }
    void set_x(double _x) {
      x = _x;
    }
    double get_x() {
      return x;
    }
    void set_y(double _y) {
      y = _y;
    }
    double get_y() {
      return y;
    }
    void set_z(double _z) {
      z = _z;
    }
    double get_z() {
      return z;
    }
  };

  // all of caesar
  class caesar
  {
  private:
    void calc_dop_coeff();

  public:
    caesar_ring10 ring_a; //\0
    caesar_ring14 ring_b; //\1
    caesar_ring24 ring_c; //\2
    caesar_ring24 ring_d; //\3
    caesar_ring24 ring_e; //\4
    caesar_ring24 ring_f; //\5
    caesar_ring24 ring_g; //\6
    caesar_ring24 ring_h; //\7
    caesar_ring14 ring_i; //\8
    caesar_ring10 ring_j; //\9

    caesar_target target;
    caesar_addback addback;

    double t_shift;
    double t_walk;
    double t_tilt;

    bool enable_walk_corr;   // 1 = enabled

    bool enable_time_gate;   // 1 = enabled
    double left_time_gate;   // if time condition not met this
    double right_time_gate;  // detector data is routed!! (CaesarCalculator)

    bool enable_en_gate;     // 1 = enabled
    double left_en_gate;     // if energy condition not met this
    double right_en_gate;    // detector data is routed!! (CaesarCalculator)

    bool use_angle;          // 1 = enabled. Geometry not taken from x,y,z 
                             // but angles theta, phi
 
    bool enable_ge_en_gate;  // 1 = enabled
    double left_ge_en_gate;  // if energy condition not met in HPGe this
    double right_ge_en_gate; // detector data is routed!! (CaesarCalculator)

    bool enable_timing_ref;  // 1 = enabled

    // Special coutour gate to see if each time and energy in a list fit the
    // conditions outlined by the gate. It is called a "dirk_gate" in order to
    // by consistent with spectcl_caesar.  The gate points can either be defined
    // manually (in a variables file), or if one is using ROOT, they can be set
    // from a TCutG using set_dirk_gate(TCutG*).

    gate2d_vector dirk_gate;

    caesar() {
#include "caesar_variables.hh"
    }

    void set_beam_beta(double beta);
    void set_target_posn(double x, double y, double z);
    void set_target_params(double x, double y, double z, double beta);

    // for conversion of ring number -> 'name'
    caesar_ring10& get_ring10(int nring);
    caesar_ring14& get_ring14(int nring);
    caesar_ring24& get_ring24(int nring);

    // for getting ring values with an int specification
    int get_neighbor_ring(int nring, int ndet, int nneigh);
    int get_neighbor_det (int nring, int ndet, int nneigh);

    double get_evar(int nring, int ndet, int order);
    double get_tvar(int nring, int ndet, int order);
    double get_doppler(int nring, int ndet);

    double get_t_sl1(int nring, int ndet);
    double get_t_sl2(int nring, int ndet);
    double get_t_xoff(int nring, int ndet);

    double get_pos_x(int nring, int ndet);
    double get_pos_y(int nring, int ndet);
    double get_pos_z(int nring, int ndet);

    void set_doppler(int nring, int ndet, double val);
  };

}


namespace cal {
  
  // Cal CAESAR rings
  class caesar_ring10_ab
  {
  public:
    double n0_ecal[10];
    double n0_edop[10];

    double n1_ecal[10];
    double n1_edop[10];

    double n2_ecal[10];
    double n2_edop[10];

    double ng_ecal[10]; //g for garbage
    double ng_edop[10];

    void reset();
  };

  class caesar_ring10
  {
  public:
    double ecal[10];
    double tcal[10];
    double edop[10];
    caesar_ring10_ab ab;

    void reset();
  };

  class caesar_ring14_ab
  {
  public:
    double n0_ecal[14];
    double n0_edop[14];

    double n1_ecal[14];
    double n1_edop[14];

    double n2_ecal[14];
    double n2_edop[14];

    double ng_ecal[14]; //g for garbage
    double ng_edop[14];

    void reset();
  };

  class caesar_ring14
  {
  public:
    double ecal[14];
    double tcal[14];
    double edop[14];
    caesar_ring14_ab ab;

    void reset();
  };

  class caesar_ring24_ab
  {
  public:
    double n0_ecal[24];
    double n0_edop[24];

    double n1_ecal[24];
    double n1_edop[24];

    double n2_ecal[24];
    double n2_edop[24];

    double ng_ecal[24]; //g for garbage
    double ng_edop[24];

    void reset();
  };

  class caesar_ring24
  {
  public:
    double ecal[24];
    double tcal[24];
    double edop[24];
    caesar_ring24_ab ab;

    void reset();
  };

  // hit detector (internal, not written to tree)
  class caesar_hit_det
  {
  public:
    int ring; //!
    int chn;  //!
  };

  // addback
  class caesar_addback
  {
  public:
    double etot;
    //
    // the tcal, ecal of the 1st hit detector
    // are put in here (satisfying all conditions
    // like Egate, Tgate, etc.).
    // This allows an easy to get 'gamma-like' matrix.
    double ecal;
    double edop;
    double tcal;

    double hitdet_n1[2]; // correlation for addback pairs
    double hitdet_n2[3]; // correlation for addback pairs

    void reset();
  };

  // all of caesar
  class caesar
  {
  private:
    // here we store all indices of hit detectors
    // CCaesarCalculator clears it after each event
    // 
    std::vector <caesar_hit_det> detlist;                     //!
    std::vector <caesar_hit_det>::iterator detlist_iter;      //!

    // some detectors might be thrown out
    // (bad timing condition etc.)
    // in the list we put the remaining good ones
    // Those are taken into account for Addback stuff
    //
    std::vector <caesar_hit_det> detlist_cal;                 //!
    std::vector <caesar_hit_det>::iterator detlist_cal_iter;  //!

    // for conversion of ring number -> 'name'
    caesar_ring10& get_ring10(int nring);
    caesar_ring14& get_ring14(int nring);
    caesar_ring24& get_ring24(int nring);

    // functions which allow us to get ring values by specifying a number
    double get_ecal(int nring, int ndet);
    double get_tcal(int nring, int ndet);
    double get_edop(int nring, int ndet);
    double get_ab_n0_ecal(int nring, int ndet);
    double get_ab_n0_edop(int nring, int ndet);
    double get_ab_n1_ecal(int nring, int ndet);
    double get_ab_n1_edop(int nring, int ndet);
    double get_ab_n2_ecal(int nring, int ndet);
    double get_ab_n2_edop(int nring, int ndet);
    double get_ab_ng_ecal(int nring, int ndet);
    double get_ab_ng_edop(int nring, int ndet);

    // functions which allow us to set ring values by specifying a number
    void set_ecal(int nring, int ndet, double val);
    void set_tcal(int nring, int ndet, double val);
    void set_edop(int nring, int ndet, double val);
    void set_ab_n0_ecal(int nring, int ndet, double val);
    void set_ab_n0_edop(int nring, int ndet, double val);
    void set_ab_n1_ecal(int nring, int ndet, double val);
    void set_ab_n1_edop(int nring, int ndet, double val);
    void set_ab_n2_ecal(int nring, int ndet, double val);
    void set_ab_n2_edop(int nring, int ndet, double val);
    void set_ab_ng_ecal(int nring, int ndet, double val);
    void set_ab_ng_edop(int nring, int ndet, double val);


  public:
    caesar_ring10 ring_a; //\0
    caesar_ring14 ring_b; //\1
    caesar_ring24 ring_c; //\2
    caesar_ring24 ring_d; //\3
    caesar_ring24 ring_e; //\4
    caesar_ring24 ring_f; //\5
    caesar_ring24 ring_g; //\6
    caesar_ring24 ring_h; //\7
    caesar_ring14 ring_i; //\8
    caesar_ring10 ring_j; //\9

    caesar_addback ab;

    double hitdet_raw[CAESAR_DETECTORS];
    double hitdet_cor[CAESAR_DETECTORS];
    double hit_raw;
    double hit_cor;

    caesar() { clear_detlists(); }
    void reset();
    void clear_detlists();

    // addback routines
    int  check_no_of_neighbors(int ring, int det, var::caesar& v);
    bool a_is_neighbor_from_b(int ring_a, int det_a,
			      int ring_b, int det_b,
			      var::caesar& v);
    void one_add_back(caesar_hit_det det, var::caesar& v);
    void two_add_back(caesar_hit_det det1, caesar_hit_det det2, var::caesar& v);
    void three_add_back(caesar_hit_det det1, 
     			caesar_hit_det det2, caesar_hit_det det3, var::caesar& v);
    //

    //     void calc_dop_coeff(var::caesar& v); // put into var::caesar now
    //     void build_all_cal_tables();

    void fill_detlist(raw::caesar* craw);
    void calibrate(raw::caesar* craw, var::caesar& cvar, double timing_ref = -1);
    void calibrate(raw::caesar* craw, var::caesar& cvar, raw::sweeper* sraw);
    void calculate(var::caesar& cvar, double timing_ref = -1);
    void calculate(var::caesar& cvar, raw::sweeper* sraw);
    void sort_hit_list();
    void route_data(int ring, int det); //, raw::caesar* craw);
  };
  
}




#endif
