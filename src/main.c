#include <stdio.h>
#include <stdlib.h>
#include <raylib.h>
#define RAYGUI_IMPLEMENTATION
#include <raygui.h>

#include "config.h"
#include "grooveInfo.h"
#include "grooveMetronome.h"
#include "grooveView.h"
#include "theme.h"

void drawBar();

int main(void){
 SetTargetFPS(60);
 InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Groove Trainer");
 InitAudioDevice();

 grooveInfo groove;
 grooveMetronome metronome;
 initGroove(&groove);
 initMetronome(&metronome, &groove);
 

 while (!WindowShouldClose()) {
     BeginDrawing();
     {
        updateMetronome(&metronome, &groove);
        ClearBackground(currentTheme[BACKGROUND]);
        drawGroove(&groove, &metronome);
     }
     EndDrawing();
 
 }

}


