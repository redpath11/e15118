#include "sweeper.hh"
#include "utils.hh"
#include <iostream>
#include <fstream>
#include <time.h>
#include <cmath>
#include "gsl_gaus_fit.h"
#include <gsl/gsl_poly.h>
using namespace std;

// Change to 1(0) to turn on(off) sweeper crdc debugging
#define __SWEEPER_DEBUG 0

// Maximum delta value for (t)crdc gain matching
#define __MAX_DELTA 5

//---------------------------------------------------------//
// class sweeper_vmetdc
void
raw::sweeper_vmetdc::unpack(unsigned short* p)
{
  unsigned short words = *(p-2) - 2;
  while (words > 0)
    {
    unsigned short ch, hit;
    ch = (*p)&0xFF;
    hit = (*p++)>>8;
    if (hit < 32)
      data[ch][hit] = *p++;
    else
      p++;
    if (hit == 0) raw[ch] = data[ch][0];
    if (hit > hits[ch]) hits[ch] = hit;
    words -= 2;
    }
};


void
raw::sweeper_vmetdc::reset()
{
	for(unsigned short i=0; i<32; i++)
		{
			raw[i] = -1;
			hits[i] = -1;
		for(unsigned short j=0; j<32; j++)
		data[i][j] = -1;
		}
}




//---------------------------------------------------------//
// class sweeper_trigger
void
raw::sweeper_trigger::reset()
{
  registr   = -1;
  sweeper   = -1;
  external1 = -1;
  external2 = -1;
  secondary = -1;
  pattern   = -1;
  for(unsigned short i=0; i< 4; ++i)
    timestamp[i] = -1;
};





void
raw::sweeper_trigger::unpack(unsigned short* pTrig)
{
//    Channel mapping:
//       ----------------------
//      | PARAMETER  | CHANNEL |
//       ----------------------
//      | sweeper    |    8    |
//      | external1  |    9    |
//      | external2  |    10   |
//      | secondary  |    11   |

  unsigned short words = (*(pTrig - 2))-2, ch;

  registr = *pTrig; ++pTrig;
  words--;
  while (words >0)
    {
      ch = ((*pTrig)&0xf000)>>12;
      switch(ch)
	{
	case 8:
	  sweeper = (*pTrig)&0xfff;
	  ++pTrig; --words; break;
	case 9:
	  external1 = (*pTrig)&0xfff;
	  ++pTrig; --words; break;
	case 10:
	  external2 = (*pTrig)&0xfff;
	  ++pTrig; --words; break;
	case 11:
	  secondary = (*pTrig)&0xfff;
	  ++pTrig; --words; break;
	default:
	  ++pTrig; --words; break;
	}
    }
};


//---------------------------------------------------------//
// sweeper::unpack_time_stamp

void
raw::sweeper::unpack_time_stamp(unsigned short* pTs)
{

//ANK: Event tag should be 5903, followed by the 16-bit trigger bit pattern and four 16-bit words of the timestamp

  unsigned short words = *(pTs-2) - 2;

  if (words!=5){
    cout << "ERROR: Timestamp has wrong size! Size = " << words << endl;

    return;
  }

  else
  {
    trigger.pattern = *pTs;//Grabbing the first 16-bit word which is the sweeper trigger bit pattern
    ++pTs;//Increment pointer to the timestamp words
      for(unsigned short i=0; i< 4; ++i)//Loop over the timestamp words
        {
        trigger.timestamp[i] = *pTs;
        ++pTs;
        }

  }

/*
  for(unsigned short i=0; i< words; ++i)
    {
      if(i< 4)
	{
	  trigger.timestamp[i] = *pTs;
	  ++pTs;
	}
      else if(i == 4)
	{
	  trigger.pattern = *pTs;
	  ++pTs;
	}
      else
	;
    }
*/
};

//---------------------------------------------------------//
// class sweeper_crdc

// raw
void
raw::sweeper_crdc::reset()
{
  anode = -1;
  tac = -1;
  sample_width = -1;
  for(unsigned short i=0; i< FPCRDC_PADS; ++i)
    {
      pad.nsamples[i] = -1;
      pad.raw[i] = -1;
#if(__UNPACK_SAMPLES)
      for(int j=0; j< FPCRDC_MAX_WIDTH; ++j)
	pad.sample[i][j] = -1;
#endif
    }
};

void
raw::sweeper_crdc_pads::integrate(std::vector< std::vector<short> >& data,
				  unsigned short sampleWidth,
				  unsigned short id)
{
  // integrate samples into pads (leave pedestal subtraction for later)
  if(sampleWidth >FPCRDC_MAX_WIDTH)
    {
      std::cerr << "\nsweeper_raw_crdc_pads::integrate passed a sample width "<<sampleWidth \
	   <<" which is too large. Bailing out\n";
      return;
    }
  for (int q=0; q< FPCRDC_PADS; ++q)
    {
      nsamples[q] = 0;
      raw[q] = 0;
      for (int s=0; s< sampleWidth; ++s)
	{
	  switch(id)
	    {
	    case 0:
	    // CRDC 1 - don't average over samples, take largest one - THR 17 August 2016
	    // normal treatment for CRDC 1 30 August 2016
	      if(data[q][s] != 0)// && data[q][s] > raw[q])
	      {
	        raw[q] += data[q][s];//
	        ++nsamples[q];
	      }
#if(__UNPACK_SAMPLES)
	      sample[q][s] = data[q][s];
#endif
	    break;

	    case 1:
	    // CRDC 2 - average over samples - THR 17 August 2016
	      if(data[q][s] != 0)
	      {
	        raw[q] += data[q][s];
	        ++nsamples[q];
#if(__UNPACK_SAMPLES)
		sample[q][s] = data[q][s];
#endif
	      }
	      break;

	    default:
	      cout << "Wrong device tag passed to raw::sweeper_crdc_pads::integrate ..." << endl;
	    break;
	    }
	}
      if(raw[q] == 0) raw[q] = -1;
    }
  // loop through pads again to normalize by the number of samples - THR 1 September 2016
  for (int qq=0; qq< FPCRDC_PADS; qq++)
    {
      if(nsamples[qq]!=0 && raw[qq]!=-1){ raw[qq] = raw[qq] / nsamples[qq];}
    }
  /* interchange raw[pad] contents for pads CRDC 1 56-63: THR 9 Sept 2016
  if(id==0)
  {
    int mirror = 63;
    int qq = 56;
    while (qq<mirror)
    {
      short tmp1 = raw[qq];
      short tmp2 = raw[mirror];

      raw[qq] = tmp2; raw[mirror] = tmp1;
      ++qq;
      --mirror;
    }
  }

 */

  /* interchange raw[pad] contents for pads CRDC 1 72-79: THR 9 Sept 2016
  if(id==0)
  {
    int mirror = 79;
    int qq = 72;
    while (qq<mirror)
    {
      short tmp1 = raw[qq];
      short tmp2 = raw[mirror];

      raw[qq] = tmp2; raw[mirror] = tmp1;
      ++qq;
      --mirror;
    }
  }
 */

};



void
raw::sweeper_crdc::unpack_raw_data(unsigned short* pCrdc, unsigned short id)
{  
  static unsigned long total=0, failed=0;
  unsigned short sample, channel, data[4], connector, previous_sample=0, ch;
  unsigned short m_threshold=0, m_sampleBegin=0, m_sampleWidth=0;

  static std::vector< std::vector<short> >
    m_data(FPCRDC_PADS, std::vector<short>(FPCRDC_MAX_WIDTH, 0));

  //Initialize m_data array
  for (int i=0; i< FPCRDC_PADS; ++i)
    {
      for (int j=0; j< FPCRDC_MAX_WIDTH; ++j)
	m_data[i][j] = 0;
    }
  
  bool mes1=true, mes2=true, mes3=true, mes4=true;
  unsigned short length = *pCrdc; ++pCrdc;
  unsigned short i = length-3;

  ++pCrdc; //\skip packet id

  m_threshold = *pCrdc; ++pCrdc;


  while (i > 0)
    {
      // if sixteenth bit is not 1
      if ((*pCrdc)>>15 != 1)
	{
	  fprintf(stderr, "CRDC data is corrupted!\n");
	  ++pCrdc; --i;
	  continue;
	} 
      else 
	{
	  sample = ((*pCrdc)&0x7FC0)>>6;
	  channel = (*pCrdc)&0x3F;
	  // Pads are staggered in Sweeper FP CRDCs
	  channel = channel - (channel%2)*2 + 1;
	  if (i == length-3) 
	    {
	      m_sampleBegin = sample;
	      previous_sample = sample;
	    }
	}
    ++pCrdc; --i;

    for (int ii=0; ii< 4; ++ii)
      data[ii] = 0;

    while ((*pCrdc)>>15 == 0)
      {
	connector = ((*pCrdc)&0x0C00)>>10;
	data[connector] = (*pCrdc)&0x3FF;
	++pCrdc; --i;
	if (i == 0) break;
      }

    if ((sample< m_sampleBegin || sample >m_sampleBegin + FPCRDC_MAX_WIDTH) && (data[0]!=0 && data[1]!=0)) 
      {
#if(__SWEEPER_DEBUG)	
//	  fprintf(stderr, " %d  %d  %d  %d \n",
//		  id+1, channel, sample, m_sampleBegin);// THR 31 August 2016
	  fprintf(stderr, "Warning in Crdc %d unpack: inconsistent sample number, ch %d: %d (first: %d \n",
		  id+1, channel, sample, m_sampleBegin);// THR 31 August 2016
#endif
	mes1 = false;
	continue;
      }

    if (sample < previous_sample)
      {
#if(__SWEEPER_DEBUG)
	  fprintf(stderr, "Warning in Crdc %d unpack: sample number lower than previous, ch %d: %d (previous: %d)\n",
		  id+1, channel, sample, previous_sample);// THR 1 Sept 2016
#endif
	mes2 = false;
	continue;
      }

    previous_sample = sample;

    for (int j=0; j<4; ++j)
      {
	ch = channel + j*64;

//      Special reordering for CRDC1 in Experiment 03038 (April 2005)
// 	Removing this portion of the code for simplicity, it can be 
// 	added back later if needed
// 	if (version == 1)
// 	  {
// 	    if (ch <= 31) ch = 95-ch;
// 	    else if (ch >= 32 && ch <= 63) ch = 159-ch;
// 	    else if (ch >= 64 && ch <= 95) ch = 95-ch;
// 	    else if (ch >= 96 && ch <= 127) ch = 159-ch;
// 	  }

	if (data[j] != 0 && ch < FPCRDC_PADS)
	  {
	    if (data[j] < m_threshold)
	      {
#if(__SWEEPER_DEBUG)
		  fprintf(stderr, "Warning in Crdc unpack: data lower than threshold: %d (threshold: %d)\n",
			  data[j], m_threshold);
#endif
		mes3 = false;
	      }
	    else 
	      {
		m_data[ch][sample-m_sampleBegin] = data[j];
	      }
	  } 
	else if (data[j] != 0 && ch >= FPCRDC_PADS) 
	  {
#if(__SWEEPER_DEBUG)
	      fprintf(stderr, "Warning in Crdc unpack: channel greater than limit: %d (limit: %d)\n",
		      ch, FPCRDC_PADS);
#endif
	    mes4 = false;
	  }
	if ((sample < m_sampleBegin || sample>m_sampleBegin + FPCRDC_MAX_WIDTH) && id==1 && data[j]!=0)
	  {
#if(__SWEEPER_DEBUG)	
	  fprintf(stderr, " %d  %d  %d  %d  %d  %d \n",
		  id+1, channel, ch, sample, m_sampleBegin, data[j]);// THR 31 August 2016
//	  fprintf(stderr, "Warning in Crdc %d unpack: inconsistent sample number, ch %d: %d (first: %d \n",
//		  id+1, channel, sample, m_sampleBegin);// THR 31 August 2016
#endif
          }
      }
    m_sampleWidth = sample - m_sampleBegin + 1;
    }

  // integrate samples into pads
  sample_width = m_sampleWidth;
  pad.integrate(m_data, m_sampleWidth,id);
  // force CRDC 1 sample_width = 1 so we can use same
  // calibrate function for both detectors THR 8/22/2016
  // if(id==0){sample_width=1;}// cout << "id=0; sample_width set to 1" << endl;}


  if (!mes1 || !mes2 || !mes3 || !mes4) failed++;
  total++;

  if (failed == 1000)
    {
#if(__SWEEPER_DEBUG)
	fprintf(stderr, "Errors in Crdc unpackings: %g%%\n", 1.0*failed/total*100);
#endif
      total = 0;

      failed = 0;
    }
};


