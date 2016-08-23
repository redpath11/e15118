#include "mona.hh"
#include "utils.hh"
#include <algorithm>
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

//---------------------------------------------------------//
// class mona_trigger

// raw
void
raw::mona_trigger::reset()
{
  monapattern = -1;
  monahits = -1;
  for(int i=0; i< 3; ++i)
    monacount_pattern[i] = -1;
  for(int i=0; i< 4; ++i)
    monatimestamp[i] = -1;
  lisapattern = -1;
  lisahits = -1;
  for(int i=0; i< 3; ++i)
    lisacount_pattern[i] = -1;
  for(int i=0; i< 4; ++i)
    lisatimestamp[i] = -1;
};

//---------------------------------------------------------//
// class mona_pmt

// raw
void
raw::mona_pmt::reset()
{
  for(int i=0; i< MONA_WALLS; ++i)
    {
      for(int j=0; j< WALL_BARS; ++j)
	{
	  traw[i][j] = -1;
	  qraw[i][j] = -1;
	}
    }
};

// cal
void
cal::mona_pmt::reset()
{
  for(int i=0; i< MONA_WALLS; ++i)
    {
      for(int j=0; j< WALL_BARS; ++j)
	{
	  tcal[i][j] = -1;
	  qcal[i][j] = -1;
	}
    }
};

void
cal::mona_pmt::calibrate(raw::mona_pmt& rw, var::mona_pmt& v)
{
  for(unsigned short i=0; i< MONA_WALLS; ++i)
    {
      for(unsigned short j=0; j< WALL_BARS; ++j)
	{
	  if(is_valid(rw.traw[i][j]))
	    {
	      tcal[i][j] = rw.traw[i][j] * v.t_slope[i][j];
	      tcal[i][j] += v.t_offset[i][j];
	    }
	  if(is_valid(rw.qraw[i][j]))
	    {
	      rw.qraw[i][j] -= short(v.q_threshold[i][j]);
	      qcal[i][j] = rw.qraw[i][j] + v.q_offset[i][j];
	      qcal[i][j] *= v.q_slope[i][j];
  	    }
	}
    }
};


//---------------------------------------------------------//
// class mona

// raw
void
raw::mona::unpack_monatrigger(unsigned short* pTrig)
{
  unsigned short words = *pTrig - 2;
  pTrig += 2;

  if(words == 8)
    {
      //1st word is pattern
      trigger.monapattern = *pTrig++;

      //2nd is hits
      trigger.monahits = *pTrig++;

      //next 2 are count_pattern
      for(int i=0; i< 2; ++i)
	trigger.monacount_pattern[i] = *pTrig++;

      //next 4 words are timestamp
      for(int i=0; i< 4; ++i)
	trigger.monatimestamp[i] = *pTrig++;
    }
//  else
//    std::cerr << "Mona trigger packet found with "<<words<<" words instead of 8. Skipping.\n";
};


void
raw::mona::unpack_lisatrigger(unsigned short* pTrig)
{
  unsigned short words = *pTrig - 2;
  pTrig += 2;

  if(words <= 8)
    {
      //1st word is pattern
      trigger.lisapattern = *pTrig++;

      //2nd is hits
      trigger.lisahits = *pTrig++;

      //next 2 are count_pattern
      for(int i=0; i< 2; ++i)
	trigger.lisacount_pattern[i] = *pTrig++;

      //next 4 words are timestamp
      for(int i=0; i< 4; ++i)
	trigger.lisatimestamp[i] = *pTrig++;
    }
  else
    std::cerr << "LISA trigger packet found with more than 8 words ("<<words<<"). Skipping.\n";
};

