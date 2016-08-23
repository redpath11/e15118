#ifndef __HAVE_UTILS_CC
#define __HAVE_UTILS_CC

#include <iostream>
#include <vector>

class gate2d
{
private:
  int np; 
  double* px;
  double* py;

public:
  gate2d(int npoints) {
    np = npoints;
    px = new double[npoints+1];
    py = new double[npoints+1];
  }

  int
  set_point(int n, double x, double y) {
    if(n>np-1) {
      std::cerr << "n("<<n<<") >np("<<np<<")\n";
      return -1;
    } else {
      px[n] = x;
      py[n] = y;
      return 1;
    }
  }

  void
  close(){
    px[np]=px[0];
    py[np]=py[0];
  }

  bool
  check_closure() {
    if(px[0]==px[np] && py[0]==py[np])
      return true;
    return false;
  }

  bool
  is_inside(double x, double y) {
    double xint;
    int i;
    int inter = 0;
    for (i=0;i<np-1;i++) {
      if (py[i] == py[i+1]) continue;
      if (y <= py[i] && y <= py[i+1]) continue;
      if (py[i] < y && py[i+1] < y) continue;
      xint = px[i] + (y-py[i])*(px[i+1]-px[i])/(py[i+1]-py[i]);
      if ((double)x < xint) inter++;
    }
    if (inter%2) return true;
    return false;
  }

  ~gate2d() {
    delete[] px;
    delete[] py;
  }
};

class gate2d_vector
{
private:
  int np; 
  std::vector<double> px;
  std::vector<double> py;

public:
  gate2d_vector() {
    np = 0;
    px.resize(0);
    py.resize(0);
  }

  void
  add_point(double x, double y) {
    ++np;
    px.push_back(x);
    py.push_back(y);
  }

  void
  close() {
    add_point(px[0], py[0]);
  }

  bool
  check_closure() {
    if(px[0]==px[np-1] && py[0]==py[np-1])
      return true;
    return false;
  }

  bool
  is_inside(double x, double y) {
    double xint;
    int i;
    int inter = 0;
    for (i=0;i<np-1;i++) {
      if (py[i] == py[i+1]) continue;
      if (y <= py[i] && y <= py[i+1]) continue;
      if (py[i] < y && py[i+1] < y) continue;
      xint = px[i] + (y-py[i])*(px[i+1]-px[i])/(py[i+1]-py[i]);
      if ((double)x < xint) inter++;
    }
    if (inter%2) return true;
    return false;
  }

  int get_size() {
    return np;
  }

  double get_x(int i) {
    if( i< np) return px[i];
    else return -1;
  }

  double get_y(int i) {
    if( i< np) return py[i];
    else return -1;
  }

  void reset() {
    np = 0;
    px.resize(0);
    py.resize(0);
  }
};


#endif