void
raw::sweeper_crdc::unpack(unsigned short* pCrdc,unsigned short id)
{
  unsigned short nWords = *(pCrdc-3) - 3; //\-3 b/c of ID word

  while(nWords >0)
    {
      // Crdcs are divided in to sub-sub packets
      unsigned short subpacketlength = *pCrdc;
      unsigned short subpackettype = *(pCrdc+1);

      switch(subpackettype)
	{
	case SWEEPER_FP_CRDC_RAW_PACKET:
	  unpack_raw_data(pCrdc,id);
	  pCrdc += subpacketlength;
	  break;

	case SWEEPER_FP_CRDC_SAMPLE_PACKET:
	  // Don't unpack samples
	  pCrdc += subpacketlength;
	  break;

	case SWEEPER_FP_CRDC_PAD_PACKET:
	  // Pad data not implemented yet
	  pCrdc += subpacketlength;
	  break;

	case SWEEPER_FP_CRDC_ANODE_PACKET:
	  anode = *(pCrdc+2);
	  if(anode == 0)
	    anode = -1;
	  tac =   *(pCrdc+3);
	  if(tac == 0)
	    tac = -1;

	  pCrdc += subpacketlength;
	  break;

	default:
	  // skip
	  pCrdc += subpacketlength; 
	  break;
	}

      nWords -= subpacketlength;
    }
};

// var
void
var::sweeper_crdc_pads::write(const char* name, FILE* f)
{
  for(int i=0; i< FPCRDC_PADS; ++i)
    {
      fprintf(f, "%s.ped[%i] = %f;\n", name, i, ped[i]);
      fprintf(f, "%s.slope[%i] = %f;\n", name, i, slope[i]);
      fprintf(f, "%s.offset[%i] = %f;\n", name, i, offset[i]);
      fprintf(f, "%s.f_scale[%i] = %f;\n", name, i, f_scale[i]);
      fprintf(f, "%s.f_sigma[%i] = %f;\n", name, i, f_sigma[i]);
    }
  fprintf(f, "%s.ref_pad = %i;\n", name, ref_pad);
};

void
var::sweeper_crdc::write(const char* name, FILE* f)
{
  std::string padname = name; padname+=".pad";
  pad.write(padname.c_str(), f);
  fprintf(f, "%s.gravity_width = %i;\n", name, gravity_width);
  fprintf(f, "%s.fit_width = %i;\n", name, fit_width);
  fprintf(f, "%s.method = %i;\n", name, method);
  fprintf(f, "%s.badpads = %i;\n", name, badpads);
  for(int i=0; i< badpads; ++i)
    fprintf(f, "%s.badpad[%i] = %i;\n", name, i, badpad[i]);
  fprintf(f, "%s.x_offset = %f;\n", name, x_offset);
  fprintf(f, "%s.x_slope = %f;\n", name, x_slope);
  fprintf(f, "%s.y_offset = %f;\n", name, y_offset);
  fprintf(f, "%s.y_slope = %f;\n", name, y_slope);
  fprintf(f, "%s.z = %f;\n", name, z);
};

// cal
void
cal::sweeper_crdc_pads::reset()
{
  for(int i=0; i< FPCRDC_PADS; ++i)
    {
      cal[i] = -1;
      fcpy[i]= -1;//THR 4 August 2016
    }
};

void
cal::sweeper_crdc_pads::calibrate(const raw::sweeper_crdc_pads& rw,
				  const var::sweeper_crdc_pads& v,
				  const short& sw,
				  const short& pm)
{
    for(int i=0; i< FPCRDC_PADS; ++i)
    {
        if(is_valid(rw.raw[i]))
        {
	    // no longer need to normalize by # of samples
	    // this is always one since we take the maximum
	    // sample to be the raw charge - THR 17 August 2016
	    // ***
	    // to keep this function the same between CRDCs 1 & 2
	    // force the sample width to 1 for CRDC1 in the
	    // raw::sweeper_crdc_pads::unpack_raw_data() function
	    // *** 9/1/2016 THR ***
	    // SHOULD NOT BE SAMPLE WIDTH (sw) this does not
	    // properly normalize the raw charge
	    // instead i normalize by nsamples[q] in
	    // raw::sweeper_crdc_pads::integrate(...)
	    // so only pedestal subtraction takes place here
//	    cout << "sw = " << sw << endl;
//            cal[i] = double((rw.raw[i] / sw) - v.ped[i]);
            cal[i] = double((rw.raw[i]) - v.ped[i]);
            //cal[i] = double(rw.raw[i] - (v.ped[i] * sw)); - JKS, 24 July 2012
	    /* search for duplicated pads - THR, 4 August 2016 */
	    fcpy[i]=0;
	    for(int k=i-10;k<i+10;k++)
	    {
	      if (i!=k && rw.raw[i]>100 && rw.raw[i] == rw.raw[k])
	        {fcpy[i]+=1;}
	    }
            if(cal[i] <= 0)
            {
                cal[i] = -1;
            }
            else
            {
                int r(v.ref_pad);
                short delta = pm - i;
                if(abs(delta)< __MAX_DELTA)
                {
                    // multiplicative method
                    double gfr=0, gf=0;
                    if(v.f_sigma[r]!=0)
                        gfr = v.f_scale[r] * exp(-0.5 * (delta/v.f_sigma[r]) * (delta/v.f_sigma[r]));
                    if(v.f_sigma[i]!=0)
                        gf  = v.f_scale[i] * exp(-0.5 * (delta/v.f_sigma[i]) * (delta/v.f_sigma[i]));
                    if(gf!=0)
                        cal[i] = cal[i] * gfr/ gf;
                }
                // Old slope / offset method. Note that this is done outside the if loop in order
                // to replicate the old gain matching
                cal[i] = cal[i] * v.slope[i] + v.offset[i];
            }
        }
    }
};

void
cal::sweeper_crdc::reset()
{
  pad.reset();
  padmax    = -1;
  padsum    = -1;
  sigma     = -1;
  x_gravity = -1;
  x_fit     = -1;
  x_chi2    = -1;
  x         = -1;
  tx        = -1;
  y         = -1;
  ty        = -1;
};

void
cal::sweeper_crdc::gravity_fit(const var::sweeper_crdc& v,
                               const int id)
{
  try {
    double maxpad = 0;
    int bad = 0;
    // find pad at avalanche site maximum (2 non-zero adjacent pads required)
    padmax = 0;
    for (int i=1; i< FPCRDC_PADS-1; ++i) {
      // reject bad pads stored in the badpad array
      bad = 0;
      for (int j=0; j< v.badpads; ++j) {
	if (i == v.badpad[j]) bad = 1;
      }
      if (bad == 0) { 
	if(is_valid(pad.cal[i]) && is_valid(pad.cal[i-1]) && is_valid(pad.cal[i+1])) {
	  if(pad.cal[i-1] > 0 && pad.cal[i+1] > 0 && pad.cal[i] > maxpad) {
	    maxpad = pad.cal[i];
	    padmax = i;
	  }
	}
      }
    }
    // if we failed to find a good maximum, bail out
    if (padmax == 0) {
      padmax = -1;
      return;
    }

    /* switch on padmax to fix problem pads THR 4 Oct 2016:
     *   crdc1.padmax = 64,65: mirror pads 64 - 71
     *   crdc1.padmax = 67 - 68: suprress 72 - 79
     *                  69: suppress 73 - 79
     *                  70: suppress 74 - 79
     *                  71: suppress > 76
     *                  72: mirror 75 - 79
     *                  73: suppress 72 - 79
     *                  */

/*
    if(padmax>=64 && padmax<=65 && id==0)
    {

      int mirror = 71;
      int qq = 64;
      while (qq<mirror)
      {
        double tmp1 = pad.cal[qq];
        double tmp2 = pad.cal[mirror];
//        if(qq<75){ tmp1 = -1.0; }

        pad.cal[qq] = tmp2; pad.cal[mirror] = tmp1;
        ++qq;
        --mirror;
      }
    }
*/      
    if(padmax>=67 && padmax<=68 && id==0)
    {
      for(int sp=72;sp<80;sp++){ pad.cal[sp]=-1; }
    }
    if(padmax==69 && id==0)
    {
      for(int sp=73;sp<80;sp++){ pad.cal[sp]=-1; }
    }
    if(padmax==70 && id==0)
    {
      for(int sp=74;sp<80;sp++){ pad.cal[sp]=-1; }
    }
    if(padmax==71 && id==0)
    {
      for(int sp=76;sp<100;sp++){ pad.cal[sp]=-1; }
    }
    /*
    if(padmax==72 && id==0)
    {

      int mirror = 79;
      int qq = 75;
      while (qq<mirror)
      {
        double tmp1 = pad.cal[qq];
        double tmp2 = pad.cal[mirror];
//        if(qq<75){ tmp1 = -1.0; }

        pad.cal[qq] = tmp2; pad.cal[mirror] = tmp1;
        ++qq;
        --mirror;
      }
    }
    if(padmax==73 && id==0)
    {
      for(int sp=72;sp<80;sp++){ pad.cal[sp]=-1; }
    }
    // Redo padmax search: THR 21 Sept 2016 
    maxpad=0; bad=0; padmax=0;
    for (int i=1; i< FPCRDC_PADS-1; ++i) {
      // reject bad pads stored in the badpad array
      bad = 0;
      for (int j=0; j< v.badpads; ++j) {
         if (i == v.badpad[j]) bad = 1;
      }
      if (bad == 0) { 
        if(is_valid(pad.cal[i]) && is_valid(pad.cal[i-1]) && is_valid(pad.cal[i+1])) {
          if(pad.cal[i-1] > 0 && pad.cal[i+1] > 0 && pad.cal[i] > maxpad) {
	      maxpad = pad.cal[i];
	      padmax = i;
	    }
  	  }
        }
      }
    */
    /* interchange cal[pad] contents for CRDC 1 pads 72-79: THR 21 Sept 2016 
    if(padmax>=71 && padmax<=74 && id==0)
    {

      int mirror = 79;
      int qq = 72;
      while (qq<mirror)
      {
        double tmp1 = pad.cal[qq];
        double tmp2 = pad.cal[mirror];
        if(qq<75){ tmp1 = -1.0; }

        pad.cal[qq] = tmp2; pad.cal[mirror] = tmp1;
        ++qq;
        --mirror;
      }
      
      // Redo padmax search: THR 21 Sept 2016 
      maxpad=0; bad=0; padmax=0;
      for (int i=1; i< FPCRDC_PADS-1; ++i) {
        // reject bad pads stored in the badpad array
        bad = 0;
        for (int j=0; j< v.badpads; ++j) {
	  if (i == v.badpad[j]) bad = 1;
        }
        if (bad == 0) { 
	  if(is_valid(pad.cal[i]) && is_valid(pad.cal[i-1]) && is_valid(pad.cal[i+1])) {
	    if(pad.cal[i-1] > 0 && pad.cal[i+1] > 0 && pad.cal[i] > maxpad) {
	      maxpad = pad.cal[i];
	      padmax = i;
	    }
  	  }
        }
      }

    }
*/

    /* add some noise to fit result when crdc1.padmax == 62 */

    /* interchange cal[pad] contents for CRDC 1 pads 72-79: THR 14 Sept 2016
    if(padmax>=69 && padmax<=70 && id==0)
    {

      int mirror = 79;
      int qq = 72;
      while (qq<mirror)
      {
        double tmp1 = pad.cal[qq];
        double tmp2 = pad.cal[mirror];

        pad.cal[qq] = tmp2; pad.cal[mirror] = tmp1;
        ++qq;
        --mirror;
      }

    }
    */
    int lowpad  = padmax - v.gravity_width/2;
    int highpad = lowpad + v.gravity_width - 1;
    if (lowpad < 0) {
      lowpad = 0;
    }
    if (highpad >= FPCRDC_PADS) {
      highpad = FPCRDC_PADS - 1;
    }
    // calculate pad center of gravity
    double sum = 0, mom = 0, mom2 =0;
    // reject bad pads stored in the badpad array
    for (int i=lowpad; i<= highpad; ++i) {
      bad = 0;
      for (int j=0; j< v.badpads; ++j) {
	if (i == v.badpad[j]) bad = 1;
      }
      if (bad == 0 && is_valid(pad.cal[i])) {
	sum += pad.cal[i];
	mom += i * pad.cal[i];
	mom2 += i * i * pad.cal[i];
      }
    }
    padsum = sum;
    x_gravity = mom / sum;
    sigma = sqrt((mom2/sum)-(x_gravity*x_gravity));
  }
  catch (...) {
    std::cerr << "CalculateGravity::operator caught:error " << std::endl;
  }
};

