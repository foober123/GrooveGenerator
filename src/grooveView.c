#include <math.h>
#include <stdio.h>
#include <raylib.h>
#include <raygui.h>
#include "grooveView.h"
#include "grooveMetronome.h"
#include "grooveInfo.h"
#include "config.h"
#include "theme.h"

void drawGrooveTitle(){
    const char* title = "Groove Generator";
    int titleFontSize = 60;
    int titleWidth = MeasureText(title, titleFontSize);

    DrawText(title, SCREEN_WIDTH/2 - (titleWidth/2) , 30, titleFontSize, currentTheme[FOREGROUND]);
}

void drawGrooveBar(const grooveInfo *g){    
    const int staffHeight = 600;

    const int qtrNoteHeight = 400;
    const int eigthNoteHeight = qtrNoteHeight * 2 / 3;
    const int sixteenthNoteHeight = qtrNoteHeight / 3;

    const int textHeightOffset = 50;
    DrawRectangle(200,staffHeight,890,10,currentTheme[FOREGROUND]);

    // Quarter Notes 
    for (int i = 0; i < 4; i++) {
        DrawRectangle(200 + (i * 220),staffHeight - qtrNoteHeight,10,qtrNoteHeight,currentTheme[FOREGROUND]);
        DrawText(TextFormat("%d", i + 1), 200 + (i * 220), staffHeight- qtrNoteHeight - textHeightOffset, 24, currentTheme[ACCENT]);
    }

    // Eight Notes
    if(g->includeEighths == true){

        for (int i = 0; i < 4; i++) {
            DrawRectangle(310 + (i * 220),staffHeight - eigthNoteHeight,10,eigthNoteHeight,currentTheme[FOREGROUND]);
            DrawText("&", 310 + (i * 220), staffHeight - eigthNoteHeight - textHeightOffset, 24, currentTheme[ACCENT]); 
        }

    }

    // 16th Notes
    if(g->includeSixteenths == true){
        for (int i = 0; i < 8; i++){
            DrawRectangle(255 + (i * 110), staffHeight-sixteenthNoteHeight, 10, sixteenthNoteHeight, currentTheme[FOREGROUND]);

            if(i % 2 == 0){
                DrawText("e", 255 + (i *110), staffHeight - sixteenthNoteHeight - textHeightOffset, 24, currentTheme[ACCENT]);    
            }
            else{
                DrawText("a", 255 + (i *110), staffHeight - sixteenthNoteHeight - textHeightOffset, 24, currentTheme[ACCENT]);    
            }

        }
    }

    DrawRectangle(880 + 200,staffHeight-qtrNoteHeight,10,qtrNoteHeight,currentTheme[THEMEBORDER]);

}

void drawGroovePanel(grooveInfo *g, grooveMetronome *m){
    GuiCheckBox((Rectangle){100,675,24,24}, "8ths", &g->includeEighths);
    GuiCheckBox((Rectangle){100,725,24,24}, "16ths", &g->includeSixteenths);

    const int bpmBar = 300;
    int bpmSpacing = MeasureText(TextFormat("%0.f", m->bpm), 20);
    
    GuiSlider((Rectangle){SCREEN_WIDTH/2 - bpmBar/2,725,bpmBar,20}, "", "", &m->bpm, 40, 400);
    DrawText(TextFormat("%.0f", m->bpm), SCREEN_WIDTH/2 - bpmSpacing/2,675,20,currentTheme[FOREGROUND]);
    if(GuiButton((Rectangle){SCREEN_WIDTH/2 + 40, 675, 20, 20}, "+")){
        m->bpm = roundf(m->bpm);
        m->bpm++;
    }
    if(GuiButton((Rectangle){SCREEN_WIDTH/2 - 60, 675, 20, 20}, "-")){
        m->bpm = roundf(m->bpm);
        m->bpm--;
    }
    GuiToggle((Rectangle){SCREEN_WIDTH/2 - 150, 750, 148, 24}, "Play", &m->enabled);
    GuiToggle((Rectangle){SCREEN_WIDTH/2 + 2, 750, 148, 24}, "Accent", &m->enableAccent);

    if(GuiButton((Rectangle){SCREEN_WIDTH/2 + SCREEN_WIDTH/3 - 75, 675, 80, 24}, "Clear")){
        clearGroove(g);
    }

    if(GuiButton((Rectangle){SCREEN_WIDTH/2 + SCREEN_WIDTH/3 - 75, 725, 80, 24}, "Rand")){
        randomizeGroove(g);
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
            DrawText("x",195 + (i * 55), 500, 40, currentTheme[THEMERED]);
        }
    }

    for (int i = 0; i < 16; i++){
        DrawRectangleLinesEx((Rectangle){195 + (i * 55), 500, 20, 110}, 0, GRAY);

        if(CheckCollisionPointRec(GetMousePosition(), (Rectangle){195 + (i * 55), 500, 20, 110}) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            g->steps[i] = !g->steps[i];

        }

    }

    //Hovering Logic

    for(int i = 0; i < 16; i++){

        if(CheckCollisionPointRec(GetMousePosition(), (Rectangle){195 + (i * 55), 500, 20, 110})){
            bool qtrNotes = i == 0 || i == 4 || i == 8 || i == 12; 
            bool eighthNotes = i == 2 || i == 6 || i == 10 || i == 14;

            if(qtrNotes){
                DrawText("x",195 + (i * 55), 500, 40, currentTheme[MUTEDRED]);
            }    

            if(g->includeEighths && (eighthNotes) ){
                DrawText("x",195 + (i * 55), 500, 40, currentTheme[MUTEDRED]);
            }

            if(g->includeSixteenths && !(qtrNotes || eighthNotes)){
                DrawText("x",195 + (i * 55), 500, 40, currentTheme[MUTEDRED]);
            }
        }

    } 
}