mona_pmtmap
raw::mona::map_tdc(unsigned short crate, unsigned short slot, unsigned short ch)
{
  // mapping:
  //    ----------------------------------------------------
  //    | crate | slot |       parameter                   |
  //    ----------------------------------------------------
  //    |   1   |  3   | a.{ch}...left <- lower 15 ch      |
  //    |       |      | b.{ch-16}...left <- upper 15 ch   |
  //    ----------------------------------------------------      
  //    |   2   |  3   | a.{ch}...right <- lower 15 ch     |
  //    |       |      | b.{ch-16}...right <- upper 15 ch  |
  //    ----------------------------------------------------
  //    |   1   |  6   | c.{ch}...left <- lower 15 ch      |
  //    |       |      | d.{ch-16}...left <- upper 15 ch   |
  //    ----------------------------------------------------
  //    |   2   |  6   | c.{ch}...right <- lower 15 ch     |
  //    |       |      | d.{ch-16}...right <- upper 15 ch  |
  //    ----------------------------------------------------
  //    |   1   |  9   | e.{ch}...left <- lower 15 ch      |
  //    |       |      | f.{ch-16}...left <- upper 15 ch   |
  //    ----------------------------------------------------
  //    |   2   |  9   | e.{ch}...right <- lower 15 ch     |
  //    |       |      | f.{ch-16}...right <- upper 15 ch  |
  //    ----------------------------------------------------
  //    |   1   |  12  | g.{ch}...left <- lower 15 ch      |
  //    |       |      | h.{ch-16}...left <- upper 15 ch   |
  //    ----------------------------------------------------
  //    |   2   |  12  | g.{ch}...right <- lower 15 ch     |
  //    |       |      | h.{ch-16}...right <- upper 15 ch  |
  //    ----------------------------------------------------
  //    |   1   |  15  | i.{ch}...left <- lower 15 ch      | 
  //    |       |      |          not used <- upper 15 ch  |
  //    ----------------------------------------------------
  //    |   2   |  15  | i.{ch}...right <- lower 15 ch     |
  //    |       |      |           not used <- upper 15 ch |
  //    ----------------------------------------------------


  static mona_pmtmap tdc_map;
  tdc_map.wall = 0;
  // Members: { wall, bar, lr (0=l, 1=r) }

  // Determine whether we're dealing w/ an upper or lower channel.
  // Expression evaluates to 0 if ch< 16, 1 if ch >16.
  unsigned short UorL = (ch * 2) / 32;

  // left/right depends on crate only:
  // crate = 1 => left  => tdc_map.lr = 0
  // crate = 2 => right => tdc_map.lr = 1
  if(crate == 1)
    tdc_map.lr = 0;
  else if (crate == 2)
    tdc_map.lr = 1;
  else
    {
      tdc_map.wall = -1;
      std::cerr << "Bad crate number " << crate <<" fed to MapTDC.\n";
      return tdc_map; //\wall = -1 means error
    }

  //set wall & bar based on slot & channel
  if(tdc_map.wall != -1)
    {
      switch(slot)
	{
	case 3:
	  tdc_map.wall = 0 + UorL;
	  break;                     
	case 6:	                     
	  tdc_map.wall = 2 + UorL;
	  break;                     
	case 9:	                     
	  tdc_map.wall = 4 + UorL;
	  break;                     
	case 12:                     
	  tdc_map.wall = 6 + UorL;
	  break;                          
	case 15:                          
	  tdc_map.wall = 8; //one wall only
	  break;
	default:
	  tdc_map.wall = -1;
	  std::cerr << "Bad slot number "<<slot<<" fed to MapTDC.\n";
	  return tdc_map;
	  break;
	}
    }

  // Channel # = ch if in upper 16 channels (UorL = 0), and
  //           = ch - 16 if in lower 16 channels (UorL = 1).

  if(tdc_map.wall< 8)
    tdc_map.bar = ch - (16 * UorL);
  else //wall 8 only uses upper 16 channels
    tdc_map.bar = ch;
    
  return tdc_map;
}

