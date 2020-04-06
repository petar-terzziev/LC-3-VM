#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <signal.h> 
#include <fcntl.h>

#include <Windows.h>
#include <conio.h>  // _kbhit

#include "instructionSet.h"
#include "core.h"
#include "bitUtilities.h"
#include "inputBuffering.h"
#include "readImage.h"

void fetchExecute() {
	uint16_t instruction = memRead(registers[R_PC]++);
	uint16_t opcode = instruction >> 12;

	switch (opcode) {
	case OP_ADD :
		add(instruction);
		break;
	case OP_AND :
		and(instruction);
		break;
	case OP_NOT :
		not(instruction);
		break;
	case OP_BR :
		branch(instruction);
		break;
	case OP_JMP :
		jump(instruction);
		break;
	case OP_JSR :
		jumpToSubroutine(instruction);
		break;
	case OP_LD :
		load(instruction);
		break;
	case OP_LDI :
		loadIndirect(instruction);
		break;
	case OP_LDR :
		loadRegister(instruction);
		break;
	case OP_LEA :
		loadEffectiveAddress(instruction);
		break;
	case OP_ST :
		store(instruction);
		break;
	case OP_STI :
		storeIndirect(instruction);
		break;
	case OP_STR :
		storeRegister(instruction);
		break;
	case OP_TRAP :
		trap(instruction);
		break;
	case OP_RES :
		abort();
		break;
	case OP_RTI :
		abort();
		break;
	default :
		printf("BAD OPCODE\n");
		break;

	}
}



int main(int argc, const char* argv[]) {
	if (argc < 2) {
		printf("lc3 [image-file1] ...\n");
		exit(2);
	}

	for (int j = 1; j < argc; j++) {
		if (!readImage(argv[j], memory)) {
			printf("Failed to load image : %s \n", argv[j]);
			exit(1);
		}

	}
	signal(SIGINT, handleInterupt);
	disableInputBuffering();

	enum {PC_START = 0x3000};

	registers[R_PC] = PC_START;

	while (1) {
		fetchExecute();
	} 

	restoreInputBuffering();
}