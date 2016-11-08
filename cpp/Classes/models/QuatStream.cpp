#include "QuatStream.h"

namespace QUAT {

QuatStream::QuatStream(ofstream * out) {
  this->out = out;
  this->mode = WRITE;
}

QuatStream::QuatStream(ifstream * in) {
  this->in = in;
  this->mode = READ;
}

void QuatStream::read(char * bytes, int n) {
  // ignore call if we're in write mode
  if (this->mode == WRITE) return;

  // Perform the read
  this->in->read(bytes, n); 
}

void QuatStream::write(char * bytes, int n) {
  // ignore call if we're in read mode
  if (this->mode == READ) return;
  
  // Perform the write
  this->out->write(bytes, n);
}

// Simple, reusable code for doing primitive types
#define tprim(A,B) {                      \
  if (this->mode == READ) {               \
    char data[sizeof(A)];                 \
    this->read((char*) data, sizeof(A));  \
    *B = *((A*) data);                    \
  } else if (this->mode == WRITE) {       \
    this->write((char*)B, sizeof(A));     \
  }                                       \
}
  
int QuatStream::version(int versionNumber) {
  int localVersion = versionNumber;
  this->integer(&localVersion);
  
  // Return 0 if we're in write mode
  return (this->mode == WRITE) ? 0 : 
  // Return the version number we found if it differed
  // from the one we wanted, otherwise 0
  ((localVersion == versionNumber) ? 0 : localVersion);
}

void QuatStream::boolean(bool * flag) tprim(bool, flag);
void QuatStream::integer(int * number) tprim(int, number); 
void QuatStream::linteger(long int * number) tprim(long int, number);

void QuatStream::word(string * s) {
  if (this->mode == READ) {
    // Clear the string so we can write new characters to it
    s->clear();

    char letter;
    int source;
    for (int i = 0; i < 4; i++) {
      // Read a letter
      this->integer(&source);

      // Change it into a normal char
      letter = source + 65;

      // Adds it to the string
      s->append(&letter);
    }
  } else if (this->mode == WRITE) {
    char letter;
    int source;

    for (int i = 0; i < 4; i++) {
      // Grab a letter from the actual string
      letter = (*s)[i];
      source = letter - 65;

      // Write a letter
      this->integer(&source);
    }
  }
}

}
