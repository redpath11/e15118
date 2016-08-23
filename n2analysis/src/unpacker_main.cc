#include <iostream>
#include "TSystem.h"
//#include "TROOT.h"
#include "TObject.h"
#include "TFile.h"
#include "TTree.h"

#include "sweeper.hh"
#include "mona.hh"
#include "caesar.hh"
#include "unpacker.hh"

#define EVENT_BUFFER 1
#define BUF_HEADER_LENGTH 16
using namespace std;

// Globals
string filename ("0");
string outfilename("0");
bool unpack_sweeper = __UNPACK_SWEEPER;
bool unpack_caesar  = __UNPACK_CAESAR;
bool unpack_mona    = __UNPACK_MONA;
bool cleared = 0;
bool print   = 1;
bool prompt  = 1;

// For handling of arguments to main.

void
print_usage_message()
{
  std::cerr << "Usage: evtunpacker -f ${input_file} -o " \
	    << "${output_file} [-s] [-m] [-c]\n" \
	    << "       -s -m -c are followed by a 1/0 to turn on/off "\
	    << "sweeper, mona, or caesar unpackers\n" \
	    << "       (default is to unpack sweeper and mona, "\
	    << "see the Makefile for how to change this)\n\n";
};

int
handle_args(int argc, char** argv)
{
  using namespace std;
  short pos = 1;
  string arg;

  if(argc == 1)
    {
      print_usage_message();
      return -1;
    }

  while(pos< argc)
    {
      arg = argv[pos];
      if(arg == "-f")
	{
	  if(pos+1< argc)
	    {
	      filename = argv[pos+1];
	      pos += 2;
	    }
	  else
	    {
	      print_usage_message();
	      return -1;
	    }
	}
      else if (arg == "-o")
	{
	  if(pos+1 < argc)
	    {
	      outfilename = argv[pos+1];
	      pos +=2;
	    }
	  else
	    {
	      print_usage_message();
	      return -1;
	    }
	}
      else if (arg == "-s" && pos+1< argc &&
	       (string(argv[pos+1])=="1" ||
		string(argv[pos+1])=="0"))
	{
	  unpack_sweeper = bool(atoi(argv[pos+1]));
	  pos +=2;
	}
      else if (arg == "-m" && pos+1< argc &&
	       (string(argv[pos+1])=="1" ||
		string(argv[pos+1])=="0"))
	{
	  unpack_mona = bool(atoi(argv[pos+1]));
	  pos +=2;
	}
      else if (arg == "-c" && pos+1< argc &&
	       (string(argv[pos+1])=="1" ||
		string(argv[pos+1])=="0"))
	{
	  unpack_caesar = bool(atoi(argv[pos+1]));
	  pos +=2;
	}
      else if (arg == "-np")
	{
	  print = 0;
	  ++pos;
	}
      else if (arg == "--force")
	{
	  prompt = 0;
	  ++pos;
	}
      else
	{
	  print_usage_message();
	  return -1;
	}
    }

  // Check if the files exist
  ifstream* fcheck = new ifstream();
  fcheck->open(filename.c_str());
  if(fcheck->fail())
    {
      cerr << "Error: file " << filename << " does not exist.\n\n";
      return -1;
    }
  fcheck->close();

  if(prompt)
    {
      fcheck->open(outfilename.c_str());
      if(!fcheck->fail())
	{
	  string answer;
	  system("clear"); cleared = 1;
	  cerr << "The file " << outfilename << \
	    " exists already. Do you want to overwrite it (y/n)?\n";
	  cin >> answer;
	  if(answer != "y")
	    {
	      if(answer != "Y")
		{
		  cerr << "Exiting...\n\n";
		  return -1;
		}
	    }
	  else cerr <<"\n";
	}
      delete fcheck;
    }
  if(outfilename == "0" || filename == "0")
    {
      print_usage_message();
      return -1;
    }
  return 1;
};


