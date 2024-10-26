/*
 * ringbuffer.h
 *
 *  Created on: Oct 23, 2024
 *      Author: doria
 */

#ifndef INC_RINGBUFFER_H_
#define INC_RINGBUFFER_H_

#include <stdint.h>
#include <stdbool.h>

// ring buffer structure
typedef struct{
	volatile uint8_t* buffer;
	uint32_t mask;
	uint32_t readIndex;
	uint32_t writeIndex;
} ring_buffer_t;


//Inicialization of ring buffer
void ring_buffer_setup(volatile ring_buffer_t* rb, volatile uint8_t* buffer, uint32_t size);
//checks if ring buffer empty
bool ring_buffer_empty(volatile ring_buffer_t* rb);
//write to ring buffer
bool ring_buffer_write(volatile ring_buffer_t* rb, uint8_t byte);
//read ring buffer
bool ring_buffer_read(volatile ring_buffer_t* rb, uint8_t* byte);


#endif /* INC_RINGBUFFER_H_ */
