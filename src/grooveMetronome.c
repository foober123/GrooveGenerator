#include "grooveMetronome.h"
#include "grooveInfo.h"
#include <raylib.h>

void initMetronome(grooveMetronome *m, grooveInfo *g)
{
m->Hihat = LoadSound("assets/hihat.wav");
m->enabled = false;
m->lastBeatTime = GetTime();
m->bpm = 120;
}

void updateMetronome(grooveMetronome *m, grooveInfo *g){
static bool wasPaused = false;

if(!wasPaused && m->enabled){
m->lastBeatTime = GetTime();
}
wasPaused = m->enabled;

if(m->enabled == false){
return;
}

double currentTime = GetTime();
float secondsPerBeat = 60.f / m->bpm;

if(currentTime - m->lastBeatTime >= secondsPerBeat){
    PlaySound(m->Hihat);
    m->lastBeatTime += secondsPerBeat;
}

}
