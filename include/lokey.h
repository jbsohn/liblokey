#ifndef LOKEY_H
#define LOKEY_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

void lokey_init(void);
void lokey_write_register(uint8_t addr, uint8_t value);
void lokey_generate_audio(float* out, int frames);

#ifdef __cplusplus
}
#endif

#endif // LOKEY_H