void
cal::sweeper_crdc::gaus_fit(const var::sweeper_crdc& v,const int id)
{
  static gaus_params par0;
  static gaus_fit_results par;
  static std::vector<double> vx(0), vy(0);
  int npoints(0), lopad, hipad, npads;
  bool bad(0);

  if(is_valid(padmax)) //\need at least a good pad maximum
    {
      vx.resize(0); vy.resize(0);
      if(is_valid(x_gravity))
	{
	  // initialize fitter using gravity fit results
	  init_gaus_params(pad.cal[padmax], x_gravity, sigma, par0);
	}
      else
	{
	  // gravity fit didn't work, use padmax to initialize
	  init_gaus_params(pad.cal[padmax], padmax, 2.5, par0);
	}
      lopad = padmax - v.fit_width/2;
      hipad = padmax + v.fit_width/2;
      if(lopad< 0) lopad = 0;
      if(hipad >FPCRDC_PADS-1) hipad = FPCRDC_PADS-1;
      npads = hipad - lopad + 1;
      for(int i=0; i< npads; ++i)
	{
	  bad = 0;
	  for (int j=0; j< v.badpads; ++j)
	    {
	      if (i+lopad == v.badpad[j]) bad = 1;
	    }
	  if(!bad)
	    {
	      ++npoints;
	      vx.push_back(double(i+lopad));
	      vy.push_back(pad.cal[i+lopad]);
	    }
	}
      if(npoints >=3)
	{
	  double x[npoints], y[npoints], sig[npoints];
	  for(int i=0; i< npoints; ++i) 
	    {
	      x[i]   = vx[i];
	      y[i]   = vy[i];
	      sig[i] = 1.; // unweighted fit seems to work best
	    }
       	  int result = fit_gaus(x, y, sig, npoints, par0, par);
	  if(result == GSL_SUCCESS)
	    {
	      x_fit = par.x0;
	      sigma = par.sig;
	      if(par.ndf!=0)
		x_chi2 = par.chi2 / par.ndf;
	    }
	}
    }
};

void
cal::sweeper_crdc::calibrate(const raw::sweeper_crdc& rw,
			     const var::sweeper_crdc& v,
			     const int id)
{
  // find max pad
  short maxpad = 0;
  int bad = 0;
  // find pad at avalanche site maximum (2 non-zero adjacent pads required)
  padmax = 0;
  for (int i=1; i< FPCRDC_PADS-1; ++i) {
    // reject bad pads stored in the badpad array
    bad = 0;
    for (int j=0; j< v.badpads; ++j) {
      if (i == v.badpad[j]) bad = 1;
    }
    if (bad == 0) { 
      if(is_valid(rw.pad.raw[i]) && is_valid(rw.pad.raw[i-1]) && is_valid(rw.pad.raw[i+1])) {
	if(rw.pad.raw[i-1] > 0 && rw.pad.raw[i+1] > 0 && rw.pad.raw[i] > maxpad) {
	  maxpad = rw.pad.raw[i];
	  padmax = i;
	}
      }
    }
  }
  // if we failed to find a good maximum, bail out
  if (padmax == 0) {
    return;
  }

  pad.calibrate(rw.pad, v.pad, rw.sample_width, padmax);
  if(v.method == 2)
    {
      this->gravity_fit(v,id);// THR 13 Sept 2016
      this->gaus_fit(v,id);// THR 14 Sept 2016
      if(is_valid(x_fit))
      {
	x = x_fit * v.x_slope + v.x_offset;
      }
    }
  else
    {
      this->gravity_fit(v,id);// THR 13 Sept 2016
      if(is_valid(x_gravity))
	x = x_gravity * v.x_slope + v.x_offset;
    }
  if(is_valid(rw.tac) && rw.tac != 4075) //\4075 is overflow
     y = rw.tac * v.y_slope + v.y_offset;
};

void
cal::sweeper_crdc::calculate_image(const cal::sweeper_crdc& p1, const var::sweeper_crdc& v1,
				   const cal::sweeper_crdc& p2, const var::sweeper_crdc& v2)
{
  if(v1.z == v2.z)
    {
      fprintf(stderr, "Cannot calculate image for crdc. Please set crdc1.z and crdc2.z to different values\n");
      return;
    }
  if(is_valid(p1.x) && is_valid(p2.x))
    {
      tx = 1000 * atan((p2.x - p1.x) / (1000 * (v2.z - v1.z)));
    }
  if(is_valid(p1.y) && is_valid(p2.y))
    {
      ty = 1000 * atan((p2.y - p1.y) / (1000 * (v2.z - v1.z)));
    }
};


//---------------------------------------------------------//
// class sweeper_track_crdc

void
raw::sweeper_track_crdc::reset()
{
  anode = -1;
  tac = -1;
  sample_width = -1;

  for(unsigned short i=0; i< TCRDC_PADS; ++i)
    {
      pad.nsamples[i] = -1;
      pad.raw[i] = -1;
#if(__UNPACK_SAMPLES)
      for(int j=0; j< TCRDC_MAX_WIDTH; ++j)
	pad.sample[i][j] = -1;
#endif
    }
};

void
raw::sweeper_track_crdc_pads::integrate(std::vector< std::vector<short> >& data,
					unsigned short sampleWidth)
{
  // integrate samples into pads (leave pedestal subtraction for later)
  if(sampleWidth >TCRDC_MAX_WIDTH)
    {
      std::cerr << "\nsweeper_raw_track_crdc_pads::integrate passed a sample width "<<sampleWidth \
	   <<" which is too large. Bailing out\n";
      return;
    }
  for (int q=0; q< TCRDC_PADS; ++q)
    {
      nsamples[q] = 0;
      raw[q] = 0;
      for (int s=0; s< sampleWidth; ++s)
	{
	  if(data[q][s] != 0) 
	    {
	      raw[q] += data[q][s];
	      ++nsamples[q];
#if(__UNPACK_SAMPLES)
	      sample[q][s] = data[q][s];
#endif
	    }
	}
      if(raw[q] == 0) raw[q] = -1;
    }
};

void
raw::sweeper_track_crdc::unpack_raw_data(unsigned short* p)
{
  static unsigned long total=0, failed=0;
  unsigned short sample, channel, data[4], connector, previous_sample=0, ch;
  unsigned short m_threshold=0, m_sampleBegin=0, m_sampleWidth=0;

  static std::vector< std::vector<short> >
    m_data(TCRDC_PADS, std::vector<short>(TCRDC_MAX_WIDTH, 0));
  for (int i=0; i< TCRDC_PADS; ++i) {
      for (int j=0; j< TCRDC_MAX_WIDTH; ++j)
	m_data[i][j] = 0;
    }

  bool mes1=true, mes2=true, mes3=true, mes4=true;
  unsigned short length = *p; ++p;
  unsigned short i = length-3;
  ++p;	// skip packet id
  m_threshold = *p; ++p;
  while (i > 0) {
    if ((*p)>>15 != 1) {
      fprintf(stderr, "CRDC data is corrupted!\n");
      ++p; i--;
      continue;
    } else { //\ get sample & channel
      sample = ((*p)&0x7FC0)>>6;
      channel = (*p)&0x3F; //\channel is last 6 bits
      if (i == length-3) {m_sampleBegin = sample; previous_sample = sample;}
    }
    ++p; i--;
    for (int ii=0; ii<4; ii++) data[ii] = 0;
    //		memset(data, 0, sizeof(data));
    while ((*p)>>15 == 0) { //\ get data
      connector = ((*p)&0x0C00)>>10;
      data[connector] = (*p)&0x3FF;
      ++p; i--;
      if (i == 0) break;
    }
    if (sample < m_sampleBegin || sample > m_sampleBegin+TCRDC_MAX_WIDTH) {
#if(__SWEEPER_DEBUG)
	fprintf(stderr, "Warning in Crdc unpack: inconsistent sample number: %d (first: %d)\n",
	       sample, m_sampleBegin);
#endif
      mes1 = false;
      continue;
    }
    if (sample < previous_sample) {
#if(__SWEEPER_DEBUG)
	fprintf(stderr, "Warning in Crdc unpack: sample number lower than previous: %d (previous: %d)\n",
	       sample, previous_sample);
#endif
      mes2 = false;
      continue;
    }
    previous_sample = sample;
    for (int j=0; j<4; j++) {
      ch = channel+j*64;
      if (data[j] != 0 && ch < TCRDC_PADS) {
	if (data[j] < m_threshold) {
#if(__SWEEPER_DEBUG)
	    fprintf(stderr, "Warning in Crdc unpack: data lower than threshold: %d (threshold: %d)\n",
		    data[j], m_threshold);
#endif
	  mes3 = false;
	} else {
	  m_data[ch][sample-m_sampleBegin] = data[j];
	}
      } else if (data[j] != 0 && ch >= TCRDC_PADS) {
#if(__SWEEPER_DEBUG)
	  fprintf(stderr, "Warning in Crdc unpack: channel greater than limit: %d (limit: %d)\n",
		  ch, TCRDC_PADS);
#endif
	mes4 = false;
      }
    }
    m_sampleWidth = sample - m_sampleBegin + 1;
  }
  // integrate samples into pads
  sample_width = m_sampleWidth;
  pad.integrate(m_data, m_sampleWidth);


  if (!mes1 || !mes2 || !mes3 || !mes4) failed++;
  total++;
  if (failed == 1000) {
#if(__SWEEPER_DEBUG)
      fprintf(stderr, "Errors in Crdc unpackings: %g%%\n", 1.0*failed/total*100);
#endif
    total = 0;
    failed = 0;
  }
};

void
raw::sweeper_track_crdc::unpack(unsigned short* pCrdc)
{
  unsigned short nWords = *(pCrdc-3) - 3; //\-3 b/c of ID word

  while(nWords >0)
    {
      // Crdcs are divided in to sub-sub packets
      unsigned short subpacketlength = *pCrdc;
      unsigned short subpackettype = *(pCrdc+1);

      switch(subpackettype)
	{
	case SWEEPER_FP_CRDC_RAW_PACKET:
	  unpack_raw_data(pCrdc);
	  pCrdc += subpacketlength;
	  break;

	case SWEEPER_FP_CRDC_SAMPLE_PACKET:
	  // Don't unpack samples
	  pCrdc += subpacketlength;
	  break;

	case SWEEPER_FP_CRDC_PAD_PACKET:
	  // Pad data not implemented yet
	  pCrdc += subpacketlength;
	  break;

	case SWEEPER_FP_CRDC_ANODE_PACKET:
	  anode = *(pCrdc+2);
	  if(anode == 0)
	    anode = -1;
	  tac =   *(pCrdc+3);
	  if(tac == 0)
	    tac = -1;

	  pCrdc += subpacketlength;
	  break;

	default:
	  // skip
	  pCrdc += subpacketlength; 
	  break;
	}

      nWords -= subpacketlength;
    }
};

