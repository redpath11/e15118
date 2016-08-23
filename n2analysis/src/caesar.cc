#include "caesar.hh"
#include "utils.hh"
#include <iostream>
#include <cmath>

// everything for setting and getting values from rings
// by specifying an index is in the following file:
#include "caesar_setters_getters.hh"


//---------------------------------------------------------//
// class fera

// raw
void
raw::fera::reset()
{
  for(unsigned short i=0; i< FERA_MAX_VSN; ++i)
    {
      for(unsigned short j=0; j< FERA_N_PER_VSN; ++j)
	{
	  eraw[i][j] = -1;
	  traw[i][j] = -1;
	}
    }
};

//---------------------------------------------------------//
// class caesar_ring

// raw
void
raw::caesar_ring10::reset()
{
  for(unsigned short i=0; i< 10; ++i)
    {
      eraw[i] = -1;
      traw[i] = -1;
    }
};

void
raw::caesar_ring14::reset()
{
  for(unsigned short i=0; i< 14; ++i)
    {
      eraw[i] = -1;
      traw[i] = -1;
    }
};

void
raw::caesar_ring24::reset()
{
  for(unsigned short i=0; i< 24; ++i)
    {
      eraw[i] = -1;
      traw[i] = -1;
    }
};

// cal
void
cal::caesar_ring10_ab::reset()
{
  for(unsigned short i=0; i< 10; ++i)
    {
      n0_ecal[i] = -1;
      n0_edop[i] = -1;

      n1_ecal[i] = -1;
      n1_edop[i] = -1;

      n2_ecal[i] = -1;
      n2_edop[i] = -1;

      ng_ecal[i] = -1;
      ng_edop[i] = -1;
    }
};

void
cal::caesar_ring10::reset()
{
  for(unsigned short i=0; i< 10; ++i)
    {
      ecal[i] = -1;
      tcal[i] = -1;
      edop[i] = -1;
    }
  ab.reset();
};

void
cal::caesar_ring14_ab::reset()
{
  for(unsigned short i=0; i< 14; ++i)
    {
      n0_ecal[i] = -1;
      n0_edop[i] = -1;
	 
      n1_ecal[i] = -1;
      n1_edop[i] = -1;
	 
      n2_ecal[i] = -1;
      n2_edop[i] = -1;
	 
      ng_ecal[i] = -1;
      ng_edop[i] = -1;
    }
};

void
cal::caesar_ring14::reset()
{
  for(unsigned short i=0; i< 14; ++i)
    {
      ecal[i] = -1;
      tcal[i] = -1;
      edop[i] = -1;
    }
  ab.reset();
};

void
cal::caesar_ring24_ab::reset()
{
  for(unsigned short i=0; i< 24; ++i)
    {
      n0_ecal[i] = -1;
      n0_edop[i] = -1;
	 
      n1_ecal[i] = -1;
      n1_edop[i] = -1;
	 
      n2_ecal[i] = -1;
      n2_edop[i] = -1;
	 
      ng_ecal[i] = -1;
      ng_edop[i] = -1;
    }
};

void
cal::caesar_ring24::reset()
{
  for(unsigned short i=0; i< 24; ++i)
    {
      ecal[i] = -1;
      tcal[i] = -1;
      edop[i] = -1;
    }
  ab.reset();
};

//---------------------------------------------------------//
// class caesar_addback

// cal
void
cal::caesar_addback::reset()
{
  etot         = -1;
  ecal         = -1;
  edop         = -1;
  tcal         = -1;
  hitdet_n1[0] = -1;
  hitdet_n1[1] = -1;
  hitdet_n2[0] = -1;
  hitdet_n2[1] = -1;
  hitdet_n2[2] = -1;
};


//---------------------------------------------------------//
// class caesar

// raw
// private
void
raw::caesar::insert_ring(short edata, short tdata, short vsn, short ch)
{ 
  static raw::caesar_detector_map caesarmap;
  short rng = caesarmap.ring(vsn, ch);
  short det = caesarmap.ch(vsn, ch);
  const char* err = "Invalid ring and detector combo: ";

  switch(rng)
    {
    case 0: //\ring a
      if(det< 10) {
	ring_a.eraw[det] = edata;
	ring_a.traw[det] = tdata;
      }
      else
	fprintf(stderr, "%s%i, %i\n", err, rng, det);
      break;
    case 1: //\ring b
      if(det< 14) {
	ring_b.eraw[det] = edata;
	ring_b.traw[det] = tdata;
      }
      else
	fprintf(stderr, "%s%i, %i\n", err, rng, det);
      break;
    case 2: //\ring c
      if(det< 24) {
	ring_c.eraw[det] = edata;
	ring_c.traw[det] = tdata;
      }
      else
	fprintf(stderr, "%s%i, %i\n", err, rng, det);
      break;
    case 3: //\ring d
      if(det< 24) {
	ring_d.eraw[det] = edata;
	ring_d.traw[det] = tdata;
      }
      else
	fprintf(stderr, "%s%i, %i\n", err, rng, det);
      break;
    case 4: //\ring e
      if(det< 24) {
	ring_e.eraw[det] = edata;
	ring_e.traw[det] = tdata;
      }
      else
	fprintf(stderr, "%s%i, %i\n", err, rng, det);
      break;
    case 5: //\ring f
      if(det< 24) {
	ring_f.eraw[det] = edata;
	ring_f.traw[det] = tdata;
      }
      else
	fprintf(stderr, "%s%i, %i\n", err, rng, det);
      break;
    case 6: //\ring g
      if(det< 24) {
	ring_g.eraw[det] = edata;
	ring_g.traw[det] = tdata;
      }
      else
	fprintf(stderr, "%s%i, %i\n", err, rng, det);
      break;
    case 7: //\ring h
      if(det< 24) {
	ring_h.eraw[det] = edata;
	ring_h.traw[det] = tdata;
      }
      else
	fprintf(stderr, "%s%i, %i\n", err, rng, det);
      break;
    case 8: //\ring i
      if(det< 14) {
	ring_i.eraw[det] = edata;
	ring_i.traw[det] = tdata;
      }
      else
	fprintf(stderr, "%s%i, %i\n", err, rng, det);
      break;
    case 9: //\ring j
      if(det< 10) {
	ring_j.eraw[det] = edata;
	ring_j.traw[det] = tdata;
      }
      else
	fprintf(stderr, "%s%i, %i\n", err, rng, det);
      break;
    default:
      fprintf(stderr, "Invalid ring: %i\n", rng);
      break;
    }
};

