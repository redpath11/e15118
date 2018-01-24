/* "Cleaned up" version of sweeper_variables.hh THR 6/14/2016
 * The previous version is saved as bkup_sweeper_variables.hh */

#ifndef __HAVE_SWEEPER_VARIABLES
#define __HAVE_SWEEPER_VARIABLES

/* NOTE: there are two separate sets of calibration parameters
 * part 1 (runs 1038 - 1123 BEFORE the focal plane box was
 * vented to attempt repairs on the CRDCS
 * part 2 (runs 1125 - 1179) AFTER
 *
 * There are separate pedestal values and CRDC calibrations
 * for these two sets of runs.
*/

/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! SET FOR PART 2 !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */

/* FP CRDC parameters */

for(int i=0; i< FPCRDC_PADS; ++i) {
  crdc1.pad.ped[i] = 0.0;
  crdc2.pad.ped[i] = 0.0;
  crdc1.pad.slope[i] = 1.0;
  crdc2.pad.slope[i] = 1.0;
  crdc1.pad.offset[i] = 0.0;
  crdc2.pad.offset[i] = 0.0;
  crdc1.pad.f_sigma[i] = 0.0;
  crdc2.pad.f_sigma[i] = 0.0;
  crdc1.pad.f_scale[i] = 0.0;
  crdc2.pad.f_scale[i] = 0.0;
}

/* Put resuts from gainmatching here */
// Set reference pads

/* part 1 
crdc1.pad.ref_pad = 70;
crdc2.pad.ref_pad = 84;
*/

/* part 2 */
crdc1.pad.ref_pad = 82;
crdc2.pad.ref_pad = 84;


// Includes for pedestal values
// from 24 June 2016 pedestal runs
/*
#include "crdc1_ped_values1_e15118.txt"
//#include "crdc1_ped_valuesmp_e15118.txt"// pedestals from largest sample
#include "crdc2_ped_values1_e15118.txt"
*/


/* from 5 July 2016 run */
#include "crdc1_ped_values2_e15118.txt"
#include "crdc2_ped_values2_e15118.txt"


/*
// Includes for gainmatch results - slopes from 3043 csweep
#include "crdc1_gainmatch_slopes1.txt"
//#include "crdc1_gainmatch_slopespm.txt"// slopes from largest sample
#include "crdc2_gainmatch_slopes1.txt"
*/

/**/
// Includes for gainmatch results - from 1125 production after venting
#include "crdc1_gainmatch_slopes2.txt"
#include "crdc2_gainmatch_slopes2.txt"

//#include "crdc1_gainmatch_offset2.txt"





// Includes for gainmatch results - offsets
//#include "crdc1_gainmatch_offset.txt"
//#include "crdc2_gainmatch_offset.txt"

// Set number of bad pads
//crdc1.badpads = 85;//THR acceptance cuts part 1
crdc1.badpads = 90;//THR badpads part 2
//crdc1.badpads = 0;
// Initialize badpad array
for(int i=0; i< FPCRDC_PADS; ++i) {
  crdc1.badpad[i] = -1;
}
/*
// CRDC 1 badpads part 1: 7 Sept 2016 THR
for(int i=0; i<56; i++)
{ crdc1.badpad[i] = i; }
for(int i=99; i< FPCRDC_PADS; i++)
{ crdc1.badpad[i-43] = i; }
*/

/**/
// CRDC 1 bad pads part 2: 12 Oct 2016 THR
for(int i=0;i<53;i++)
{ crdc1.badpad[i] = i; }
crdc1.badpad[53]=54;
crdc1.badpad[54]=56;
crdc1.badpad[55]=63;
crdc1.badpad[56]=64;
for(int i=95;i<128;i++)
{ crdc1.badpad[i-38] = i; }



/* FROM ONLINE WORK

crdc1.badpad[40] = 40;
crdc1.badpad[41] = 41;
crdc1.badpad[42] = 42;
crdc1.badpad[43] = 43;
crdc1.badpad[44] = 44;


crdc1.badpad[0] = 54;
crdc1.badpad[1] = 58;
crdc1.badpad[2] = 60;
crdc1.badpad[3] = 63;
crdc1.badpad[4] = 64;
crdc1.badpad[5] = 95;

*/


