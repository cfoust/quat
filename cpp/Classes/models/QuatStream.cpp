#include "QuatStream.h"

namespace QUAT {

bool QuatStream::isWriting() {
  return this->mode == WRITE;
}

QuatStream::QuatStream(ofstream * out) {
  this->out = out;
  this->mode = WRITE;
  this->index = 0;
}

QuatStream::QuatStream(ifstream * in) {
  this->in = in;
  this->mode = READ;
  this->index = 0;
}

// LOLOL can't believe I'm doing the exact "encryption" I broke
// before.
#include "keys/key.cpp"

void QuatStream::shuffle(char * bytes, int n) {
  for (int i = 0; i < n; i++) {
    bytes[i] ^= key[index];
    index++;
    index %= key_len;
  }
}

void QuatStream::read(char * bytes, int n) {
  // ignore call if we're in write mode
  if (this->mode == WRITE) return;

  // Perform the read
  this->in->read(bytes, n); 
  this->shuffle(bytes, n);
}

void QuatStream::write(char * bytes, int n) {
  // ignore call if we're in read mode
  if (this->mode == READ) return;

  // Make a quick buffer
  char buffer[n];

  // Copy the data into it
  memcpy(buffer, bytes, n);
  
  // Encrypt it
  this->shuffle(buffer, n);

  // Perform the write
  this->out->write(buffer, n);
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
void QuatStream::character(char * c) tprim(char, c);
void QuatStream::integer(int * number) tprim(int, number); 
void QuatStream::linteger(long int * number) tprim(long int, number);
void QuatStream::luinteger(unsigned long * number) tprim(unsigned long, number);

void QuatStream::word(string * s) {
  if (this->mode == READ) {

    char newWord[5];
    newWord[4] = 0;
    for (int i = 0; i < 4; i++) {
      // Read a letter
      this->character(&newWord[i]);
    }

    s->assign(newWord, 4);
  } else if (this->mode == WRITE) {
    char letter;
    int source;

    for (int i = 0; i < 4; i++) {
      // Grab a letter from the actual string
      letter = (*s)[i];

      // Write a letter
      this->character(&letter);
    }
  }
}

}
