#include <string>

#include "format.h"
#include <iomanip>
#include <iostream>

using std::string;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long int uptime) { 
  int hours = uptime/3600;
  int minutes = (uptime % 3600) / 60;
  int seconds = uptime % 60;
  std::ostringstream formattedTime;
  formattedTime << std::setfill('0') << std::setw(2) << hours << ":" << std::setfill('0') << std::setw(2) << minutes << ":" << std::setfill('0') << std::setw(2) << seconds;
  std::string timeString = formattedTime.str();
  return timeString;
}