// var
void
var::sweeper_track_crdc_pads::write(const char* name, FILE* f)
{
  for(int i=0; i< TCRDC_PADS; ++i)
    {
      fprintf(f, "%s.ped[%i] = %f;\n", name, i, ped[i]);
      fprintf(f, "%s.slope[%i] = %f;\n", name, i, slope[i]);
      fprintf(f, "%s.offset[%i] = %f;\n", name, i, offset[i]);
      fprintf(f, "%s.f_scale[%i] = %f;\n", name, i, f_scale[i]);
      fprintf(f, "%s.f_sigma[%i] = %f;\n", name, i, f_sigma[i]);
    }
  fprintf(f, "%s.ref_pad = %i;\n", name, ref_pad);
};

void
var::sweeper_track_crdc::write(const char* name, FILE* f)
{
  std::string padname = name; padname+=".pad";
  pad.write(padname.c_str(), f);
  fprintf(f, "%s.gravity_width = %i;\n", name, gravity_width);
  fprintf(f, "%s.fit_width = %i;\n", name, fit_width);
  fprintf(f, "%s.method = %i;\n", name, method);
  fprintf(f, "%s.badpads = %i;\n", name, badpads);
  for(int i=0; i< badpads; ++i)
    fprintf(f, "%s.badpad[%i] = %i;\n", name, i, badpad[i]);
  fprintf(f, "%s.x_offset = %f;\n", name, x_offset);
  fprintf(f, "%s.x_slope = %f;\n", name, x_slope);
  fprintf(f, "%s.y_offset = %f;\n", name, y_offset);
  fprintf(f, "%s.y_slope = %f;\n", name, y_slope);
  fprintf(f, "%s.z = %f;\n", name, z);
  fprintf(f, "%s.rotate_spikes = %i;\n", name, rotate_spikes);
  fprintf(f, "%s.force_correlation = %i;\n", name, force_correlation);
  fprintf(f, "%s.corr_slope = %f;\n", name, corr_slope);
  fprintf(f, "%s.corr_offset = %f;\n", name, corr_offset);
};

// cal
void
cal::sweeper_track_crdc_pads::reset()
{
  for(int i=0; i< TCRDC_PADS; ++i)
    {
      cal[i] = -1;
    }
};

void
cal::sweeper_track_crdc_pads::calibrate(const raw::sweeper_track_crdc_pads& rw,
					const var::sweeper_track_crdc_pads& v,
					const short& sw,
					const short& pm)
{
  for(int i=0; i< TCRDC_PADS; ++i)
    {
      if(is_valid(rw.raw[i]))
	{
	  cal[i] = double((rw.raw[i] / rw.nsamples[i]) - v.ped[i]);
	  //cal[i] = double(rw.raw[i] - (v.ped[i] * rw.nsamples[i])); - JKS, 
	  if(cal[i] <= 0)
	    {
	      cal[i] = -1;
	    }
	  else
	    {
	      short delta = pm - i;
	      if(abs(delta)< __MAX_DELTA)
		{
		  int r(v.ref_pad);

		  // multiplicative method
		  double gfr=0, gf=0;
		  if(v.f_sigma[r]!=0)
		    gfr = v.f_scale[r] * exp(-0.5 * (delta/v.f_sigma[r]) * (delta/v.f_sigma[r]));
		  if(v.f_sigma[i]!=0)
		    gf  = v.f_scale[i] * exp(-0.5 * (delta/v.f_sigma[i]) * (delta/v.f_sigma[i]));
		  if(gf!=0)
		    cal[i] = cal[i] * gfr / gf;
		}
	      // Old slope / offset method. Note that this is done outside the if loop in order
	      // to replicate the old gain matching
	      cal[i] = cal[i] * v.slope[i] + v.offset[i];
	    }		 
	}
    }
};

void
cal::sweeper_track_crdc::reset()
{
  pad.reset();
  padmax    = -1;
  padsum    = -1;
  sigma     = -1;
  x_gravity = -1;
  x_fit     = -1;
  x_chi2    = -1;
  x         = -1;
  tx        = -1;
  y         = -1;
  ty        = -1;
};


void
cal::sweeper_track_crdc::gravity_fit(const var::sweeper_track_crdc& v)
{
  try {
    double maxpad = 0;
    int bad = 0;
    // find pad at avalanche site maximum (2 non-zero adjacent pads required)
    padmax = 0;
    for (int i=1; i< TCRDC_PADS-1; ++i) {
      // reject bad pads stored in the badpad array
      bad = 0;
      for (int j=0; j< v.badpads; ++j) {
	if (i == v.badpad[j]) bad = 1;
      }
      if (bad == 0) { 
	if(is_valid(pad.cal[i]) && is_valid(pad.cal[i-1]) && is_valid(pad.cal[i+1])) {
	  if(pad.cal[i-1] > 0 && pad.cal[i+1] > 0 && pad.cal[i] > maxpad) {
	    maxpad = pad.cal[i];
	    padmax = i;
	  }
	}
      }
    }
    // if we failed to find a good maximum, bail out
    if (padmax == 0) {
      return;
    }
    int lowpad  = padmax - v.gravity_width/2;
    int highpad = lowpad +  v.gravity_width - 1;
    if (lowpad < 0) {
      lowpad = 0;
    }
    if (highpad >= TCRDC_PADS) {
      highpad = TCRDC_PADS - 1;
    }
    // calculate pad center of gravity
    double sum = 0, mom = 0, mom2 =0;
    // reject bad pads stored in the badpad array
    for (int i=lowpad; i<= highpad; ++i) {
      bad = 0;
      for (int j=0; j< v.badpads; ++j) {
	if (i == v.badpad[j]) bad = 1;
      }
      if (bad == 0 && is_valid(pad.cal[i])) {
	sum += pad.cal[i];
	mom += i * pad.cal[i];
	mom2 += i * i * pad.cal[i];
      }
    }
    padsum = sum;
    x_gravity = mom / sum;
    sigma = sqrt((mom2/sum)-(x_gravity*x_gravity));
  }
  catch (...) {
    std::cerr << "CalculateGravity::operator caught:error " << std::endl;
  }
};

void
cal::sweeper_track_crdc::gaus_fit(const var::sweeper_track_crdc& v)
{
  static gaus_params par0;
  static gaus_fit_results par;
  static std::vector<double> vx(0), vy(0);
  int npoints(0), lopad, hipad, npads;
  bool bad(0);

  if(is_valid(padmax)) //\need at least a good pad maximum
    {
      vx.resize(0); vy.resize(0);
      if(is_valid(x_gravity))
	{
	  // initialize fitter using gravity fit results
	  init_gaus_params(pad.cal[padmax], x_gravity, sigma, par0);
	}
      else
	{
	  // gravity fit didn't work, use padmax to initialize
	  init_gaus_params(pad.cal[padmax], padmax, 2.5, par0);
	}
      lopad = padmax - v.fit_width/2;
      hipad = padmax + v.fit_width/2;
      if(lopad< 0) lopad = 0;
      if(hipad >FPCRDC_PADS-1) hipad = FPCRDC_PADS-1;
      npads = hipad - lopad + 1;
      for(int i=0; i< npads; ++i)
	{
	  bad = 0;
	  for (int j=0; j< v.badpads; ++j)
	    {
	      if (i+lopad == v.badpad[j]) bad = 1;
	    }
	  if(!bad)
	    {
	      ++npoints;
	      vx.push_back(double(i+lopad));
	      vy.push_back(pad.cal[i+lopad]);
	    }
	}
      if(npoints >=3)
	{
	  double x[npoints], y[npoints], sig[npoints];
	  for(int i=0; i< npoints; ++i) 
	    {
	      x[i]   = vx[i];
	      y[i]   = vy[i];
	      sig[i] = 1.; // unweighted fit seems to work best
	    }
       	  int result = fit_gaus(x, y, sig, npoints, par0, par);
	  if(result == GSL_SUCCESS)
	    {
	      x_fit = par.x0;
	      sigma = par.sig;
	      if(par.ndf!=0)
		x_chi2 = par.chi2 / par.ndf;
	    }
	}
    }
};

void
cal::sweeper_track_crdc::calibrate(const raw::sweeper_track_crdc& rw,
				   const var::sweeper_track_crdc& v)
{
  // find max pad
  short maxpad = 0;
  int bad = 0;
  // find pad at avalanche site maximum (2 non-zero adjacent pads required)
  padmax = 0;
  for (int i=1; i< TCRDC_PADS-1; ++i) {
    // reject bad pads stored in the badpad array
    bad = 0;
    for (int j=0; j< v.badpads; ++j) {
      if (i == v.badpad[j]) bad = 1;
    }
    if (bad == 0) { 
      if(is_valid(rw.pad.raw[i]) && is_valid(rw.pad.raw[i-1]) && is_valid(rw.pad.raw[i+1])) {
	if(rw.pad.raw[i-1] > 0 && rw.pad.raw[i+1] > 0 && rw.pad.raw[i] > maxpad) {
	  maxpad = rw.pad.raw[i];
	  padmax = i;
	}
      }
    }
  }
  // if we failed to find a good maximum, bail out
  if (padmax == 0) {
    return;
  }

  pad.calibrate(rw.pad, v.pad, rw.sample_width, padmax);
  if(v.method == 2)
    {
      this->gravity_fit(v);
      this->gaus_fit(v);
      if(is_valid(x_fit))
	x = x_fit * v.x_slope + v.x_offset;
    }
  else
    {
      this->gravity_fit(v);
      if(is_valid(x_gravity))
	x = x_gravity * v.x_slope + v.x_offset;
    }
  if(is_valid(rw.tac) && rw.tac != 4075) //\4075 is overflow
     y = rw.tac * v.y_slope + v.y_offset;
};


void
cal::sweeper_track_crdc::calculate_image(const cal::sweeper_track_crdc& p1, const var::sweeper_track_crdc& v1,
					 const cal::sweeper_track_crdc& p2, const var::sweeper_track_crdc& v2)
{
  if(v1.z == v2.z)
    {
      fprintf(stderr, "Cannot calculate image for track_crdc. Please set tcrdc1.z and tcrdc2.z to different values\n");
      return;
    }
  if(is_valid(p1.x) && is_valid(p2.x))
    {
      tx = 1000 * atan((p2.x - p1.x) / (1000 * (v2.z - v1.z)));
    }
  if(is_valid(p1.y) && is_valid(p2.y))
    {
      ty = 1000 * atan((p2.y - p1.y) / (1000 * (v2.z - v1.z)));
    }
};

void
cal::sweeper_track_crdc::force_correlation(const cal::sweeper_track_crdc& other_tcrdc,
					   const var::sweeper_track_crdc& v)
{
  x = v.corr_slope * other_tcrdc.x + v.corr_offset;
};

void
cal::sweeper_track_crdc::calibrate_y(const raw::sweeper_track_crdc& rw,
				     const var::sweeper_track_crdc& v)
{
  if(is_valid(rw.tac) && rw.tac != 4075) //\4075 is overflow
    y = rw.tac * v.y_slope + v.y_offset;
};

