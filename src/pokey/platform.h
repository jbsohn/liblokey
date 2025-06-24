// platform.h
#pragma once

// PLATFORM Sound
int PLATFORM_SoundSetup(Sound_setup_t *setup);
static void PLATFORM_SoundPause(void);
static void PLATFORM_SoundExit(void);
static void PLATFORM_SoundContinue(void);
static void PLATFORM_SoundLock();
static void PLATFORM_SoundUnlock();