mona_pmtmap
raw::mona::map_lisatdc(unsigned short crate, unsigned short slot, unsigned short ch)
{
  // mapping:
  //    ----------------------------------------------------
  //    | crate | slot |       parameter                   |
  //    ----------------------------------------------------
  //    |   1   |  3   | j.{ch}...left <- lower 15 ch      |
  //    |       |      | k.{ch-16}...left <- upper 15 ch   |
  //    ----------------------------------------------------      
  //    |   2   |  3   | j.{ch}...right <- lower 15 ch     |
  //    |       |      | k.{ch-16}...right <- upper 15 ch  |
  //    ----------------------------------------------------
  //    |   1   |  6   | l.{ch}...left <- lower 15 ch      |
  //    |       |      | m.{ch-16}...left <- upper 15 ch   |
  //    ----------------------------------------------------
  //    |   2   |  6   | l.{ch}...right <- lower 15 ch     |
  //    |       |      | m.{ch-16}...right <- upper 15 ch  |
  //    ----------------------------------------------------
  //    |   1   |  9   | l.{ch}...left <- lower 15 ch      |
  //    |       |      | m.{ch-16}...left <- upper 15 ch   |
  //    ----------------------------------------------------
  //    |   2   |  9   | n.{ch}...right <- lower 15 ch     |
  //    |       |      | o.{ch-16}...right <- upper 15 ch  |
  //    ----------------------------------------------------
  //    |   1   |  12  | n.{ch}...left <- lower 15 ch      |
  //    |       |      | o.{ch-16}...left <- upper 15 ch   |
  //    ----------------------------------------------------
  //    |   2   |  12  | p.{ch}...right <- lower 15 ch     |
  //    |       |      | q.{ch-16}...right <- upper 15 ch  |
  //    ----------------------------------------------------
  //    |   1   |  15  | r.{ch}...left <- lower 15 ch      | 
  //    |       |      |          not used <- upper 15 ch  |
  //    ----------------------------------------------------
  //    |   2   |  15  | r.{ch}...right <- lower 15 ch     |
  //    |       |      |           not used <- upper 15 ch |
  //    ----------------------------------------------------


  static mona_pmtmap tdc_map;
  tdc_map.wall = 0;
  // Members: { wall, bar, lr (0=l, 1=r) }

  // Determine whether we're dealing w/ an upper or lower channel.
  // Expression evaluates to 0 if ch< 16, 1 if ch >16.
  unsigned short UorL = (ch * 2) / 32;

  // left/right depends on crate only:
  // crate = 1 => left  => tdc_map.lr = 0
  // crate = 2 => right => tdc_map.lr = 1
  if(crate == 1)
    tdc_map.lr = 0;
  else if (crate == 2)
    tdc_map.lr = 1;
  else
    {
      tdc_map.wall = -1;
      std::cerr << "Bad crate number " << crate <<" fed to MapTDC.\n";
      return tdc_map; //\wall = -1 means error
    }

  //set wall & bar based on slot & channel
  if(tdc_map.wall != -1)
    {
      switch(slot)
	{
	case 3:
	  tdc_map.wall = 9 + UorL;
	  break;                     
	case 6:	                     
	  tdc_map.wall = 11 + UorL;
	  break;                     
	case 9:	                     
	  tdc_map.wall = 13 + UorL;
	  break;                     
	case 12:                     
	  tdc_map.wall = 15 + UorL;
	  break;                          
	case 15:                          
	  tdc_map.wall = 17; //one wall only
	  break;
	default:
	  tdc_map.wall = -1;
	  std::cerr << "Bad slot number "<<slot<<" fed to MapTDC.\n";
	  return tdc_map;
	  break;
	}
    }

  // Channel # = ch if in upper 16 channels (UorL = 0), and
  //           = ch - 16 if in lower 16 channels (UorL = 1).

  if(tdc_map.wall< 17)
    tdc_map.bar = ch - (16 * UorL);
  else //wall 8 only uses upper 16 channels
    tdc_map.bar = ch;
    
  return tdc_map;
}


void
raw::mona::unpack_tdc(unsigned short* pTDC, bool LISA)
{
  unsigned short packetlength = *pTDC - 2;
  pTDC += 2;
  unsigned short ll = 0; //counter for how many times we increment pTDC
  ll += 2; //skip the first two words

  while (ll< packetlength) //unpack the TDC
    {
      //first, figure out which TDC we're dealing with
      unsigned short HeaderTop = *pTDC;
      unsigned short nSlot  = (HeaderTop & ALLH_GEOMASK)   >> ALLH_GEOSHIFT;
//      unsigned short nType  = (HeaderTop & ALLH_TYPEMASK)  >> ALLH_TYPESHIFT;
      unsigned short nCrate = (HeaderTop & HDRH_CRATEMASK) >> HDRH_CRATESHIFT;
      ++pTDC; ++ll;

      unsigned short nChannels = (*pTDC & HDRL_COUNTMASK)  >> HDRL_COUNTSHIFT;
      ++pTDC; ++ll;

      if(nChannels >32)
	{
	  std::cerr << "mona::unpack_tdc found more than 32 channels, bailing out.\n";
	  return;
	}

      for(int i =0; i < nChannels; i++)
	{
	  unsigned short nChan = (*pTDC & DATAH_CHANMASK)  >> DATAH_CHANSHIFT;
	  ++pTDC; ++ll;

	  //get wall, bar & l/r from mona::MapTDC
      mona_pmtmap tdc_id;
	  if(LISA)
      {
          tdc_id = this->map_lisatdc(nCrate, nSlot, nChan);
      } else tdc_id = this->map_tdc(nCrate, nSlot, nChan);

	  if(tdc_id.wall != -1)
	    {
	      //unpack data into tree parameters
	      if(tdc_id.lr == 0)
		this->l.traw[tdc_id.wall][tdc_id.bar] = (*pTDC & DATAL_DATAMASK);
	      else if(tdc_id.lr == 1)
		this->r.traw[tdc_id.wall][tdc_id.bar] = (*pTDC & DATAL_DATAMASK);
	      else
		std::cerr << "WARNING: Invalid tdc_id.lr = " << tdc_id.lr <<std::endl;
	    }
	  else
	    {
	      std::cerr << "WARNING: Something went wrong in mona::map_tdc.\n";
	      return;
	    }

	  ++pTDC; ++ll;
	}
      pTDC += 2; ll+=2; //skip trailing longword
    }
};

