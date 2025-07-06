#pragma once

#include "twist/stress.hpp"
#include "twist/model.hpp"
#include "twist/randomize.hpp"
#include "twist/sim.hpp"

#include <chrono>

#include <wheels/test/framework.hpp>

////////////////////////////////////////////////////////////////////////////////

// Stress testing

#define TWIST_STRESS_TEST(name, time_budget) \
    void TwistStressTestBody##name();        \
    TEST(name, ::wheels::test::TestOptions().TimeLimit(time_budget)) {  \
      ::course::test::twist::stress::Test([] {                \
        TwistStressTestBody##name(); \
      }, {time_budget});                    \
    }                                     \
    void TwistStressTestBody##name()

////////////////////////////////////////////////////////////////////////////////

// Stateless model checking

#define TWIST_MODEL(name, params) \
    void TwistModelBody##name();        \
    TEST(name, ::wheels::test::TestOptions().TimeLimit(::course::test::twist::model::TimeBudget())) {                \
      static_assert(::course::test::twist::model::IsBuildSupported());                                   \
      ::course::test::twist::model::Check([] {                \
        TwistModelBody##name(); \
      }, params);                    \
    }                                     \
    void TwistModelBody##name()

////////////////////////////////////////////////////////////////////////////////

// Randomized testing

#define TWIST_RANDOMIZE(name, time_budget) \
  void TwistRandomCheckBody##name();        \
  TEST(name, ::wheels::test::TestOptions().TimeLimit(::course::test::twist::randomize::TestTimeLimit(time_budget))) { \
    static_assert(::course::test::twist::randomize::IsBuildSupported());              \
    ::course::test::twist::randomize::Check([] {                \
      TwistRandomCheckBody##name(); \
    }, {time_budget});                    \
  }                                     \
  void TwistRandomCheckBody##name()

////////////////////////////////////////////////////////////////////////////////

// Just deterministic simulation

#define TWIST_SIMULATION(name, scheduler) \
  void TwistSimulationBody##name();        \
  SIMPLE_TEST(name) { \
    static_assert(::course::test::twist::sim::IsBuildSupported());              \
    ::course::test::twist::sim::RunSimulation([] {                \
      TwistSimulationBody##name(); \
    }, {scheduler});                    \
  }                                     \
  void TwistSimulationBody##name()
