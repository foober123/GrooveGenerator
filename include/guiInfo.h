#ifndef GUIINFO_H
#define GUIINFO_H
#include "theme.h"

typedef struct{
Color *currentTheme;
int themeIndex;
bool isSettings;

} guiInfo;

void initDefaultGUI(guiInfo *b);


#endif
