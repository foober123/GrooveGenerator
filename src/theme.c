#include "theme.h"
#include "raylib.h"
#include "config.h"
#include <stdio.h>

Color lightTheme[COLOR_COUNT] = {
[FOREGROUND] = BLACK,
[BACKGROUND] = RAYWHITE,
[SELECTED] = GRAY,
[ACCENT] = DARKGRAY,
[THEMEBORDER] = LIGHTGRAY,
[MUTED] = GRAY,

[THEMERED] = RED,
[THEMEBLUE] = BLUE


};

Color oneDark[COLOR_COUNT] = {
[BACKGROUND] = {40, 44, 52, 255},
[FOREGROUND] = {171, 178, 191, 255},
[SELECTED] = {92, 99, 112, 255},
[ACCENT] = {229, 192, 123, 255},
[THEMEBORDER] = {33, 37, 43, 255},
[MUTED] = {57, 63, 74, 255},

[THEMERED] = {232, 102, 113, 255},
[THEMEBLUE] = {97, 175, 239, 255},

[MUTEDRED] = {232, 102, 113, 120},

};

Color oneLight[COLOR_COUNT] = {
[BACKGROUND] = {250, 250, 250, 255},
[FOREGROUND] = {56, 58, 66, 255},
[SELECTED] = {152, 104, 1, 255}, 
[ACCENT] = {152, 104, 1, 255},
[THEMEBORDER] = {201, 201, 201, 255},
[MUTED] = {230, 230, 230, 255},

[THEMERED] = {228, 86, 73, 255},
[THEMEBLUE] = {64, 120, 242, 255},

[MUTEDRED] = {228, 86, 73, 120},





};


Color *currentTheme = CTHEME;
