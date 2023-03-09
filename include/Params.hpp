#pragma once
#include <iostream>
#include <string>
#include <filesystem>
#include <vector>
namespace CGC {
const std::vector<int> VAR_CG_loader = {1, 2, 4, 8};
int VAR_CG                           = 4;
const int const_var_CG               = 4; // Cholesky Decomposition
// const int const_var_CG = 10; // GoogLeNet
int VAR_KERNEL                       = 0;
const int MAX_W                      = 4;
const std::vector<double> ECR_loader = {0.5, 1.0, 2.0, 4.0};
const std::vector<double> CCE_loader = {0.001, 0.5, 1, 1.5, 2};
double ECR                           = 1.0;
double CCE                           = 0.5;
const double REC_TIME_MS             = 2000;
// const double CCR              = CCR * ECR;

const std::filesystem::path Output_root     = ".";
const std::filesystem::path Output_dir_name = "GraphsWithCG";
} // namespace CGC
