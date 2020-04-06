#include "core.h"

#include <stdint.h> // uint16_t
#include <stdio.h>  // FILE
#include <signal.h> // SIGINT
/* windows only */
#include <Windows.h>
#include <conio.h>  // _kbhit

HANDLE hStdin = INVALID_HANDLE_VALUE;

uint16_t checkKey()
{
    return WaitForSingleObject(hStdin, 1000) == WAIT_OBJECT_0 && _kbhit();
}

void updateFlags(uint16_t r) {
    if (registers[r] == 0) {
        registers[R_COND] = FL_ZRO;
    }
    else if (registers[r] >> 15) {
        registers[R_COND] = FL_NEG;
    }
    else {
        registers[R_COND] = FL_POS;
    }
}

void memWrite(uint16_t address, uint16_t val) {
    memory[address] = val;
}

uint16_t memRead(uint16_t address) {
    if (address == MR_KBSR) {
        if (checkKey()) {
            memory[MR_KBSR] = (1 << 15);
            memory[MR_KBDR] = getchar();
        }
        else {
            memory[MR_KBSR] = 0;
        }

    }
    return memory[address];
}