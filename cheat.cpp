// cheat.cpp
#include "cheat.hpp"
#include "resolver.hpp"
#include <windows.h>

namespace cheat
{
    std::atomic<bool> god_mode{ true };
    std::atomic<bool> unlock_secret{ true };
    std::atomic<bool> freeze_time{ false };
    std::atomic<bool> no_game_over{ true };
    std::atomic<bool> teleport{ false };
    std::atomic<bool> running{ true };

    static resolver::GameAddrs g_addrs{};

    static void update_title(HWND hwnd)
    {
        wchar_t title[128] = L"Automata";
        if (god_mode)      wcscat_s(title, L" [GOD]");
        if (unlock_secret) wcscat_s(title, L" [NIER]");
        if (freeze_time)   wcscat_s(title, L" [FREEZE]");
        if (no_game_over)  wcscat_s(title, L" [NOGO]");
        if (teleport)      wcscat_s(title, L" [TP]");
        SetWindowTextW(hwnd, title);
    }

    static void main_loop()
    {
        HWND hwnd = nullptr;
        while (running && !hwnd)
        {
            hwnd = FindWindowW(L"NierSecretChallenge", nullptr);
            Sleep(100);
        }
        if (!running) return;

        while (running && !resolver::resolve(g_addrs))
            Sleep(500);

        if (!running) return;

        DWORD last_title = 0;

        while (running)
        {
            if (god_mode && g_addrs.integrity)
                *reinterpret_cast<int*>(g_addrs.integrity) = 100;

            if (unlock_secret && g_addrs.secret)
                *reinterpret_cast<unsigned char*>(g_addrs.secret) = 1;

            if (freeze_time && g_addrs.sim_time)
                *reinterpret_cast<float*>(g_addrs.sim_time) = 0.0f;

            if (no_game_over && g_addrs.game_over)
                *reinterpret_cast<unsigned char*>(g_addrs.game_over) = 0;

            if (teleport && g_addrs.pos_x && g_addrs.pos_y)
            {
                *reinterpret_cast<float*>(g_addrs.pos_x) = teleport_x;
                *reinterpret_cast<float*>(g_addrs.pos_y) = teleport_y;
            }

            DWORD now = GetTickCount();
            if (now - last_title > 500)
            {
                update_title(hwnd);
                last_title = now;
            }

            Sleep(10);
        }
    }

    static void hotkey_loop()
    {
        auto pressed = [](int vk) -> bool {
            static bool prev[256] = { false };
            bool now = (GetAsyncKeyState(vk) & 0x8000) != 0;
            bool res = now && !prev[vk];
            prev[vk] = now;
            return res;
        };

        while (running)
        {
            if (pressed(VK_F1)) god_mode      = !god_mode;
            if (pressed(VK_F2)) unlock_secret = !unlock_secret;
            if (pressed(VK_F3)) freeze_time   = !freeze_time;
            if (pressed(VK_F4)) no_game_over  = !no_game_over;
            if (pressed(VK_F5)) teleport      = !teleport;

            if (pressed(VK_END))
            {
                running = false;
                HWND hwnd = FindWindowW(L"NierSecretChallenge", nullptr);
                if (hwnd) PostMessageW(hwnd, WM_CLOSE, 0, 0);
                break;
            }

            Sleep(30);
        }
    }

    DWORD WINAPI main_thread(LPVOID)
    {
        main_loop();
        return 0;
    }

    DWORD WINAPI hotkey_thread(LPVOID)
    {
        hotkey_loop();
        return 0;
    }
}