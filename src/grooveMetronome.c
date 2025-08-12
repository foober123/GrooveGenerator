#include "config.h"
#include "grooveMetronome.h"
#include "grooveInfo.h"
#include <raylib.h>


void loadAccentSound(grooveMetronome *m){
switch (ACCENTSOUND){
    case SNARE:
        m->Accent = LoadSound("assets/snare.wav");
        m->accentVolume = DEFAULT_SNARE_VOLUME;
        break;
    case KICK:
        m->Accent = LoadSound("assets/kick.wav");
        m->accentVolume = DEFAULT_KICK_VOLUME;
        break;
    }





}


void initMetronome(grooveMetronome *m, grooveInfo *g)
{
m->Hihat = LoadSound("assets/hihat.wav");
loadAccentSound(m);

SetSoundVolume(m->Hihat, DEFAULT_HIHAT_VOLUME);
SetSoundVolume(m->Accent, DEFAULT_SNARE_VOLUME);

m->hihatVolume = DEFAULT_HIHAT_VOLUME;

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
    PlaySound(m->Accent);
    }

    m->lastBeatTime += secondsPerStep;
    m->beatCount = (m->beatCount + 1)  % 16;
}

}