mona_pmtmap
raw::mona::map_qdc(unsigned short crate, unsigned short slot, unsigned short ch)
{
  // mapping:
  //    ----------------------------------------------------
  //    | crate | slot |            parameter              | 
  //    ----------------------------------------------------
  //    |   0   |   3  | a.{ch}...right <- lower 15 ch     |
  //    |       |      | a.{ch-16}...left <- upper 15 ch   |
  //    ----------------------------------------------------  
  //    |   0   |   4  | b.{ch}...right <- lower 15 ch     |
  //    |       |      | b.{ch-16}...right <- upper 15 ch  |
  //    ----------------------------------------------------
  //    |   0   |   5  | c.{ch}...right <- lower 15 ch     |
  //    |       |      | c.{ch-16}...left <- upper 15 ch   |
  //    ----------------------------------------------------
  //    |   0   |   6  | d.{ch}...right <- lower 15 ch     |
  //    |       |      | d.{ch-16}...right <- upper 15 ch  |
  //    ----------------------------------------------------
  //    |   0   |   7  | e.{ch}...right <- lower 15 ch     |
  //    |       |      | e.{ch-16}...left <- upper 15 ch   |
  //    ----------------------------------------------------
  //    |   0   |   8  | f.{ch}...right <- lower 15 ch     |
  //    |       |      | f.{ch-16}...right <- upper 15 ch  |
  //    ----------------------------------------------------
  //    |   0   |   9  | g.{ch}...right<- lower 15 ch      |
  //    |       |      | g.{ch-16}...left <- upper 15 ch   |
  //    ----------------------------------------------------
  //    |   0   |  10  | h.{ch}...right <- lower 15 ch     |
  //    |       |      | h.{ch-16}...right <- upper 15 ch  |
  //    ----------------------------------------------------
  //    |   0   |  11  | i.{ch}...left <- lower 15 ch      |
  //    |       |      | i.{ch-16}...left <- lower 15 ch   |
  //    ----------------------------------------------------
 
  static mona_pmtmap qdc_map;
  qdc_map.wall = 0; qdc_map.bar = 0; qdc_map.lr = 0;
  // Members: { wall, bar, [0/1 = left/right] }

  if(crate !=0)
    {
      std::cerr << "Invalid crate number "<<crate<<" fed to map_qdc\n";
      qdc_map.wall = -1; //\signifies an error
      return qdc_map;
    }

  //set wall based on slot #
  //we can do this in one line as long as things don't move around
  //if they do change then use switch...case, like for the TDCs
  if(11 >= slot && slot >= 3)
    qdc_map.wall = slot - 3;
  else
    {
      std::cerr << "Invalid slot number "<<slot<<" fed to map_qdc\n";
      qdc_map.wall = -1; return qdc_map;
    }

  //set channel number
  // Channel # = ch if in upper 16 channels (UorL = 0), and
  //           = ch - 16 if in lower 16 channels.
  if(ch< 16)
    {
      qdc_map.bar = ch;
      qdc_map.lr = 1;
    }
  else if(ch< 32)
    {
      qdc_map.bar = ch - 16;
      qdc_map.lr = 0;
    }
  else
    {
      std::cerr << "Invalid channel number "<<ch<<" fed to map_qdc\n";
      qdc_map.wall = -1; return qdc_map;
    }

  return qdc_map;
};

