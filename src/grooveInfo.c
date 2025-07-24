#include "grooveInfo.h"
#include <stdlib.h>
#include <stdbool.h>


void initGroove(grooveInfo *g){

for (int i = 0; i < 16; i++) {
g->steps[i] = false;

}
g->isPlaying = false;
g->includeEighths = false;
g->includeSixteenths = false;

g->BPM = 120;
}

void randomizeGroove(grooveInfo *g){
for(int i = 0; i < 16; i++){
    g->steps[i] = rand() % 2;
    }
}