double
cal::sweeper_track_crdc::rotate_spikes(double x1,
				       double x2)
{
  // spike rotation for e09040, "hard-coded" for right now
  // x1 == tcrdc1.x, x2 == tcrdc2.x

  double slp = 1.3553;
  double off = 6.0851;

  gate2d s1(4);
  s1.set_point(0,-30.7843,-29.653);
  s1.set_point(1,-9.60784,-29.1798);
  s1.set_point(2,-12.9412,-26.0252);
  s1.set_point(3,-31.2745,-26.3407);
  s1.close();

  gate2d s2(5);
  s2.set_point(0,-26.5686,-16.5615);
  s2.set_point(1,-0.490196,-15.4574);
  s2.set_point(2,-0.686275,-11.9874);
  s2.set_point(3,-26.6667,-12.6183);
  s2.set_point(4,-26.5686,-15.6151);
  s2.close();

  gate2d s3(5);
  s3.set_point(0,-16.4706,-5.9633);
  s3.set_point(1,10.8824,-4.74006);
  s3.set_point(2,10.3922,-1.37615);
  s3.set_point(3,-17.2549,-2.59939);
  s3.set_point(4,-17.2549,-5.35168);
  s3.close();

  gate2d s4(6);
  s4.set_point(0,-6.07843,11.5142);
  s4.set_point(1,22.6471,12.4606);
  s4.set_point(2,23.4314,14.1956);
  s4.set_point(3,18.7255,15.142);
  s4.set_point(4,-4.60784,14.6688);
  s4.set_point(5,-6.37255,13.4069);
  s4.close();

  gate2d s5(5);
  s5.set_point(0,5.78431,22.3975);
  s5.set_point(1,34.8039,23.817);
  s5.set_point(2,32.8431,27.6025);
  s5.set_point(3,5.09804,25.7098);
  s5.set_point(4,4.70588,24.1325);
  s5.close();

  if(s1.is_inside(x1, x2)) return off + slp * x1;
  if(s2.is_inside(x1, x2)) return off + slp * x1;
  if(s3.is_inside(x1, x2)) return off + slp * x1;
  if(s4.is_inside(x1, x2)) return off + slp * x1;
  if(s5.is_inside(x1, x2)) return off + slp * x1;
  return x2;
};


//---------------------------------------------------------//
// class sweeper_ion_chamber

// raw
void
raw::sweeper_ion_chamber::reset()
{
  for(int i=0; i< IC_CHANNELS; ++i)
    raw[i] = -1;
};

void
raw::sweeper_ion_chamber::unpack(unsigned short* pIc)
{
  if (*(pIc+1) == SWEEPER_FP_IC_ENERGY_PACKET)
    {
      // IC packet with times
      unsigned short length, ch;
      length = *pIc; ++pIc;
      ++pIc;
      length -= 2;
      while (length > 0) 
	{
	  ch = ((*pIc)&0xf000)>>12;
	  raw[ch] = (*pIc)&0xfff; ++pIc;
	  length--;
	}
    }
};

// var
void
var::sweeper_ion_chamber::write(const char* name, FILE* f)
{
  for(int i=0; i< IC_CHANNELS; ++i)
    {
      fprintf(f, "%s.slope[%i] = %f;\n", name, i, slope[i]);
      fprintf(f, "%s.offset[%i] = %f;\n", name, i, offset[i]);
      for(unsigned int j=0; j< IC_CORR_ORDER+1; ++j)
	fprintf(f, "%s.corr[%i][%i] = %f;\n", name, i, j, corr[i][j]);
      fprintf(f, "%s.corr_scale[%i] = %f;\n", name, i, corr_scale[i]);
    }
  fprintf(f, "%s.de_slope = %f;\n", name, de_slope);
  fprintf(f, "%s.de_offset = %f;\n", name, de_offset);
};

// cal
void
cal::sweeper_ion_chamber::reset()
{
  for(int i=0; i< IC_CHANNELS; ++i)
    {
      cal[i] = -1;
      corr[i] = -1;
    }

  sum     = -1;
  de      = -1;
  de_corr = -1;
};

void
cal::sweeper_ion_chamber::calibrate(const raw::sweeper_ion_chamber& rw,
				    const var::sweeper_ion_chamber& v)
{
  int ch = 0;
  for(int i=0; i< IC_CHANNELS; ++i)
    {
      sum = 0;
      if(is_valid(rw.raw[i]))
	{
	  cal[i] = rw.raw[i] * v.slope[i] + v.offset[i];
	  sum += cal[i];
	  if(cal[i] != 0) ++ch;
	}
    }

  if(sum == 0) 
    {
      sum = -1;
      return;
    }
  if(ch != 0)
    {
      sum /= ch;
      de = sum * v.de_slope + v.de_offset;
    }
};

void
cal::sweeper_ion_chamber::correct(const var::sweeper_ion_chamber& v,
				  const double& x_corr) //\ = crdc2.x
{
  int ch = 0;
  if(is_valid(x_corr))
    {
      for(int i=0; i< IC_CHANNELS; ++i)
	{
	  if(is_valid(cal[i]))
	    {
	      double denom = 0;
	      for(unsigned int k=0; k< IC_CORR_ORDER+1; ++k)
		denom += v.corr[i][k] * pow(x_corr, k);
	      if(denom != 0)
		{
		  corr[i] = v.corr_scale[i] * cal[i] / denom;
		  ch ++;
		  de_corr += corr[i];
		}
	    }
	}
    }
    de_corr /= ch;
};


#ifdef __WITH_HODOSCOPE
//---------------------------------------------------------//
// class sweeper_hodoscope

// raw
void
raw::sweeper_hodoscope::reset()
{
  for(int i=0; i< HODO_CH; ++i){
    raw[i] = -1;
    }
};

void
raw::sweeper_hodoscope::unpack(unsigned short* pHs)
{
      // Hodoscope packet
      unsigned short length,ch,id;
      length = *(pHs-2); 
      length -= 2;
      id = *pHs; ++pHs;
      --length;
      while (length > 0) 
	{
      	 //masks for channel and value came from Daniel's description of hodoscope packet - JKS, 23 May 2012
		ch = (((*pHs)&0xE000)>>13) +id*8;
	    if (ch < HODO_CH)
	    {
		raw[ch] = (*pHs)&0x1FFF;
	    }
		++pHs;
		length--;
	}
};

// var
void
var::sweeper_hodoscope::write(const char* name, FILE* f)
{
  for(int i=0; i< HODO_CH; ++i)
    {
      fprintf(f, "%s.slope[%i] = %f;\n", name, i, slope[i]);
      fprintf(f, "%s.offset[%i] = %f;\n", name, i, offset[i]);
    }
};

// cal
void
cal::sweeper_hodoscope::reset()
{
  for(int i=0; i< HODO_CH; ++i)
    {
      cal[i] = -1;
    }
  x  = -1;
  tx = -1;
  y  = -1;
  ty = -1;
  sum     = -1;
  maxcrystal = -1;
  mult    = 0;
};

void
cal::sweeper_hodoscope::calibrate(const raw::sweeper_hodoscope& rw,
				    const var::sweeper_hodoscope& v)
{
  mult = 0;
  double maxvalue=0;
  sum = 0;
  for(int i=0; i< HODO_CH; ++i)
    {
      if(is_valid(rw.raw[i]))
	{
	  cal[i] = rw.raw[i] * v.slope[i] + v.offset[i];
	  sum += cal[i];
	  if(cal[i] != 0) ++mult;
	  if(cal[i] > maxvalue)
	  {
	  	maxvalue=cal[i];
		maxcrystal = i;
	  }
	}
    }

  if(sum == 0) 
    {
      sum = -1;
    }
    return;
};

void
cal::sweeper_hodoscope::calculate_image(const cal::sweeper_crdc& p1, const var::sweeper_crdc& v1,
				       const cal::sweeper_crdc& p2, const var::sweeper_crdc& v2,
				       const double& z)
{
  if(v1.z == v2.z)
    {
      fprintf(stderr, "Cannot calculate image for fp_scint. Please set crdc1.z and crdc2.z to different values\n");
      return;
    }
  if(is_valid(p1.x) && is_valid(p2.x))
    {
      tx = 1000 * atan((p2.x - p1.x) / (1000 * (v2.z - v1.z)));
      x  = p1.x + 1000 * (z - v1.z) * tan(tx / 1000);
    }
  if(is_valid(p1.y) && is_valid(p2.y))
    {
      ty = 1000 * atan((p2.y - p1.y) / (1000 * (v2.z - v1.z)));
      y  = p1.y + 1000 * (z - v1.z) * tan(ty / 1000);
    }
};
#endif
//---------------------------------------------------------//
#ifdef __WITH_SEGTARG
/////////////////////////////////////////12/18/15/////////////////////
// class sweeper_segtargadc
void
raw::sweeper_segtargadc::reset()
{
  for(int i=0; i< SEGTARG_CH; ++i){
    raw[i] = -1;
    }
};

void
raw::sweeper_segtargadc::unpack(unsigned short* pHs)
{
  
      // Segtargadc packet
      unsigned short length,ch;// unused variable: ,id;
      length = *(pHs-2); 
      length -= 2;
//      3id = *pHs; ++pHs;
      //--length;

      while (length > 0) 
	{
		ch = ((*pHs)&0x00FF);
		++pHs;
	    if (ch < SEGTARG_CH)
	    {
		raw[ch] = (*pHs)&0x1FFF;
	    }
		++pHs;
		length -= 2;//HL 2/9/16
	}

};

// var
void
var::sweeper_segtargadc::write(const char* name, FILE* f)
{
  for(int i=0; i<4; ++i)
  {
    for(int j=0; j<4; j++)
    {
      fprintf(f, "st.cnr_slope[%i] = %f;\n", i, cnr_slope[i][j]);
      fprintf(f, "st.cnr_offset[%i] = %f;\n", i, cnr_offset[i][j]);
    }
  }
};


void
cal::sweeper_segtargadc::reset()
{
  for(int i=0; i<4; i++)
    {
    anode[i] = -1;
    x[i] = -1;
    y[i] = -1;
    ecal[i] = -1;
    for (int j=0; j<4; j++)
    	{
	corner[i][j] = -1;
   	}
    
    }

};

void
cal::sweeper_segtargadc::calibrate(const raw::sweeper_segtargadc& rw,
				    const var::sweeper_segtargadc& v)
{
// dump calibration results into anode and corner arrays
//anode[0]=cal[15];// anode for detector during test
anode[0]=double(rw.raw[16]);// first detector that beam hits
anode[1]=double(rw.raw[20]);
anode[2]=double(rw.raw[24]);
anode[3]=double(rw.raw[31]);// last detector that beam hits

// corners for detector 0: LU, RU, RD, LD
for(int i=0; i<4; i++)
{
  corner[0][i]=double(rw.raw[i+4]) * v.cnr_slope[0][i] + v.cnr_offset[0][i];
}
// corners for detector 1: LU, RU, RD, LD
for(int i=0; i<4; i++)
{
  corner[1][i]=double(rw.raw[i]) * v.cnr_slope[1][i] + v.cnr_offset[1][i];
}
// corners for detector 2: LU, RU, RD, LD
for(int i=0; i<4; i++)
{
  corner[2][i]=double(rw.raw[i+12]) * v.cnr_slope[2][i] + v.cnr_offset[2][i];
}
// corners for detector 3: LU, RU, RD, LD
for(int i=0; i<4; i++)
{
  corner[3][i]=double(rw.raw[i+8]) * v.cnr_slope[3][i] + v.cnr_offset[3][i];
}

for(int i=0;i<4;i++)
{
  ecal[i] = anode[i] * v.e_slope[i] + v.e_offset[i];
}

};
#endif
///////////////////////////////////////////////////////////////////
// class sweeper_fp_scint

// raw
void
raw::sweeper_fp_scint::reset()
{
  for(int i=0; i< 4; ++i)
    {
      qraw[i] = -1;
      traw[i] = -1;
    }
};

// var
void
var::sweeper_fp_scint::write(const char* name, FILE* f)
{
  for(int i=0; i< 4; ++i)
    {
      fprintf(f, "%s.q_slope[%i] = %f;\n", name, i, q_slope[i]);
      fprintf(f, "%s.q_offset[%i] = %f;\n", name, i, q_offset[i]);
      fprintf(f, "%s.t_slope[%i] = %f;\n", name, i, t_slope[i]);
      fprintf(f, "%s.t_offset[%i] = %f;\n", name, i, t_offset[i]);
    }
  fprintf(f, "%s.required_pmts = %i;\n", name, required_pmts);
  fprintf(f, "%s.corr_scale = %f;\n", name, corr_scale);
  fprintf(f, "%s.corr_offset = %f;\n", name, corr_offset);
  for(unsigned int i=0; i< POSCORR_ORDER; ++i)
    fprintf(f, "%s.corr[%i] = %f;\n", name, i, corr[i]);
  fprintf(f, "%s.z = %f;\n", name, z);
};

