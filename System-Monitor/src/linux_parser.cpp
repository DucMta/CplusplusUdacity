#include <dirent.h>
#include <unistd.h>
#include <sstream>
#include <string>
#include <vector>
#include <iostream>

#include "linux_parser.h"

using std::stof;
using std::string;
using std::to_string;
using std::vector;

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, kernel, version;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> version >> kernel;
  }
  return kernel;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
//   int count =0;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
//         count++;
      }
    }
  }
//   std::cout << "number pids:" << count;
  closedir(directory);
  return pids;
}

// TODO: Read and return the system memory utilization
float LinuxParser::MemoryUtilization() { 
  string line;
  string meminfo;
  string number_meminfo;
  string kB;
  float memtotal = 0.0;
  float memfree = 0.0;
  std::ifstream filestream(kProcDirectory + kMeminfoFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >> meminfo >> number_meminfo >> kB) {
        if (meminfo == "MemTotal:") {
          memtotal = stof(number_meminfo);
        }
        else if(meminfo == "MemFree:")
        {
          memfree = stof(number_meminfo);
          return (memtotal - memfree)/memtotal;
        }
        else
        {
        }
      }
    }
  }
  return (memtotal - memfree)/memtotal;  
}

// TODO: Read and return the system uptime
long LinuxParser::UpTime() {
  long total_time = 0;
  long s_total_time;
  long s_idle_time;
  string line;
  std::ifstream stream(kProcDirectory + kUptimeFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> s_total_time >> s_idle_time;
    total_time = s_total_time;
  }
  return total_time;  
}

// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() { return 0; }

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid) { return 0; }

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() { return 0; }

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() { return 0; }

// TODO: Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() {
 
}

// DucLH12
float LinuxParser::ProcessorUtilization(int pid) {
  string utime, stime, cutime, cstime, starttime;
  float total_time, uptime, Hertz;
  float seconds = 0.0;
  float cpu_usage = 0.0;
  string line;
  string str_pid = to_string(pid);
  std::ifstream stream(kProcDirectory + str_pid + kStatFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
     for(int i = 0; i < 14; i++)
     {
       linestream >> utime;
     }
    linestream >> stime >> cutime >> cstime;
    for(int i =0; i < 5; i++)
    {
      linestream >> starttime;
    }
    total_time = stof(utime) + stof(stime) + stof(cutime) + stof(cstime);
    uptime = (float)UpTime();
    Hertz = sysconf(_SC_CLK_TCK);
    seconds = uptime - (stof(starttime)/Hertz);
    cpu_usage = 100*((float)(total_time/Hertz)/seconds);
  }
  return cpu_usage;
}
//DucLH12

// TODO: Read and return the total number of processes
int LinuxParser::TotalProcesses() {
  string process;
  int number_process = 2;
  string s_nprocess;
  string line;
  std::ifstream stream(kProcDirectory + kStatFilename);
  if (stream.is_open()) {
    while (std::getline(stream, line)) {
    std::istringstream linestream(line);
    	while (linestream >> process >> s_nprocess) {
    		if(process == "processes")
        	{
          		number_process = stoi(s_nprocess);
          		return number_process;
        	}
     	}
    }
  }
  return number_process;  
}

// TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses() {
  string process;
  int number_process = 2;
  string s_nprocess;
  string line;
  std::ifstream stream(kProcDirectory + kStatFilename);
  if (stream.is_open()) {
    while (std::getline(stream, line)) {
    std::istringstream linestream(line);
    	while (linestream >> process >> s_nprocess) {
    		if(process == "procs_running")
        	{
          		number_process = stoi(s_nprocess);
          		return number_process;
        	}
     	}
    }
  }
  return number_process;  
}

// TODO: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid) {
  string command, param2, param3;
  string line;
  string str_pid = to_string(pid);
  std::ifstream stream(kProcDirectory + str_pid + kCmdlineFilename);
  if (stream.is_open()) {
    	std::getline(stream, line);
    	std::istringstream linestream(line);
    	linestream >> command >> param2 >> param3;
    }
  return command;  
}

// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(int pid) {
  string key_ram, ram, kb;
  string line;
  string str_pid = to_string(pid);
  std::ifstream stream(kProcDirectory + str_pid + kStatusFilename);
  if (stream.is_open()) {
    while (std::getline(stream, line)) {
    std::istringstream linestream(line);
    	while (linestream >> key_ram >> ram >> kb) {
    		if(key_ram == "VmSize:")
        	{
              int ram_temp = stoi(ram);
              ram_temp =  ram_temp/1000;
              ram = to_string(ram_temp);
          	  return ram;
        	}
     	}
    }
  }
  return ram;   
}

// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int pid) { 
  string key_uid, uid;
  string line;
  string str_pid = to_string(pid);
  std::ifstream stream(kProcDirectory + str_pid + kStatusFilename);
  if (stream.is_open()) {
    while (std::getline(stream, line)) {
    std::istringstream linestream(line);
    	while (linestream >> key_uid >> uid) {
    		if(key_uid == "Uid:")
        	{
          		return uid;
        	}
     	}
    }
  }
  return uid;  
}

// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int pid) {
  string username;
  string line;
  string total_str = ":x:" + Uid(pid);
  std::ifstream stream(kPasswordPath);
  size_t found;
  if (stream.is_open()) {
    while (std::getline(stream, line)) {
       found = line.find(total_str);
    	if (found != std::string::npos) {
          string username = line.substr(0, found);
          return username;
    	}
    }
  }
  return username;  
}

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid) {
  string uptime, xxx;
  string line;
  string str_pid = to_string(pid);
  std::ifstream stream(kProcDirectory + str_pid + kStatFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
     for(int i = 0; i < 22; i++)
     {
		linestream >> uptime;
     }
  }
  long clock_ticks = std::stol(uptime);
  long ticks_per_second = sysconf(_SC_CLK_TCK);
  long seconds = clock_ticks / ticks_per_second;
  return seconds;
}
