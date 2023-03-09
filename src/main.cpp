#include <iostream>
#include <string>
#include <filesystem>
#include "../include/FileUtil.hpp"
#include "../include/Params.hpp"
#include "../include/GraphUtil.hpp"
CGC::FileUtil FU;
namespace fs    = std::filesystem;
const bool test = false;
const int total_roop =
    CGC::VAR_CG_loader.size() * CGC::ECR_loader.size() * CGC::CCE_loader.size();
int progress = 0;
void RunForEachParams(fs::path p, fs::path outroot = ".") {
  std::string OutputDirName;
  for (auto& vcg : CGC::VAR_CG_loader) {
    CGC::VAR_CG   = vcg;
    OutputDirName = "VAR_CG_" + std::to_string(vcg);
    auto vp       = FU.CreateDirectory(outroot, OutputDirName);
    for (auto& ecr : CGC::ECR_loader) {
      CGC::ECR      = ecr;
      OutputDirName = "CRR_" + std::to_string(ecr);
      auto ecrp     = FU.CreateDirectory(vp, OutputDirName);
      for (auto& cce : CGC::CCE_loader) {
        CGC::CCE      = cce;
        OutputDirName = "CCR_" + std::to_string(cce);
        auto ccep     = FU.CreateDirectory(ecrp, OutputDirName);
        auto dirlist  = FU.GenerateImitateDir(p, ccep);
        auto filelist = FU.GetImitateFiles(p, ccep);
        for (auto& x : filelist) {
          CGC::VAR_KERNEL = 0;
          CGC::Graph G(x.first);
          CGC::CGInfo cgi;
          G.ComposeCGsandGraphsandOutput(cgi, x.second);
        }
        auto conflist = FU.GetImitateFiles(p, ccep, ".conf");
        for (auto& i : conflist) {
          fs::copy(i.first, i.second);
          CGC::add_conf(i.second);
        }
        progress++;
        std::cout << progress << " / " << total_roop << std::endl;
      }
    }
  }
}
void RunForConstantParams(fs::path p, fs::path outroot = ".") {
  std::string OutputDirName;
  for (auto& ecr : CGC::ECR_loader) {
    CGC::ECR      = ecr;
    OutputDirName = "CRR_" + std::to_string(ecr);
    auto ecrp     = FU.CreateDirectory(outroot, OutputDirName);
    for (auto& cce : CGC::CCE_loader) {
      CGC::CCE      = cce;
      OutputDirName = "CCR_" + std::to_string(cce);
      auto ccep     = FU.CreateDirectory(ecrp, OutputDirName);
      auto dirlist  = FU.GenerateImitateDir(p, ccep);
      auto filelist = FU.GetImitateFiles(p, ccep);
      for (auto& x : filelist) {
        CGC::VAR_KERNEL = 0;
        std::ifstream ifs(x.first);
        std::string Inp;
        std::getline(ifs, Inp);
        CGC::VAR_CG = std::stoi(Inp);
        ifs.close();
        CGC::Graph G(x.first);
        CGC::CGInfo cgi;
        G.ComposeConstantGraphsandOutput(cgi, x.second);
      }

      auto conflist = FU.GetImitateFiles(p, ccep, ".conf");
      for (auto& i : conflist) {
        fs::copy(i.first, i.second);
        CGC::add_conf(i.second);
      }

      progress++;
      std::cout << progress << " / " << total_roop << std::endl;
    }
  }
}

void Cholesky_ParamCompose(fs::path p, fs::path outroot = ".") {
  std::string OutputDirName = "hello";
  fs::path Time_basep =
      "/home/gp.sc.cc.tohoku.ac.jp/skaneko/working/DagSimuroot/"
      "CommandGroupComposer/src/Cholesky_timebase.txt";
  for (auto& ecr : CGC::ECR_loader) {
    CGC::ECR      = ecr;
    OutputDirName = "CRR_" + std::to_string(ecr);
    auto happydir = FU.CreateDirectory(outroot, OutputDirName);
    auto dirlist  = FU.GenerateImitateDir(p, happydir);
    auto filelist = FU.GetImitateFiles(p, happydir);

    // std::cout << filelist.size() << std::endl;
    for (auto& x : filelist) {
      // std::cout << x.first << " " << x.second << std::endl;
      CGC::VAR_KERNEL = 0;
      std::ifstream ifs(x.first);
      std::ifstream ifsc(Time_basep);
      std::ofstream ofs;
      std::string Inp;
      ofs.open(x.second);
      std::getline(ifsc, Inp);
      ofs << Inp << std::endl;
      int color = 4;
      int task  = 9;
      for (int i = 0; i < task; i++) {
        std::getline(ifsc, Inp);
        int get = std::stoi(Inp);
        ofs << int(get * ecr) << std::endl;
      }
      for (int i = 0; i < color; i++) {
        std::string a, b;
        ifsc >> a >> b;
        int get = std::stoi(b);
        ofs << a << " " << int(get * ecr) << std::endl;
        std::getline(ifsc, Inp);
        std::getline(ifsc, Inp);
        ofs << Inp << std::endl;
      }
      while (std::getline(ifs, Inp)) {
        ofs << Inp << std::endl;
      }
      ifs.close();
      ifsc.close();
      ofs.close();
    }
    auto conflist = FU.GetImitateFiles(p, happydir, ".conf");
    for (auto& i : conflist) {
      fs::copy(i.first, i.second);
      CGC::add_conf(i.second);
    }
  }
}
int mode = 2;
int main(int argc, char* argv[]) {
  fs::path MdgDir;
  fs::path OutDir = ".";
  if (test) {
    MdgDir = "C:/Users/thebe/working/Massive-Dags-Generator/build/GraphBase";
  }
  else {
    if (argc < 2 || argc >= 4) {
      std::cout << "You need 1 or 2 path in commandline input to execute this "
                   "application!"
                << std::endl;
      abort();
    }
    MdgDir = argv[1];
    if (argc == 3) {
      OutDir = argv[2];
    }
  }
  auto rootpath = FU.CreateDirectory(OutDir, "CGCout");
  if (mode == 0) {
    RunForEachParams(MdgDir, rootpath);
  }
  else if (mode == 1) {
    RunForConstantParams(MdgDir, rootpath);
  }
  else {
    Cholesky_ParamCompose(MdgDir, rootpath);
  }

  return 0;
}