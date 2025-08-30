#include "theme.h"
#include "raylib.h"
#include "config.h"


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
[BACKGROUND] = {40, 44, 52, 255},       // #282c34
[FOREGROUND] = {171, 178, 191, 255},    // #abb2bf
[SELECTED] = {92, 99, 112, 255},        // #5c6370
[ACCENT] = {229, 192, 123, 255},        // #e5c07b
[THEMEBORDER] = {33, 37, 43, 255},      // #21252b
[MUTED] = {57, 63, 74, 255},            // #393f4a

[THEMERED] = {232, 102, 113, 255},      // #e86671
[THEMEBLUE] = {97, 175, 239, 255},      // #61afef

[MUTEDRED] = {232, 102, 113, 120},      // #e86671

};

Color oneLight[COLOR_COUNT] = {
[BACKGROUND] = {250, 250, 250, 255},    // #fafafa
[FOREGROUND] = {56, 58, 66, 255},       // #383a42
[SELECTED] = {152, 104, 1, 255},        // #986801
[ACCENT] = {152, 104, 1, 255},          // #986801
[THEMEBORDER] = {201, 201, 201, 255},   // #c9c9c9
[MUTED] = {230, 230, 230, 255},         // #e6e6e6

[THEMERED] = {228, 86, 73, 255},        // #e45649
[THEMEBLUE] = {64, 120, 242, 255},      // #4078f2

[MUTEDRED] = {228, 86, 73, 120},        // #e45649
};

const int THEMECOUNT = 3;
const Color *themeList[] = {lightTheme, oneDark, oneLight};

