#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <filesystem>
namespace fs = std::filesystem;
/*
const std::vector<std::string> tabs = {
    "#4E79A7", "#A0CBE8", "#F28E2B", "#FFBE7D", "#59A14F", "#8CD17D", "#B6992D",
    "#F1CE63", "#499894", "#86BCB6", "#E15759", "#FF9D9A", "#79706E", "#BAB0AC",
    "#D37295", "#FABFD2", "#B07AA1", "#D4A6C8", "#9D7660", "#D7B5A6"};
    */
const std::vector<std::string> tabs = {
    "#1f77b4", "#ff7f0e", "#2ca02c", "#d62728", "#9467bd", "#8c564b",
    "#e377c2", "#7f7f7f", "#bcbd22", "#17becf", "#4E79A7"};

int main(int argc, char* argv[]) {
  fs::path ComposedDag;
  if (argc != 2) {
    std::cout << "You need only 1 path in commandline input to execute this "
                 "application!"
              << std::endl;
    abort();
  }
  ComposedDag = argv[1];
  std::ifstream ifs;
  ifs.open(ComposedDag);
  int CGtype, Tasktype;
  ifs >> CGtype >> Tasktype;
  int garv;
  for (int i = 0; i < Tasktype; i++) {
    ifs >> garv;
  }
  for (int i = 0; i < CGtype; i++) {
    int w;
    ifs >> w >> garv;
    for (int j = 0; j < w; j++) {
      ifs >> garv;
    }
  }
  int nodes;
  ifs >> nodes;
  std::vector<std::string> outputs;
  for (int i = 0; i < nodes; i++) {
    int pred, type;
    ifs >> pred >> type;
    std::cout << pred << " " << type << std::endl;
    outputs.push_back(std::to_string(i) + " [label=" + std::to_string(i) +
                      ",style=filled,color=\"" + tabs[type % tabs.size()] +
                      "\"];");
    for (int j = 0; j < pred; j++) {
      int pre;
      ifs >> pre;
      outputs.push_back(std::to_string(pre) + " -> " + std::to_string(i) + ";");
    }
  }
  bool output_standardoutput = true;
  if (output_standardoutput) {
    std::cout << "digraph G{" << std::endl;
    for (auto& x : outputs) {
      std::cout << x << std::endl;
    }
    std::cout << "}" << std::endl;
  }
  ifs.close();
  return 0;
}