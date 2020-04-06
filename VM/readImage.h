#pragma once


#pragma warning(disable:4996)
#include <stdio.h>
#include <stdint.h>



void readImageFile(FILE* file, uint16_t memory[]);
int readImage(const char* imagePath, uint16_t memory[]);