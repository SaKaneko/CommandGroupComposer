#pragma once
#include <iostream>
#include <fstream>
#include <filesystem>
#include "../include/Params.hpp"
#include "RandomUtil.hpp"
namespace fs = std::filesystem;
namespace CGC {
class CGInfo {
  int var_cg;
  std::vector<int> ECOST;
  std::vector<int> CCOST;
  std::vector<int> W;
  std::vector<std::vector<int>> type_kernel;

public:
  CGInfo()
      : var_cg(CGC::VAR_CG), ECOST(0), CCOST(CGC::VAR_CG, 0), W(CGC::VAR_CG, 1),
        type_kernel(CGC::VAR_CG) {
    double AVR_ECOST = REC_TIME_MS * ECR;
    double AVR_CCOST = REC_TIME_MS * ECR * CCE;
    for (auto& i : ECOST) {
      i = BoundNormalDistribution(AVR_ECOST, AVR_ECOST / 3, 1, AVR_ECOST * 2);
    }
    for (auto& i : CCOST) {
      i = BoundNormalDistribution(AVR_CCOST, AVR_CCOST / 3, 1, AVR_CCOST * 2);
    }
    std::random_device rnd;
    std::mt19937 mt(rnd());
    std::uniform_int_distribution<> randW(1, CGC::MAX_W);
    for (auto& i : W) {
      i = randW(mt);
    }
    for (int i = 0; i < type_kernel.size(); i++) {
      for (int j = 0; j < W[i]; j++) {
        type_kernel[i].push_back(CGC::VAR_KERNEL);
        CGC::VAR_KERNEL++;
        ECOST.push_back(BoundNormalDistribution(AVR_ECOST, AVR_ECOST / 3, 1,
                                                AVR_ECOST * 2));
      }
    }
  }

  void OverwriteGraph(fs::path& base_p, fs::path& output_p) {
    std::ofstream ofs;
    std::ifstream ifs;
    ifs.open(base_p, std::ios::in);
    ofs.open(output_p);
    ofs << var_cg << " " << CGC::VAR_KERNEL << std::endl;
    for (auto& i : ECOST) {
      ofs << i << std::endl;
    }
    for (int i = 0; i < var_cg; i++) {
      ofs << W[i] << " " << CCOST[i] << std::endl;
      for (int j = 0; j < W[i]; j++) {
        ofs << type_kernel[i][j];
        if (j == W[i] - 1) {
          ofs << std::endl;
        }
        else {
          ofs << " ";
        }
      }
    }
    std::string reading_line_buffer;
    int kernel_type_itr = 0;
    std::getline(ifs, reading_line_buffer);
    int nodes = std::stoi(reading_line_buffer);

    std::vector<int> CGatNode(nodes);
    std::random_device rnd;
    std::mt19937 mt(rnd());
    std::uniform_int_distribution<> randW(0, var_cg - 1);
    for (auto& i : CGatNode) {
      i = randW(mt);
    }
    auto CGtypeitr = CGatNode.begin();
    ofs << nodes << std::endl;
    while (std::getline(ifs, reading_line_buffer)) {
      ofs << reading_line_buffer << " " << *CGtypeitr << std::endl;
      CGtypeitr++;
      if (std::stoi(reading_line_buffer) != 0) {
        std::getline(ifs, reading_line_buffer);
        ofs << reading_line_buffer << std::endl;
      }
    }
    ifs.close();
    ofs.close();
    return;
  }
};
class Graph {
  fs::path p;
  bool check_is_DAG(fs::path& p) {
    // To Do:余裕があったら中身がDAGかどうか確認する関数
    return true;
  }

  std::vector<std::string> GenerateCGs() {}

public:
  Graph(fs::path pin) : p(pin) {
    if (!check_is_DAG(p)) {
      std::cout << "error! File " << p << " is not DAG. abort" << std::endl;
      abort();
    }
  }
  bool ComposeCGsandGraphsandOutput(CGC::CGInfo& ci, fs::path output_path) {
    ci.OverwriteGraph(p, output_path);
    return true;
  }
  bool GenerateNewCGsAndOutputToFile(fs::path output_path) {
    return true;
  }
};
} // namespace CGC