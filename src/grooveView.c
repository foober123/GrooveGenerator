#include <math.h>
#include <stdio.h>
#include <raylib.h>
#include <raygui.h>
#include "grooveView.h"
#include "grooveMetronome.h"
#include "grooveInfo.h"
#include "config.h"
#include "guiInfo.h"

void drawGrooveTitle(guiInfo *b){
    const char* title = "Groove Generator";
    int titleFontSize = 60;
    int titleWidth = MeasureText(title, titleFontSize);

    DrawText(title, SCREEN_WIDTH/2 - (titleWidth/2) , 30, titleFontSize, b->currentTheme[FOREGROUND]);
}

void drawGrooveBar(const grooveInfo *g, guiInfo *b){    
    const int staffHeight = 600;

    const int qtrNoteHeight = 400;
    const int eigthNoteHeight = qtrNoteHeight * 2 / 3;
    const int sixteenthNoteHeight = qtrNoteHeight / 3;

    const int textHeightOffset = 50;
    DrawRectangle(200,staffHeight,890,10,b->currentTheme[FOREGROUND]);

    // Quarter Notes 
    for (int i = 0; i < 4; i++) {
        DrawRectangle(200 + (i * 220),staffHeight - qtrNoteHeight,10,qtrNoteHeight,b->currentTheme[FOREGROUND]);
        DrawText(TextFormat("%d", i + 1), 200 + (i * 220), staffHeight- qtrNoteHeight - textHeightOffset, 24, b->currentTheme[ACCENT]);
    }

    // Eight Notes
    if(g->includeEighths == true){

        for (int i = 0; i < 4; i++) {
            DrawRectangle(310 + (i * 220),staffHeight - eigthNoteHeight,10,eigthNoteHeight,b->currentTheme[FOREGROUND]);
            DrawText("&", 310 + (i * 220), staffHeight - eigthNoteHeight - textHeightOffset, 24,b->currentTheme[ACCENT]); 
        }

    }

    // 16th Notes
    if(g->includeSixteenths == true){
        for (int i = 0; i < 8; i++){
            DrawRectangle(255 + (i * 110), staffHeight-sixteenthNoteHeight, 10, sixteenthNoteHeight,b->currentTheme[FOREGROUND]);

            if(i % 2 == 0){
                DrawText("e", 255 + (i *110), staffHeight - sixteenthNoteHeight - textHeightOffset, 24,b->currentTheme[ACCENT]);    
            }
            else{
                DrawText("a", 255 + (i *110), staffHeight - sixteenthNoteHeight - textHeightOffset, 24,b->currentTheme[ACCENT]);    
            }

        }
    }

    DrawRectangle(880 + 200,staffHeight-qtrNoteHeight,10,qtrNoteHeight,b->currentTheme[THEMEBORDER]);

}

void drawGroovePanel(grooveInfo *g, grooveMetronome *m, guiInfo *b){
    GuiCheckBox((Rectangle){100,675,24,24}, "8ths", &g->includeEighths);
    GuiCheckBox((Rectangle){100,725,24,24}, "16ths", &g->includeSixteenths);

    const int bpmBar = 300;
    int bpmSpacing = MeasureText(TextFormat("%0.f", m->bpm), 20);
    
    GuiSlider((Rectangle){SCREEN_WIDTH/2 - bpmBar/2,725,bpmBar,20}, "", "", &m->bpm, 40, 400);
    DrawText(TextFormat("%.0f", m->bpm), SCREEN_WIDTH/2 - bpmSpacing/2,675,20,b->currentTheme[FOREGROUND]);
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

void drawGrooveMarks(grooveInfo *g, guiInfo *b){
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
            DrawText("x",195 + (i * 55), 500, 40, b->currentTheme[THEMERED]);
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
                DrawText("x",195 + (i * 55), 500, 40, b->currentTheme[MUTEDRED]);
            }    

            if(g->includeEighths && (eighthNotes) ){
                DrawText("x",195 + (i * 55), 500, 40, b->currentTheme[MUTEDRED]);
            }

            if(g->includeSixteenths && !(qtrNotes || eighthNotes)){
                DrawText("x",195 + (i * 55), 500, 40, b->currentTheme[MUTEDRED]);
            }
        }

    } 
}


void drawGrooveTracer(grooveInfo *g, grooveMetronome *m, guiInfo *b){
    bool qtrNotes = m->beatCount == 0 || m->beatCount == 4 || m->beatCount == 8 || m->beatCount == 12; 
    bool eighthNotes = m->beatCount == 2 || m->beatCount == 6 || m->beatCount == 10 || m->beatCount == 14;


    if(SHOWTRACER == false || m->enabled == false){
    return;
    }
    

            if(qtrNotes){
                DrawText("*", 195 + (m->beatCount * 55), 100, 40, b->currentTheme[THEMEBLUE]);
            }    

            if(g->includeEighths && (eighthNotes) ){
                DrawText("*", 195 + (m->beatCount * 55), 100, 40, b->currentTheme[THEMEBLUE]);
            }

            if(g->includeSixteenths && !(qtrNotes || eighthNotes)){
                DrawText("*", 195 + (m->beatCount * 55), 100, 40, b->currentTheme[THEMEBLUE]);
            }

}

