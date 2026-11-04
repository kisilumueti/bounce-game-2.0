#include "bounce/engine.hpp"
#include <algorithm>
#include <cmath>
namespace bounce {
Engine::Engine(Config config) : config_(config) { reset(); }
void Engine::reset() noexcept { state_ = Snapshot{}; state_.y = config_.floor_y - config_.radius; coyote_time_ = 0.0; }
bool Engine::jump() noexcept { if (state_.crashed || (!state_.grounded && coyote_time_ <= 0.0)) return false; state_.velocity_y = config_.jump_velocity; state_.grounded = false; coyote_time_ = 0.0; ++state_.jumps; return true; }
void Engine::step(double dt) noexcept { if (state_.crashed || !std::isfinite(dt) || dt <= 0.0) return; dt = std::min(dt, 0.05); state_.elapsed += dt; state_.score += dt * 19.48; state_.velocity_y += config_.gravity * dt; state_.y += state_.velocity_y * dt; if (state_.grounded) coyote_time_ = std::max(0.0, coyote_time_ - dt); if (state_.y + config_.radius >= config_.floor_y) { state_.y = config_.floor_y - config_.radius; state_.velocity_y = 0.0; state_.grounded = true; coyote_time_ = 0.09; } else { state_.grounded = false; coyote_time_ = std::max(0.0, coyote_time_ - dt); } }
const Snapshot& Engine::state() const noexcept { return state_; }
}