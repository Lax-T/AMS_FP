#include "stm32f10x.h"
#define CoreFreqMHz 32
#define USDELAY_CALC(delay) (delay*CoreFreqMHz-28)

void uSDelay(unsigned int delay );

void mSDelay(unsigned int delay);

