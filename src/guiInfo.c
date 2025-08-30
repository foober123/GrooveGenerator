#include "config.h"
#include "theme.h"
#include <raylib.h>
#include "guiInfo.h"


int getThemeIndex(Color *theme,const Color *themelist[], int count);


void initDefaultGUI(guiInfo *b){
b->themeIndex = getThemeIndex(CTHEME, &themeList[THEMECOUNT], THEMECOUNT); 
b->currentTheme = CTHEME;

b->isSettings = false;
}

int getThemeIndex(Color *theme,const Color *themelist[], int count){
for (int i = 0; i < count; i++) {
    if(themelist[i] == theme) return i;
}
return -1;
}
