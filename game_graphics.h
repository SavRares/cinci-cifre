#pragma once
#include <winbgim.h>
#include "base_dependencies.h"

// CONSTANTS

const int DIGIT_TILE_HEIGHT = 19;
const int DIGIT_TILE_WIDTH = 11;

struct RGB_color {
    int r;
    int g;
    int b;
};

const RGB_color _WHITE {225, 225, 225};
const RGB_color _BLACK {25, 25, 25};
const RGB_color _RED {255, 100, 100};
const RGB_color _GREY {100, 100, 100};

#define GREYED_OUT_DIGIT_BG _GREY
#define NORMAL_DIGIT_BG _WHITE

// FUNCTIONS

void drawFilledRect(int left, int top, int right, int bottom) {
    int poly_points[8] = 
    {
        left, top,
        right, top,
        right, bottom,
        left, bottom
    };

    fillpoly(4, poly_points);
}

void drawDigit(int left, int top, unsigned short num, bool greyed_out) {
    RGB_color bg_color;
    if (greyed_out == true)
        bg_color = GREYED_OUT_DIGIT_BG;
    else
        bg_color = NORMAL_DIGIT_BG;

    int bottom = top + DIGIT_TILE_HEIGHT;
    int right = left + DIGIT_TILE_WIDTH;

    setcolor(RGB(bg_color.r, bg_color.g, bg_color.b));
    setfillstyle(1, RGB(bg_color.r, bg_color.g, bg_color.b));
    drawFilledRect(left, top, right, bottom);

    char text[2];
    text[0] = (char)num + '0';
    text[1] = '\0';

    setcolor(RGB(_BLACK.r, _BLACK.g, _BLACK.b));
    setbkcolor(RGB(bg_color.r, bg_color.g, bg_color.b));

    /* QUARANTINE. THESE FUNCTIONS ARE EVIL AND I STILL DON'T KNOW HOW THEY WORK.
    setusercharsize(3, 1, 2, 1);
    settextstyle(EUROPEAN_FONT, HORIZ_DIR, 0);
    */
    
    outtextxy(left + 2, top + 2, text);
}

void drawHiddenDigit(int left, int top) {
    int bottom = top + DIGIT_TILE_HEIGHT;
    int right = left + DIGIT_TILE_WIDTH;

    setcolor(RGB(_RED.r, _RED.g, _RED.b));
    setfillstyle(1, RGB(_RED.r, _RED.g, _RED.b));
    drawFilledRect(left, top, right, bottom);

    setcolor(RGB(_BLACK.r, _BLACK.g, _BLACK.b));
    line(left, top, right, bottom);
    line(right, top, left, bottom);
}

void drawPerm(int left, int top, permutation perm, bool greyed_out) {
    for (int i = 0; i < PERM_LEN; i++) {
        drawDigit(left + (DIGIT_TILE_WIDTH + 2) * i, top, perm.digit[i], greyed_out);
    }
}

void drawHiddenPerm(int left, int top) {
    for (int i = 0; i < PERM_LEN; i++) {
        drawHiddenDigit(left + (DIGIT_TILE_WIDTH + 2) * i, top);
    }
}
