#pragma once

#include "body.hpp"

#include <twist/build.hpp>

#include <chrono>
#include <string>

namespace course::test::twist {

namespace sim {

constexpr bool IsBuildSupported() {
  return ::twist::build::kIsolatedSim;
}

struct Params {
  // Supported: Fair, Random, Coop
  std::string scheduler;
};

void RunSimulation(TestBody body, Params params);

}  // namespace sim

}  // namespace course::test::twist
