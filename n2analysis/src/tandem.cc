#include "tandem.hh"
#include "utils.hh"
#include "sweeper_definitions.hh" //\defines constants like C, AMU_MASS, etc.
#include <cmath>

//-------------------------------------------//
// class tandem

// cal
void
cal::tandem::reset()
{
  tof_vrel = -1;
  vrel     = -1;
  angle    = -1;
  edecay   = -1;
};

void
cal::tandem::calculate(cal::sweeper* sweeper,
		       cal::mona   * mona,
		       var::sweeper& svar)
{

  if(is_valid(mona->v) && is_valid(sweeper->v)) {
    tof_vrel = mona->v - sweeper->v;
  }

  static int warned = 0;
  if(svar.mass<= 0)
    {
      if(warned == 0) {
	fprintf(stderr,
		"Aborting tandem calculation, "
		"please set sweeper->mass to a value >0\n\n");
	++warned;
      }
      return;
    }


  if(is_valid(mona->v) &&
     is_valid(mona->x) && is_valid(mona->y) && is_valid(mona->z) &&
     is_valid(sweeper->itrack.tx) && is_valid(sweeper->itrack.ty) &&
     is_valid(sweeper->itrack.de))
    {
      // fragment
      double f_betagamma0 = (svar.brho / 3.107) * svar.charge / svar.mass;
      double f_gamma0 = sqrt(f_betagamma0 * f_betagamma0 + 1);
      double f_ke0 = AMU_MASS * (f_gamma0 - 1);

      double f_ke = (1 + sweeper->itrack.de) * f_ke0 + svar.target_eloss; //\MeV/u
      double f_gamma = (f_ke / AMU_MASS) + 1;
      double f_beta = 1 - 1 / (f_gamma*f_gamma); //it is beta squared.
      double f_vel = C * sqrt(f_beta); //cm/ns

      double f_z = 100; //\arbitrary "track" distance
      double f_x = f_z * tan(sweeper->itrack.tx/1000);
      double f_y = f_z * tan(sweeper->itrack.ty/1000);

      double f_momentum = svar.mass * sqrt(f_beta) * f_gamma;
      double f_energy   = svar.mass * f_gamma; //\total energy

      // neutron
      double n_gamma = 1 / sqrt(1 - (mona->v/C)*(mona->v/C));
      double n_beta  = 1 - 1 / (n_gamma*n_gamma);

      double n_momentum = (N_MASS / AMU_MASS) * sqrt(n_beta) * n_gamma;
      double n_energy   = (N_MASS / AMU_MASS) * n_gamma;

      // both
      double f_n_sum = f_x * mona->x + f_y * mona->y + f_z * mona->z;
      double f_n_product = (sqrt(mona->x*mona->x + mona->y*mona->y + mona->z*mona->z) *
			    sqrt(f_x*f_x + f_y*f_y + f_z*f_z));

      double f_n_costh = f_n_sum / f_n_product;
      double f_n_energy = (svar.mass*svar.mass + (N_MASS/AMU_MASS)*(N_MASS/AMU_MASS) +
			   2*(f_energy*n_energy - (f_momentum*n_momentum * f_n_costh)));

      // parameters
      vrel = mona->v - f_vel;
      angle = acos(f_n_sum / f_n_product); //\radians
      edecay = sqrt(f_n_energy) - N_MASS/AMU_MASS - svar.mass; //\amu
      edecay *= AMU_MASS; //\MeV
    }
};
