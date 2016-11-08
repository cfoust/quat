#ifndef __QUAT_STREAM_H__
#define __QUAT_STREAM_H__

#include <string>
#include <fstream>
#include "cocos2d.h"

namespace QUAT {

using namespace std;

enum MODE {
  READ,
  WRITE
};

class QuatStream 
{
private:
  // The two streams we use to read and write files
  ofstream * out;
  ifstream * in;
  
  // The variable that marks whether we're in reading
  // or writing mode 
  //
  // This doesn't change the behavior of functions,
  // it's just a marker of sorts.
  MODE mode;

  // Read n bytes from the in stream and store them in
  // the memory pointed to by bytes.
  void read(char * bytes, int n);

  // Write n bytes to the out stream source from the memory
  // pointed to by bytes.
  void write(char * bytes, int n);

public:
  // The constructor for writing a file 
	QuatStream(ofstream * out);

  // The constructor for reading a file
	QuatStream(ifstream * in);

  // Works when writing and reading. Outputs a version number
  // into the file and verifies it on read.
  //
  // Returns 0 when writing.
  //
  // Returns 0 if the version numbers matched on read, otherwise
  // returns the alternate version number.
  int version(int versionNumber);

  // Stream writes to pointers on read and reads from them on write.
  // Thus you don't need a separate method for reading and writing
  // to a class.
  void boolean(bool * flag); 
  void character(char * c); 
  void integer(int * number); 
  void linteger(long int * number);
  void word(string * s);

  bool isWriting();
};

}

#endif // __QUAT_STREAM_H__
