#include "AverageFilter.h"

uint16_t AverageFilter(uint16_t* data, uint32_t size) {
	uint32_t sum = 0;
	uint16_t max = 0;
	uint16_t min = 0xFFFF;
	
	for (uint32_t i = 0; i < size; i++) {
		sum += data[i];
		if (data[i] > max) max = data[i];
		if (data[i] < min) min = data[i];
	}
	
	sum -= max + min;
	sum = sum / (size - 2);
	return sum;
}
