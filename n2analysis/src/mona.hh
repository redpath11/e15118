#ifndef __HAVE_MONA_RAWS_HH
#define __HAVE_MONA_RAWS_HH

#include "mona_packets.hh"
#include "mona_definitions.hh"
#include "detector.hh"
#include <vector>
#include <cmath>

#define __LEFT  = 0
#define __RIGHT = 1


struct mona_pmtmap
{
  short wall;
  short bar;
  bool  lr;
};


namespace raw {

  class mona_trigger
  {
  public:
    short monapattern;
    short monahits;
//    short monacount_pattern[2];
    short monacount_pattern[3];// changed b/c loop in mona.cc line 18 expects 3 elements
    short monatimestamp[4];

    short lisapattern;
    short lisahits;
//    short lisacount_pattern[2];
    short lisacount_pattern[3];// changed b/c loop in mona.cc line 24 expects 3 elements
    short lisatimestamp[4];
  public:
    void reset();
  };

  class mona_pmt
  {
  public:
    short traw[MONA_WALLS][WALL_BARS];
    short qraw[MONA_WALLS][WALL_BARS];

  public:
    void reset();
  };

  class mona: public detector
  {
  public:
    mona_trigger trigger;
    mona_pmt l;
    mona_pmt r;

  public:
    void reset();
    void unpack(unsigned short* pM);
    void legacy_unpack(unsigned short* pLeg);
    void unpack_monatrigger(unsigned short* pTrig);
    void unpack_lisatrigger(unsigned short* pTrig);
    void unpack_tdc(unsigned short* pTDC, bool LISA);
    void unpack_qdc(unsigned short* pQDC, bool LISA);

    mona_pmtmap map_tdc(unsigned short crate, 
			unsigned short slot, 
			unsigned short ch);

    mona_pmtmap map_qdc(unsigned short crate, 
			unsigned short slot, 
			unsigned short ch);

    mona_pmtmap map_lisatdc(unsigned short crate, 
			unsigned short slot, 
			unsigned short ch);

    mona_pmtmap map_lisaqdc(unsigned short crate, 
			unsigned short slot, 
			unsigned short ch);
  };

}

namespace var {

  class mona_pmt
  {
  public:
    double t_slope[MONA_WALLS][WALL_BARS];
    double t_offset[MONA_WALLS][WALL_BARS];
    double q_slope[MONA_WALLS][WALL_BARS];
    double q_offset[MONA_WALLS][WALL_BARS];
    double q_threshold[MONA_WALLS][WALL_BARS];
  };

  class mona_location
  {
  public:
    double x[MONA_WALLS][WALL_BARS];
    double y[MONA_WALLS][WALL_BARS];
    double z[MONA_WALLS][WALL_BARS];
    double ox[MONA_WALLS][WALL_BARS];
    double oy[MONA_WALLS][WALL_BARS];
    double oz[MONA_WALLS][WALL_BARS];

    double mag2(int i, int j) {
      return (x[i][j]*x[i][j] + y[i][j]*y[i][j] + z[i][j]*z[i][j]);
    }
    double o_mag2(int i, int j) {
      return (ox[i][j]*x[i][j] + oy[i][j]*y[i][j] + oz[i][j]*z[i][j]);
    }
  };

  class mona
  {
  public:
    mona_pmt l;
    mona_pmt r;

    double xpos_slope[MONA_WALLS][WALL_BARS];
    double xpos_offset[MONA_WALLS][WALL_BARS];
    double tmean_offset[MONA_WALLS][WALL_BARS];
    mona_location location;
    double mona_tmean_offset;
    double lisa1_tmean_offset;
    double lisa2_tmean_offset;
    double nwindow_low;
    double nwindow_high;
    short sort_param;

  public:
    mona(){
#include "mona_variables.hh"
    }
  };

}

namespace monatemp {
  struct hit
  {
    double x;
    double y;
    double z;
    double rho;
    double phi;
    double theta;
    double t;
    double v;
    double ke;
    double q;
    void reset() {
      x = -1; y = -1; z = -1;
      rho = -1; phi = -1; theta = -1;
      t = -1; v = -1; ke = -1; q = -1;
    }
    double mag2() {
      return x*x + y*y + z*z;
    }
    double mag() {
      return sqrt(x*x + y*y + z*z);
    }
  };

  struct time_compare
  {
    bool operator() (monatemp::hit h1, monatemp::hit h2) {
      return (h1.t< h2.t);
    }
  };

  struct velocity_compare
  {
    bool operator() (monatemp::hit h1, monatemp::hit h2) {

      return (h1.v >h2.v);
    }
  };
}


namespace cal {

  class mona_pmt
  {
  public:
    double tcal[MONA_WALLS][WALL_BARS];
    double qcal[MONA_WALLS][WALL_BARS];

  public:
    void reset();
    void calibrate(raw::mona_pmt& rw, var::mona_pmt& v);
  };

  class mona_hit
  {
  public:
    double x[MONA_HITS];
    double y[MONA_HITS];
    double z[MONA_HITS];
    double rho[MONA_HITS];
    double phi[MONA_HITS];
    double theta[MONA_HITS];
    double t[MONA_HITS];
    double v[MONA_HITS];
    double ke[MONA_HITS];
    double q[MONA_HITS];

  public:
    void reset();
    void fill(int i, monatemp::hit& h);
  };

  class mona
  {
  private:
    void fill_hit(monatemp::hit& h);
    monatemp::hit calculate_hit(int i, int j,
				var::mona_location& location);

  public:
    int mult;
    mona_pmt l;
    mona_pmt r;
    double xpos[MONA_WALLS][WALL_BARS];
    double tmean[MONA_WALLS][WALL_BARS];
    double qmean[MONA_WALLS][WALL_BARS];
    mona_hit hit;
    double x;
    double y;
    double z;
    double rho;
    double phi;
    double theta;
    double t;
    double v;
    double ke;
    double q;

  public:
    void reset();
    void calibrate(raw::mona* rw, var::mona& v);
  };

}



#endif
