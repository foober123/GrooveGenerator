#include <raylib.h>
#include <math.h>
#include "config.h"
#include "grooveKeybinds.h"
#include "grooveMetronome.h"
#include "grooveInfo.h"

void BpmControls(grooveMetronome *m)
{
static float bpmChangeTimer = 0.0f;
const float bpmChangeDelay = 0.05f;
float dt = GetFrameTime();

bpmChangeTimer -= dt;

if (IsKeyDown(KEY_X) && bpmChangeTimer <= 0.0f) {
    m->bpm = roundf(m->bpm);
    if (m->bpm < 400) m->bpm++;
    bpmChangeTimer = bpmChangeDelay;
}

if (IsKeyDown(KEY_A) && bpmChangeTimer <= 0.0f) {
    m->bpm = roundf(m->bpm);
    if (m->bpm > 40) m->bpm--;
    bpmChangeTimer = bpmChangeDelay;
}



};



void handleGrooveKeybinds(grooveInfo *g, grooveMetronome *m){
    


    if(IsKeyPressed(KEY_ONE)) m->bpm = DEFAULT_BPM;
    if(IsKeyPressed(KEY_TWO)) m->bpm = BPM_PRESET_1;
    if(IsKeyPressed(KEY_THREE)) m->bpm = BPM_PRESET_2;
    if(IsKeyPressed(KEY_FOUR)) m->bpm = BPM_PRESET_3;




    if(IsKeyPressed(KEY_SPACE)){
        m->enabled = !m->enabled;

    }

    if(IsKeyPressed(KEY_RIGHT_ALT)){
        m->enableAccent = !m->enableAccent;

    }

    if(IsKeyPressed(KEY_C)){
        clearGroove(g);
    }

    if(IsKeyPressed(KEY_R)){
        randomizeGroove(g);
    }
    /*
    if(IsKeyDown(KEY_X)){ 
        m->bpm = roundf(m->bpm);

        if(m->bpm != 400){
        m->bpm++;
        }
    }

    if(IsKeyDown(KEY_A)){
        m->bpm = roundf(m->bpm);

        if(m->bpm != 40){
        m->bpm--;
        }
    }
    */

    BpmControls(m);
};


