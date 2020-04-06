
#include <stdint.h> // uint16_t
#include <stdio.h>  // FILE
#include <signal.h> // SIGINT
/* windows only */
#include <Windows.h>
#include <conio.h>  // _kbhit

#include "inputBuffering.h"


HANDLE hfStdin = INVALID_HANDLE_VALUE;
DWORD fdwMode, fdwOldMode;

void disableInputBuffering() {
	hfStdin = GetStdHandle(STD_INPUT_HANDLE);
	GetConsoleMode(hfStdin, &fdwOldMode);
	fdwMode = fdwOldMode ^ ENABLE_ECHO_INPUT ^ ENABLE_LINE_INPUT;
	SetConsoleMode(hfStdin, fdwMode);
	FlushConsoleInputBuffer(hfStdin);

}

void restoreInputBuffering() {
	SetConsoleMode(hfStdin, fdwOldMode);
}

void handleInterupt(int signal) {
	restoreInputBuffering();
	printf("\n");
	exit(-2);
}

