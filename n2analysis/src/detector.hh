#ifndef __HAVE_DETECTOR_HH
#define __HAVE_DETECTOR_HH


// Parent class for detector systems.

namespace raw {

  class detector
  {
  public:
    virtual void reset() = 0;
    virtual void unpack(unsigned short* p) = 0;
    virtual ~detector() { };
  };

}


#endif
