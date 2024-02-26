#include "processor.h"
#include <string>
#include "linux_parser.h"

using std::string;

// TODO: Return the aggregate CPU utilization
float Processor::Utilization() { 
  long user, nice, system, idle, iowait, irq, softirq, steal, guest, guest_nice; 
  string line;
  std::ifstream stream(LinuxParser::kProcDirectory + LinuxParser::kStatFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> user>> nice>> system>> idle>> iowait>> irq>> softirq>> steal>> guest>> guest_nice;
  }
  // Guest time is already accounted in usertime
  user = user - guest;                             // As you see here, it subtracts guest from user time
  nice = nice - guest_nice;                         // and guest_nice from nice time
  // Fields existing on kernels >= 2.6
  // (and RHEL's patched kernel 2.4...)
  unsigned long long int idlealltime = idle + iowait;  // ioWait is added in the idleTime
  unsigned long long int systemalltime = system + irq + softirq;
  unsigned long long int virtalltime = guest + guest_nice;
  unsigned long long int totaltime = user + nice + systemalltime + idlealltime + steal + virtalltime;
  return float(totaltime-idlealltime)/totaltime;  
}