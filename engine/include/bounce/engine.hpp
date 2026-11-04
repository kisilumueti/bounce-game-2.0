#pragma once
#include <cstdint>
namespace bounce {
struct Config { double gravity{1850.0}; double jump_velocity{-690.0}; double floor_y{430.0}; double radius{20.0}; };
struct Snapshot { double x{155.0}; double y{410.0}; double velocity_y{0.0}; double score{0.0}; double elapsed{0.0}; bool grounded{true}; bool crashed{false}; std::uint32_t jumps{0}; };
class Engine final { public: explicit Engine(Config config = {}); void reset() noexcept; bool jump() noexcept; void step(double delta_seconds) noexcept; [[nodiscard]] const Snapshot& state() const noexcept; private: Config config_; Snapshot state_{}; double coyote_time_{0.0}; };
}