// scanner.hpp
#pragma once
#include <windows.h>
#include <cstdint>
#include <vector>
#include <utility>

namespace scanner
{
    std::uintptr_t find(std::uintptr_t start, std::uintptr_t end, const char* pattern);
    std::uintptr_t find_in_text(const char* pattern);
    std::pair<std::uintptr_t, std::uintptr_t> text_range();
    std::uintptr_t resolve_rip(std::uintptr_t instr_addr, std::size_t disp_offset, std::size_t instr_size);
}