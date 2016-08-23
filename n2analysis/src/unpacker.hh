#ifndef __HAVE_UNPACKER_HH
#define __HAVE_UNPACKER_HH

#include "detector.hh"
#include <vector>
#include <fstream>

namespace raw {

  class unpacker
    {
    private:
      unsigned short buffer[4096];

    public:
      void read_buffer(std::ifstream& ifs);
      void read_online_buffer(unsigned short* inbuffer);
      unsigned short* get_buffer();
      unsigned short  get_buffer_type();
      unsigned short  get_run_number();
      unsigned short  get_n_evts();
      unsigned short* find_packet(unsigned short tag, unsigned short* p);
      void unpack_detector(detector* det, std::vector<unsigned short>& pkt_id, unsigned short* pEvt);
    };

}


#endif
