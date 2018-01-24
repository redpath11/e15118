#ifndef __HAVE_MONA_VARIABLES
#define __HAVE_MONA_VARIABLES

#include "MoNA_QDCfittedSLOOFF.txt"
#include "LISA_QDCfittedSLOOFF.txt"
#include "MoNA_QDCfittedTHRE.txt"
#include "LISA_QDCfittedTHRE.txt"
//#include "LISA_QDCfittedTHRE_LOW.txt"
#include "mona_locations.hh"
#include "lisa_locations.hh"
/* calibations used online
#include "tcal_mona_output.txt"
#include "tcal_lisa_output.txt"
#include "xpos_mona_output.txt"
#include "xpos_lisa_output.txt"
*/

/* calibrations from HOPE */
#include "HOPE_tcal_mona_output.txt"
#include "HOPE_tcal_lisa_output.txt"
#include "HOPE_xpos_mona_output.txt"
#include "HOPE_xpos_lisa_output.txt"

// THR try different xpos calibration for layer N
//#include "LayerN_xpos_q8_output.txt"
//#include "xpos_lisa_output.txt"

#include "tmean_offsets.h"
//#include "HOPE_tmean_offsets.h"

/* Global offsets used in first round of analysis*/
//  mona_tmean_offset = 386.107;
  /*  F-27 */
  // adjusted 28 Nov 2017 to account for survey offsets
  mona_tmean_offset  = 453.107-1.;//THR 3/15/2016 set to make F-27 velocity physical
  lisa1_tmean_offset = 443.5-1.;//THR 4/10/2017
  lisa2_tmean_offset = 442.5-1.;//THR 11/11/2016
  
  /* Ne-29 
  mona_tmean_offset  = 453.107-0.4232;//THR 3/15/2016 set to make F-27 velocity physical
  lisa1_tmean_offset = 443.5-0.4232;//THR 4/10/2017
  lisa2_tmean_offset = 442.5-0.4232;//THR 11/11/2016
//  lisa1_tmean_offset = 386.107+23.14;//23.14 added by ANK 8/24/15
//  lisa2_tmean_offset = 386.107+23.14;//23.14 added by ANK 8/24/15
*/

/* Set to zero to check HOPE tmean offsets 
  mona_tmean_offset = 0.;
  lisa1_tmean_offset = 0.;
  lisa2_tmean_offset = 0.;
*/

/* HOPE global tmean offsets F-27 
  mona_tmean_offset = 451.819905;
  lisa1_tmean_offset = 428.219905;
  lisa2_tmean_offset = 427.219905;
*/

  nwindow_low  = 50;
  nwindow_high = 1e6;
  sort_param   = 0;    // time sorting (anything other than 2 is time sort;
                       // 2 is velocity sort)

#endif
