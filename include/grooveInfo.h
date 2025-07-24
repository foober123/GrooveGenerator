#ifndef GROOVE_INFO_H
#define GROOVE_INFO_H

#include <stdbool.h>

typedef struct{
bool steps[16]; 
bool isPlaying;
bool includeEighths;
bool includeSixteenths;

float BPM;
} grooveInfo ;

void initGroove(grooveInfo *g);
void randomizeGroove(grooveInfo *g);

#endif
