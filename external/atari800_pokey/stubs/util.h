#pragma once

// This is a stubbed version of the util.h header from the Atari800 project.
// It exists to satisfy include dependencies in pokey.c but does not currently
// contain any functional declarations. Add contents here only if required.

void *Util_malloc(size_t size);

// Utility functions
// static void* Util_malloc(size_t size) { return malloc(size); }
// static int Util_sscanbool(const char *ptr) { return strcmp(ptr, "0") == 0 ? 0 : 1; }
// static int Util_sscandec(const char *ptr) { return atoi(ptr); }
// static int Util_time(void) { return 0; }
//
// #define Util_sleep(x) usleep((int)((x) * 1e6))  // sleep in microseconds