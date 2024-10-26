/*
 * ringbuffer.c
 *
 *  Created on: Oct 23, 2024
 *      Author: doria
 */

#include "ringbuffer.h"

void ring_buffer_setup(volatile ring_buffer_t* rb, volatile uint8_t* buffer, uint32_t size)
{
	rb->buffer = buffer;
	rb->readIndex = 0;
	rb->writeIndex = 0;
	rb->mask = size - 1; // zakładając, że zmienna size jest potęgą 2
}
bool ring_buffer_empty(volatile ring_buffer_t* rb)
{
	return rb->readIndex == rb->writeIndex;
}

bool ring_buffer_read(volatile ring_buffer_t* rb, uint8_t* byte)
{
	uint32_t localReadIndex = rb->readIndex;
	uint32_t localWriteIndex = rb->writeIndex;
	if(localReadIndex == localWriteIndex)
	{
		return false;
	}
	*byte = rb->buffer[localReadIndex];
	localReadIndex = (localReadIndex + 1) & rb->mask; // jeżeli wykroczymy poza zasięg to wracamy na początek
	rb->readIndex = localReadIndex;


	return true;
}



bool ring_buffer_write(volatile ring_buffer_t* rb, uint8_t byte)
{
	uint32_t localReadIndex = rb->readIndex;
	uint32_t localWriteIndex = rb->writeIndex;

	uint32_t nextWriteIndex = (localWriteIndex + 1) & rb->mask; // działa tak samo jak w localReadIndex

	// ponieważ tutaj zdarzy się sytuacja, że chcemy coś zapisać ale tym samym dojdziemy do sytuacji gdzie
	// writeIndex == readIndex i stracimy wszystkie wcześniej zapisane dane
	if(nextWriteIndex == localReadIndex)
	{
		return false;
	}
	rb->buffer[localWriteIndex] = byte;
	rb->writeIndex = nextWriteIndex;
	return true;
}
