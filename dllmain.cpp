// dllmain.cpp
#include <windows.h>
#include "cheat.hpp"

BOOL APIENTRY DllMain(HMODULE hModule, DWORD reason, LPVOID)
{
    switch (reason)
    {
    case DLL_PROCESS_ATTACH:
        DisableThreadLibraryCalls(hModule);
        CreateThread(nullptr, 0, cheat::main_thread,   nullptr, 0, nullptr);
        CreateThread(nullptr, 0, cheat::hotkey_thread, nullptr, 0, nullptr);
        MessageBoxW(nullptr,
            L"Automata Simulation v3.0 — Cheat loaded.\n\n"
            L"F1 — God Mode\n"
            L"F2 — Unlock NIER\n"
            L"F3 — Freeze Time\n"
            L"F4 — No Game Over\n"
            L"F5 — Teleport\n"
            L"END — Unload & close",
            L"Cheat", MB_OK | MB_ICONINFORMATION);
        break;

    case DLL_PROCESS_DETACH:
        cheat::running = false;
        Sleep(50);
        break;
    }
    return TRUE;
}