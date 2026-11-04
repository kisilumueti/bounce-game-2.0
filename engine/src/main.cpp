#include "bounce/engine.hpp"
#include <iomanip>
#include <iostream>
int main() { bounce::Engine game; constexpr double frame = 1.0 / 60.0; for (int i=0;i<600;++i) { if(i==60||i==180||i==300||i==420) game.jump(); game.step(frame); } const auto& s=game.state(); std::cout<<"NEON BOUNCE 2.0 / C++ ENGINE\nElapsed: "<<std::fixed<<std::setprecision(2)<<s.elapsed<<"s\nScore: "<<static_cast<long long>(s.score)<<"\nJumps: "<<s.jumps<<"\nPlayer Y: "<<s.y<<"\n"; return 0; }