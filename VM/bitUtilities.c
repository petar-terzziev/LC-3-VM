#include "bitUtilities.h"

// Big Endian to little endian 
uint16_t swap16(uint16_t x) {
	return (x << 8) | (x >> 8);
}

uint16_t signExtend(uint16_t x, int bitCount) {
	if ((x >> (bitCount - 1)) & 1) {
		x |= (0xFFFF << bitCount);
	}
	return x;
}