// public
void
raw::caesar::reset()
{
  trigbit   = -1;
  evtlength = -1;
  e_hit     = -1;
  t_hit     = -1;
  vsn.reset();
  ring_a.reset();
  ring_b.reset();
  ring_c.reset();
  ring_d.reset();
  ring_e.reset();
  ring_f.reset();
  ring_g.reset();
  ring_h.reset();
  ring_i.reset();
  ring_j.reset();
};

void
raw::caesar::unpack(unsigned short* p)
{
  // Credit to D. Weisshaar, NSCL, the author of this FERA unpacking
  // routine, orignally written for his SpecTcl code. It has been
  // modified here to fit the raw::caesar tree structure and to
  // remove the use of specialized SpecTcl classes such as CEvent.

  unsigned short PacketLength = *(p-2);
  unsigned short nWords;

  // Min & max values needed to unpack fera-> caesar
  short min_en = 0;
  short max_en = FERA_RANGE;
  short min_ti = 0;
  short max_ti = FERA_RANGE;

  register unsigned short wrdleft;

  {
    int version = *p; ++p;

    switch (version)
    {
    case FERA_VERSION_00:
      break;

    case FERA_VERSION_01:
      trigbit = *p; ++p;
      PacketLength--;
      break;
		
    default:
      printf("Uncorrect version number of CAESAR data!\n");
      return;
    }
  }

  nWords = PacketLength - 3;

  evtlength = PacketLength;
  e_hit = 0;
  t_hit = 0;

  while (nWords > 0) {
    unsigned short packet_id, packet_length;
    
    wrdleft   = *p; ++p;
    packet_length = wrdleft;
    
    packet_id = *p; ++p;
    wrdleft -= 2;

#ifdef FERA_CHECK_PKT
    if(packet_id == FERA_TIME_ID || 
       packet_id == FERA_ENERGY_ID)
#endif
    {
      while (wrdleft > 0)
      { 
	unsigned short header, numch;
	unsigned short data = -1, n_vsn, n_chn;
	
	header = *p; ++p;
	wrdleft--;
	
#ifdef FERAN_CHECK_PKT
	if (header&0x8000 != 0x8000) 
	{
	  printf("FERA Header word not found!\n");
	}
#endif
	numch = (header & 0x7800) >> 11;
	if (numch == 0) numch = 16; 

	for (int i=0; i<numch; i++) 
	{
	  data = *p; ++p;
	  wrdleft--; 
	  n_chn = (data & FERA_DETMASK) >> 11;
	  data &= FERA_NRGMASK;
  
	  //
	  // vsn is a number 1...FERA_MAX_VSN in data stream
	  // I want to use it 0...FERA_MAX_VSN-1
	  //
	  n_vsn =  header & 0xff;
	  if(n_vsn)
	  {
	    n_vsn--;
	    {
	      if(n_vsn < FERA_MAX_VSN && n_chn < FERA_N_PER_VSN)
	      {
		if(packet_id == FERA_ENERGY_ID)
		{
		  if(data >min_en && data< max_en) 
		  {
		    vsn.eraw[n_vsn][n_chn] = data;
		    e_hit += 1;
		  }
		  else
		  {
		    vsn.eraw[n_vsn][n_chn] = data + FERA_ROUTING;
		  }
		}
		else if(packet_id == FERA_TIME_ID)
		{
		   if(data >min_ti && data< max_ti) 
		   {
		     vsn.traw[n_vsn][n_chn] = data;
		     t_hit += 1;
		   }
		   else
		   {
		     vsn.traw[n_vsn][n_chn] = data + FERA_ROUTING;
		   }
		}
	      }
	      else
	      {
		std::cerr << "FERA unpack: VSN:" << n_vsn << " n_chn:" << n_chn
			  << "  exceed VSN/chn limit(s) of " << FERA_MAX_VSN 
			  << "/" << FERA_N_PER_VSN << "\n";
	      }
	    }
	    
	  } // if(n_vsn)
	  else
	  {
	    std::cerr << "FERA unpack: vsn == 0 read" << std::endl
		      << "header: 0x" << std::hex << header << std::dec
		      << "\n";
	  }
	} // for (int i=0; i<numch; i++)
      } // while (wrdleft > 0)
    } // if(packet_id == FERA_TIME_ID || 

#ifdef FERA_CHECK_PKT
    else 
    {
      fprintf(stderr, "Wrong packet ID: 0x%04x\n", packet_id);
      return;
    }
#endif

    nWords -= packet_length;
  } // while (nWords > 0)

  for(int i=0; i< FERA_MAX_VSN; ++i)
    {
      for(int j=0; j< FERA_N_PER_VSN; ++j)
	{
	  if(vsn.traw[i][j] != -1 && vsn.traw[i][j]< FERA_ROUTING &&
	     vsn.eraw[i][j] != -1 && vsn.eraw[i][j]< FERA_ROUTING)
	    {
	      insert_ring(vsn.eraw[i][j], vsn.traw[i][j], i, j);
	    }
	}
    }
};

// var

// Calculate doppler coefficients this method is private because
// it should only be used when it is called from set_beam_beta();
void 
var::caesar::calc_dop_coeff()
{
  double beta = target.get_beta();
  double the_gamma = 
    1/sqrt(1.-beta * beta);
  
  for(int ring=0; ring< CAESAR_RINGS; ring++)
    for(int det=0; det< caesar_det_per_ring[ring]; det++)
      {
	double x = get_pos_x(ring, det) - target.get_x();
	double y = get_pos_y(ring, det) - target.get_y();
	double z = get_pos_z(ring, det) - target.get_z();

	double __sqrt = sqrt(x*x + y*y + z*z);
	if(__sqrt != 0)
	  {
	    set_doppler(ring, det, the_gamma *
			  (1 - beta * (z/__sqrt)));
	  }
	else
	  {
	    fprintf(stderr,
		    "Warning: detector positions all == 0.\n"
		    "Cannot calculate doppler coefficients.\n\n"
		    );
	  }
      }
}

