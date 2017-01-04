#ifndef __TIME_UTILS_H__
#define __TIME_UTILS_H__

#include <vector>
#include <string>
#include <sstream>
#include <chrono>
#include <cmath>

namespace QUAT {

using namespace std;

class TimeUtils
{
public:

  // Returns the number of milliseconds since epoch.
  //
  // Should not be used for timestamps, just for judging relative time
  // differences (e.g between two function calls.)
  static unsigned long epochMs();

  // Formats milliseconds into a string in the format
  // HH:MM:SS.msmsms
  // 
  // Does not leave zeroes in spots that are not in use.
  // For example:
  // 12.123
  // 1:12.123
  // 12:12:12.123
  static string formatMs(unsigned long ms);
};

}

#endif // __TIME_UTILS_H__

