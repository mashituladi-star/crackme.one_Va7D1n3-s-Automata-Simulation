// scanner.cpp
#include "scanner.hpp"
#include <cstring>

namespace scanner
{
    static bool parse(const char* pattern, std::vector<std::uint8_t>& bytes, std::vector<bool>& mask)
    {
        bytes.clear();
        mask.clear();
        const char* p = pattern;
        while (*p)
        {
            while (*p == ' ') ++p;
            if (!*p) break;
            if (*p == '?')
            {
                bytes.push_back(0);
                mask.push_back(false);
                ++p;
                if (*p == '?') ++p;
            }
            else
            {
                auto hex = [](char c) -> int {
                    if (c >= '0' && c <= '9') return c - '0';
                    if (c >= 'A' && c <= 'F') return c - 'A' + 10;
                    if (c >= 'a' && c <= 'f') return c - 'a' + 10;
                    return -1;
                };
                int h = hex(*p++);
                int l = hex(*p++);
                if (h < 0 || l < 0) return false;
                bytes.push_back(static_cast<std::uint8_t>((h << 4) | l));
                mask.push_back(true);
            }
        }
        return !bytes.empty();
    }

    std::uintptr_t find(std::uintptr_t start, std::uintptr_t end, const char* pattern)
    {
        std::vector<std::uint8_t> bytes;
        std::vector<bool> mask;
        if (!parse(pattern, bytes, mask)) return 0;
        const std::size_t n = bytes.size();
        if (end < start + n) return 0;
        for (std::uintptr_t addr = start; addr <= end - n; ++addr)
        {
            bool ok = true;
            for (std::size_t i = 0; i < n; ++i)
            {
                if (mask[i] && *reinterpret_cast<std::uint8_t*>(addr + i) != bytes[i])
                {
                    ok = false;
                    break;
                }
            }
            if (ok) return addr;
        }
        return 0;
    }

    std::pair<std::uintptr_t, std::uintptr_t> text_range()
    {
        auto base = reinterpret_cast<std::uintptr_t>(GetModuleHandleW(nullptr));
        auto dos = reinterpret_cast<IMAGE_DOS_HEADER*>(base);
        if (dos->e_magic != IMAGE_DOS_SIGNATURE) return { 0, 0 };
        auto nt = reinterpret_cast<IMAGE_NT_HEADERS*>(base + dos->e_lfanew);
        if (nt->Signature != IMAGE_NT_SIGNATURE) return { 0, 0 };
        auto sec = IMAGE_FIRST_SECTION(nt);
        for (WORD i = 0; i < nt->FileHeader.NumberOfSections; ++i, ++sec)
        {
            if (std::memcmp(sec->Name, ".text", 5) == 0)
                return { base + sec->VirtualAddress,
                         base + sec->VirtualAddress + sec->Misc.VirtualSize };
        }
        return { 0, 0 };
    }

    std::uintptr_t find_in_text(const char* pattern)
    {
        auto [s, e] = text_range();
        if (!s || !e) return 0;
        return find(s, e, pattern);
    }

    std::uintptr_t resolve_rip(std::uintptr_t instr_addr, std::size_t disp_offset, std::size_t instr_size)
    {
        auto disp = *reinterpret_cast<std::int32_t*>(instr_addr + disp_offset);
        return instr_addr + instr_size + disp;
    }
}