void
var::caesar::set_beam_beta(double beta)
{
  target.set_beta(beta);
  calc_dop_coeff();
  printf("Recalculating doppler coefficients.\n\n");
}

void
var::caesar::set_target_posn(double x,
			     double y,
			     double z)
{
  target.set_x(x);
  target.set_y(y);
  target.set_z(z);
  calc_dop_coeff();
  printf("Recalculating doppler coefficients.\n\n");
}

void var::caesar::set_target_params(double x,
				    double y,
				    double z,
				    double beta)
{
  target.set_x(x);
  target.set_y(y);
  target.set_z(z);
  target.set_beta(beta);
  calc_dop_coeff();
  printf("Recalculating doppler coefficients.\n\n");
}


// cal
// public
void
cal::caesar::reset()
{
  ring_a.reset();
  ring_b.reset();
  ring_c.reset();
  ring_d.reset();
  ring_e.reset();
  ring_f.reset();
  ring_g.reset();
  ring_h.reset();
  ring_i.reset();
  ring_j.reset();

  ab.reset();

  hit_raw = -1;
  hit_cor = -1;
  for(int i=0; i< CAESAR_DETECTORS; ++i)
    {
      hitdet_raw[i] = -1;
      hitdet_cor[i] = -1;
    }
};

int
cal::caesar::check_no_of_neighbors(int ring,
				   int det,
				   var::caesar& v)
{
  int neighbors=0;

  for(int i=0; i< CAESAR_MAX_NEIGHBORS; ++i)
    {
      int n_ring = v.get_neighbor_ring(ring, det, i);
      int n_det  = v.get_neighbor_det (ring, det, i);

      if(n_ring >= 0 && n_det > 0)
	{
	  double _ecal = get_ecal(n_ring, n_det);
	  if(is_valid(_ecal) && _ecal < CAESAR_ROUTE_CAL)
	    {
	      neighbors++;
	    }
	}
    }
  return neighbors;
}

bool
cal::caesar::a_is_neighbor_from_b(int ring_a, int det_a,
				  int ring_b, int det_b,
				  var::caesar & v)
{
  for(int i=0; i< CAESAR_MAX_NEIGHBORS; ++i)
  {
    int n_ring = v.get_neighbor_ring(ring_b, det_b, i);
    int n_det  = v.get_neighbor_det (ring_b, det_b, i);

    if(is_valid(n_ring) && is_valid(n_det))
      {
	if(n_ring == ring_a && n_det == det_a)
	  return true;
      }
  }

  return false;
}

void
cal::caesar::one_add_back(caesar_hit_det det,
			  var::caesar& v)
{
#ifdef CAESAR_AB_PSPEC
//   set_ab_n0_ecal(det.ring, det.chn, get_ecal(det.ring, det.chn));
//   set_ab_n0_edop(det.ring, det.chn, get_ecal(det.ring, det.chn) *
// 		 v.get_doppler(det.ring, det.chn));
#endif
  if(get_tcal(det.ring, det.chn) > v.left_time_gate &&
     get_tcal(det.ring, det.chn) < v.right_time_gate)
  {
#ifdef CAESAR_AB_PSPEC
    fprintf(stderr, "CAESAR_AB_PSPEC not implemented yet!!\n\n");
//     caesar.addback.ecal_n0p[det.ring][det.chn] = 
//       caesar.ecal[det.ring][det.chn];
//     caesar.addback.edop_n0p[det.ring][det.chn] = 
//       caesar.ecal[det.ring][det.chn] *
//       caesar.doppler[det.ring][det.chn];
#else
    set_ab_n0_ecal(det.ring, det.chn, get_ecal(det.ring, det.chn));
    set_ab_n0_edop(det.ring, det.chn, get_ecal(det.ring, det.chn) *
		   v.get_doppler(det.ring, det.chn));
#endif
  }
}

//
// Two (VALID!) detectors are given
// and addback will be done here
//
//
// CAESAR_AB_PSPEC set  : n1 set if tcal-encal 2d gate satisfied
//                        n1p set if n0 and 1d time gate staisfied
//
// CAESAR_AB_PSPEC unset: n1 set if 2d AND 1d gate satisfied
//                        no n1p spectra
//

void
cal::caesar::two_add_back(caesar_hit_det det1, 
			  caesar_hit_det det2,
			  var::caesar& v)
{
  double encal1 = get_ecal(det1.ring, det1.chn);
  double encal2 = get_ecal(det2.ring, det2.chn);

  double ensum = encal1 + encal2 + v.addback.n1_offset;

  bool prompt = false;
  if((get_tcal(det1.ring, det1.chn) > v.left_time_gate &&
      get_tcal(det1.ring, det1.chn) < v.right_time_gate) ||
     (get_tcal(det2.ring, det2.chn) > v.left_time_gate &&
      get_tcal(det2.ring, det2.chn) < v.right_time_gate))
  {
    prompt = true;
  }

  if(encal1 > encal2)
  {
#ifdef CAESAR_AB_PSPEC
    fprintf(stderr, "CAESAR_AB_PSPEC not implemented yet!!\n\n");
//     ecal_n1[det1.ring][det1.chn] =  ensum;
//     edop_n1[det1.ring][det1.chn] =  ensum *
//       caesar.doppler[det1.ring][det1.chn];
#endif
    if(prompt)
    {
#ifdef CAESAR_AB_PSPEC
//       ecal_n1p[det1.ring][det1.chn] =  ensum;
//       edop_n1p[det1.ring][det1.chn] =  ensum *
// 	caesar.doppler[det1.ring][det1.chn]; 
#else
      set_ab_n1_ecal(det1.ring, det1.chn, ensum);
      set_ab_n1_edop(det1.ring, det1.chn, ensum *
		     v.get_doppler(det1.ring, det1.chn));
#endif
    }
  }
  else 
  {
#ifdef CAESAR_AB_PSPEC
//     ecal_n1[det2.ring][det2.chn] =  ensum;
//     edop_n1[det2.ring][det2.chn] =  ensum *
//       caesar.doppler[det2.ring][det2.chn];
#endif
    if(prompt)
    {
#ifdef CAESAR_AB_PSPEC
//       ecal_n1p[det2.ring][det2.chn] =  ensum;
//       edop_n1p[det2.ring][det2.chn] =  ensum *
// 	caesar.doppler[det2.ring][det2.chn]; 
#else
      set_ab_n1_ecal(det2.ring, det2.chn, ensum);
      set_ab_n1_edop(det2.ring, det2.chn, ensum *
		     v.get_doppler(det2.ring, det2.chn));
#endif
    }

  }

  int det1_id = caesar_det_offset[det1.ring] + det1.chn;
  int det2_id = caesar_det_offset[det2.ring] + det2.chn;

  if(det1_id < det2_id)
  {
    ab.hitdet_n1[0] = det1_id; 
    ab.hitdet_n1[1] = det2_id; 
  }
  else
  {
    ab.hitdet_n1[1] = det1_id; 
    ab.hitdet_n1[0] = det2_id; 
  }
}

