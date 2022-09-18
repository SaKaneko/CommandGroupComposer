#pragma once
#include <iostream>
#include <string>
#include <filesystem>
#include <vector>
namespace CGC {
const int TASK_TYPES          = 8;
const int CG_TYPES            = 4;
const int Max_TASKS_IN_CG     = 4;
const std::vector<double> ECR = {0.5, 1.0, 2.0};
const double CCE              = 0.50;
const double REC_TYME_MS      = 2000;
// const double CCR              = CCR * ECR;

const std::filesystem::path Output_root     = ".";
const std::filesystem::path Output_dir_name = "GraphsWithCG";
} // namespace CGC
