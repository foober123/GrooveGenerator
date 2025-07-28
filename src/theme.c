#include "theme.h"
#include "raylib.h"
#include "config.h"
#include <stdio.h>

Color tokyoNight[COLOR_COUNT] = {
[FOREGROUND] = {169, 177, 220, 255},
[BACKGROUND] = {26, 27, 44, 255},
[SELECTED] = {40, 52, 74, 255},
[ACCENT] = {224, 175, 104, 255},
[THEMEBORDER] = {40, 52, 74, 255},
[MUTED] = {122, 162, 247, 255},


[THEMERED] = {247, 118, 142, 255},
[THEMEBLUE] = {122, 162, 247, 255}
};

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







};

Color *currentTheme = CTHEME;
