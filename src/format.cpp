#include "format.h"

#include <string>

using std::string;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds) {
  int hours = seconds / 3600;
  int minutes = (seconds % 3600) / 60;
  int shortSeconds = (seconds % 3600) / 60;
  char timestring[9];
  sprintf(timestring, "%02d:%02d:%02d", hours, minutes, shortSeconds);
  return string(timestring);
}