// Set badpads
/* THR August 2016 -ONLINE
crdc1.badpad[0] = 54;
crdc1.badpad[1] = 58;
crdc1.badpad[2] = 60;
crdc1.badpad[3] = 61;
crdc1.badpad[4] = 63;
crdc1.badpad[5] = 74;
crdc1.badpad[6] = 78;
crdc1.badpad[7] = 79;
crdc1.badpad[8] = 88;
crdc1.badpad[9] = 89;
crdc1.badpad[10]= 94;
crdc1.badpad[11]= 95;
*/


/* FROM ONLINE WORK
crdc1.badpad[0] = 65;
crdc1.badpad[1] = 62; 
crdc1.badpad[2] = 70; 
crdc1.badpad[3] = 80;
crdc1.badpad[4] = 81;
crdc1.badpad[5] = 54;
crdc1.badpad[6] = 53;
crdc1.badpad[7] = 52;
crdc1.badpad[8] = 50;
crdc1.badpad[9] = 49;
crdc1.badpad[10] = 48;
crdc1.badpad[11] = 47;
crdc1.badpad[12] = 46;
*/


crdc1.x_slope  = 2.54;

/* Part 1 */
crdc1.x_offset = -177.87;
crdc1.y_offset = 104.04;
crdc1.y_slope = -0.07469;


/* Part 2 - same as part 1 */


// CRDC 1 x & y slopes & offsets - ONLINE
/*
crdc2.x_offset = 186.81;
crdc2.y_offset = 126.83;
crdc2.y_slope = -0.07389;
*/



//crdc1.x_offset = 0.0;
//crdc1.x_offset = -178.8;//ANK 8/26/2015
//crdc1.y_slope = 1.0; // 0.065
//crdc1.y_slope = -0.200; // 0.065
//crdc1.y_offset = 0.0;
//crdc1.y_offset = 117.1;//ANK 8/26/2015
crdc1.z = 1.725; // In meters, JKS, 9 July 2012
crdc1.method = 2;// changed back to 2 on 7/22/2016
crdc1.fit_width = 10;
crdc1.gravity_width = 20;

// Set number of badpads
//crdc2.badpads = 14;//part 1
crdc2.badpads = 24;//part 2
// Initialize badpad array
for(int i=0; i< FPCRDC_PADS; ++i) {
  crdc2.badpad[i] = -1;
}

/* part 1
for(int i=0; i<13; i++)
{ crdc2.badpad[i] = i; }

crdc2.badpad[13]=24;
*/

/* part 2 */
for(int i=0;i<18;i++)
{ crdc2.badpad[i] = i; }
crdc2.badpad[18] = 23;
crdc2.badpad[19] = 24;
crdc2.badpad[20] = 30;
crdc2.badpad[21] = 31;
crdc2.badpad[22] = 32;
crdc2.badpad[23] = 127;


/* FROM ONLINE WORK
// Set badpads
crdc2.badpad[0] = 0;
crdc2.badpad[1] = 1;
crdc2.badpad[2] = 2;
crdc2.badpad[3] = 3;
crdc2.badpad[4] = 4;
crdc2.badpad[5] = 5;
crdc2.badpad[6] = 6;
crdc2.badpad[7] = 7;
crdc2.badpad[8] = 8;
crdc2.badpad[9] = 9;
crdc2.badpad[10] = 10;
crdc2.badpad[11] = 11;
crdc2.badpad[12] = 12;
crdc2.badpad[13] = 13;
crdc2.badpad[14] = 14;
crdc2.badpad[15] = 15;
crdc2.badpad[16] = 16;
crdc2.badpad[17] = 24;
crdc2.badpad[18] = 31;
crdc2.badpad[19] = 126;
crdc2.badpad[20] = 127;


crdc2.badpad[0] = 24;
crdc2.badpad[1] = 31;
crdc2.badpad[2] = 80;
crdc2.badpad[3] = 96;
crdc2.badpad[4] = 111;

*/

