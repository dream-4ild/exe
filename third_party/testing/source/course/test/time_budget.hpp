#pragma once

#include <wheels/core/stop_watch.hpp>

#include <wheels/test/current.hpp>

#include <algorithm>

#include <chrono>

namespace course::test {

// Not thread-safe!

class TimeBudget {
  using Clock = std::chrono::steady_clock;
  using Units = Clock::duration;

  static constexpr Units kBatchThreshold = std::chrono::milliseconds(10);

  static constexpr Units kDefaultSafeMargin = std::chrono::milliseconds(250);

 public:
  // Constructors

  // Default: inherit current test time limit
  TimeBudget()
      : TimeBudget(GetCurrentTestTimeLimit(), kDefaultSafeMargin) {
  }

  // Explicit test budget (=> default safe margin)
  explicit TimeBudget(Units budget)
      : TimeBudget(budget, kDefaultSafeMargin) {
  }

  // Static constructors

  static TimeBudget Set(Units budget) {
    return TimeBudget(budget, kDefaultSafeMargin);
  }

  static TimeBudget TestTimeLimitWithMargin(Units safe_margin) {
    return TimeBudget(GetCurrentTestTimeLimit(), safe_margin);
  }

  bool KeepRunning() {
    ++count_;
    if (count_ == batch_) {
      Adapt();
      return TimeLeft() > safe_margin_;
    } else {
      return true;
    }
  }

  operator bool() {
    return KeepRunning();
  }

 private:
  TimeBudget(Units budget, Units safe_margin)
      : budget_(budget), safe_margin_(safe_margin) {
    start_ = Clock::now();
  }

  static Units GetCurrentTestTimeLimit() {
    return ::wheels::test::TestTimeLeft();
  }

  void Adapt() {
    auto elapsed = batch_timer_.Elapsed();

    if (elapsed * 2 < kBatchThreshold) {
      batch_ *= 2;
    } else {
      // Restart batch
      batch_timer_.Restart();
      count_ = 0;

      if (elapsed > kBatchThreshold * 2) {
        batch_ = std::max(batch_ / 2, (size_t)1);
      }
    }
  }

  Units TimeLeft() const {
    auto now = Clock::now();
    auto expiration = start_ + budget_;
    if (now > expiration) {
      return Units(0);
    } else {
      // expiration >= now
      return expiration - now;
    }
  }


 private:
  const Units budget_;
  const Units safe_margin_;
  Clock::time_point start_;

  ::wheels::StopWatch<> batch_timer_;
  size_t count_ = 0;
  size_t batch_ = 1;
};

}  // namespace course::test
