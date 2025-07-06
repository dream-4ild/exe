#include "sim.hpp"

#if defined(__TWIST_BUILD_ISOLATED_SIM__)

#include <twist/sim.hpp>

#include <wheels/core/panic.hpp>
#include <wheels/test/framework.hpp>

namespace course::test::twist {

namespace sim {

static auto MakeScheduler(std::string type) -> std::unique_ptr<::twist::sim::IScheduler> {
  if (type == "Fair") {
    return std::make_unique<::twist::sim::sched::FairScheduler>();
  } else if (type == "Random") {
    return std::make_unique<::twist::sim::sched::RandomScheduler>();
  } else if (type == "Coop") {
    return std::make_unique<::twist::sim::sched::CoopScheduler>();
  } else {
    WHEELS_PANIC("Unexpected scheduler type" << type);
  }
}

void RunSimulation(TestBody body, Params params) {
  if (!::twist::sim::DetCheck(body)) {
    FAIL_TEST("The test routine behaves nondeterministically (in a deterministic simulation)");
  }

  auto scheduler = MakeScheduler(params.scheduler);
  ::twist::sim::Simulator sim{scheduler.get()};


  auto result = sim.Run(body);

  ASSERT_TRUE_M(result.Ok(), result.std_err);

  // TODO: Error report, logging
}

}  // namespace sim

}  // namespace course::test::twist

#else

//

#endif