/* FROM ONLINE WORK
crdc2.badpad[0] = 17;
crdc2.badpad[1] = 18;
crdc2.badpad[2] = 19;
crdc2.badpad[3] = 20;
crdc2.badpad[4] = 21;
crdc2.badpad[5] = 24;
crdc2.badpad[6] = 48;
crdc2.badpad[7] = 49;
crdc2.badpad[8] = 50;
crdc2.badpad[9] = 51;
crdc2.badpad[10] = 52;
crdc2.badpad[11] = 54;
crdc2.badpad[12] = 57;
crdc2.badpad[13] = 58;
crdc2.badpad[14] = 59;
crdc2.badpad[15] = 60;
crdc2.badpad[16] = 63;
crdc2.badpad[17] = 73;
crdc2.badpad[18] = 78;
crdc2.badpad[19] = 79;
crdc2.badpad[20] = 89;
crdc2.badpad[21] = 121;
crdc2.badpad[22] = 77;
crdc2.badpad[23] = 80;
*/

// CRDC 2 x & y slopes & offsets
crdc2.x_slope  = -2.54;
/* Part 1 
crdc2.x_offset = 186.968;
crdc2.y_slope = -0.074139;// from r3016 - 6/30/2016
crdc2.y_offset = 127.35;// from r3016 - 6/30/2016
*/


/* Part 2 */
crdc2.x_offset = 186.896;
crdc2.y_slope = -0.07371;// from r3161 - 10/12/2016
//crdc2.y_offset = 124.700;// from r3161 - 10/12/2016
crdc2.y_offset = 124.700-18.99;// ignore offset from mask, make the beam y=0


//crdc2.x_offset = 0.0;
//crdc2.x_offset = 187.0;
//crdc2.y_slope = 1.0;//-0.065*0.34;
//crdc2.y_slope = -0.200;//-0.065*0.34;
//crdc2.y_offset = 0.0;//THR: 2/7/2016
//crdc2.y_offset = 124.4;//THR: 2/7/2016
crdc2.z = crdc1.z+1.588; //in meters, TR 29 June 2016
crdc2.method = 2;
crdc2.fit_width = 10;
crdc2.gravity_width = 20;

/* END FP CRDC parameters */

/* TCRDC parameters */
// TCRDC1 pedestals were here - see bkup_sweeper_variables.hh

for(int i=0;i<63;i++)
  {tcrdc1.pad.ped[i]=-1;}


// tcrdc2 pedestals were here - see bkup_sweeper_variables.hh

for(int i=0;i<63;i++)
  {tcrdc2.pad.ped[i]=-1;}

for(int i=0; i< TCRDC_PADS; ++i) {
  tcrdc1.pad.slope[i] = 1;
  tcrdc2.pad.slope[i] = 1;

  tcrdc1.pad.offset[i] = 0;
  tcrdc2.pad.offset[i] = 0;
  tcrdc1.pad.f_sigma[i] = 0;
  tcrdc2.pad.f_sigma[i] = 0;
  tcrdc1.pad.f_scale[i] = 0;
  tcrdc2.pad.f_scale[i] = 0;
}
tcrdc1.pad.ref_pad = 50;
tcrdc2.pad.ref_pad = 50;


tcrdc1.badpads = 0;
for(int i=0; i< TCRDC_PADS; ++i) {
  tcrdc1.badpad[i] = -1;
}
tcrdc1.x_slope  = 2.54;
tcrdc1.x_offset = -112.217;
tcrdc1.y_slope = -0.0331225;
tcrdc1.y_offset = 34.4605;
tcrdc1.z = -4.776;
tcrdc1.method = 1;
tcrdc1.fit_width = 10;
tcrdc1.gravity_width = 20;

tcrdc2.badpads = 0;
for(int i=0; i< TCRDC_PADS; ++i) {
  tcrdc2.badpad[i] = -1;
}
tcrdc2.x_slope  = -2.54;
tcrdc2.x_offset = 116.1288;
tcrdc2.y_slope = -0.034431;
tcrdc2.y_offset = 24.6765;
tcrdc2.z = -2.502;
tcrdc2.method = 1;
tcrdc2.fit_width = 10;
tcrdc2.gravity_width = 20;

tcrdc1.corr_slope  = 1;
tcrdc1.corr_offset = 0;
tcrdc2.corr_slope  = 1.3553;
tcrdc2.corr_offset = 6.0851;

/* END TCRDC parameters */

/* IC parameters */

for(int i=0; i< IC_CHANNELS; ++i) {
  ic.slope[i] = 1;
  ic.offset[i] = 0;
  for(unsigned int j=0; j< IC_CORR_ORDER; ++j)
    ic.corr[i][j] = 1.;
  ic.corr_scale[i] = 12;
}