void
cal::caesar::three_add_back(caesar_hit_det det1, 
			    caesar_hit_det det2,
			    caesar_hit_det det3,
			    var::caesar& v)
{
  double encal1 = get_ecal(det1.ring, det1.chn);
  double encal2 = get_ecal(det2.ring, det2.chn);
  double encal3 = get_ecal(det3.ring, det3.chn);
  
  double ensum = encal1+encal2+encal3;

  if(encal1 > encal2 && encal1>encal3)
    {
      set_ab_n2_ecal(det1.ring, det1.chn, ensum);
      set_ab_n2_edop(det1.ring, det1.chn, ensum *
		     v.get_doppler(det1.ring, det1.chn));
    }
  else if (encal2 > encal3 && encal2>encal1)
    {
      set_ab_n2_ecal(det2.ring, det2.chn, ensum);
      set_ab_n2_edop(det2.ring, det2.chn, ensum *
		     v.get_doppler(det2.ring, det2.chn));
    }
  else
    {
      set_ab_n2_ecal(det3.ring, det3.chn, ensum);
      set_ab_n2_edop(det3.ring, det3.chn, ensum *
		     v.get_doppler(det3.ring, det3.chn));
    } 

  int det1_id = caesar_det_offset[det1.ring] + det1.chn;
  int det2_id = caesar_det_offset[det2.ring] + det2.chn;
  int det3_id = caesar_det_offset[det3.ring] + det3.chn;

  if(det1_id < det2_id)
    {
      if(det2_id < det3_id)
	{
	  ab.hitdet_n2[0] = det1_id; 
	  ab.hitdet_n2[1] = det2_id; 
	  ab.hitdet_n2[2] = det3_id; 
	}
      else
	if(det1_id < det3_id)
	  {
	    ab.hitdet_n2[0] = det1_id; 
	    ab.hitdet_n2[1] = det3_id; 
	    ab.hitdet_n2[2] = det2_id;
	  }
	else
	  {
	    ab.hitdet_n2[0] = det3_id; 
	    ab.hitdet_n2[1] = det1_id; 
	    ab.hitdet_n2[2] = det2_id;
	  }
    }
  else
    if(det1_id < det3_id)
      {
	ab.hitdet_n2[0] = det2_id; 
	ab.hitdet_n2[1] = det1_id; 
	ab.hitdet_n2[2] = det3_id;
      }
    else
      if(det2_id < det3_id)
	{
	  ab.hitdet_n2[0] = det2_id; 
	  ab.hitdet_n2[1] = det3_id; 
	  ab.hitdet_n2[2] = det1_id;
	}
      else
	{
	  ab.hitdet_n2[0] = det3_id; 
	  ab.hitdet_n2[1] = det2_id; 
	  ab.hitdet_n2[2] = det1_id;
	}
}

void
cal::caesar::fill_detlist(raw::caesar* craw)
{
  static caesar_hit_det hitdet;
  for(int i(0); i< 24; ++i)
    {
      if(i < 10)
	{
	  if( is_valid(craw->ring_a.eraw[i]) && is_valid(craw->ring_a.traw[i]) )
	    {
	      hitdet.ring = 0;
	      hitdet.chn  = i;
	      detlist.push_back(hitdet);
	    }
	}
      if(i< 14)
	{
	  if( is_valid(craw->ring_b.eraw[i]) && is_valid(craw->ring_b.traw[i]) )
	    {
	      hitdet.ring = 1;
	      hitdet.chn  = i;
	      detlist.push_back(hitdet);
	    }
	}
      if( is_valid(craw->ring_c.eraw[i]) && is_valid(craw->ring_c.traw[i]) )
	{
	  hitdet.ring = 2;
	  hitdet.chn  = i;
	  detlist.push_back(hitdet);
	}
      if( is_valid(craw->ring_d.eraw[i]) && is_valid(craw->ring_d.traw[i]) )
	{
	  hitdet.ring = 3;
	  hitdet.chn  = i;
	  detlist.push_back(hitdet);
	}
      if( is_valid(craw->ring_e.eraw[i]) && is_valid(craw->ring_e.traw[i]) )
	{
	  hitdet.ring = 4;
	  hitdet.chn  = i;
	  detlist.push_back(hitdet);
	}
      if( is_valid(craw->ring_f.eraw[i]) && is_valid(craw->ring_f.traw[i]) )
	{
	  hitdet.ring = 5;
	  hitdet.chn  = i;
	  detlist.push_back(hitdet);
	}
      if( is_valid(craw->ring_g.eraw[i]) && is_valid(craw->ring_g.traw[i]) )
	{
	  hitdet.ring = 6;
	  hitdet.chn  = i;
	  detlist.push_back(hitdet);
	}
      if( is_valid(craw->ring_h.eraw[i]) && is_valid(craw->ring_h.traw[i]) )
	{
	  hitdet.ring = 7;
	  hitdet.chn  = i;
	  detlist.push_back(hitdet);
	}
      if(i< 14)
	{
	  if( is_valid(craw->ring_i.eraw[i]) && is_valid(craw->ring_i.traw[i]) )
	    {
	      hitdet.ring = 8;
	      hitdet.chn  = i;
	      detlist.push_back(hitdet);
	    }
	}
      if(i< 10)
	{
	  if( is_valid(craw->ring_j.eraw[i]) && is_valid(craw->ring_j.traw[i]) )
	    {
	      hitdet.ring = 9;
	      hitdet.chn  = i;
	      detlist.push_back(hitdet);
	    }
	}
    }
}

