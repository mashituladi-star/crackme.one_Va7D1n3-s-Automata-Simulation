// resolver.hpp
#pragma once
#include <cstdint>

namespace resolver
{
    struct GameAddrs
    {
        std::uintptr_t fn_game_tick = 0;
        std::uintptr_t fn_wnd_proc  = 0;
        std::uintptr_t fn_button    = 0;

        std::uintptr_t integrity    = 0;
        std::uintptr_t sim_time     = 0;
        std::uintptr_t sim_started  = 0;
        std::uintptr_t secret       = 0;
        std::uintptr_t game_over    = 0;
        std::uintptr_t pos_x        = 0;
        std::uintptr_t pos_y        = 0;
    };

    bool resolve(GameAddrs& out);
}