// include results for offline gainmatching 
// and x position correction THR 11/14/2016
#include"ic_gainmatch_slopes.txt"
#include"r1063_ic_xcorr.txt"

// CHECK THIS, are these all still bad? ... yes THR 11/8/2016
// slopes and offsets for bad chs ... will zero these channels
/**/
ic.slope[0] = 0;
ic.slope[4] = 0;
ic.slope[7] = 0;
ic.slope[15] = 0;
ic.offset[0] = -1;
ic.offset[4] = -1;
ic.offset[7] = -1;
ic.offset[15] = -1;


/* online IC gainmatch results
ic.slope[1] = 0.708464;
ic.slope[2] = 0.964247;
ic.slope[3] = 0.809773;
ic.slope[5] = 0.814522;
ic.slope[6] = 1.01131;
ic.slope[8] = 1.00138;
ic.slope[9] = 1.02044;
ic.slope[10] = 0.964371;
ic.slope[11] = 1.13057;
ic.slope[12] = 0.931663;
ic.slope[13] = 0.99124;
ic.slope[14] = 0.973563;
*/




ic.de_slope = 1;
ic.de_offset = 0;

// Include results of x position correction - 3rd order in x
//#include"r3043_ic_xcorr.txt"

/* END IC parameters */

/* Thin parameters */
thin.z = crdc2.z+0.902; //THR 20 June 2016
for(int i=0; i< 4; ++i) {
  thin.t_slope[i] = 0.0625;// TR, HL 18 August 2015
  thin.q_slope[i] = 1;
  thin.q_offset[i] = 0;
}

/* thin q gainmatch (online)
thin.q_slope[1]=0.879;
thin.q_slope[2]=1.214;
thin.q_slope[3]=1.209;
*/

// thin q and t gainmatch - THR 11/7/2016
// ref pmt = 3
thin.q_slope[0] = 0.698995;
thin.q_offset[0] = 72.4834;
thin.q_slope[1] = 0.424234;
thin.q_offset[1] = 175.016;
thin.q_slope[2] = 1.01571;
thin.q_offset[2] = 17.6865;

thin.t_offset[0] = -0.8;
thin.t_offset[1] = -1.0404;
thin.t_offset[2] = 2.6626;
thin.t_offset[3] = -0.598611;

/*
thin.t_offset[0] =  44.99;
thin.t_offset[1] = -23.36;
thin.t_offset[2] =  18.36;
thin.t_offset[3] = -20.76;
*/

/**/
for(unsigned int i=2; i< POSCORR_ORDER; ++i) {
  thin.corr[i] = 0;
}

// corrected against crdc2.x THR 11/11/2016
thin.required_pmts = 4;
thin.corr_scale = 1;
thin.corr_offset = 1;
thin.corr[0] = 416.091;
thin.corr[1] = -0.172968;
thin.corr[2] = -0.00697237;
thin.corr[3] = 1.13954e-5;
thin.corr[4] = 2.90084e-7;


//Thin online t gainmatching 08/24/2015 KES
/*
thin.t_offset[0] = 45.4202;
thin.t_offset[1] = 44.541;
thin.t_offset[2] = 51.027-2.52;
thin.t_offset[3] = 46.1034-0.684;

//Thin online q gainmatching 08/24/2015 KES
thin.q_slope[0] = 0.973259;
thin.q_offset[0] = -176.761;
thin.q_slope[1] = 1;
thin.q_offset[1] = 0.0203766;
thin.q_slope[2] = 0.966542;
thin.q_offset[2] = 105.869;
thin.q_slope[3] = 0.940968;
thin.q_offset[3] = 171.364;
*/

#ifdef __WITH_SEGTARG

#include "st_variables.hh"

/* Segmented Target Si Detectors

for(int i=0; i< 32; ++i) {
  segtargadc.slope[i]  =    1;
  segtargadc.offset[i] =    0;
}

// test on Feb 8 run: segtargadc.slope[15] = 0.008;


// Put slopes for calibrating anode signals here
segtargadc.slope[16] = 1;// D1 anode (first detector beam hits)
segtargadc.offset[16] =    0;

segtargadc.slope[23] = 1;// D2 anode
segtargadc.offset[23] =    0;

segtargadc.slope[26] = 1;// D3 anode
segtargadc.offset[16] =    0;

segtargadc.slope[31] = 1;// D4 anode (last detector beam hits)
segtargadc.offset[16] =    0;

 */