mona_pmtmap
raw::mona::map_lisaqdc(unsigned short crate, unsigned short slot, unsigned short ch)
{
  // mapping:
  //    ----------------------------------------------------
  //    | crate | slot |            parameter              | 
  //    ----------------------------------------------------
  //    |   0   |   3  | j.{ch}...right <- lower 15 ch     |
  //    |       |      | j.{ch-16}...left <- upper 15 ch   |
  //    ----------------------------------------------------  
  //    |   0   |   4  | k.{ch}...right <- lower 15 ch     |
  //    |       |      | k.{ch-16}...right <- upper 15 ch  |
  //    ----------------------------------------------------
  //    |   0   |   5  | l.{ch}...right <- lower 15 ch     |
  //    |       |      | l.{ch-16}...left <- upper 15 ch   |
  //    ----------------------------------------------------
  //    |   0   |   6  | m.{ch}...right <- lower 15 ch     |
  //    |       |      | m.{ch-16}...right <- upper 15 ch  |
  //    ----------------------------------------------------
  //    |   0   |   7  | n.{ch}...right <- lower 15 ch     |
  //    |       |      | n.{ch-16}...left <- upper 15 ch   |
  //    ----------------------------------------------------
  //    |   0   |   8  | o.{ch}...right <- lower 15 ch     |
  //    |       |      | o.{ch-16}...right <- upper 15 ch  |
  //    ----------------------------------------------------
  //    |   0   |   9  | p.{ch}...right<- lower 15 ch      |
  //    |       |      | p.{ch-16}...left <- upper 15 ch   |
  //    ----------------------------------------------------
  //    |   0   |  10  | q.{ch}...right <- lower 15 ch     |
  //    |       |      | q.{ch-16}...right <- upper 15 ch  |
  //    ----------------------------------------------------
  //    |   0   |  11  | r.{ch}...left <- lower 15 ch      |
  //    |       |      | r.{ch-16}...left <- lower 15 ch   |
  //    ----------------------------------------------------
 
  static mona_pmtmap qdc_map;
  qdc_map.wall = 0; qdc_map.bar = 0; qdc_map.lr = 0;
  // Members: { wall, bar, [0/1 = left/right] }

  if(crate !=0)
    {
      std::cerr << "Invalid crate number "<<crate<<" fed to map_qdc\n";
      qdc_map.wall = -1; //\signifies an error
      return qdc_map;
    }

  //set wall based on slot #
  //we can do this in one line as long as things don't move around
  //if they do change then use switch...case, like for the TDCs
  if(11 >= slot && slot >= 3)
    qdc_map.wall = slot - 3 + 9;
  else
    {
      std::cerr << "Invalid slot number "<<slot<<" fed to map_qdc\n";
      qdc_map.wall = -1; return qdc_map;
    }

  //set channel number
  // Channel # = ch if in upper 16 channels (UorL = 0), and
  //           = ch - 16 if in lower 16 channels.
  if(ch< 16)
    {
      qdc_map.bar = ch;
      qdc_map.lr = 1;
    }
  else if(ch< 32)
    {
      qdc_map.bar = ch - 16;
      qdc_map.lr = 0;
    }
  else
    {
      std::cerr << "Invalid channel number "<<ch<<" fed to map_qdc\n";
      qdc_map.wall = -1; return qdc_map;
    }

  return qdc_map;
};

void
raw::mona::unpack_qdc(unsigned short* pQDC, bool LISA)
{
  unsigned short packetlength = *pQDC - 2;
  pQDC += 2;
  unsigned short ll = 0; //counter for how many times we increment pQDC
  ll += 2; //skip the first two words

  while (ll< packetlength) //unpack the QDC
    {
      //first, figure out which QDC we're dealing with
      unsigned short HeaderTop = *pQDC;
      unsigned short nSlot  = (HeaderTop & ALLH_GEOMASK)   >> ALLH_GEOSHIFT;
//      unsigned short nType  = (HeaderTop & ALLH_TYPEMASK)  >> ALLH_TYPESHIFT;
      unsigned short nCrate = (HeaderTop & HDRH_CRATEMASK) >> HDRH_CRATESHIFT;
      ++pQDC; ++ll;

      unsigned short nChannels = (*pQDC & HDRL_COUNTMASK)  >> HDRL_COUNTSHIFT;
      ++pQDC; ++ll;

      if(nChannels >32)
	{
	  std::cerr << "mona::unpack_qdc found more than 32 channels, bailing out.\n";
	  return;
	}

      for(int i =0; i < nChannels; i++)
	{
	  unsigned short nChan = (*pQDC & DATAH_CHANMASK)  >> DATAH_CHANSHIFT;
	  ++pQDC; ++ll;


	  //get wall, bar & l/r from mona::map_qdc
      mona_pmtmap qdc_id;
	  if(LISA)
      {
          qdc_id = map_lisaqdc(nCrate, nSlot, nChan);
      } else qdc_id = map_qdc(nCrate, nSlot, nChan);

	  if(qdc_id.wall != -1)
	    {
	      //unpack data into tree parameters
	      if(qdc_id.lr == 0)
		l.qraw[qdc_id.wall][qdc_id.bar] = (*pQDC & DATAL_DATAMASK);
	      else if(qdc_id.lr == 1)	                                
		r.qraw[qdc_id.wall][qdc_id.bar] = (*pQDC & DATAL_DATAMASK);
	      else
		std::cerr << "WARNING: Invalid qdc_id.lr = " << qdc_id.lr <<std::endl;
	    }
	  else
	    std::cerr << "WARNING: Something went wrong in mona::map_qdc.\n";

	  ++pQDC; ++ll;
	}
      pQDC += 2; ll+=2; //skip trailing longword
    }
}

