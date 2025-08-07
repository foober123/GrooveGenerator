#ifndef GROOVE_METRONOME_H
#define GROOVE_METRONOME_H

#include "raylib.h"
#include "grooveInfo.h"

typedef struct{
Sound Hihat;
Sound Snare;

float hihatVolume;
float snareVolume;

double lastBeatTime;
bool enabled;
float bpm;
bool enableAccent;
int beatCount;

} grooveMetronome;
void initMetronome(grooveMetronome *m, grooveInfo *g);
void updateMetronome(grooveMetronome *m, grooveInfo *g);

#endif
