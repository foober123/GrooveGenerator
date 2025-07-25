#include <math.h>
#include <stdio.h>
#include <raylib.h>
#include <raygui.h>
#include "grooveView.h"
#include "grooveMetronome.h"
#include "grooveInfo.h"
#include "config.h"

void drawGrooveTitle(){
 const char* title = "Groove Generator";
 int titleFontSize = 60;
 int titleWidth = MeasureText(title, titleFontSize);
  
 DrawText(title, SCREEN_WIDTH/2 - (titleWidth/2) , 30, titleFontSize, BLACK);
}

void drawGrooveBar(const grooveInfo *g){    
    const int staffHeight = 600;

    char buffer[4];
    const int qtrNoteHeight = 400;
    const int eigthNoteHeight = qtrNoteHeight * 2 / 3;
    const int sixteenthNoteHeight = qtrNoteHeight / 3;
    
    const int textHeightOffset = 50;
    DrawRectangle(200,staffHeight,890,10,BLACK);
   
    // Quarter Notes 
    for (int i = 0; i < 4; i++) {
    DrawRectangle(200 + (i * 220),staffHeight - qtrNoteHeight,10,qtrNoteHeight,BLACK);
        sprintf(buffer, "%d", i + 1);
        DrawText(buffer, 200 + (i * 220), staffHeight- qtrNoteHeight - textHeightOffset, 24, BLACK);
    }
    
    // Eight Notes
    if(g->includeEighths == true){

    for (int i = 0; i < 4; i++) {
    DrawRectangle(310 + (i * 220),staffHeight - eigthNoteHeight,10,eigthNoteHeight,BLACK);
    DrawText("&", 310 + (i * 220), staffHeight - eigthNoteHeight - textHeightOffset, 24, BLACK); 
    }

    }

    // 16th Notes
    if(g->includeSixteenths == true){
    for (int i = 0; i < 8; i++){
    DrawRectangle(255 + (i * 110), staffHeight-sixteenthNoteHeight, 10, sixteenthNoteHeight, BLACK);

    if(i % 2 == 0){
    DrawText("e", 255 + (i *110), staffHeight - sixteenthNoteHeight - textHeightOffset, 24, BLACK);    
        }
    else{
    DrawText("a", 255 + (i *110), staffHeight - sixteenthNoteHeight - textHeightOffset, 24, BLACK);    
    }

    }
    }
        
    DrawRectangle(880 + 200,staffHeight-qtrNoteHeight,10,qtrNoteHeight,GRAY);

}

void drawGroovePanel(grooveInfo *g, grooveMetronome *m){
    GuiCheckBox((Rectangle){100,675,20,20}, "8ths", &g->includeEighths);
    GuiCheckBox((Rectangle){100,725,20,20}, "16ths", &g->includeSixteenths);
    
    const int bpmBar = 300;
    int bpmSpacing = MeasureText(TextFormat("%0.f", m->bpm), 20);

    //BPM BAR
    DrawText(TextFormat("%.0f", m->bpm), SCREEN_WIDTH/2 - bpmSpacing/2,675,20,BLACK);
    GuiSliderBar((Rectangle){SCREEN_WIDTH/2 - bpmBar/2,725,bpmBar,20}, "", "", &m->bpm, 40, 400);
    if(GuiButton((Rectangle){SCREEN_WIDTH/2 + 40, 675, 20, 20}, "+")){
        m->bpm = roundf(m->bpm);
        m->bpm++;
    }
    if(GuiButton((Rectangle){SCREEN_WIDTH/2 - 60, 675, 20, 20}, "-")){
        m->bpm = roundf(m->bpm);
        m->bpm--;
    }
    GuiToggle((Rectangle){SCREEN_WIDTH/2 - 150, 750, 148, 24}, "Play", &m->enabled);
    
    if(GuiButton((Rectangle){SCREEN_WIDTH/3 - 75, 675, 80, 24}, "Clear")){
    for (int i = 0; i < 16; i++) {
        g->steps[i] = false;
    }
    }
}

void drawGrooveMarks(grooveInfo *g){
    if(!g->includeEighths){
    g->steps[2] = false;
    g->steps[6] = false;
    g->steps[10] = false;
    g->steps[14] = false;

    }

    if(!g->includeSixteenths){
    for (int i = 0; i < 16; i++) {
    if(i % 2 != 0){
    g->steps[i] = false;
            }
        }
    }

    for (int i = 0; i < 16; i++) {
    if(g->steps[i] == true){
        DrawCircle(205 + (i * 55), 600, 10.0, RED);
        }
    }

    for (int i = 0; i < 16; i++){
        DrawRectangleLinesEx((Rectangle){195 + (i * 55), 590, 20, 20}, 0, GRAY);

        if(CheckCollisionPointRec(GetMousePosition(), (Rectangle){195 + (i * 55), 590, 20, 20}) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
        g->steps[i] = !g->steps[i];

        }

}

}

void drawGroove(grooveInfo *g, grooveMetronome *m){
drawGrooveTitle();
drawGrooveBar(g);
drawGroovePanel(g, m);
drawGrooveMarks(g);
}
