#include <iostream>
#include <string>
#include <filesystem>
#include "../include/FileUtil.hpp"
#include "../include/Params.hpp"
#include "../include/GraphUtil.hpp"
CGC::FileUtil FU;
namespace fs    = std::filesystem;
const bool test = false;
void RunForEachParams(fs::path p, fs::path outroot = ".") {
  std::string OutputDirName;
  for (auto& vcg : CGC::VAR_CG_loader) {
    CGC::VAR_CG   = vcg;
    OutputDirName = "VAR_CG_" + std::to_string(vcg);
    auto vp       = FU.CreateDirectory(outroot, OutputDirName);
    for (auto& ecr : CGC::ECR_loader) {
      CGC::ECR      = ecr;
      OutputDirName = "ECR_" + std::to_string(ecr);
      auto ecrp     = FU.CreateDirectory(vp, OutputDirName);
      for (auto& cce : CGC::CCE_loader) {
        CGC::CCE      = cce;
        OutputDirName = "cce_" + std::to_string(cce);
        auto ccep     = FU.CreateDirectory(ecrp, OutputDirName);
        auto dirlist  = FU.GenerateImitateDir(p, ccep);
        auto filelist = FU.GetImitateFiles(p, ccep);
        for (auto& x : filelist) {
          CGC::Graph G(x.first);
          CGC::CGInfo cgi;
          G.ComposeCGsandGraphsandOutput(cgi, x.second);
        }
        auto conflist = FU.GetImitateFiles(p, ccep, ".conf");
        for (auto& i : conflist) {
          fs::copy(i.first, i.second);
          CGC::add_conf(i.second);
        }
      }
    }
  }
}
int main(int argc, char* argv[]) {
  fs::path MdgDir;
  fs::path OutDir = ".";
  if (test) {
    MdgDir = "C:/Users/thebe/working/Massive-Dags-Generator/build/GraphBase";
  }
  else {
    if (argc < 2 || argc >=4 ) {
      std::cout << "You need 1 or 2 path in commandline input to execute this "
                   "application!"
                << std::endl;
      abort();
    }
    MdgDir = argv[1];
    if(argc==3){
      OutDir = argv[2];
    }
  }
  auto rootpath = FU.CreateDirectory(OutDir, "CGCout");
  RunForEachParams(MdgDir, rootpath);
  return 0;
}