void
raw::mona::reset()
{
  trigger.reset();
  l.reset();
  r.reset();
};

void
raw::mona::unpack(unsigned short* pM)
{

  // Passed a pointer which points at the first data
  // word in a mona packet, the two words before it
  // are the length of the mona packet and the packet
  // id that was used to distinguish it as a mona packet

  // Philosophy of the unpacker: read the subpacket header
  // (length and size) into the variables packetlength and
  // packettag, via the pointer pS, whose position we increment such that
  // it points at the first data word in the subpacket. Then based on 
  // the packettag, decide what to do next. Normally we will pass the
  // memory location of pS onto the approaprite unpack function for the
  // packet identified by packettag. In any case, pS is always incremented by
  // the value (packetlength-2), so that it will point exactly at the beginning
  // of the header of the next subpacket.
  unsigned short nWords = *(pM-2) - 2;
  //std::cout <<"nWords = " <<nWords <<std::endl;
  unsigned short packetlength, packettag;

  // this part for compatibility with older evt data structure:
  if ((((*(pM-1) == 0x5000))&((*(pM+1) != 0x5001)))
      |((*(pM-1) == 0x5010)&(*(pM-2) < 7))
      ) // checking if one of old mona packets
        // No version packet means the old file structure,
        // short trigger packet as well,
        // so use the legacy unpacker.
    {
      std::cout <<"using legacy unpacker" <<std::endl;
      legacy_unpack(pM);
      // Pointer pM has not been advanced, but we are returning anyway:
      return;
    }
  // regular mona packets are read:
  while(nWords >0)
    {
      packetlength = *pM;
      packettag = *(pM+1);

     // std::cout <<hex <<packettag <<endl;

      switch(packettag)
	{
	case MONA_VERSION_PACKET:
	  //do nothing
	  pM += packetlength;
	  break;
    
	case LISA_VERSION_PACKET:
	  //do nothing
	  pM += packetlength;
	  break;

	case MONA_TRIGGER_PACKET:
	  //std::cout <<"found mona trigger packet." <<std::endl;
	  unpack_monatrigger(pM);
	  pM += packetlength;
	  break;

	case LISA_TRIGGER_PACKET:
	  //std::cout <<"found mona trigger packet." <<std::endl;
	  unpack_lisatrigger(pM);
	  pM += packetlength;
	  break;
    
	case MONA_TDC_PACKET:
	  unpack_tdc(pM,0);
	  pM += packetlength;
	  break;

        case LISA_TDC_PACKET:
	  unpack_tdc(pM,1);
	  pM += packetlength;
	  break;

        case MONA_QDC_PACKET:
	 // std::cout <<"found mona qdc packet." <<std::endl;
	  unpack_qdc(pM,0);
	  pM += packetlength;
	  break;

        case LISA_QDC_PACKET:
	  //std::cout <<"found lisa qdc packet." <<std::endl;
	  unpack_qdc(pM,1);
	  pM += packetlength;
	  break;
    
        default:
	  pM += packetlength;
	  break;
	}

      nWords -= packetlength;
    }
};