//cal
void
cal::sweeper_fp_scint::reset()
{
  for(int i=0; i< 4; ++i)
    {
      tcal[i] = -1;
      qcal[i] = -1;
    }
  e     = -1;
  ecorr = -1;
  t     = -1;
  xpos  = -1;
  ypos  = -1;
  x     = -1;
  tx    = -1;
  y     = -1;
  ty    = -1;
};

void
cal::sweeper_fp_scint::calibrate(const raw::sweeper_fp_scint& rw,
 				 const var::sweeper_fp_scint& v,
				 const double& jittersub)
{
  int qvalids = 0;
  double etop, ebot;
  static double de[4];
  for(int i=0; i< 4; ++i)
    {
      if(is_valid(rw.traw[i]) && is_valid(jittersub)) {
	tcal[i]  = rw.traw[i] * v.t_slope[i] - jittersub + v.t_offset[i];
      }
      if(is_valid(rw.qraw[i])) {
	qcal[i] = rw.qraw[i] * v.q_slope[i] + v.q_offset[i];
	++qvalids;
      }
    }

  // energy
  if(qvalids == 4)
    {
      de[0] = sqrt(qcal[0]*qcal[0] + qcal[1]*qcal[1]);
      de[1] = sqrt(qcal[2]*qcal[2] + qcal[3]*qcal[3]);
      de[2] = sqrt(qcal[0]*qcal[0] + qcal[2]*qcal[2]);
      de[3] = sqrt(qcal[1]*qcal[1] + qcal[3]*qcal[3]);

      etop = (qcal[0] + qcal[2]) / 2;
      ebot = (qcal[1] + qcal[3]) / 2;
      e = sqrt(etop*etop + ebot*ebot) / 2;

      if(de[1] != 0) xpos = log(de[0]/de[1]);
      if(de[3] != 0) xpos = log(de[2]/de[1]);
    }

  // time
  double tsum = 0;
  int nfired = 0;
  for(int i=0; i< 4; ++i)
    {
      if(is_valid(tcal[i]))
	{
	  tsum += tcal[i];
	  ++nfired;
	}
    }
  if(nfired >=v.required_pmts && nfired !=0)
    t = tsum / nfired;
};

void
cal::sweeper_fp_scint::calculate_image(const cal::sweeper_crdc& p1, const var::sweeper_crdc& v1,
				       const cal::sweeper_crdc& p2, const var::sweeper_crdc& v2,
				       const double& z)
{
  if(v1.z == v2.z)
    {
      fprintf(stderr, "Cannot calculate image for fp_scint. Please set crdc1.z and crdc2.z to different values\n");
      return;
    }
  if(is_valid(p1.x) && is_valid(p2.x))
    {
      tx = 1000 * atan((p2.x - p1.x) / (1000 * (v2.z - v1.z)));
      x  = p1.x + 1000 * (z - v1.z) * tan(tx / 1000);
    }
  if(is_valid(p1.y) && is_valid(p2.y))
    {
      ty = 1000 * atan((p2.y - p1.y) / (1000 * (v2.z - v1.z)));
      y  = p1.y + 1000 * (z - v1.z) * tan(ty / 1000);
    }
};

// Added by SMM on 05/05/10 to do position calibration of fp scints
void
cal::sweeper_fp_scint::position_correct(const var::sweeper_fp_scint& v)
{
    if (is_valid(e) && is_valid(x))
    {
        double denom = gsl_poly_eval(v.corr,POSCORR_ORDER,x);
        ecorr = e*v.corr_scale/denom + v.corr_offset;
    }
};

void
cal::sweeper_tofcorr::reset()
{
  rf_thin    = -1;
  a1900_thin = -1;
  pot_thin   = -1;
};

void
cal::sweeper_tofcorr::calculate(const cal::sweeper_tof& tof,      
				const var::sweeper_tof& v,        
				const cal::sweeper_focus& fp)
{
  if(is_valid(fp.x) && is_valid(fp.tx))
    {
      if(is_valid(tof.rf_thin))
	{
	  rf_thin = tof.rf_thin + \
	    fp.x*v.rf.x + fp.tx*v.rf.tx + \
	    fp.x*fp.x*v.rf.x2 + fp.tx*fp.tx*v.rf.tx2 + \
	    fp.x*fp.tx*v.rf.xtx;
	}
      if(is_valid(tof.a1900_thin))
	{
	  a1900_thin = tof.a1900_thin + \
	    fp.x*v.a1900.x + fp.tx*v.a1900.tx + \
	    fp.x*fp.x*v.a1900.x2 + fp.tx*fp.tx*v.a1900.tx2 + \
	    fp.x*fp.tx*v.a1900.xtx;
	}
      if(is_valid(tof.pot_thin))
	{
	  pot_thin = tof.pot_thin + \
	    fp.x*v.pot.x + fp.tx*v.pot.tx + \
	    fp.x*fp.x*v.pot.x2 + fp.tx*fp.tx*v.pot.tx2 + \
	    fp.x*fp.tx*v.pot.xtx;
	}
    }
};


//---------------------------------------------------------//
// class sweeper_scint

// raw
void
raw::sweeper_scint::reset()
{
  traw = -1;
  qraw = -1;
};

// var
void
var::sweeper_scint::write(const char* name, FILE* f)
{
  fprintf(f, "%s.t_slope = %f;\n", name, t_slope);
  fprintf(f, "%s.t_offset = %f;\n", name, t_offset);
  fprintf(f, "%s.q_slope = %f;\n", name, q_slope);
  fprintf(f, "%s.q_offset = %f;\n", name, q_offset);
  fprintf(f, "%s.z = %f;\n", name, z);
};

// cal
void
cal::sweeper_scint::reset()
{
  tcal = -1;
  qcal = -1;
};

void
cal::sweeper_scint::calibrate(const raw::sweeper_scint& rw,
			      const var::sweeper_scint& v,
			      const double& jittersub)
{
  if(is_valid(rw.traw) && is_valid(jittersub))
    tcal = rw.traw * v.t_slope + v.t_offset - jittersub;
  if(is_valid(rw.qraw))
    qcal = rw.qraw * v.q_slope + v.q_offset;
};


//---------------------------------------------------------//
// class sweeper_timing_detector

// raw
void
raw::sweeper_timing_detector::reset()
{
  traw = -1;
};

// var
void
var::sweeper_timing_detector::write(const char* name, FILE* f)
{
  fprintf(f, "%s.t_slope = %f;\n", name, t_slope);
  fprintf(f, "%s.t_offset = %f;\n", name, t_offset);
  fprintf(f, "%s.z = %f;\n", name, z);
};

// cal
void
cal::sweeper_timing_detector::reset()
{
  tcal = -1;
};

void
cal::sweeper_timing_detector::calibrate(const raw::sweeper_timing_detector& rw,
					const var::sweeper_timing_detector& v,
					const double& jittersub)
{
  if(is_valid(rw.traw) && is_valid(jittersub))
    tcal = rw.traw * v.t_slope + v.t_offset - jittersub;
};


//---------------------------------------------------------//
// sweeper::unpack_fp_scint
void
raw::sweeper::unpack_fp_scint(unsigned short* pFp)
{
//     Zero suppressed data of energies and times
//      Channel mapping:
//       ----------------------------------------------
// 	 | DETECTOR     | ENERGY CHANNEL| TIME CHANNEL|
//       ----------------------------------------------
// 	 | ThinLU	| 0	       	| 0	      |
// 	 | ThinLD	| 1	       	| 1	      |
// 	 | ThinRU	| 2	       	| 2	      |
// 	 | ThinRD	| 3	       	| 3	      |
// 	 | ThickLU	| 4	       	| 4	      |
// 	 | ThickLD	| 5	       	| 5	      |
// 	 | ThickRU	| 6	       	| 6	      |
// 	 | ThickRD	| 7	       	| 7	      |
//       | Pot Energy   | 8             | n/a         |
//       | A1900 Energy | 9             | n/a         |

  unsigned short words = *(pFp-2) - 2, ID;
  short tval, qval;
  while(words >0)
    {
      ID = ((*pFp)&0xF000)>>12;
      if(ID< 8)
	{
	  qval = (*pFp)&0xfff; ++pFp;
	  tval = (*pFp)&0xfff; ++pFp;
	  if(tval==0) tval = -1;
	  if(qval==0) qval = -1;
	  if(ID< 4)
	    {
	      thin.qraw[ID] = qval;
	      thin.traw[ID] = tval;
	    }
	  else
	    {
#ifndef __WITH_HODOSCOPE
	      thick.qraw[ID-4] = qval;
	      thick.traw[ID-4] = tval;
#endif
	    }
	  words -= 2;
	}
      else if (ID == 8)
	{
	  qval = (*pFp)&0xfff; ++pFp;
	  if(qval==0) qval = -1;
	  pot.qraw = qval;
	  words -= 1;
	}
      else
	{
	  ++pFp;
	  words -= 1;
	}
    }
};

//---------------------------------------------------------//
// class sweeper_diamond_detector

#ifdef __WITH_DIAMOND
// raw
void
raw::sweeper_diamond_detector::reset()
{
  for(unsigned short ch = 0; ch< DIA_CH; ++ch)
    {
      traw[ch] = -1;
      qraw[ch] = -1;
    }
};

void
raw::sweeper::unpack_diamond(unsigned short* pDia)
{
  unsigned short words = (*(pDia-2))-2, ch; 

  while (words >0)
    {
      ch = ((*pDia)&0xf000)>>12; 
      diamond.traw[ch] = (*pDia)&0xfff;
      ++pDia; --words;
    } 
};

// var
void
var::sweeper_diamond_detector::write(const char* name, FILE* f)
{
  for(unsigned short i=0; i< DIA_CH; ++i)
    {
      fprintf(f, "%s.t_slope[%d]  = %f;\n",name,i,t_slope[i]);
      fprintf(f, "%s.q_slope[%d]  = %f;\n",name,i,q_slope[i]);
      fprintf(f, "%s.t_offset[%d] = %f;\n",name,i,t_offset[i]);
      fprintf(f, "%s.q_offset[%d] = %f;\n",name,i,q_offset[i]);
    }
};

// cal
void
cal::sweeper_diamond_detector::reset()
{
  for(unsigned short ch=0; ch< DIA_CH; ++ch)
    {
      tcal[ch] = -1;
      qcal[ch] = -1;
    }
  strip = -1;
  nhits = -1;
  t_hit = -1;
};

void
cal::sweeper_diamond_detector::calibrate(const raw::sweeper_diamond_detector& rw,
					 const var::sweeper_diamond_detector& v,
					 const double& jittersub)
{
  if(is_valid(jittersub))
    {
      nhits = 0;
      for(unsigned int i=0; i<DIA_CH; ++i)
	{
	  if(is_valid(rw.traw[i]))
	    {
	      tcal[i] = rw.traw[i] * v.t_slope[i] + v.t_offset[i] - jittersub;
	      qcal[i] = rw.qraw[i] * v.q_slope[i] + v.q_offset[i];
	      ++nhits;
	      strip = i;
	    }
	}
      if(nhits == 1)
	{
	  t_hit = tcal[strip];
	}
      else
	{
	  strip = -1;
	}
    }
}
#endif


//---------------------------------------------------------//
// class sweeper_tof

// raw
void
raw::sweeper::unpack_tof(unsigned short* pTof)
{
  unsigned short words = *(pTof-2)-2, ch;

  while (words >0)
    {
      ch = ((*pTof)&0xf000)>>12;
      switch(ch)
	{
	case CH_A1900:
	  a1900.traw = (*pTof)&0xfff;
	  ++pTof; --words;  break;
	case CH_RF:
	  rf.traw    = (*pTof)&0xfff;
	  ++pTof; --words;  break;
	case CH_POT:
	  pot.traw   = (*pTof)&0xfff;
	  ++pTof; --words;  break;
	default:
	  ++pTof; --words;  break;
	}
    }
};