void
cal::caesar::clear_detlists()
{
  detlist.clear();
  detlist_cal.clear();
}

void
cal::caesar::calibrate(raw::caesar* craw,
		       var::caesar& cvar,
		       double timing_ref)
{
  fill_detlist(craw);
  hit_raw = 0;

  // only loop over valid hits
  // (thus no is_valids() are necessary)
  for(detlist_iter  = detlist.begin();
      detlist_iter != detlist.end();
      detlist_iter++)
    {
     
      hit_raw += 1.;

      hitdet_raw[(int)hit_raw] = 
	caesar_det_offset[detlist_iter->ring] + detlist_iter->chn;
   
      // energy calibration
      {
	double enraw = craw->get_eraw(detlist_iter->ring,
				      detlist_iter->chn);
      	enraw += drand48();

	double en = 0;
	for(short order=0; order<= __CAESAR_ECAL_ORDER; ++order)
	  {
	    en += pow(enraw, order) * 
	      cvar.get_evar(detlist_iter->ring, detlist_iter->chn, order);
	  }

	set_ecal(detlist_iter->ring, detlist_iter->chn, en);

	double time = craw->get_traw(detlist_iter->ring,
				     detlist_iter->chn) ;
	time += cvar.t_shift;
	time += drand48(); 

	// walk correction
	if(cvar.enable_walk_corr)
	  {
	    en /= 8; //TEMPORARY
	
	    time -= 
	      cvar.get_t_sl1(detlist_iter->ring,
			     detlist_iter->chn) /
	      (en + cvar.get_t_xoff(detlist_iter->ring,
				    detlist_iter->chn));

	    time -=
	      cvar.get_t_sl2(detlist_iter->ring,
			     detlist_iter->chn) / (en*en);
	
	    time += cvar.t_tilt * en;
	  }
      
	// time calibration
	double t_cal (0);
	for(short order = 0; order<= __CAESAR_TCAL_ORDER; ++order)
	  {
	    t_cal += pow(time, order) *
	      cvar.get_tvar(detlist_iter->ring, detlist_iter->chn, order);
	  }

	set_tcal(detlist_iter->ring, detlist_iter->chn, t_cal);
     
      }
    }
  

#ifdef CAESAR_TESTSPECS
  fprintf(stderr, "CAESAR_TESTSPECS NOT IMPLEMENTED YET.\n\n");
//   // Doppler corrected energy spectra without additional constraints 
//   // checked in calculator (e.g. timing)
//   // r1:   hitraw == 1
//   // r2:   hitraw == 2
//   // r2nn: as r2 AND detectors are nearest neighbours
//   if(caesar.hit_raw == 1)
//     {
//       caesar.detlist_iter  = caesar.detlist.begin();
//       int ring1 = caesar.detlist_iter->ring;
//       int chn1  = caesar.detlist_iter->chn;
//       double encal1 = caesar.ecal[ring1][chn1];
//       caesar.addback.edop_r1[ring1][chn1] = (encal1) *
// 	caesar.doppler[ring1][chn1];
//     }    

//   if(caesar.hit_raw == 2)
//     {
//       caesar.detlist_iter  = caesar.detlist.begin();
//       int ring1 = caesar.detlist_iter->ring;
//       int chn1  = caesar.detlist_iter->chn;
//       caesar.detlist_iter++;
//       int ring2 = caesar.detlist_iter->ring;
//       int chn2  = caesar.detlist_iter->chn;
    
//       double encal1 = caesar.ecal[ring1][chn1];
//       double encal2 = caesar.ecal[ring2][chn2];

//       if (encal1 > encal2)
// 	{
// 	  caesar.addback.edop_r2[ring1][chn1] = (encal1 + encal2) *
// 	    caesar.doppler[ring1][chn1];

// 	  if(caesar.addback.AisNeighborFromB(ring1, chn1, ring2, chn2) ||
// 	     caesar.addback.AisNeighborFromB(ring1, chn1, ring2, chn2))
// 	    {
// 	      caesar.addback.edop_r2nn[ring1][chn1] = (encal1 + encal2) *
// 		caesar.doppler[ring1][chn1];
// 	    }
      
// 	}
//       else
// 	{
// 	  caesar.addback.edop_r2[ring2][chn2] = (encal1 + encal2) *
// 	    caesar.doppler[ring2][chn2];
      
// 	  if(caesar.addback.AisNeighborFromB(ring1, chn1, ring2, chn2) ||
// 	     caesar.addback.AisNeighborFromB(ring1, chn1, ring2, chn2))
// 	    {
// 	      caesar.addback.edop_r2nn[ring2][chn2] = (encal1 + encal2) *
// 		caesar.doppler[ring2][chn2];
// 	    } 
// 	}
//     }
#endif

  // now call the calculate routine
  calculate(cvar, timing_ref);
};