void
raw::mona::legacy_unpack(unsigned short* pMona)
//unpacks mona packet and trigger bit packet
{
  unsigned short nWords = *(pMona-2) - 2;
  unsigned short ll = 0;
  unsigned short packettag = *(pMona-1);
  
  // unpack data packet:
  switch(packettag)
    {
    case 0x5000:
      while(ll< nWords)
	{
	  unsigned short HeaderTop = *pMona;
	  unsigned short nSlot  = (HeaderTop & ALLH_GEOMASK)   >> ALLH_GEOSHIFT;
//	  unsigned short nType  = (HeaderTop & ALLH_TYPEMASK)  >> ALLH_TYPESHIFT;
	  unsigned short nCrate = (HeaderTop & HDRH_CRATEMASK) >> HDRH_CRATESHIFT;
	  ++pMona; ++ll;
	  
	  unsigned short nChannels = (*pMona & HDRL_COUNTMASK) >> HDRL_COUNTSHIFT;
	  ++pMona; ++ll;
	  
	  if(nCrate == 1 || nCrate == 2) //\tdc
	    {
	      for(int i =0; i < nChannels; i++)
		{
		  unsigned short nChan = (*pMona & DATAH_CHANMASK)  >> DATAH_CHANSHIFT;
		  ++pMona; ++ll;
		  
		  //get wall, bar & l/r from mona::MapTDC
		  mona_pmtmap tdc_id = this->map_tdc(nCrate, nSlot, nChan);
		  
		  if(tdc_id.wall != -1)
		    {
		      if(tdc_id.lr == 0)
			this->l.traw[tdc_id.wall][tdc_id.bar] = (*pMona & DATAL_DATAMASK);
		      else if(tdc_id.lr == 1)
			this->r.traw[tdc_id.wall][tdc_id.bar] = (*pMona & DATAL_DATAMASK);
		      else
			std::cerr << "WARNING: Invalid tdc_id.lr = " << tdc_id.lr <<std::endl;
		    }
		  else
		    {
		      std::cerr << "WARNING: Something went wrong in mona::map_tdc.\n";
		      return;
		    }
		  
		  ++pMona; ++ll;
		}
	      pMona += 2; ll+=2; //skip trailing longword
	    }
	  else if(nCrate == 0) //\qdc
	    {
	      for(int i =0; i < nChannels; i++)
		{
		  unsigned short nChan = (*pMona & DATAH_CHANMASK)  >> DATAH_CHANSHIFT;
		  ++pMona; ++ll;
		  
		  //get wall, bar & l/r from mona::map_qdc
		  mona_pmtmap qdc_id = map_qdc(nCrate, nSlot, nChan);
		  
		  if(qdc_id.wall != -1)
		    {
		      //unpack data into tree parameters
		      if(!qdc_id.lr)
			l.qraw[qdc_id.wall][qdc_id.bar] = (*pMona & DATAL_DATAMASK);
		      else if(qdc_id.lr)	                                
			r.qraw[qdc_id.wall][qdc_id.bar] = (*pMona & DATAL_DATAMASK);
		      else
			std::cerr << "WARNING: Invalid qdc_id.lr = " << qdc_id.lr <<std::endl;
		    }
		  else
		    std::cerr << "WARNING: Something went wrong in mona::map_qdc.\n";
		  
		  ++pMona; ++ll;
		}
	      pMona += 2; ll+=2; //skip trailing longword
	    }
	  else
	   {;}//	std::cerr << "Invalid CAEN ADC Crate Id " <<nCrate<<std::endl;
	}  
      break;
      
      
      // skip cans packet if present:
    case 0x5050:
      //do nothing
      break;
      
    case 0x5010:
      trigger.monapattern = *(pMona);
      trigger.monahits    = *(pMona+1);
      for(int i=0; i < 2; ++i) trigger.monacount_pattern[i] = *(pMona+2+i);
      break;
    }
}

// cal
void
cal::mona::reset()
{
  l.reset();
  r.reset();
  hit.reset();

  mult  = -1;
  x     = -1;
  y     = -1;
  z     = -1;
  rho   = -1;
  phi   = -1;
  theta = -1;
  t     = -1;
  v     = -1;
  q     = -1;
  ke    = -1;

  for(int i=0; i< MONA_WALLS; ++i)
    {
      for(int j=0; j< WALL_BARS; ++j)
	{
	  xpos[i][j]  = -1;
	  tmean[i][j] = -1;
	  qmean[i][j] = -1;
	}
    }
};

monatemp::hit
cal::mona::calculate_hit(int i, int j, var::mona_location& location)
{
  static monatemp::hit hit;
  hit.reset();
  //\todo: DOUBLE CHECK THIS!!!!!
  static bool warned = 0;
  if(location.o_mag2(i, j) == 0)
    {
      if(!warned)
	{
	  std::cerr << "WARNING: orientation vector has magnitude 0.\n"\
		    << "Setting positions to -1 for every event.\n"
		    << "This is your only warning!!!\n";
	  warned = 1;
	}
      return hit;
    }
 
  //cartesian coordinates
  // x
  hit.x  = xpos[i][j] * location.oz[i][j] / 
                        sqrt(pow(location.ox[i][j], 2) +\
			     pow(location.oz[i][j], 2));

  hit.x += location.x[i][j];

  // y
  hit.y  = location.y[i][j] * location.oz[i][j] / 
                              sqrt(pow(location.oy[i][j], 2) +\
	                           pow(location.oz[i][j], 2));

  // z
  hit.z  = location.z[i][j];

  hit.z += xpos[i][j] * location.ox[i][j] /
                        sqrt(pow(location.ox[i][j], 2) +\
			     pow(location.oz[i][j], 2));

  hit.z += location.y[i][j] * location.oy[i][j] / 
                              sqrt(pow(location.oy[i][j], 2) +\
				   pow(location.oz[i][j], 2));
  //total radius
  static double radius;
  radius = hit.mag();

  //rho
  hit.rho = sqrt(hit.x*hit.x + hit.y*hit.y);
  //phi (in radians)
  hit.phi = atan2(hit.y, hit.x);
  //theta (in radians)
  if(radius >0)
    hit.theta= acos(hit.z / radius);// DV, HL, TR 19 August 2015

  hit.t = tmean[i][j];
  if(hit.t !=0)
    hit.v = radius / hit.t; //\cm/ns

  if(hit.v< C && hit.v >0)
    hit.ke = N_MASS * (1/sqrt(1 - (hit.v/C)*(hit.v/C)) - 1);

  return hit;
};