int
main(int argc, char** argv)
{
  if(handle_args(argc, argv) == -1)
     return 0;

  ifstream ifs(filename.c_str(), ios::in | ios::binary);

  // The class that will handle unpacking functions
  //  raw::unpacker* unpack = new raw::unpacker();
  //  raw::unpacker* unpack = new raw::unpacker();
  raw::unpacker unpack;

  // Define instances of the classes for your detector systems
  // They must be defined on the heap just like below!!!
    raw::sweeper* sweeper = new raw::sweeper();
    raw::mona*    mona    = new raw::mona();
    raw::caesar*  caesar  = new raw::caesar();

  
  //----BEGIN ROOT SPECIFIC STUFF----//
  
  TFile* rootfile = new TFile(outfilename.c_str(), "RECREATE");
  string t_title = "TTree created from ";
  t_title += filename;
  TTree* roottree = new TTree("t", t_title.c_str());

  // Load the root libraries generated for each detector class
  gSystem->Load("detector_hh.so");
  gSystem->Load("unpacker_cc.so");
  if(unpack_sweeper)
    gSystem->Load("sweeper_cc.so");
  if(unpack_mona)
    gSystem->Load("mona_cc.so");
  if(unpack_caesar)
    gSystem->Load("caesar_cc.so");

  // Create a TTree branch for each detector system
  if(unpack_sweeper)
    roottree->Branch("sweeper", "raw::sweeper", &sweeper);
  if(unpack_mona)
    roottree->Branch("mona"   , "raw::mona"   , &mona);
  if(unpack_caesar)
    roottree->Branch("caesar" , "raw::caesar" , &caesar);

  // Also make a branch to hold the run number
  unsigned int runnum;
  roottree->Branch("runnum" , &runnum , "runnum/i");

  //-----END ROOT SPECIFIC STUFF-----//
  
  unsigned short* pEvt, nEvts, evtLength;//May not not later MDJ
  int nBuffers = 0;// '' MDJ

  if(!cleared) system("clear");
  cout << "Unpacking NSCL event file " << filename <<"\n";
  cout << "into " << outfilename <<"\n\n";
  if(print)
    cout << "Buffers read:      0"; flush(cout);

  while(!ifs.eof())
    {
      unpack.read_buffer(ifs);// Change MDJ
      if(unpack.get_buffer_type() == EVENT_BUFFER)// Check evt == Physics evt MDJ
	{
	  ++nBuffers;// # of evts MDJ
	  if(print)
//            cout  << "\n" << nBuffers << "\n"; flush(cout);
	    {
	      if(nBuffers/100 > (nBuffers-1)/100)//  if(nBuffers/100 > (nBuffers-1)/100) HL5/2/15
	      {
		  for(int i=nBuffers; i>0; i/=10)
		    cout<<"\b";
		  cout  <<nBuffers; flush(cout);
		}
	    }

	  runnum = unpack.get_run_number();// Rewrite get_run_number() MDJ
	  nEvts = unpack.get_n_evts();// Probably won't need... MDJ
	  pEvt  = unpack.get_buffer();// Will need to be changed MDJ
	  pEvt += BUF_HEADER_LENGTH;


	  vector<unsigned short> sweeper_packets;
	  sweeper_packets.push_back(SWEEPER_PACKET);

	  vector<unsigned short> monalisa_packets;
	  monalisa_packets.push_back(MONA_PACKET);
	  monalisa_packets.push_back(MONA_TRIGGER_PACKET);
	  monalisa_packets.push_back(LISA_PACKET);

	  vector<unsigned short> caesar_packets;
	  caesar_packets.push_back(FERA_PACKET);
	 
	 //Wont need to loop over evts MDJ
	  for(unsigned short i=0; i< nEvts; ++i) //\loop events
	    {
	      evtLength = *pEvt;
// Here is where the various detector's packets get unpacked.
	      if(unpack_sweeper)
		{
		unpack.unpack_detector(sweeper, sweeper_packets, pEvt);
		}
	      if(unpack_mona)
		{
		  unpack.unpack_detector(mona, monalisa_packets, pEvt);
		}
	      if(unpack_caesar)
		{
		unpack.unpack_detector(caesar, caesar_packets, pEvt);
		}
	      //--ROOT SPECIFIC--//
	      roottree->Fill();
  	      //-----------------//

	      // Move on to the next event
	      pEvt += evtLength;
	    }
	}
    }

    if(print){
      cout << "\nRead a total of " << nBuffers << " buffers.\n";
      cout << "Done.\n\n";
    };
  ifs.close();

//-----ROOT SPECIFIC-----//
  rootfile = roottree->GetCurrentFile();
  roottree->Write();
  rootfile->Close();

//-----------------------//

  delete sweeper;
  delete mona;
  delete caesar;

  return 0;
}