// var
void
var::sweeper_tofcorr::write(const char* name, FILE* f)
{
  fprintf(f, "%s.x = %f;\n", name, x);
  fprintf(f, "%s.tx = %f;\n", name, tx);
  fprintf(f, "%s.x2 = %f;\n", name, x2);
  fprintf(f, "%s.tx2 = %f;\n", name, tx2);
  fprintf(f, "%s.xtx = %f;\n", name, xtx);
};

void
var::sweeper_tof::write(const char* name, FILE* f)
{
  std::string corrname = name; corrname += ".rf";
  rf.write(corrname.c_str(), f);
  corrname = name; corrname += ".a1900";
  a1900.write(corrname.c_str(), f);
  corrname = name; corrname += ".pot";
  pot.write(corrname.c_str(), f);
};

// cal
void
cal::sweeper_tof::reset()
{
  rf_a1900   = -1;
  rf_pot     = -1;  
  rf_thin    = -1; 
  a1900_pot  = -1;
  a1900_thin = -1;
  pot_thin   = -1;
#ifdef __WITH_DIAMOND
  rf_diamond    = -1;
  a1900_diamond = -1;
  pot_diamond   = -1;
  diamond_thin  = -1;
#endif
};

#ifdef __WITH_DIAMOND
void
cal::sweeper_tof::calculate(const double& rf,  const double& a1900,
			    const double& pot, const double& thin,
			    const double& dia)
{
  if(is_valid(rf))
    {
      if(is_valid(a1900))
	rf_a1900 = a1900 - rf;
      if(is_valid(pot))
	rf_pot = pot - rf;
      if(is_valid(dia))
	rf_diamond = rf - dia;
      if(is_valid(thin))
	rf_thin = thin - rf;
    }
  if(is_valid(a1900))
    {
      if(is_valid(pot))
	a1900_pot = pot - a1900;
      if(is_valid(dia))
	a1900_diamond = a1900 - dia;
      if(is_valid(thin))
	a1900_thin = thin - a1900;
    }
  if(is_valid(pot))
    {
      if(is_valid(dia))
	pot_diamond = pot - dia;
      if(is_valid(thin))
	pot_thin = thin - pot;
    }
  if(is_valid(dia))
    {
      if(is_valid(thin))
	diamond_thin = dia - thin;
    }
};
#else
void
cal::sweeper_tof::calculate(const double& rf,  const double& a1900,
			    const double& pot, const double& thin)
{
  if(is_valid(rf))
    {
      if(is_valid(a1900))
	rf_a1900 = a1900 - rf;
      if(is_valid(pot))
	rf_pot = pot - rf;
      if(is_valid(thin))
	rf_thin = thin - rf;
    }
  if(is_valid(a1900))
    {
      if(is_valid(pot))
	a1900_pot = pot - a1900;
      if(is_valid(thin))
	a1900_thin = thin - a1900;
    }
  if(is_valid(pot))
    {
      if(is_valid(thin))
	pot_thin = thin - pot;
    }
};
#endif

//---------------------------------------------------------//
// class sweeper_ftrack

// var
void
var::sweeper_ftrack::write(const char* name, FILE* f)
{
  fprintf(f, "%s.z = %f;\n", name, z);
  fprintf(f, "%s.filename = \"%s\";\n", name, filename.c_str());
};

// cal
void
cal::sweeper_ftrack::reset()
{
  x  = -1;
  tx = -1;
  y  = -1;
  ty = -1;
};

void
cal::sweeper_ftrack::calculate(const cal::sweeper_track_crdc& tcrdc1,
			       const var::sweeper_ftrack& v)
{ 
  static cosy_map fmap;
  static int ncalls = 0, goodmap = 0;
  if(ncalls == 0) {
    goodmap = fmap.initialize(v.filename);
    ++ncalls;
  }
  if(goodmap == -1) return;

  static const int npar = fmap.get_npar();
  static const int ncoef = fmap.get_ncoef();
  static const int nlines = fmap.get_nlines();

  static int nprints = 0;
  if(npar != 6 || ncoef != 5) {
    if(nprints ==0) {
      fprintf(stderr, "Invalid forward map file. Aborting forward map calculation.\n\n");
      ++nprints;
    }
    return;
  }
  static double input[6];
  input[0] = tcrdc1.x  / 1000; //\m
  input[1] = tcrdc1.tx / 1000; //\rad
  input[2] = tcrdc1.y  / 1000; //\m
  input[3] = tcrdc1.ty / 1000; //\rad
  input[4] = 0;                //\length
  input[5] = 0;                //\de

  static double output[6]; //\ { trgt_x, trgt_tx, trgt_y, trgt_ty, na, na }
  for(int i=0; i< 6; ++i)
    output[i] = 0;

  if(is_valid(tcrdc1.x)  && is_valid(tcrdc1.y) &&
     is_valid(tcrdc1.tx) && is_valid(tcrdc1.ty)) {
  double factor;
  for(int i=0; i< nlines; ++i)
    {
      factor = 1;
      for(int j=0; j< npar; ++j)
	factor *= pow(input[j], fmap.get_pwr(i,j));
      for(int k=0; k< ncoef; ++k)
	output[k] += factor * fmap.get_coef(i,k);
    }

  if(v.z == 0)
    {
      x  = output[0] * 1000; //\mm
      tx = output[1] * 1000; //\mrad
      y  = output[2] * 1000; //\mm
      ty = output[3] * 1000; //\mrad
    }
  else //\project to a different position
    {
      x  = (output[0] + v.z*tan(output[1])) * 1000; //\mm
      tx =  output[1] * 1000;                       //\mrad
      y  = (output[2] + v.z*tan(output[3])) * 1000; //\mm
      ty =  output[3] * 1000;                       //\mrad
    }
  }
};

//---------------------------------------------------------//
// class sweeper_itrack

// var
void
var::sweeper_itrack::write(const char* name, FILE* f)
{
  fprintf(f, "%s.z = %f;\n", name, z);
  fprintf(f, "%s.tx_offset = %f;\n", name, tx_offset);
  fprintf(f, "%s.ty_offset = %f;\n", name, ty_offset);
  fprintf(f, "%s.filename = \"%s\";\n", name, filename.c_str());
};

// cal
void
cal::sweeper_itrack::reset()
{
  x   = -1;
  tx  = -1;
  y   = -1;
  ty  = -1;
  len = -1;
  de  = -1;
};

void
cal::sweeper_itrack::calculate(const cal::sweeper_crdc& crdc1,
			       const double& trgt_x,
			       const var::sweeper& v)
{
  static cosy_map imap;
  static int ncalls = 0, goodmap = 0;
  static int maptype = 0; //\ 4 = cosy, 5 = schiller
  const var::sweeper_itrack& vv = v.itrack;
  if(ncalls == 0) {
    goodmap = imap.initialize(vv.filename);
    ++ncalls;
    if(goodmap != -1) {
      double col5sum = 0;
      for(int i=0; i< imap.get_nlines(); ++i)
	col5sum += imap.get_coef(i, 4);
      if(col5sum >0) {
	maptype = 5;
	printf("\n"
	       "Map file %s\n"
	       "has non-zero entries in the 5th collumn.\n"
	       "Performing a 5-parameter inverse reconstruction.\n\n",
	       vv.filename.c_str());
      } else {
	maptype = 4;
	printf("\n"
	       "Map file %s\n"
	       "has only zeros in the 5th collumn.\n"
	       "Performing a 4-parameter inverse reconstruction.\n\n",
	       vv.filename.c_str());
      }
    }
  }
  if(goodmap == -1) return;

  static const int npar = imap.get_npar();
  static const int ncoef = imap.get_ncoef();
  static const int nlines = imap.get_nlines(); 

  static int nprints = 0;
  if(npar != 5 || ncoef != 5) {
    if(nprints ==0) {
      fprintf(stderr, "Invalid inverse map file. Aborting inverse map calculation.\n\n");
      ++nprints;
    }
    return;
  }
  static double input[5];
  input[0] = crdc1.x  / 1000; //\m
  input[1] = crdc1.tx / 1000; //\mrad
  input[2] = crdc1.y  / 1000; //\m
  input[3] = crdc1.ty / 1000; //\rad
  if(maptype == 5)
    input[4] = trgt_x / 1000; //\m
  else
    input[4] = 0;

  double output[5]; //\ { trgt_tx, trgt_y, trgt_ty, de, len }

  for(int i=0; i< 5; ++i)
    output[i] = 0;

  if(is_valid(crdc1.x)  && is_valid(crdc1.y)  && 
     is_valid(crdc1.tx) && is_valid(crdc1.ty) &&
     (maptype == 4 || is_valid(trgt_x))) {

  double factor;
  for(int i=0; i< nlines; ++i)
    {
      factor = 1;
      for(int j=0; j< npar;  ++j) {
	factor *= pow(input[j], imap.get_pwr(i, j));
      }
      for(int k=0; k< ncoef; ++k) {
	output[k] += factor * imap.get_coef(i, k);
      }
    }

  // get posns, angles
  tx = (output[0] + vv.tx_offset) * 1000; //\mrad
  y  =  output[1] * 1000; //\mm
  ty = (output[2] + vv.ty_offset) * 1000; //\mrad
  de =  output[3];
  if(maptype == 4)
    {
      x  =  0;
      len = output[4];
    }
  else
    {
      x  = trgt_x; //\mm
      if(crdc1.tx != 0) {
	len =(output[4] + v.crdc1.z + (v.thin.z-v.crdc1.z)/cos(crdc1.tx/1000));
	len *= 100; //\ cm from trgt -> thin scint
      }
    }
  if(vv.z != 0) //\calculate projection
    {
      x += vv.z*tan(tx/1000) * 1000; //\mm
      y += vv.z*tan(ty/1000) * 1000; //\mm
    }
  }
};

//---------------------------------------------------------//
// class sweeper_focus

// var
void
var::sweeper_focus::write(const char* name, FILE* f)
{
  fprintf(f, "%s.z = %f;\n", name, z);
};

// cal
void
cal::sweeper_focus::reset()
{
  x  = -1;
  tx = -1;
  y  = -1;
  ty = -1;
};

void
cal::sweeper_focus::calculate_image(const cal::sweeper_crdc& p1, const var::sweeper_crdc& v1,
				    const cal::sweeper_crdc& p2, const var::sweeper_crdc& v2,
				    const var::sweeper_focus& v)
{
  if(v1.z == v2.z)
    {
      fprintf(stderr,
	      "Cannot calculate image for focus. "
	      "Please set crdc1.z and crdc2.z to different values.\n");
      return;
    }
  if(is_valid(p1.x) && is_valid(p2.x))
    {
      tx = 1000 * atan((p2.x - p1.x) / (1000 * (v2.z - v1.z)));
      x  = p1.x + 1000 * (v.z - v1.z) * tan(tx / 1000);
    }
  if(is_valid(p1.y) && is_valid(p2.y))
    {
      ty = 1000 * atan((p2.y - p1.y) / (1000 * (v2.z - v1.z)));
      y  = p1.y + 1000 * (v.z - v1.z) * tan(ty / 1000);
    }
};


//---------------------------------------------------------//
// class sweeper

// raw
void
raw::sweeper::reset()
{
  trigger.reset();
  crdc1.reset();
  crdc2.reset();
  tcrdc1.reset();
  tcrdc2.reset();
  ic.reset();
  thin.reset();
  tdc.reset();
#ifdef __WITH_SEGTARG
  st.reset();
#endif
#ifdef __WITH_HODOSCOPE
  hodo.reset();
#else
  thick.reset();
#endif
  pot.reset();
  a1900.reset();
  rf.reset(); 
#ifdef __WITH_DIAMOND
  diamond.reset();
#endif
};

