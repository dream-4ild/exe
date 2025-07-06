#pragma once

#include <twist/ed/std/atomic.hpp>
#include <twist/ed/wait/futex.hpp>
#include <twist/ed/wait/spin.hpp>

#include <cstdint>


class Mutex {
public:
    void Lock() {
        if (state_.exchange(1) > 0) {
            twist::ed::SpinWait wait;
            while (state_.exchange(2) > 0) {
                if (wait.ConsiderParking()) {
                    twist::ed::futex::Wait(state_, 2);
                } else {
                    wait();
                }
            }
        }
    }

    void Unlock() {
        const auto wake_key = twist::ed::futex::PrepareWake(state_);

        if (state_.exchange(0) == 2) {
            twist::ed::futex::WakeOne(wake_key);
        }
    }


    bool TryLock() {
        uint32_t old = 0;
        return state_.compare_exchange_weak(old, 1);
    }

    // BasicLockable
    // https://en.cppreference.com/w/cpp/named_req/BasicLockable

    // NOLINTNEXTLINE
    void lock() {
        Lock();
    }

    // NOLINTNEXTLINE
    void unlock() {
        Unlock();
    }

private:
    twist::ed::std::atomic<uint32_t> state_{0};
};
