#include <stdio.h>
#include <stdlib.h>
#include <raylib.h>
#define RAYGUI_IMPLEMENTATION
#include <raygui.h>

#include "config.h"
#include "grooveInfo.h"
#include "grooveMetronome.h"
#include "grooveView.h"


void drawBar();

int main(void){

 InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Groove Trainer");
 InitAudioDevice();

 grooveInfo groove;
 grooveMetronome metronome;
 initGroove(&groove);
 initMetronome(&metronome, &groove);
 GuiSetStyle(DEFAULT, TEXT_SIZE, 24);
 

 while (!WindowShouldClose()) {
     BeginDrawing();
     {
        updateMetronome(&metronome, &groove);
        ClearBackground(RAYWHITE);
        drawGroove(&groove, &metronome);
     }
     EndDrawing();
 
 }

}


