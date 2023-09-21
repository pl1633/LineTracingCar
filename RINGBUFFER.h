#ifndef __RINGBUFFER_H_
#define __RINGBUFFER_H_

#include "RoboCAR.h"

#define BUFF_SIZE	100

typedef struct
{
    int head;
    int tail;
    unsigned char Buff[BUFF_SIZE];
}RingBuff;



int RingBuff_full(RingBuff ring);
int RingBuff_empty(RingBuff ring);
void RingBuff_Put( RingBuff *ring, unsigned char data);
unsigned char RingBuff_Get( RingBuff *ring);


RingBuff ring;



#endif
