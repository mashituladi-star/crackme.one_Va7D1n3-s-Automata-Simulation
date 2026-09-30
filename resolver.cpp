// resolver.cpp
#include "resolver.hpp"
#include "scanner.hpp"
#include "signatures.hpp"
#include "offsets.hpp"
#include <windows.h>

namespace resolver
{
    bool resolve(GameAddrs& out)
    {
        const auto base = reinterpret_cast<std::uintptr_t>(GetModuleHandleW(nullptr));
        const auto range = scanner::text_range();
        const auto text_end = range.second;
        if (!text_end) return false;

        out.fn_game_tick = scanner::find_in_text(sig::game_tick);
        out.fn_wnd_proc  = scanner::find_in_text(sig::wnd_proc);
        out.fn_button    = scanner::find_in_text(sig::button_handler);

        if (!out.fn_game_tick || !out.fn_wnd_proc || !out.fn_button)
            return false;

        const auto tick_end = out.fn_game_tick + 0x100;
        if (tick_end > text_end) return false;

        auto instr = scanner::find(out.fn_game_tick, tick_end, sig::sim_started_cmp);
        if (instr)
            out.sim_started = scanner::resolve_rip(instr, 2, 7);

        instr = scanner::find(out.fn_game_tick, tick_end, sig::sim_time_load);
        if (instr)
            out.sim_time = scanner::resolve_rip(instr, 5, 9);
        else
        {
            instr = scanner::find(out.fn_game_tick, tick_end, sig::sim_time_add);
            if (instr)
                out.sim_time = scanner::resolve_rip(instr, 5, 9);
        }

        const auto btn_end = out.fn_button + 0x80;
        instr = scanner::find(out.fn_button, btn_end, sig::secret_cmp);
        if (instr)
            out.secret = scanner::resolve_rip(instr, 2, 7);

        if (!out.integrity) out.integrity = base + offsets::integrity::value;
        if (!out.game_over) out.game_over = base + offsets::flags::game_over;
        if (!out.pos_x)     out.pos_x     = base + offsets::player::pos_x;
        if (!out.pos_y)     out.pos_y     = base + offsets::player::pos_y;

        return out.sim_time != 0 && out.secret != 0;
    }
}