#include "TimeUtils.h"

namespace QUAT {

unsigned long TimeUtils::epochMs() {
	return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}


// The amounts of milliseconds for each time increment.
#define MSHOUR 3600000
#define MSMIN 60000
#define MSSEC 1000

// Handy compiler macro that divides out the milliseconds
// for a certain time increment and adds it to the string stream.
//
// Since all of the code is the same set of operations, it makes
// sense to use a compiler macro. Don't Repeat Yourself, after all.
#define tfmt(A, B, C)                      \
  unsigned long A = ((ms - (ms % B)) / B); \
  if (A > 0) {                             \
    if (A < 10) {                          \
      out << "0";                          \
    }                                      \
    out << A;                              \
  } else {                                 \
    out << "00";                           \
  }                                        \
  ms -= A * B;                             \
  out << C;                                

string TimeUtils::formatMs(unsigned long ms) {
  std::ostringstream out;

  tfmt(mins, MSMIN, ":");
  tfmt(sec, MSSEC, ".");

  // Add zeroes if necessary
  if (ms < 100) {
    out << "0";
  }
  if (ms < 10) {
    out << "0";
  }
  out << ms;

  return out.str();
}

}

