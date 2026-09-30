// cheat.hpp
#pragma once
#include <windows.h>
#include <atomic>

namespace cheat
{
    extern std::atomic<bool> god_mode;
    extern std::atomic<bool> unlock_secret;
    extern std::atomic<bool> freeze_time;
    extern std::atomic<bool> no_game_over;
    extern std::atomic<bool> teleport;
    extern std::atomic<bool> running;

    constexpr float teleport_x = 225.0f;
    constexpr float teleport_y = 370.0f;

    DWORD WINAPI main_thread(LPVOID);
    DWORD WINAPI hotkey_thread(LPVOID);
}