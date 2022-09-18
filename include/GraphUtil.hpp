#pragma once
#include <iostream>
#include <fstream>
#include <filesystem>
namespace fs = std::filesystem;
namespace CGC {
class Graph {
  fs::path p;
  bool check_is_DAG(fs::path& p) {

    return true;
  }

public:
  Graph(fs::path pin) : p(pin) {
    if (!check_is_DAG(p)) {
      std::cout << "error! File " << p << " is not DAG. abort" << std::endl;
      abort();
    }
  }

  bool GenerateNewCGsAndOutputToFile(fs::path output_path) {}
};
} // namespace CGC