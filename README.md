# libLOKEY

🎧 A portable, embeddable POKEY audio engine for desktop, web, and embedded systems.  
*Also affectionately known as "lokey-pokey" by its creators.*

---

## 🎯 Project Goals and Roadmap

`libLOKEY` is currently in early development. The goal is to create a high-quality, portable POKEY audio engine suitable for:

- SDL2-based desktop tools and games
- WebAssembly builds for browser demos and testing
- Embedded RP2040-based hardware (e.g., Atari 7800 flash cartridges)
- Clean and modern C and C++ APIs
- Modular structure with portable wrappers and test targets

---

## 📦 Planned Platform Support

| Platform     | Planned Support Notes                        |
|--------------|----------------------------------------------|
| 🛠 Linux      | First-class development with CMake + SDL     |
| 🛠 macOS      | Local testing and development                |
| 🛠 Windows    | MinGW/MSVC builds planned                    |
| 🛠 WASM       | WebAssembly builds via Emscripten            |
| 🛠 RP2040     | Embedded output via PWM, DAC, or I2S planned |

---

## 🧩 Planned API Overview

### C API (`lokey.h`)
These functions will form the basic C interface:

```c
void lokey_init(void);
void lokey_write_register(uint8_t addr, uint8_t value);
void lokey_generate_audio(float* out, int frames);
```

### C++ API (`lokey_audio.hpp`)
A modern wrapper for easier integration:

```cpp
lokey::AudioEngine engine;
engine.write(0x0F, 0xAA);
engine.render(buffer, num_frames);
```

---

## 🫡 Acknowledgments

`libLOKEY` uses a modified version of the **POKEY sound emulation code from the [Atari800 project](http://atari800.sourceforge.net/)**.

We want to express our **deep appreciation and respect** to the original authors and maintainers of Atari800. Their outstanding work in preserving and emulating Atari’s 8-bit systems — including the **POKEY chip** — made this project possible. Without their reverse engineering efforts, `libLOKEY` would not exist.

We aim to carry that legacy forward by making their work accessible in modern contexts:

- 🧪 Testable in CI environments  
- 🌐 Runnable in browsers  
- 🔌 Deployable on embedded hardware

### 🧩 About Our Fork

- We have made **minimal and respectful changes** to `pokey.c` and `pokey.h` from the Atari800 source tree
- Global state and platform-specific I/O have been isolated behind **lightweight stubs**
- A clean wrapper (`lokey.c` / `lokey.h`) presents a portable API usable across targets

This structure allows us to track upstream changes more easily while using the core logic as-is.

---

## 📜 Licensing

The POKEY emulation code from Atari800 is licensed under the **GNU General Public License v2**.  
`libLOKEY` maintains compatibility with that license.

- Atari800 project: [http://atari800.sourceforge.net/](http://atari800.sourceforge.net/)
- Full GPLv2 license text: [https://www.gnu.org/licenses/old-licenses/gpl-2.0.html](https://www.gnu.org/licenses/old-licenses/gpl-2.0.html)

See `LICENSE.txt` for more details.

---

## 🚧 Status

This project is under active development. The public API, platform support, and audio output paths are still being built. Expect frequent changes and improvements.

---

Thanks again to the Atari800 team for laying the foundation this project builds on.
