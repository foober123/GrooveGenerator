#ifndef THEME_H
#define THEME_H

#include "raylib.h"

typedef enum{
    FOREGROUND,
    BACKGROUND,
    SELECTED,
    ACCENT,
    THEMEBORDER,
    MUTED,

    THEMERED,
    THEMEBLUE,

    COLOR_COUNT
} colorscheme;

extern Color tokyoNight[];
extern Color lightTheme[];
extern Color oneDark[];

extern Color *currentTheme;

#endif