void
cal::caesar::calculate(var::caesar&  cvar,
		       double timing_ref)
{
  //
  // hardware energy gate (operates on ecal)
  //

  if(cvar.enable_en_gate == CAESAR_GATE_EN)
    {
      for(detlist_iter  = detlist.begin();
	  detlist_iter != detlist.end();
	  detlist_iter++)
	{
	  if(get_ecal(detlist_iter->ring,
		      detlist_iter->chn) < cvar.left_en_gate ||
	     get_ecal(detlist_iter->ring,
		      detlist_iter->chn) > cvar.right_en_gate)
	    {
	      route_data(detlist_iter->ring, detlist_iter->chn);
	      // 	      route_data(caesar.detlist_iter->ring, caesar.detlist_iter->chn, craw);
	    }
	}
    }

  // timing vs other source
  if(cvar.enable_timing_ref)
    {
      if(timing_ref != -1)
	{
	  for(detlist_iter  = detlist.begin();
	      detlist_iter != detlist.end();
	      detlist_iter++)
	    { 
	      // leave the raw alone
	      // 	  set_traw(detlist_iter->ring, detlist_iter->chn,
	      // 		   get_traw(detlist_iter->ring, detlist_iter->chn) - timing_ref);

	      set_tcal(detlist_iter->ring, detlist_iter->chn,
		       get_tcal(detlist_iter->ring, detlist_iter->chn) - timing_ref);
	    }
	}
      else
	{
	  for(detlist_iter  = detlist.begin();
	      detlist_iter != detlist.end();
	      detlist_iter++)
	    {
	      route_data(detlist_iter->ring, detlist_iter->chn);
	    }
	}
    }

  //
  // hardware timing gate (operates on tcal)
  // (caesar.timing HAS TO BE DONE first, e.g. object is reference)
  //
  if(cvar.enable_time_gate == CAESAR_GATE_TI)
    {
      for(detlist_iter  = detlist.begin();
	  detlist_iter != detlist.end();
	  detlist_iter++)
	{
	  if(get_tcal(detlist_iter->ring,
		      detlist_iter->chn) < cvar.left_time_gate  ||
	     get_tcal(detlist_iter->ring,
		      detlist_iter->chn) > cvar.right_time_gate)
	    {
	      route_data(detlist_iter->ring, detlist_iter->chn);
	    }
	}
    }


  //
  // energy coincidence with a HPGe detector
  // 
  if(cvar.enable_ge_en_gate)
    {
      fprintf(stderr,
	      "HPGe energy coincidence not implemented yet.\n"
	      "Please set enable_ge_en_gate to 0.\n\n");
      //       if( !HPGe.HPGE_en.isValid() ||
      // 	  HPGe.HPGE_en > caesar.rightGeEnGate ||
      // 	  HPGe.HPGE_en < caesar.leftGeEnGate)
      // 	{
      // 	  for(caesar.detlist_iter  = caesar.detlist.begin();
      // 	      caesar.detlist_iter != caesar.detlist.end();
      // 	      caesar.detlist_iter++)
      // 	    {
      // 	      RouteData(caesar.detlist_iter->ring, caesar.detlist_iter->chn);
      // 	    }
      // 	} /* ( !HPGe.HPGE_en.isValid() || */
      //       else
      // 	{
      // 	  HPGe.HPGE_gated_en = HPGe.HPGE_en;
      // 	  HPGe.HPGE_gated_ti = HPGe.HPGE_ti;
      // 	}
    }

  
  //
  // Use our var:;caesar dirk_gate to check if each pair tcal (x-axis!)
  // and ecal (y-axis) has to satifisfy it's condition, otherwise the
  // detector will be routed
  //
  
  if( cvar.dirk_gate.get_size() >0 )
    {
      int ring, chn;

      for(detlist_iter  = detlist.begin();
	  detlist_iter != detlist.end();
	  detlist_iter++)
	{
	  ring = detlist_iter->ring;
	  chn  = detlist_iter->chn; 
	
	  if(cvar.dirk_gate.is_inside( get_tcal(ring, chn), get_ecal(ring, chn) ))
	    {
	      ; // fine
	    }
	  else
	    {
	      route_data(ring, chn);
	    }
	}
    }



  //
  // Doppler reconstruction last!
  // Data might be routed before.....
  //
  hit_cor = 0;
  detlist_cal.clear();
	
  ab.etot = 0;
  
  for(detlist_iter  = detlist.begin();
      detlist_iter != detlist.end();
      detlist_iter++)
    {
      caesar_hit_det h;
      h.ring = detlist_iter->ring;
      h.chn  = detlist_iter->chn;
    
#if(0)
      cout << "ring:" << h.ring << "  chn:" << h.chn
	   << " en:" << caesar.ecal[h.ring][h.chn]
	   << " ti:" << caesar.tcal[h.ring][h.chn] << endl;
#endif

      // doppler reconstruction
      set_edop(h.ring, h.chn, 
	       cvar.get_doppler(h.ring, h.chn) * get_ecal(h.ring, h.chn));
   
      //
      // For Addback analysis we only take into account
      // 'good' and 'non-routed' events. So we make
      // another detlist...
      //
      if(get_ecal(h.ring, h.chn) < CAESAR_ROUTE_CAL)
	{
	  ab.etot += get_ecal(h.ring, h.chn);

	  detlist_cal.push_back(h);
	  hit_cor++;
			 
	  hitdet_cor[(int)hit_cor] = 
	    caesar_det_offset[detlist_iter->ring] + detlist_iter->chn;

#if(0)
	  cout << "caesar.hitdet_cor[" << (int)caesar.hit_cor << "] =" 
	       << CaesarDetOffset[caesar.detlist_iter->ring] + caesar.detlist_iter->chn
	       << endl;
#endif		 
	  // cout << "push back  ring" <<  CaesarRingName[h.ring]
	  //	   << "  det:" << h.chn << endl;
	}
    }
 
  sort_hit_list();

  //
  // Addback
  //
  // I re-use detlist here !!!
  // So don't use detlist and detlist_iter after 
  // this addback part in the code anymore
  //
  {
    int ring, chn;


    // caesar.ecal caesar.tcal caesar.edop
    // randomly set by the value of ONE CsI in an event
    if((int)hit_cor > 0)
      {
	static unsigned short cts=0;

	detlist_cal_iter  = detlist_cal.begin();

	detlist_cal_iter += (cts++ % (unsigned short)hit_cor);

	ring = detlist_cal_iter->ring;
	chn  = detlist_cal_iter->chn;
      
	ab.ecal = get_ecal(ring, chn);
	ab.edop = get_edop(ring, chn);
	ab.tcal = get_tcal(ring, chn);
      }

    switch ((int)hit_cor)
      {
      case 0:
	break;
      
      case 1:
      
	detlist_cal_iter  = detlist_cal.begin();
	one_add_back(*(detlist_cal_iter), cvar);

	break;

      case 2:
	detlist_cal_iter  = detlist_cal.begin();
	ring = detlist_cal_iter->ring;
	chn  = detlist_cal_iter->chn;

#ifdef CAESAR_TESTSPECS
	fprintf(stderr,
		"CAESAR_TESTSPECS not implemented yet!!\n");
	// 	//
	// 	// h2: addback for ANY hit_corr==2, no neighbour check
	// 	//
	// 	{
	// 	  detlist_cal_iter++;
	// 	  int ring2 = detlist_cal_iter->ring;
	// 	  int chn2  = detlist_cal_iter->chn;
	// 	  detlist_cal_iter  = detlist_cal.begin();

	// 	  double encal1 = get_ecal(ring , chn );
	// 	  double encal2 = get_ecal(ring2, chn2);
	
	// 	  if (encal1 > encal2)
	// 	    {
	// 	      addback.edop_h2[ring ][chn ] = (encal1 + encal2) *
	// 		caesar.doppler[ring ][chn ];
	// 	    }
	// 	  else 
	// 	    {
	// 	      caesar.addback.edop_h2[ring2][chn2] = (encal1 + encal2) *
	// 		caesar.doppler[ring2][chn2];
	// 	    }

	// 	}
#endif

	if( check_no_of_neighbors(ring, chn, cvar) == 0 )
	  {
	    one_add_back(*(detlist_cal_iter), cvar);
		
	    detlist_cal_iter++;
	    one_add_back(*(detlist_cal_iter), cvar);
	  }
	else 
	  // add_back  (because hit == 2 )
	  {
	    two_add_back(*detlist_cal_iter, 
			 *(detlist_cal_iter+1), cvar);
	  }
      
	break;
      
      case 3:
	{
	  int single = 0;
	  detlist.clear();

#ifdef CAESAR_TESTSPECS
	  fprintf(stderr,
		  "CAESAR_TESTSPECS not implemented yet!!\n");
	  //
	  // h3: addback for ANY hit_corr==3, no neighbour check
	  //	  
	  // 	  {
	  // 	    caesar.detlist_cal_iter  = caesar.detlist_cal.begin();
	  // 	    int ring1 = caesar.detlist_cal_iter->ring;
	  // 	    int chn1  = caesar.detlist_cal_iter->chn;
	  // 	    caesar.detlist_cal_iter++;
	  // 	    int ring2 = caesar.detlist_cal_iter->ring;
	  // 	    int chn2  = caesar.detlist_cal_iter->chn;
	  // 	    caesar.detlist_cal_iter++;
	  // 	    int ring3 = caesar.detlist_cal_iter->ring;
	  // 	    int chn3  = caesar.detlist_cal_iter->chn;
	  // 	    caesar.detlist_cal_iter  = caesar.detlist_cal.begin();
	  
	  // 	    double encal1 = caesar.ecal[ring1][chn1];
	  // 	    double encal2 = caesar.ecal[ring2][chn2];
	  // 	    double encal3 = caesar.ecal[ring3][chn3];
	  
	  // 	    if (encal1 > encal2 && encal1 > encal3)
	  // 	      {
	  // 		caesar.addback.edop_h3[ring1][chn1] = 
	  // 		  (encal1 + encal2 + encal3) *
	  // 		  caesar.doppler[ring1][chn1];
	  // 	      }
	  // 	    else 
	  // 	      if (encal2 > encal1 && encal2 > encal3)
	    
	  // 		{
	  // 		  caesar.addback.edop_h3[ring2][chn2] = 
	  // 		    (encal1 + encal2 + encal3) *
	  // 		    caesar.doppler[ring2][chn2];
	  // 		}
	  // 	      else
	  // 		{
	  // 		  caesar.addback.edop_h3[ring3][chn3] = 
	  // 		    (encal1 + encal2 + encal3) *
	  // 		    caesar.doppler[ring3][chn3];
	  // 		}

	  // 	  }
#endif

	  for(detlist_cal_iter  = detlist_cal.begin();
	      detlist_cal_iter != detlist_cal.end();
	      detlist_cal_iter++)
	    {
	      int ring = detlist_cal_iter->ring;
	      int chn  = detlist_cal_iter->chn;
	  
	      // 
 
	      if( check_no_of_neighbors(ring, chn, cvar) == 0 )
		{
		  one_add_back(*(detlist_cal_iter), cvar);
		  single++;
		}
	      else
		{
		  detlist.push_back(*(detlist_cal_iter));
		}
	    }

	  switch (single)
	    {
	    case 0:
	      // ....Triple hit ???
	      //
	      detlist_cal_iter  = detlist_cal.begin();
	      three_add_back(*detlist_cal_iter,
			     *(detlist_cal_iter+1),
			     *(detlist_cal_iter+2),
			     cvar);
	  
#if(0)
	      for(detlist_cal_iter  = detlist_cal.begin();
		  detlist_cal_iter != detlist_cal.end();
		  detlist_cal_iter++)
		{
		  int ring = detlist_cal_iter->ring;
		  int chn  = detlist_cal_iter->chn;
	      
		  set_ab_ng_ecal(ring, chn,
				 get_ecal(ring, chn));
		  set_ab_ng_edop(ring, chn, get_ecal(ring, chn) *
				 cvar.get_doppler(ring, chn));
	      
		}
#endif
	      break;

	    case 1:
	      // one is single, two dets left with hit neighbors,
	      // so they should be neighbors
	      // (but consider hit (1)(2)(3) and 2 neighbor of 1,3 but 
	      // not vice versa.....)
	      {
		detlist_iter = detlist.begin();

		if(a_is_neighbor_from_b(detlist_iter->ring,
					detlist_iter->chn,
					(detlist_iter+1)->ring,
					(detlist_iter+1)->chn,
					 cvar));
		  two_add_back(*detlist_iter,
			       *(detlist_iter+1), cvar);

	      }
	      break;

	    case 2:
	      // okay: A, B, C, and C single and A is assigned neighbor of B
	      // but not vice versa. That's a C, A = 0 and B=1 and single = 2
	      // event......
	      //
	      {
		detlist_iter = detlist.begin();
		ring = detlist_iter->ring;
		chn  = detlist_iter->chn; 

		for(detlist_cal_iter  = detlist_cal.begin();
		    detlist_cal_iter != detlist_cal.end();
		    detlist_cal_iter++)
		  {
		    int ring2 = detlist_cal_iter->ring;
		    int chn2  = detlist_cal_iter->chn;
	      
		    if(a_is_neighbor_from_b(ring2, chn2, ring, chn, cvar))
		      {
			two_add_back(*detlist_iter,
				     *detlist_cal_iter, cvar);


#if(0)
			double encal1 = get_ecal(ring, chn);
			double encal2 = get_ecal(ring2, chn2);
		
			if (encal1 > encal2)
			  {
			    set_ab_n1_ecal(ring, chn,  encal1 + encal2);
			    set_ab_n1_edop(ring, chn, (encal1 + encal2) *
					   cvar.get_doppler(ring, chn));
			  }
			else 
			  {
                            set_ab_n1_ecal(ring2, chn2,  encal1 + encal2);
			    set_ab_n1_edop(ring2, chn2,  (encal1 + encal2) *
					   cvar.get_doppler(ring2, chn2));
			  }
#endif
		      }
		  }
	      }
	      break;
				 
	    case 3:
	      //fine...all n0
	      break;
	    }
	}
	break;
	
      case 4:
	{
	  int single=0;
	  detlist.clear();
	
	  for(detlist_cal_iter  = detlist_cal.begin();
	      detlist_cal_iter != detlist_cal.end();
	      detlist_cal_iter++)
	    {
	      int ring = detlist_cal_iter->ring;
	      int chn  = detlist_cal_iter->chn;
	  
	      // 
 
	      if( check_no_of_neighbors(ring, chn, cvar) == 0 )
		{
		  one_add_back(*(detlist_cal_iter), cvar);
		  single++;
		}
	      else
		{
		  detlist.push_back(*(detlist_cal_iter));
		}
	    }

	  switch (single)
	    {
	    case 1:
	      break;

	    case 2:
	      {
		detlist_iter = detlist.begin();
	    
		if(a_is_neighbor_from_b(detlist_iter->ring,
					detlist_iter->chn,
					(detlist_iter+1)->ring,
					(detlist_iter+1)->chn,
					 cvar))
		  two_add_back(*detlist_iter,
			       *(detlist_iter+1), cvar);
	      }	  
	      break;
	  
	    case 3:
	      // same as fold = 3 and single = 2
	      {
		detlist_iter = detlist.begin();
		ring = detlist_iter->ring;
		chn  = detlist_iter->chn; 
	    
		for(detlist_cal_iter  = detlist_cal.begin();
		    detlist_cal_iter != detlist_cal.end();
		    detlist_cal_iter++)
		  {
		    int ring2 = detlist_cal_iter->ring;
		    int chn2  = detlist_cal_iter->chn;
	      
		    if(a_is_neighbor_from_b(ring2, chn2, ring, chn, cvar))
		      {
			two_add_back(*detlist_iter,
				     *detlist_cal_iter, cvar);
		      }
		  }
	      }
	      break;
	  
	    case 4:
	      // fine....all n0
	      break;
	    
	    }
	}
	break;


      default:
	for(detlist_cal_iter  = detlist_cal.begin();
	    detlist_cal_iter != detlist_cal.end();
	    detlist_cal_iter++)
	  {
	    int ring = detlist_cal_iter->ring;
	    int chn  = detlist_cal_iter->chn;

	    if( check_no_of_neighbors(ring, chn, cvar) == 0 )
	      {
		one_add_back(*(detlist_cal_iter), cvar);
	      }
	    else // put into garbage....
	      {
		set_ab_ng_ecal(ring, chn, get_ecal(ring, chn));
		set_ab_ng_edop(ring, chn, get_ecal(ring, chn) *
			       cvar.get_doppler(ring, chn));
	      }
	  }
	break;
      }
  }
 
  detlist.clear();
};