//for testing segtarg variables
//segtargadc.slope[21] = 23;//slope test, 15/21/15 HL
//segtargadc.offset[4] =11;//offset test, 15/21/15

/* END S.T. Si detector variables */

#endif

#ifdef __WITH_HODOSCOPE
hodo.z = thin.z+0.005; //JKS, 9 July 2012
for(int i=0; i< 25; ++i) {
  hodo.slope[i]  =    1;
  hodo.offset[i] =    0;
}
// THR: added slopes and offsets calculated by JB
// from calibration with Cs-137 4/14/2016
//#include "hodo_SlopesOffsets.txt"

// set thresholds to 50 adc units
for(int i=0;i<HODO_CH;i++)
{ hodo.thr[i]=50.; }

#else
thick.z = 5.052;
for(int i=0; i< 4; ++i) {
  thick.t_slope[i]  = 0.1;
  thick.q_slope[i]  =    1;
  thick.q_offset[i] =    0;
}

thick.t_offset[0] = -29.23;
thick.t_offset[1] = -19.80;
thick.t_offset[2] = -37.89;
thick.t_offset[3] = -18.65;

thick.required_pmts = 4;
thick.corr_scale = 1;
thick.corr_offset = 0;
for(unsigned int i=0; i< POSCORR_ORDER; ++i) {
  thick.corr[i] = 0;
}
#endif

pot.q_slope = 1;
pot.q_offset = 0;
pot.t_slope = 0.0625; //HL, TR 18 August 2015
pot.t_offset = -43.87 + 50.599;
pot.z = -1.04; //JKS, 9 July 2012
// pot.z = -1.006;// THR 26 January 2017

rf.t_slope = 0.0625; //HL, TR 18 August 2015
rf.t_offset = 0;
rf.z = 0;

a1900.t_slope = 0.0625; //HL, TR 18 August 2015
a1900.t_offset = -186.18-394.75;
a1900.z = -10.878;

tofcorr.rf.x      = 0;
tofcorr.rf.tx     = 0;
tofcorr.rf.x2     = 0;
tofcorr.rf.tx2    = 0;
tofcorr.rf.xtx    = 0;
tofcorr.a1900.x   = 0;
tofcorr.a1900.tx  = 0;
tofcorr.a1900.x2  = 0;
tofcorr.a1900.tx2 = 0;
tofcorr.a1900.xtx = 0;
tofcorr.pot.x     = 0;
tofcorr.pot.tx    = 0;
tofcorr.pot.x2    = 0;
tofcorr.pot.tx2   = 0;
tofcorr.pot.xtx   = 0;

itrack.z = 0;
itrack.tx_offset = 0;
itrack.ty_offset = 0;
//itrack.filename = "/user/e11506/maps/10_5780kG_9Li.imap"; //JKS, 9 July 2012
itrack.filename = "/projects/e15118/n2analysis/maps/z8a22_Hp9_7124_Bp3.445_order3_angle-0.3_pos0.50_DL1.64.imap";
ftrack.z = 0;
//ftrack.filename = "/user/e11506/maps/10_5780kG_9Li.map";  //JKS, 9 July 2012
ftrack.filename = "/projects/e1518/n2analysis/maps/z8a22_Hp9_7124_Bp3.445_order3_angle-0.3_pos0.50_DL1.64.map";
focus.z  = 1.8;
brho = 3.69; //THR, 22 July 2016
mass = 24; //THR, 22 July 2016
charge = 8; //THR, 22 July 2016
target_eloss = 0;

//spike rotation
tcrdc1.rotate_spikes = 0;
tcrdc2.rotate_spikes = 0;
tcrdc1.force_correlation = 0;
tcrdc2.force_correlation = 0;

// diamond detector
#ifdef __WITH_DIAMOND
for(unsigned short i=0; i< DIA_CH; ++i)
  {
    diamond.t_slope[i]  = 1;
    diamond.q_slope[i]  = 1;
    diamond.t_offset[i] = 0;
    diamond.q_offset[i] = 0;
  }
#endif

#endif
