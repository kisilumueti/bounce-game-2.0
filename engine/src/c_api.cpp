#include "bounce/engine.hpp"
#include <cstdint>
#ifdef __EMSCRIPTEN__
#include <emscripten/emscripten.h>
#define BOUNCE_EXPORT EMSCRIPTEN_KEEPALIVE
#else
#define BOUNCE_EXPORT
#endif
namespace { bounce::Engine engine; }
extern "C" {
BOUNCE_EXPORT void bounce_reset() { engine.reset(); }
BOUNCE_EXPORT int bounce_jump() { return engine.jump() ? 1 : 0; }
BOUNCE_EXPORT void bounce_step(double dt) { engine.step(dt); }
BOUNCE_EXPORT double bounce_x() { return engine.state().x; }
BOUNCE_EXPORT double bounce_y() { return engine.state().y; }
BOUNCE_EXPORT double bounce_velocity_y() { return engine.state().velocity_y; }
BOUNCE_EXPORT double bounce_score() { return engine.state().score; }
BOUNCE_EXPORT int bounce_grounded() { return engine.state().grounded ? 1 : 0; }
BOUNCE_EXPORT std::uint32_t bounce_jumps() { return engine.state().jumps; }
}