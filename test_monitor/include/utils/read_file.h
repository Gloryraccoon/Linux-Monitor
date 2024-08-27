#pragma once

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace monitor {
class ReadFile {
 public:
  explicit ReadFile(const std::string& name) : ifs_(name) {}
  ~ReadFile() { ifs_.close(); }

  bool ReadLine(std::vector<std::string>* args);

 private:
  std::ifstream ifs_;
};
}  // namespace monitor