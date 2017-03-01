/* This function reads in the partial inverse
 * ion-optical matrix (.imap) that has been
 * derived from the forward matrix
*/

#include <fstream>
#include <iostream>
//#include <algorithm>
//#include <iterator>
//#include <vector>
#include <cmath>
#include <string>
#include <stdlib.h>
#include <cstdio>

/* Function Declarations */
int initialize(std::string map_file, double **C, double **pwr);
int get_collumns(std::string map_file);
int get_npar(std::string map_file, int ncoef);
int get_nlines(std::string map_file);
double ** AllocateMatrix(int m,int n);
void WriteMatrix(double ** Matrix, int n, int m);
void test0();

/* Function Definitions */
/*
int main()
{
  test0();

  return 0;
}
*/
// test:
//   line counting function
//   column counting function
//   parameter counting function
//   Coeff matrix allocation
//   Par matrix allocation
//   initialization

/*
void test0()
{
  std::string map_file = "/projects/e15118/n2analysis/maps/z8a24_Hp9_7124_Bp3.445_order3_angle-0.3_pos0.50_DL1.64.imap";
  int nlines = get_nlines(map_file);
  int ncol = get_collumns(map_file);
  int ncoef= ncol - 1;
  std::cout << "Columns: " << ncol << std::endl;
  int npar = get_npar(map_file, ncoef);
  std::cout << "Paramters: " << npar << std::endl;

  double ** Coeff = AllocateMatrix(nlines,ncoef);
  double ** Pars  = AllocateMatrix(nlines,npar);

  initialize(map_file,Coeff,Pars);

  WriteMatrix(Coeff,nlines,ncoef);
  WriteMatrix(Pars,nlines,npar);

  std::string fmap_file= "/projects/e15118/n2analysis/maps/z8a24_Hp9_7124_Bp3.445_order3_angle-0.3_pos0.50_DL1.64.map";
  int fnlines = get_nlines(fmap_file);
  int fncol   = get_collumns(fmap_file);
  int fncoef  = ncol - 1;
  std::cout << "Columns: " << fncol << std::endl;
  int fnpar   = get_npar(fmap_file, fncoef);
  std::cout << "Parameters: " << fnpar << std::endl;

  double ** fCoeff = AllocateMatrix(fnlines,fncoef);
  double ** fPars  = AllocateMatrix(fnlines,fnpar);

  initialize(fmap_file,fCoeff,fPars);

  WriteMatrix(fCoeff,fnlines,fncoef);
  WriteMatrix(fPars,fnlines,fnpar);
}

*/
int initialize(std::string map_file, double **C, double **pwr)
{
  std::ifstream ifs(map_file.c_str(), std::ios::in);
  char bbb[5000];
  if(ifs.fail())
  {
    fprintf(stderr,
     "Error: Map file %s does not exist. Aborting map calculation.\n\n",
     map_file.c_str());
    ifs.close();
    return -1;
  }
  else
  {
    ifs.getline(bbb,5000);
    std::string sss(bbb);
    if(sss == "     I  COEFFICIENT            ORDER EXPONENTS")
    {
      std::cerr <<"I think you specified a SpecTcl format map. Exiting.\n\n";
      return -1;
    }
  }
  ifs.close();

  int ncol = get_collumns(map_file);
  int ncoef = ncol - 1;
  int npar = get_npar(map_file, ncoef);

  int nlines = 0;

  FILE* fin = fopen(map_file.c_str(),"r");
  char buf[14], buf2[1];

  bool done = 0;
  std::string sbuf;
  size_t nel;
  while(1)
  {
    fseek(fin,1,SEEK_CUR);
    for(int j=0; j< ncoef; ++j)
    {
      nel = fread(buf,sizeof(char),14,fin);
      //if(nel!=14) fprintf(stderr, "Error in initialize: nel =\%dn", int(nel));
      sbuf = std::string(buf);
      if(sbuf == "--------------" || feof(fin))
      {
        done = 1;
        break;
      }
      C[nlines][j] = atof(buf);
    }
    if(done) break;
    fseek(fin,1,SEEK_CUR);
    for(int k=0; k< npar; ++k)
    {
      nel = fread(buf2,sizeof(char),1,fin);
      pwr[nlines][k] = atoi(buf2);
    }
    fseek(fin,1,SEEK_CUR);
    ++nlines;
  }

  fclose(fin);
  return 0;
}



/* read through the first line and tally the number
 * of 14 byte segments until the \n character
 * is reached; report the tally as ncol
*/
int get_collumns(std::string map_file)
{
  FILE* fff = fopen(map_file.c_str(),"r");
  char buf[14];
  int ncol = 0;
  bool done = 0;
  size_t nel;
  fseek(fff,1,0);
  while(1) {
    nel = fread(buf,1,14,fff);
    if(nel!=14) fprintf(stderr, "Error in get_collumns.\n");
    for(int i=0; i< 14; ++i) {
      if(buf[i]=='\n') {
	done=1;
      }
    }
    ++ncol;
    if(done) break;
  }

  fclose(fff);
  printf("Columns: %i\n",ncol);
  printf("Coeffs (ncol-1): %i\n",ncol-1);
  return ncol;
};

/* starting from the beginning of the .imap file
 * seek through the first ncoef columns to get
 * to the column that encodes the powers of the
 * parameters that go with each coefficient
*/
int get_npar(std::string map_file, int ncoef)
{
  FILE* fff = fopen(map_file.c_str(),"r");
  fseek(fff,1,0);
  for(int i=0; i< ncoef; ++i)
    fseek(fff,14,SEEK_CUR);
  fseek(fff,1,SEEK_CUR);
  int npar = 0;
  char buf[1];
  size_t nel;
  while(1) {
    nel = fread(buf,1,1,fff);
    if(nel!=1) fprintf(stderr, "Error in get_npar\n");
    if(buf[0]=='\n') break;
    ++npar;
  }
  fclose(fff);
  printf("NPar: %i\n",npar);
  return npar;
};


/* ROOT is lame and can't use the istream_iterator
 * class 

int get_nlines(std::string map_file)
{
  std::ifstream ifile(map_file.c_str());
  ifile.unsetf(std::ios_base::skipws);

  // count the newlines with an algorithm specialized for counting
  unsigned line_count = std::count(
  	std::istream_iterator<char>(ifile),
	std::istream_iterator<char>(),
	'\n');
  std::cout << "Lines: " << line_count << std::endl;

  return line_count;

}
... so we have to do this a lamer way */

int get_nlines(std::string map_file)
{
  unsigned int line_count = 0;
  FILE *ifile = fopen(map_file.c_str(),"r");
  int ch;

  while (EOF != (ch=getc(ifile)))
  {
    if ('\n' == ch) ++line_count;
  }
  printf("Lines: %u\n",line_count);

  return line_count;

}


double ** AllocateMatrix(int m,int n)
{
  double ** Matrix;
  Matrix = new double*[m];
  for(int i=0;i<m;i++)
  {
    Matrix[i] = new double[n];
    for(int j=0;j<n;j++){ Matrix[i][j] = 0.0; }
  }

  return Matrix;
}


void DeallocateMatrix(double ** Matrix,int m, int n)
{
  for(int i=0;i<m;i++)
    delete Matrix[i];
  delete Matrix;
}


// Write out a given matrix
void WriteMatrix(double ** Matrix, int n, int m)
{
  for(int i=0;i < n;i++)
  {
    std::cout << std::endl;
     for (int j=0 ; j < m;j++){
        printf("  A[%2d][%2d] = %12.4E",i, j, Matrix[i][j]);
     }
  }
    std::cout << std::endl;
}
