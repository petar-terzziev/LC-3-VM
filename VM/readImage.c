#include <stdio.h>
#include <stdint.h>

#include "bitUtilities.h"
#include "readImage.h"




void readImageFile(FILE* file, uint16_t memory[]) {
	printf("READ IMAGE FILE\n ");

	uint16_t origin;
	fread(&origin, sizeof(origin), 1, file);

	origin = swap16(origin);

	uint16_t maxRead = UINT16_MAX - origin;
	uint16_t* program = memory + origin;
	size_t read = fread(program, sizeof(uint16_t), maxRead, file);

	while (read-- > 0) {
		*program = swap16(*program);
		++program;

	}
}

int readImage(const char* imagePath, uint16_t memory[]) {
	
	printf("READ IMAGE FILE\n");

	FILE* file = fopen(imagePath, "rb");

	if (!file) {
		return 0;
	}

	readImageFile(file, memory);
	fclose(file);
	return 1;
}