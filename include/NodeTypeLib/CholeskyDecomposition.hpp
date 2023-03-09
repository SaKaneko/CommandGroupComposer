#pragma once
#include <vector>

namespace NTL {
std::vector<int> NTLib(int nodes) {
  std::vector<ll> retv = {0, 1, 1, 1, 1, 2, 2, 2, 3, 0, 1, 1, 1, 2, 2, 2, 2, 3,
                          3, 0, 1, 1, 2, 2, 2, 3, 3, 3, 0, 1, 3, 3, 3, 3, 0};
  if (nodes != retv.size()) {
    abort();
  }
  return retv;
}
/*
std::vector<int> NTLib(int nodes) {
  std::vector<ll> retv = {0, 1, 1, 1, 1, 2, 2, 2, 3, 0, 1, 1, 1, 2, 2, 2, 2, 3,
                          3, 0, 1, 1, 2, 2, 2, 3, 3, 3, 0, 1, 3, 3, 3, 3, 0};
  if (nodes != retv.size()) {
    abort();
  }
  return retv;
}*/

} // namespace NTL