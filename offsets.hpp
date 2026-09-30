// offsets.hpp
#pragma once
#include <cstdint>
#include <cstddef>

#ifdef _WIN32
#  include <windows.h>
#else
   using UINT     = unsigned int;
   using UINT_PTR = std::uintptr_t;
#endif

namespace offsets
{
    namespace player
    {
        constexpr std::uintptr_t pos_x = 0x6008;
        constexpr std::uintptr_t pos_y = 0x6004;
        constexpr std::uintptr_t angle = 0xB060;
        constexpr std::uintptr_t secret_index = 0xB0EC;
    }

    namespace integrity
    {
        constexpr std::uintptr_t value = 0x6000;
        constexpr int max = 100;
        constexpr int hit_damage = 5;
    }

    namespace flags
    {
        constexpr std::uintptr_t simulation_started = 0xB0E8;
        constexpr std::uintptr_t secret_unlocked = 0xB0E9;
        constexpr std::uintptr_t game_over = 0xB0F0;
    }

    namespace timing
    {
        constexpr std::uintptr_t sim_time = 0xB0F4;
        constexpr float tick_delta = 0.05f;
    }

    namespace vectors
    {
        namespace objects
        {
            constexpr std::uintptr_t begin    = 0xB0D0;
            constexpr std::uintptr_t end      = 0xB0D8;
            constexpr std::uintptr_t capacity = 0xB0E0;
            constexpr std::uintptr_t stride   = 72;
        }
        namespace projectiles
        {
            constexpr std::uintptr_t begin    = 0xB0C8;
            constexpr std::uintptr_t end      = 0xB0D0;
            constexpr std::uintptr_t capacity = 0xB0C0;
            constexpr std::uintptr_t stride   = 8;
        }
        namespace enemies
        {
            constexpr std::uintptr_t begin    = 0xB098;
            constexpr std::uintptr_t end      = 0xB0A0;
            constexpr std::uintptr_t capacity = 0xB0A0;
            constexpr std::uintptr_t stride   = 8;
        }
        namespace fx
        {
            constexpr std::uintptr_t begin    = 0xB070;
            constexpr std::uintptr_t end      = 0xB078;
            constexpr std::uintptr_t capacity = 0xB080;
            constexpr std::uintptr_t stride   = 16;
        }
    }

    namespace object_layout
    {
        constexpr std::uintptr_t x = 0x00;
        constexpr std::uintptr_t y = 0x04;
        constexpr std::uintptr_t vx = 0x08;
        constexpr std::uintptr_t vy = 0x0C;
        constexpr std::uintptr_t type = 0x10;
        constexpr std::uintptr_t name_ptr = 0x18;
        constexpr std::uintptr_t name_len = 0x20;
        constexpr std::uintptr_t name_buf = 0x28;
        constexpr std::uintptr_t label = 0x38;
        constexpr std::uintptr_t is_special = 0x40;
    }

    namespace fx_layout
    {
        constexpr std::uintptr_t x = 0x00;
        constexpr std::uintptr_t y = 0x04;
        constexpr std::uintptr_t vx = 0x08;
        constexpr std::uintptr_t vy = 0x0C;
    }

    namespace enemy_layout
    {
        constexpr std::uintptr_t angle = 0x00;
        constexpr std::uintptr_t radius = 0x04;
    }

    namespace secret
    {
        constexpr wchar_t sequence[] = L"NIER";
        constexpr std::size_t length = 4;
    }

    namespace ui
    {
        constexpr wchar_t window_class[] = L"NierSecretChallenge";
        constexpr wchar_t window_title[] = L"Automata Simulation v3.0";
        constexpr std::uintptr_t brush = 0xB040;
        constexpr std::uintptr_t font_sm = 0xB038;
        constexpr std::uintptr_t font_lg = 0xB030;
        constexpr std::uintptr_t label_override = 0xB058;
        constexpr std::uintptr_t label_matrix = 0xB050;
        constexpr std::uintptr_t button_engage = 0xB048;
        constexpr UINT_PTR timer_id = 1;
    }

    namespace wm
    {
        constexpr UINT command = 0x0111;
        constexpr UINT timer = 0x0113;
        constexpr UINT paint = 0x000F;
        constexpr UINT char_input = 0x0102;
        constexpr UINT destroy = 0x0002;
        constexpr UINT ctlcolorstatic = 0x0138;
    }
}