void
raw::sweeper::unpack(unsigned short* pS)
{

  // Passed a pointer which points at the first data
  // word in a sweeper packet, the two words before it
  // are the length of the sweeper packet and the packet
  // id that was used to distinguish it as a sweeper packet

  // Philosophy of the unpacker: read the subpacket header
  // (length and size) into the variables packetlength and
  // packettag, via the pointer pS, whose position we increment such that
  // it points at the first data word in the subpacket. Then based on 
  // the packettag, decide what to do next. Normally we will pass the
  // memory location of pS onto the approaprite unpack function for the
  // packet identified by packettag. In any case, pS is always incremented by
  // the value (packetlength-2), so that it will point exactly at the beginning
  // of the header of the next subpacket.

  unsigned short nWords = *(pS-2) - 2;
  unsigned short packetlength, packettag, ID = 0;

  // skip version number
  ++pS;
  --nWords;

  while(nWords >0)
    {
      packetlength = *pS; ++pS;
      packettag = *pS; ++pS;

      switch(packettag)
	{
	case SWEEPER_TIMESTAMP_PACKET:
	  unpack_time_stamp(pS);
	  pS += packetlength-2;
	  break;

	case SWEEPER_TRIGGER_PACKET:
	  trigger.unpack(pS);
	  pS += packetlength-2;
	  break;

	case SWEEPER_TOF_PACKET:
	  unpack_tof(pS);
	  pS += packetlength-2;
	  break;

	case SWEEPER_DIA_PACKET:
#ifdef __WITH_DIAMOND
	  unpack_diamond(pS);
	  pS += packetlength-2;
	  break;
#else
	  std::cerr << "Found a diamond packet tag: 0x" << packettag <<"\n";
	  std::cerr << "But the flag to unpack it is not set!\n";
	  std::cerr << "You can change it in sweeper.hh, line 4.\n\n";
	  pS += packetlength-2;
	  break;
#endif

        case SWEEPER_FP_TA_SEG_PACKET:
#ifdef __WITH_SEGTARG
          st.unpack(pS);
	  pS += packetlength-2;
	  break;
#endif

	case SWEEPER_FP_HODO_PACKET:
#ifdef __WITH_HODOSCOPE
	  //std::cout <<"Hodoscope packet!" <<"\n";
	  //ID = *pS;
	  //pS++;
	  hodo.unpack(pS);
	  pS += packetlength-2;
	  break;

#else
	  std::cerr << "Found a hodoscope packet tag: 0x" << packettag <<"\n";
	  std::cerr << "But the flag to unpack it is not set!\n";
	  std::cerr << "You can change it in sweeper.hh, line 6.\n\n";
	  pS += packetlength-2;
	  break;
#endif
	case SWEEPER_FP_SCINT_PACKET:
	  unpack_fp_scint(pS);
	  pS += packetlength-2;
	  break;

	case SWEEPER_FP_IC_PACKET:
	  ic.unpack(pS);
	  pS += packetlength-2;
	  break;

	case SWEEPER_FP_CRDC_PACKET:
	  ID = *pS;
	  if(ID == 0)  crdc1.unpack(pS+1,0);
	  if(ID == 1)  crdc2.unpack(pS+1,1);
	  if(ID == 2) tcrdc1.unpack(pS+1);
	  if(ID == 3) tcrdc2.unpack(pS+1);
	  pS += packetlength-2;
	  break;

	case SWEEPER_VME_TDC_PACKET:
	  tdc.unpack(pS);
	  pS += packetlength-2;
	break;

	case SWEEPER_PPAC1_PACKET:
	  pS += packetlength-2;
	break;

	case SWEEPER_PPAC2_PACKET:
	  pS += packetlength-2;
	break;

	default:
	  std::cerr << "Unrecognized sweeper packet tag: ";
	  std::cerr << "0x"<< std::hex << packettag <<". Skipping.\n";
	  pS += packetlength-2;
	  break;
	}

	for(int i=0; i<4; i++)
	  {
	    thin.traw[i] = tdc.data[i][0];
	  }

	rf.traw = tdc.data[5][0];
	pot.traw = tdc.data[6][0];
	a1900.traw = tdc.data[7][0];

      nWords -= packetlength;
    }
};

// var
void
var::sweeper::write(const char* name, const char* filename)
{
  std::ifstream* fcheck = new std::ifstream(filename, std::ios::in);
  if(!fcheck->fail()) {
    std::string answer;
    std::cout << "\nThe file "<<filename<<" aready exists. Do you want to overwrite it (y/n)?\n";
    std::cin >> answer;
    if(!( answer=="y" || answer == "Y" )) {
      std::cout << "\nSaving of variables aborted.\n\n";
      return;
    }
  }
  delete fcheck;

  FILE* fout;
  fout = fopen(filename, "w");

  time_t ttt;
  time (&ttt);
  fprintf(fout, "// Sweeper Variables File: %s\n", filename);
  fprintf(fout, "// Saved on: %s\n", ctime(&ttt));
  fprintf(fout, "{\n\n\n");

  fprintf(fout,
	  "printf(\"Reading in variable settings for %s\\n\nWARNING: If the instance of var::sweeper that you are using for your calibration is not called %s, this file is doing nothing!!!\\n\\n\");\n\n",
	  name, name);

  fprintf(fout, "%s.brho = %f;\n",         name, brho);
  fprintf(fout, "%s.mass = %f;\n",         name, mass);
  fprintf(fout, "%s.charge = %i;\n",       name, charge);
  fprintf(fout, "%s.target_eloss = %f;\n", name, target_eloss);

  std::string tmp;
  tmp = name; tmp+=".crdc1"   ; crdc1.write(tmp.c_str(),   fout);
  tmp = name; tmp+=".crdc2"   ; crdc2.write(tmp.c_str(),   fout);
  tmp = name; tmp+=".tcrdc1"  ; tcrdc1.write(tmp.c_str(),  fout);
  tmp = name; tmp+=".tcrdc2"  ; tcrdc2.write(tmp.c_str(),  fout);
  tmp = name; tmp+=".focus"   ; focus.write(tmp.c_str(),   fout);
  tmp = name; tmp+=".ic"      ; ic.write(tmp.c_str(),      fout);
  tmp = name; tmp+=".thin"    ; thin.write(tmp.c_str(),    fout);
#ifdef __WITH_SEGTARG
  tmp = name; tmp+=".st"    ; st.write(tmp.c_str(),    fout);
#endif
#ifdef __WITH_HODOSCOPE
  tmp = name; tmp+=".hodo"    ; hodo.write(tmp.c_str(),    fout);
#else
  tmp = name; tmp+=".thick"   ; thick.write(tmp.c_str(),   fout);
#endif
  tmp = name; tmp+=".pot"     ; pot.write(tmp.c_str(),     fout);
  tmp = name; tmp+= ".rf"     ; rf.write(tmp.c_str(),      fout);
  tmp = name; tmp+= ".a1900"  ; a1900.write(tmp.c_str(),   fout);
  tmp = name; tmp+= ".tofcorr"; tofcorr.write(tmp.c_str(), fout);
  tmp = name; tmp+= ".ftrack" ; ftrack.write(tmp.c_str(),  fout);
  tmp = name; tmp+= ".itrack" ; itrack.write(tmp.c_str(),  fout);

  fprintf(fout, "\n\n\n}\n");
  fclose(fout);
};

// cal
void
cal::sweeper::reset()
{
  crdc1.reset();
  crdc2.reset();
  tcrdc1.reset();
  tcrdc2.reset();
  ic.reset();
  thin.reset();
#ifdef __WITH_SEGTARG
  st.reset();
#endif
#ifdef __WITH_HODOSCOPE
  hodo.reset();
#else
  thick.reset();
#endif
  pot.reset();
  rf.reset();
  a1900.reset();
  tof.reset();
  tofcorr.reset();
  focus.reset();
  ftrack.reset();
  itrack.reset();
  v = -1;
  e = -1;
  p = -1;
#ifdef __WITH_DIAMOND
  diamond.reset();
#endif
};

void
cal::sweeper::calculate_energy(const var::sweeper& v)
{
  static double mass_warned = 0;
  if(v.mass == 0) {
    if(mass_warned == 0) {
      fprintf(stderr,
	      "\nWarning: sweeper mass set to zero. "
	      "Can't calculate energy.\n\n");
      ++mass_warned;
    }
    return;
  }
  // central track stuff
  double betagamma0 = v.brho / 3.107 * v.charge / v.mass;
  double gamma0 = sqrt(betagamma0*betagamma0 + 1);
  double energy0 = v.mass * AMU_MASS * (gamma0 - 1); //\MeV
  
  // calculate e, p
  if(is_valid(itrack.de))
  {
    this->e = (1 + itrack.de) * energy0; //\MeV
    this->p = e * sqrt(1 + 2 * v.mass * AMU_MASS / e) / 1e3; //\GeV/c
    this->e /= v.mass;
  }
};


void
cal::sweeper::calibrate(const raw::sweeper* rw,
			const var::sweeper& v)
{
  /* Pass id tag for crdc 1 / 2 THR 13 September 2016 */
  crdc1.calibrate(rw->crdc1, v.crdc1,0);
  crdc2.calibrate(rw->crdc2, v.crdc2,1);
  crdc1.calculate_image(crdc1, v.crdc1, crdc2, v.crdc2);
  crdc2.calculate_image(crdc1, v.crdc1, crdc2, v.crdc2);

  tcrdc1.calibrate(rw->tcrdc1, v.tcrdc1);
  if(v.tcrdc2.force_correlation) {
    tcrdc2.force_correlation(tcrdc1, v.tcrdc2);
    tcrdc2.calibrate_y(rw->tcrdc2, v.tcrdc2);
  }
  else
    tcrdc2.calibrate(rw->tcrdc2, v.tcrdc2);
  tcrdc1.calculate_image(tcrdc1, v.tcrdc1, tcrdc2, v.tcrdc2);
  tcrdc2.calculate_image(tcrdc1, v.tcrdc1, tcrdc2, v.tcrdc2);

  focus.calculate_image(crdc1, v.crdc1, crdc2, v.crdc2, v.focus);

  ic.calibrate(rw->ic, v.ic);
  ic.correct(v.ic, crdc2.x);

  double js = -1;
  if(is_valid(rw->thin.traw[0]))
    js = rw->thin.traw[0] * v.thin.t_slope[0];
  thin.calibrate(rw->thin, v.thin, js);
  thin.calculate_image(crdc1, v.crdc1, crdc2, v.crdc2, v.thin.z);
  thin.position_correct(v.thin);

  pot.calibrate(rw->pot, v.pot, js);
  rf.calibrate(rw->rf, v.rf, js);
  a1900.calibrate(rw->a1900, v.a1900, js);
#ifdef __WITH_DIAMOND
  diamond.calibrate(rw->diamond, v.diamond, js);
  tof.calculate(rf.tcal, a1900.tcal, pot.tcal, thin.t, diamond.t_hit);
#else
  tof.calculate(rf.tcal, a1900.tcal, pot.tcal, thin.t);
#endif

#ifdef __WITH_SEGTARG
  st.calibrate(rw->st,v.st);
#endif

#ifdef __WITH_HODOSCOPE
  hodo.calibrate(rw->hodo,v.hodo);
  hodo.calculate_image(crdc1, v.crdc1, crdc2, v.crdc2, v.hodo.z);
#else
  thick.calibrate(rw->thick, v.thick, js);
  thick.calculate_image(crdc1, v.crdc1, crdc2, v.crdc2, v.thick.z);
  thick.position_correct(v.thick);
#endif
  tofcorr.calculate(tof, v.tofcorr, focus);

  if(is_valid(tof.pot_thin))
    {
      if(tof.pot_thin != 0)
	this->v = (v.thin.z - v.pot.z) / tof.pot_thin;
    }

  if(v.ftrack.filename != "")
    ftrack.calculate(tcrdc1, v.ftrack);

  if(v.itrack.filename != "")
    itrack.calculate(crdc1,  ftrack.x,  v);

  calculate_energy(v);

};