void setGrooveStyle(guiInfo *b){
    GuiSetStyle(DEFAULT, TEXT_SIZE, 24);
    GuiSetStyle(DEFAULT, TEXT_COLOR_NORMAL, ColorToInt(b->currentTheme[FOREGROUND]));
    GuiSetStyle(DEFAULT, BASE_COLOR_NORMAL, ColorToInt(b->currentTheme[THEMEBORDER]));
    GuiSetStyle(DEFAULT, BASE_COLOR_FOCUSED, ColorToInt(b->currentTheme[FOREGROUND]));
    GuiSetStyle(DEFAULT, TEXT_COLOR_FOCUSED, ColorToInt(b->currentTheme[THEMEBLUE]));

    GuiSetStyle(BUTTON, TEXT_COLOR_NORMAL, ColorToInt(b->currentTheme[FOREGROUND]));
    GuiSetStyle(BUTTON, BORDER_COLOR_FOCUSED, ColorToInt(b->currentTheme[SELECTED]));

    GuiSetStyle(CHECKBOX, BORDER_COLOR_NORMAL, ColorToInt(b->currentTheme[FOREGROUND]));
    GuiSetStyle(CHECKBOX, TEXT_COLOR_NORMAL, ColorToInt(b->currentTheme[ACCENT]));
    GuiSetStyle(CHECKBOX, TEXT_COLOR_FOCUSED, ColorToInt(b->currentTheme[THEMEBLUE]));
    GuiSetStyle(CHECKBOX, BASE_COLOR_FOCUSED, ColorToInt(b->currentTheme[THEMEBLUE])); 

    GuiSetStyle(SLIDER, TEXT_COLOR_FOCUSED, ColorToInt(b->currentTheme[THEMEBLUE]));
    GuiSetStyle(SLIDER, TEXT_COLOR_PRESSED, ColorToInt(b->currentTheme[THEMEBLUE]));

    GuiSetStyle(TOGGLE, TEXT_COLOR_PRESSED, ColorToInt(b->currentTheme[THEMERED]));
    GuiSetStyle(TOGGLE, BASE_COLOR_PRESSED, ColorToInt(b->currentTheme[MUTED]));


}

void drawGrooveSettings(grooveMetronome *m, guiInfo *b){
const Rectangle settingsMenu = (Rectangle){0, 5, 240, 790};
const Rectangle mixBox = (Rectangle){20,settingsMenu.height * 1/4,200,300};


if(!b->isSettings)GuiToggle((Rectangle){5,5,26,26}, "#141#", &b->isSettings);

if(b->isSettings){
DrawRectangleRec(settingsMenu, b->currentTheme[MUTED]);
GuiToggle((Rectangle){settingsMenu.width - 24 - 10, 10, 24 , 24}, "#113#", &b->isSettings);
if(GuiButton((Rectangle){20,settingsMenu.height * 1/8,200,30}, "THEME")){
b->themeIndex = (b->themeIndex + 1) % 3;
b->currentTheme = themeList[b->themeIndex];
}

GuiGroupBox(mixBox, "Mix");
GuiSliderBar((Rectangle){settingsMenu.width/2 - 50, settingsMenu.height * 2.5/8, 100, 20}, "M", "", &m->masterVolume, 0.0, 1.0);
GuiSliderBar((Rectangle){settingsMenu.width/2 - 50, settingsMenu.height * 3/8, 100, 20}, "H", "", &m->hihatVolume, 0.0, 1.0);
GuiSliderBar((Rectangle){settingsMenu.width/2 - 50, settingsMenu.height * 3.5/8, 100, 20}, "S", "", &m->snareVolume, 0.0, 1.0);
GuiSliderBar((Rectangle){settingsMenu.width/2 - 50, settingsMenu.height * 4/8, 100, 20}, "K", "", &m->kickVolume, 0.0, 1.0);

if(CheckCollisionPointRec(GetMousePosition(), mixBox)){
   SetSoundVolume(m->Hihat, m->hihatVolume * m->masterVolume); 
   SetSoundVolume(m->Snare, m->snareVolume * m->masterVolume);
   SetSoundVolume(m->Kick, m->kickVolume * m->masterVolume);
}


}
}


void drawGroove(grooveInfo *g, grooveMetronome *m, guiInfo *b){
    setGrooveStyle(b);
    drawGrooveTitle(b);
    drawGrooveBar(g, b);
    drawGroovePanel(g, m, b);
    drawGrooveMarks(g, b);
    drawGrooveTracer(g, m, b);
    drawGrooveSettings(m, b);

    ClearBackground(b->currentTheme[BACKGROUND]);

}
