#include "grooveKeybinds.h"
#include <raylib.h>
#define RAYGUI_IMPLEMENTATION
#include <raygui.h>

#include "config.h"
#include "grooveInfo.h"
#include "grooveMetronome.h"
#include "grooveView.h"
#include "guiInfo.h"

int main(void){
 SetTargetFPS(60);
 InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Groove Trainer");
 InitAudioDevice();

 guiInfo gui; 
 grooveInfo groove;
 grooveMetronome metronome;

 initDefaultGUI(&gui);
 initGroove(&groove);
 initMetronome(&metronome, &groove);
 

 while (!WindowShouldClose()) {
     BeginDrawing();
     {
        handleGrooveKeybinds(&groove, &metronome);
        updateMetronome(&metronome, &groove);
        drawGroove(&groove, &metronome, &gui);
     }
     EndDrawing();
 
 }

}