void drawGrooveTracer(grooveInfo *g, grooveMetronome *m){
    bool qtrNotes = m->beatCount == 0 || m->beatCount == 4 || m->beatCount == 8 || m->beatCount == 12; 
    bool eighthNotes = m->beatCount == 2 || m->beatCount == 6 || m->beatCount == 10 || m->beatCount == 14;


    if(SHOWTRACER == false || m->enabled == false){
    return;
    }
    

            if(qtrNotes){
                DrawText("*", 195 + (m->beatCount * 55), 100, 40, currentTheme[THEMEBLUE]);
            }    

            if(g->includeEighths && (eighthNotes) ){
                DrawText("*", 195 + (m->beatCount * 55), 100, 40, currentTheme[THEMEBLUE]);
            }

            if(g->includeSixteenths && !(qtrNotes || eighthNotes)){
                DrawText("*", 195 + (m->beatCount * 55), 100, 40, currentTheme[THEMEBLUE]);
            }

}

void setGrooveStyle(){
    GuiSetStyle(DEFAULT, TEXT_SIZE, 24);
    GuiSetStyle(DEFAULT, TEXT_COLOR_NORMAL, ColorToInt(currentTheme[FOREGROUND]));
    GuiSetStyle(DEFAULT, BASE_COLOR_NORMAL, ColorToInt(currentTheme[THEMEBORDER]));
    GuiSetStyle(DEFAULT, BASE_COLOR_FOCUSED, ColorToInt(currentTheme[FOREGROUND]));
    GuiSetStyle(DEFAULT, TEXT_COLOR_FOCUSED, ColorToInt(currentTheme[THEMEBLUE]));

    GuiSetStyle(BUTTON, TEXT_COLOR_NORMAL, ColorToInt(currentTheme[FOREGROUND]));
    GuiSetStyle(BUTTON, BORDER_COLOR_FOCUSED, ColorToInt(currentTheme[SELECTED]));

    GuiSetStyle(CHECKBOX, BORDER_COLOR_NORMAL, ColorToInt(currentTheme[FOREGROUND]));
    GuiSetStyle(CHECKBOX, TEXT_COLOR_NORMAL, ColorToInt(currentTheme[ACCENT]));
    GuiSetStyle(CHECKBOX, TEXT_COLOR_FOCUSED, ColorToInt(currentTheme[THEMEBLUE]));
    GuiSetStyle(CHECKBOX, BASE_COLOR_FOCUSED, ColorToInt(currentTheme[THEMEBLUE])); 

    GuiSetStyle(SLIDER, TEXT_COLOR_FOCUSED, ColorToInt(currentTheme[THEMEBLUE]));
    GuiSetStyle(SLIDER, TEXT_COLOR_PRESSED, ColorToInt(currentTheme[THEMEBLUE]));

    GuiSetStyle(TOGGLE, TEXT_COLOR_PRESSED, ColorToInt(currentTheme[THEMERED]));
    GuiSetStyle(TOGGLE, BASE_COLOR_PRESSED, ColorToInt(currentTheme[MUTED]));



}

void drawGroove(grooveInfo *g, grooveMetronome *m){
    setGrooveStyle();
    drawGrooveTitle();
    drawGrooveBar(g);
    drawGroovePanel(g, m);
    drawGrooveMarks(g);
    drawGrooveTracer(g, m);
}
