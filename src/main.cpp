#include <iostream>
#include <string>
#include <filesystem>
#include "../include/FileUtil.hpp"
#include "../include/Params.hpp"
#include "../include/GraphUtil.hpp"

namespace fs    = std::filesystem;
const bool test = true;
int main(int argc, char* argv[]) {
  fs::path MdgDir;
  if (test) {
    MdgDir = "C:/Users/thebe/working/Massive-Dags-Generator/build/MdgOut";
  }
  else {
    if (argc < 2) {
      std::cout << "You need only 1 path in commandline input to execute this "
                   "application!"
                << std::endl;
      abort();
    }
    MdgDir = argv[1];
  }
  CGC::FileUtil FU;
  auto OutputDir =
      FU.CreateDirectory(CGC::Output_root, CGC::Output_dir_name.string<char>());
  auto dirlist  = FU.GenerateImitateDir(MdgDir, OutputDir);
  auto filelist = FU.GetImitateFiles(MdgDir, OutputDir);
  for (auto& x : filelist) {
    CGC::Graph G(x.first);
    CGC::CGInfo cgi;
    G.ComposeCGsandGraphsandOutput(cgi, x.second);
  }

  return 0;
}