#include "unpacker.hh"
#include <iostream>

static const unsigned short BUFTYPE_POSN(1);
static const unsigned short RUNNUM_POSN (3);
static const unsigned short NEVTS_POSN  (6);

using namespace raw;

void
unpacker::read_buffer(std::ifstream& ifs)
{
  ifs.read((char*)buffer, sizeof(buffer));
};

void
unpacker::read_online_buffer(unsigned short* inbuffer)
{
    for (int i=0;i<4096;++i)
    {
        buffer[i] = inbuffer[i];
    }
};

unsigned short*
unpacker::get_buffer()
{
  return &buffer[0];
};

unsigned short
unpacker::get_buffer_type()
{
  return buffer[BUFTYPE_POSN];
};

unsigned short
unpacker::get_run_number()
{
  return buffer[RUNNUM_POSN];
};

unsigned short
unpacker::get_n_evts()
{
  return buffer[NEVTS_POSN];
};

unsigned short*
unpacker::find_packet(unsigned short tag, unsigned short* pEvt)
{
  // Search for a packet IDed by tag, and return a pointer
  // to the first *DATA* word in the packet. If no packet
  // is found, return the null pointer.
  // Takes in a pointer to the beginning of the event packet
  // (i.e. the packetlength)

  unsigned short* p = pEvt;
  unsigned short* pOut   = NULL;
  unsigned short  nWords = *p; //\event size
  unsigned short  sWords; //\sub event size
  ++p; --nWords;

  while(nWords >0)
    {
      sWords = *p;
      ++p;

      if(*p == tag)
	{
	  pOut = p+1; //\points to first data word
	  break;
	}
      else
	{
	  p += sWords-1;
	  nWords -= sWords;
	}
    }

  return pOut;
};

void
unpacker::unpack_detector(detector* det, std::vector<unsigned short>& pkt_id, unsigned short* pEvt)
{
  //std::cout <<"here1" <<std::endl;
  unsigned short* pUnpack = NULL;
  det->reset();
  for(unsigned int i=0; i< pkt_id.size(); ++i)
    {
      pUnpack = NULL;
      pUnpack = find_packet(pkt_id[i], pEvt);
      if(pUnpack != NULL)
        //std::cout <<"here" <<std::endl;
	det->unpack(pUnpack);
    }
};

