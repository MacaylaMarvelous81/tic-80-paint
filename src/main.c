#include <malloc.h>
#include "tic80.h"

const int8_t COLOR_LAYOUT_BG = 3;
const int8_t COLOR_LAYOUT_PANEL = 10;
const int32_t CANVAS_WIDTH = 16;
const int32_t CANVAS_HEIGHT = 16;

int8_t selected_color;
bool during_left;

void update_input() {
    Mouse mouse_data;
    mouse(&mouse_data);

    FRAMEBUFFER->MOUSE_CURSOR = 128;

    if (!mouse_data.left) during_left = false;

    if (mouse_data.x >= 100 && mouse_data.x <= 228 && mouse_data.y >= 4 && mouse_data.y <= 132) {
        FRAMEBUFFER->MOUSE_CURSOR = 129;

        if (mouse_data.left) {
            int sprite_x = (mouse_data.x - 100) / 8;
            int sprite_y = (mouse_data.y - 4) / 8;

            mset(sprite_x, sprite_y, selected_color);
        }
    }

    if (mouse_data.x >= 29 && mouse_data.x <= 77 && mouse_data.y >= 16 && mouse_data.y <= 28) {
        FRAMEBUFFER->MOUSE_CURSOR = 129;

        if (mouse_data.left) {
            int low = (mouse_data.x - 29) / 6;
            bool is_top_row = mouse_data.y - 16 < 6;

            selected_color = low + (is_top_row ? 0 : 8);
        }
    }

    if (mouse_data.x >= 15 && mouse_data.x <= 90 && mouse_data.y >= 120 && mouse_data.y <= 128) {
        FRAMEBUFFER->MOUSE_CURSOR = 129;

        if (mouse_data.left && !during_left) {
            sfx(0, -1, -1, -1, 0, 15, 15, 0);
            sync(4, 0, true);
        }
    }

    if (mouse_data.left) during_left = true;
}

void draw_layout() {
    cls(COLOR_LAYOUT_BG);
    rect(10, 4, 85, 128, COLOR_LAYOUT_PANEL);

    int32_t color_header_width = print("COLOR", 29, 10, 15, false, 1, false);
    rect(color_header_width + 32, 11, 4, 4, selected_color);
    for (int32_t i = 0; i < 16; i++)
    {
        rect(i % 8 * 6 + 29, 16 + (i < 8 ? 0 : 6), 6, 6, i);
    }

    rect(15, 120, 75, 8, 8);
    print("SAVE TO CART", 20, 121, 0, false, 1, false);
}

void draw_canvas() {
    // 100, 4, 128, 128
    for (int32_t x = 0; x < CANVAS_WIDTH; x++) {
        for (int32_t y = 0; y < CANVAS_HEIGHT; y++) {
            int8_t color = mget(x, y);
            rect(x * 8 + 100, y * 8 + 4, 8, 8, color);
        }
    }
}

WASM_EXPORT("TIC")
void TIC() {
    update_input();
    draw_layout();
    draw_canvas();
}