void
cal::caesar::calculate(var::caesar& cvar,
		       raw::sweeper* sraw)
{
  if( is_valid(sraw->pot.traw) )
    {
      double tref = sraw->pot.traw * 0.1 / 0.25;
      this->calculate(cvar, tref);
    }
  else
    this->calculate(cvar, -1);
};


void
cal::caesar::calibrate(raw::caesar* craw,
		       var::caesar& cvar,
		       raw::sweeper* sraw)
{
  if( is_valid(sraw->pot.traw) )
    {
      double tref = sraw->pot.traw * 0.1 / 0.25;
      this->calibrate(craw, cvar, tref);
    }
  else
    this->calibrate(craw, cvar, -1);
};



//
// route data for given detector
// if data is already routed it won't 
// be routed again
//
// special case: filter file sets cal, not raw data
// so we need to check cal end raw seperately
//
void
cal::caesar::route_data(int ring,
			int det)
  //			raw::caesar* craw)
{
//  since in the root analysis I treat raw data as
//  fully raw, no routing is done of the raw data.
///////////
//   if( is_valid(craw->get_eraw(ring, det)) )
//     {
//       double _eraw = craw->get_eraw(ring, det);
//       if(_eraw < CAESAR_ROUTE_RAW) 
// 	_eraw += CAESAR_ROUTE_RAW; 

//       double _traw = craw->get_traw(ring, det);
//       if(_traw < CAESAR_ROUTE_RAW) 
// 	_traw += CAESAR_ROUTE_RAW; 
//     }

  if( is_valid(get_ecal(ring, det)) )
    {
      if(get_ecal(ring, det) < CAESAR_ROUTE_CAL)
	set_ecal(ring, det, get_ecal(ring, det) + CAESAR_ROUTE_CAL);
      
      if(get_tcal(ring, det) < CAESAR_ROUTE_RAW)
	set_tcal(ring, det, get_tcal(ring, det) + CAESAR_ROUTE_RAW);
    }
}

void
cal::caesar::sort_hit_list()
{
  for(int i=0; i< hit_cor; i++)
    for(int j=i+1; j< hit_cor; j++)
      {
	if(hitdet_cor[i+1] > hitdet_cor[j+1])
	  {
	    int tmp = int(hitdet_cor[i+1]);
	    hitdet_cor[i+1] = hitdet_cor[j+1];
	    hitdet_cor[j+1] = tmp;
	  }
      }

  for(int i=0; i< hit_raw; i++)
    for(int j=i+1; j< hit_raw; j++)
      {
	if(hitdet_raw[i+1] > hitdet_raw[j+1])
	  {
	    int tmp = int(hitdet_raw[i+1]);
	    hitdet_raw[i+1] = hitdet_raw[j+1];
	    hitdet_raw[j+1] = tmp;
	  }
      }
}
