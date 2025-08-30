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

    MUTEDRED,

    COLOR_COUNT
} colorscheme;

extern Color lightTheme[];
extern Color oneDark[];
extern Color oneLight[];


extern const int THEMECOUNT;
extern const Color *themeList[];

#endif
