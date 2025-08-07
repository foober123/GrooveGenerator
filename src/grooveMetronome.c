#include "config.h"
#include "grooveMetronome.h"
#include "grooveInfo.h"
#include <raylib.h>

void initMetronome(grooveMetronome *m, grooveInfo *g)
{
m->Hihat = LoadSound("assets/hihat.wav");
m->Snare = LoadSound("assets/snare.wav");

SetSoundVolume(m->Hihat, DEFAULT_HIHAT_VOLUME);
SetSoundVolume(m->Snare, DEFAULT_SNARE_VOLUME);

m->hihatVolume = DEFAULT_HIHAT_VOLUME;
m->snareVolume = DEFAULT_SNARE_VOLUME;

m->beatCount = 0;
m->enabled = false;
m->enableAccent = false;
m->lastBeatTime = GetTime();
m->bpm = DEFAULT_BPM;
}

void updateMetronome(grooveMetronome *m, grooveInfo *g){
static bool wasPaused = false;

if(!wasPaused && m->enabled){
m->beatCount = 0;
m->lastBeatTime = GetTime();
}
wasPaused = m->enabled;

if(m->enabled == false){
return;
}

double currentTime = GetTime();
float secondsPerStep = 60.f / (4 * m->bpm); 

if(currentTime - m->lastBeatTime >= secondsPerStep){

    if(m->beatCount % 4 == 0){
        PlaySound(m->Hihat);
    }

    if(m->enableAccent && g->steps[m->beatCount]){
    PlaySound(m->Snare);
    }

    m->lastBeatTime += secondsPerStep;
    m->beatCount = (m->beatCount + 1)  % 16;
}

}
