#pragma once

#include "tpgz/controller.h"
#include "tpgz/font.h"
#include "menus/menu.h"
#include "tpgz/cheats.h"
#include "tpgz/save_injector.h"

extern bool loading_initiated;
extern bool trigger_menu_anim;

enum Caller {
        Gorge,
        SaveInjection,
        AreaReload,
        SaveTempFlags
};

namespace Utilities {
    void move_cursor(int& cursor, int LINES);
    void menu_anim(Font& font, int idx);
    void render_lines(Font& font, Line lines[], int cursor, int LINES);
    void render_lines_with_items(Font& font, Line lines[], int cursor, int LINES, Cheats::Cheat Items[]);
    void trigger_load(Caller);
    void set_during_load(Caller);
}  // namespace Utilities