#include "font.h"
#include "menu.h"
#include "controller.h"
#include "utils.h"
#include "libtpw_c/include/flag.h"

#define LINES 12

static Cursor cursor = {0, 0};
bool init_once = false;
bool flags_menu_visible;

bool boss_flag;
bool rupee_flag;
bool midna_charge;
bool transform_warp;
bool midna_on_z;
bool epona_stolen;
bool epona_tamed;
bool map_warping;
bool midna_healthy;
bool midna_on_back;
bool wolf_sense;
bool hide_weapon_as_wolf;

Line lines[LINES] = {
    {"boss flag", BOSS_FLAG_INDEX, "Set the boss flag value. Press A to lock the value", true, &boss_flag},
    {"rupee cutscenes", RUPEE_CS_FLAG_INDEX, "Toggle flag for rupee cutscenes being enabled", true, &rupee_flag},
    {"epona stolen", EPONA_STOLEN_INDEX, "Toggle flag for Epona being stolen", true, &epona_stolen},
    {"epona tamed", EPONA_TAMED_INDEX, "Toggle flag for Epona being tamed", true, &epona_tamed},
    {"map warping", MAP_WARPING_INDEX, "Toggle flag for having map warping", true, &map_warping},
    {"midna charge", MIDNA_CHARGE_INDEX, "Toggle flag for Midna charge", true, &midna_charge},
    {"midna healthy", MIDNA_HEALTHY, "Toggle flag for Midna being healthy/sick", true, &midna_healthy},
    {"midna on back", MIDNA_ON_BACK, "Toggle flag for Midna appearing on Wolf Link's back", true, &midna_on_back},
    {"midna on z", MIDNA_Z_INDEX, "Toggle flag for being able to use Midna", true, &midna_on_z},
    {"transform/warp", TRANSFORM_WARP_INDEX, "Toggle flag for transforming/warping", true, &transform_warp},
    {"wolf sense", WOLF_SENSE_INDEX, "Toggle flag for having wolf sense", true, &wolf_sense},
    {"hide weapon as wolf", HIDE_WEAPON_AS_WOLF, "Toggle flag for hiding weapons as wolf", true, &hide_weapon_as_wolf}};

void FlagsMenu::render(Font& font) {
    // update flags
    boss_flag = (TP::get_boss_flags() > 0x00);
    rupee_flag = (tp_gameInfo.inventory.rupee_cs_flags & (1 << 0));
    midna_charge = (tp_gameInfo.epona_stolen_and_midna_charge_flag & (1 << 0));
    transform_warp = (tp_gameInfo.transform_flag & (1 << 2));
    midna_on_z = (tp_gameInfo.midna_on_up_and_hide_weapon_as_wolf & (1 << 4));
    epona_stolen = (tp_gameInfo.epona_stolen_and_midna_charge_flag & (1 << 7));
    epona_tamed = (tp_gameInfo.epona_tamed_and_map_warp_flag & (1 << 0));
    map_warping = (tp_gameInfo.epona_tamed_and_map_warp_flag & (1 << 2));
    midna_healthy = (tp_gameInfo.midna_state_flag & (1 << 3));
    midna_on_back = (tp_gameInfo.midna_on_back_flag & (1 << 3));
    wolf_sense = (tp_gameInfo.have_sense_flag & (1 << 3));
    hide_weapon_as_wolf = (tp_gameInfo.midna_on_up_and_hide_weapon_as_wolf & (1 << 3));

    if (button_is_pressed(Controller::B)) {
        init_once = false;
        flags_menu_visible = false;
        mm_visible = true;
        return;
    }

    if (!init_once) {
        current_input = 0;
        init_once = true;
    }

    if (current_input == 256 && a_held == false) {
        switch (cursor.x) {
            case BOSS_FLAG_INDEX: {
                if (boss_flag) {
                    tp_bossFlags = 0x00;
                } else {
                    tp_bossFlags = 0xFF;
                }
                break;
            }
            case RUPEE_CS_FLAG_INDEX: {
                if (rupee_flag) {
                    tp_gameInfo.inventory.rupee_cs_flags = 0x00;
                } else {
                    tp_gameInfo.inventory.rupee_cs_flags = 0xFF;
		}
		break;
            }
            case EPONA_STOLEN_INDEX: {
                tp_gameInfo.epona_stolen_and_midna_charge_flag ^= 0x80;
                break;
            }
            case EPONA_TAMED_INDEX: {
                tp_gameInfo.epona_tamed_and_map_warp_flag ^= 0x01;
                break;
            }
            case MAP_WARPING_INDEX: {
                tp_gameInfo.epona_tamed_and_map_warp_flag ^= 0x04;
                break;
            }
            case MIDNA_HEALTHY: {
                tp_gameInfo.midna_state_flag ^= 0x08;
                break;
            }
            case MIDNA_ON_BACK: {
                tp_gameInfo.midna_on_back_flag ^= 0x08;
                break;
            }
            case MIDNA_Z_INDEX: {
                tp_gameInfo.midna_on_up_and_hide_weapon_as_wolf ^= 0x10;
                break;
            }
            case TRANSFORM_WARP_INDEX: {
                tp_gameInfo.transform_flag ^= 0x04;
                break;
            }
            case WOLF_SENSE_INDEX: {
                tp_gameInfo.have_sense_flag ^= 0x08;
                break;
            }

            case MIDNA_CHARGE_INDEX: {
                tp_gameInfo.epona_stolen_and_midna_charge_flag ^= 0x01;
                break;
            }

            case HIDE_WEAPON_AS_WOLF: {
                tp_gameInfo.midna_on_up_and_hide_weapon_as_wolf ^= 0x08;
                break;
            }
        }
    }

    Utilities::move_cursor(cursor, LINES);
    Utilities::render_lines(font, lines, cursor.x, LINES, 150.0f);
}
