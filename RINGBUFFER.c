#include "ringbuffer.h"
#include "UART.h"



void RingBuff_Init(RingBuff ring)
{
  ring.head = 0;
  ring.tail = 0;
}


int RingBuff_full(RingBuff ring)
{
    if((ring.head + 1) % BUFF_SIZE == ring.tail)
    {
        return 1;
    }

    return 0;
}


int RingBuff_empty(RingBuff ring)
{
    if(ring.head == ring.tail)
    {
        return 1;
    }
    return 0;
}


void RingBuff_Put(RingBuff *ring, u08 data)
{
    if( RingBuff_full( *ring))
    {
        //return;
    }
	else
	{
      ring->head = (ring->head + 1) % BUFF_SIZE;
      ring->Buff[ring->head] = data; 
	}	
    
}


unsigned char RingBuff_Get(RingBuff *ring)
{
    if(RingBuff_empty( *ring))
    {
        return 0;
    }
    ring->tail = (ring->tail + 1) % BUFF_SIZE;
    
    return ring->Buff[ring->tail];
}
