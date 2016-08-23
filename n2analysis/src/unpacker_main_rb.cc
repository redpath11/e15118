#include <iostream>
#include "TSystem.h"
//#include "TROOT.h"
#include "TObject.h"
#include "TFile.h"
#include "TTree.h"

#include "sweeper.hh"
#include "mona.hh"
#include "caesar.hh"
#include "unpacker_rb.hh"

// Define header tags
#define EVENT_BUFFER 30//0x001e
#define BUF_HEADER_LENGTH 4
#define BEGIN_RUN 1
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
  
  // Edited to read in Ring Buffer format by MDJ 5/14/2012.
  //
  // IMPORTANT: If you have a data type you wish to unpack but is not BEGIN_RUN or EVENT_BUFFER,
  // 	        then you must include it in a new IF statement and modify the AND statement of 
  // 	        the UNKNOWN tag. Otherwise, this code will skip over it and keep reading.  
  //            Also: This code may explode if a single event contains more than 2048 words.
  //
  // A Short Explanation:
  //            Each header contains 4 words, the first two designate the total length (in words)
  //            and the second two notate the TYPE. The first 4 words are read in with
  //            unpack.read_header(ifs,8). This stores the first 4 words in an array header[4096].
  //            Individual elements of the array can be retrieved with unpack.get_header_element(i).
  //            The TYPE of the header is checked with an IF statement, if its garbage, then the code 
  //            skips a distance "shiftdistance" along the file and reads in the next 4 words.
  //            IT IS ASSUMED THAT THE NEXT FOUR WORDS WILL BE A HEADER!!! 
  //
  //	        If the tag is something interesting (PHYSICS), the whole event is read in and unpacked.
  //            The process repeats until the end of the file is reached.
  
  
  unsigned short* pEvt, nEvts;
  int nEvents = 0;// # of Events
  int itemlength;// FULL length of header
  int shiftdistance; // Distance to next header

 // Output text
  if(!cleared) system("clear");
  cout << "Unpacking NSCL event file " << filename <<"\n";
  cout << "into " << outfilename <<"\n\n";
  if(print)
    cout << "Events read:       0"; flush(cout);//\n

while(!ifs.eof()){

     // Grab 1st header
     unpack.read_header(ifs,8);// 8 = 4 words, since each word is 2 bytes.

     if(unpack.get_header_element(2) == BEGIN_RUN){ // BEGIN_RUN tag
        itemlength = unpack.get_header_element(0);
 	unpack.read_header(ifs,8);
	runnum = unpack.get_header_element(0);
	// Now move pointer to the end of the segment that was read in:
	shiftdistance = itemlength - 16;
        ifs.seekg(shiftdistance, ios::cur);
	// Read in next header
	unpack.read_header(ifs,8); 
        }

     if(unpack.get_header_element(2) != EVENT_BUFFER && unpack.get_header_element(2) != BEGIN_RUN){// UNKNOWN tag
        itemlength = unpack.get_header_element(0);
        shiftdistance = itemlength - 8;
        ifs.seekg(shiftdistance, ios::cur);      
        }

    if(unpack.get_header_element(2) == EVENT_BUFFER){ // PHYSICS tag
        itemlength = unpack.get_header_element(0);
        unpack.read_header(ifs,itemlength-8);//Read in Events (-8 to account for first 4 words)
        nEvts = unpack.get_header_element(2);//Get # of Events

          // Grab pointer to full event length (including header)
          pEvt  = unpack.get_header();

	  vector<unsigned short> sweeper_packets;
	  sweeper_packets.push_back(SWEEPER_PACKET);

	  vector<unsigned short> monalisa_packets;
	  monalisa_packets.push_back(MONA_PACKET);
	  monalisa_packets.push_back(LISA_PACKET);

	  vector<unsigned short> caesar_packets;
	  caesar_packets.push_back(FERA_PACKET);
	
	      // Here is where the various detector's packets get unpacked.
	      if(unpack_sweeper)
		unpack.unpack_detector(sweeper, sweeper_packets, pEvt);
	      if(unpack_mona){
		 unpack.unpack_detector(mona, monalisa_packets, pEvt);
		 }
	      if(unpack_caesar)
		unpack.unpack_detector(caesar, caesar_packets, pEvt);

	      //--ROOT SPECIFIC--//
	      roottree->Fill();
  	      //-----------------//
	      
	 //---------------- COUNTER -------------------//
	   ++nEvents;
	   if(print)
             {
	      if(nEvents/100 > (nEvents-1)/100)
		{
		  for(int i=nEvents; i>0; i/=10)
		    cout << "\b";
		    cout << nEvents; flush(cout);
		}
	      }
    	 } // Close PHYSICS IF statement
} // End of While Loop = End Of File
  
    if(print){
      cout << "\nRead a total of " << nEvents << " events.\n";
      cout << "Done.\n\n";
      };
  
  // Close file
  ifs.close();

  delete sweeper;
  delete mona;
  delete caesar;

//-----ROOT SPECIFIC-----//
  rootfile = roottree->GetCurrentFile();
  roottree->Write();
  rootfile->Close();

//-----------------------//

  return 0;
}