void
cal::mona::fill_hit(monatemp::hit& h)
{
  x = h.x; y = h.y; z = h.z;
  rho = h.rho; phi = h.phi;
  theta = h.theta;
  t = h.t; v = h.v; 
  ke = h.ke; q = h.q;
};

void
cal::mona::calibrate(raw::mona* rw, var::mona& v)
{
  l.calibrate(rw->l, v.l);
  r.calibrate(rw->r, v.r);

  static monatemp::hit this_hit;
  static std::vector<monatemp::hit> all_hits;
  all_hits.resize(0);

  // calculate hit parameters for every valid event and put into array
  for(int i=0; i< MONA_WALLS; ++i)
    {
      for(int j=0; j< WALL_BARS; ++j)
	{
	  this_hit.reset();
	  if(is_valid(l.tcal[i][j]) && is_valid(r.tcal[i][j]))
	    {

	    if(i < 9 )
	    	{
	      tmean[i][j] = v.mona_tmean_offset + v.tmean_offset[i][j] \
		- (l.tcal[i][j] + r.tcal[i][j]) / 2;
		}
		else if (i<13) {
	      tmean[i][j] = v.lisa1_tmean_offset + v.tmean_offset[i][j] \
		- (l.tcal[i][j] + r.tcal[i][j]) / 2;
		}
		else {
	      tmean[i][j] = v.lisa2_tmean_offset + v.tmean_offset[i][j] \
		- (l.tcal[i][j] + r.tcal[i][j]) / 2;
		}

	      xpos[i][j]  = (l.tcal[i][j] - r.tcal[i][j]) * v.xpos_slope[i][j] \
		+ v.xpos_offset[i][j];

	      this_hit = calculate_hit(i, j, v.location);
	    }
	  if(is_valid(l.qcal[i][j]) && is_valid(r.qcal[i][j]))
	    {
	      qmean[i][j] = sqrt(l.qcal[i][j]*r.qcal[i][j]);
	      this_hit.q = qmean[i][j];
	    }
	  if( is_valid(this_hit.t) && is_valid(this_hit.v))
	    all_hits.push_back(this_hit);
	}
    }

  // now sort the valid hits and put them into the output parameters
  mult = all_hits.size();

  if(v.sort_param == 2) //\velocity
    sort(all_hits.begin(), all_hits.end(), monatemp::velocity_compare());
  else
    sort(all_hits.begin(), all_hits.end(), monatemp::time_compare());

  for(unsigned int i=0; i< MONA_HITS; ++i)
    {
      if(i< all_hits.size())
	hit.fill(i, all_hits[i]);
      else
	break;
    }

  int hit_index = -1;
  for(unsigned int i=0; i< MONA_HITS; ++i)
    {
      if(i< all_hits.size())
	{
	  if(all_hits[i].t > v.nwindow_low &&
	     all_hits[i].t< v.nwindow_high)
	    {
	      hit_index = i; 
	      break;
	    }
	}
      else
	break;
    }
  if(hit_index >-1)
    fill_hit(all_hits[hit_index]);
};


//---------------------------------------------------------//
// class mona_hit

//cal
void
cal::mona_hit::reset()
{
  for(int i=0; i< MONA_HITS; ++i)
    {
      x[i]   = -1;  
      y[i]   = -1;  
      z[i]   = -1;  
      rho[i] = -1;
      phi[i] = -1;
      t[i]   = -1;  
      v[i]   = -1;  
      ke[i]  = -1; 
      q[i]   = -1;
    }
};


void
cal::mona_hit::fill(int i, monatemp::hit& h)
{
  x[i] = h.x; y[i] = h.y; z[i] = h.z;
  rho[i] = h.rho; phi[i] = h.phi;
  theta[i] = h.theta;
  t[i] = h.t; v[i] = h.v; 
  ke[i] = h.ke; q[i] = h.q;
};
