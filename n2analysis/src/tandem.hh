#ifndef __HAVE_TANDEM_HH
#define __HAVE_TANDEM_HH

#include "sweeper.hh"
#include "mona.hh"


//---------------------------------------//
// cals

namespace cal {

  class tandem
  {
  public:
    double tof_vrel;
    double vrel;
    double angle;
    double edecay;

  public:
    void reset();
    void calculate(cal::sweeper* scal,
		   cal::mona   * mcal,
		   var::sweeper& svar);
  };

}



#endif
