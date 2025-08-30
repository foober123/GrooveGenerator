#include "config.h"
#include "grooveMetronome.h"
#include "grooveInfo.h"
#include "theme.h"
#include <raylib.h>


void initMetronome(grooveMetronome *m, grooveInfo *g)
{
m->currentAccent = SNARE;
m->masterVolume = 1.0;
m->Hihat = LoadSound("assets/hihat.wav");
m->Snare = LoadSound("assets/snare.wav");
m->Kick = LoadSound("assets/kick.wav");

m->hihatVolume = DEFAULT_HIHAT_VOLUME;
m->kickVolume = DEFAULT_KICK_VOLUME;
m->snareVolume = DEFAULT_SNARE_VOLUME;

SetSoundVolume(m->Hihat, DEFAULT_HIHAT_VOLUME);
SetSoundVolume(m->Kick, DEFAULT_KICK_VOLUME);
SetSoundVolume(m->Snare, DEFAULT_SNARE_VOLUME);

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
        switch (m->currentAccent) {
            case SNARE:
            PlaySound(m->Snare);
            break;

            case KICK:
            PlaySound(m->Kick);
            break;
            
            default:
            break;
        }
        
    }

    m->lastBeatTime += secondsPerStep;
    m->beatCount = (m->beatCount + 1)  % 16;
}

}
