# libLOKEY

🎧 A portable, embeddable POKEY audio engine for desktop, web, and embedded systems.  
*Also affectionately known as "lokey-pokey" by its creator.*

---

## 🕹️ What’s a POKEY?

**POKEY** stands for **POtentiometer and KEYboard** — a custom chip developed at Atari in the late 1970s by **Doug Neubauer** (who also created *Star Raiders*). It handled:

- 4 channels of square wave audio
- Paddle/joystick input
- Keyboard scanning
- Serial I/O and timers

Though originally designed for utility and control tasks, **POKEY became a signature part of the Atari sound** — powering everything from explosions to funky chiptunes.

You'll find POKEY in:

- **Atari 400/800** and **XL/XE** home computers
- **Atari 5200** and **7800** consoles
- Classic **arcade games**, including:
    - *Centipede*, *Millipede*, *Missile Command*, *Tempest*
    - *Food Fight*, *Cloak & Dagger*, *Liberator*, *Juno First* (quad-POKEY!)
    - *Star Wars* and *Return of the Jedi* (with vector audio)

Arcade machines often used **multiple POKEY chips** to create rich, layered audio and increase input resolution — with up to 16 total sound channels.

---

## 🎯 What This Project Does

**libLOKEY** is a lightweight, modern C++ wrapper around the original Atari `pokey.c` sound core.

It provides:

- 🔄 A clean per-instance interface (`PokeyAdapter`)
- 🔊 A mix-ready audio engine (`Lokey`)
- 🎧 Support for rendering audio output with one or more POKEYs
- 🧪 C and C++ APIs for use in games, emulators, audio apps, or embedded platforms (like RP2040)

This project is built for clarity, modularity, and a little nostalgic joy.

---

## 🎵 Iconic POKEY Soundtracks (John's Picks)

Despite its limitations, POKEY delivered some of the most memorable chiptunes of the early gaming era. Two games in particular stand out as personal favorites:

- **🎶 M.U.L.E.**  
  A funky, tempo-shifting theme that’s equal parts charming and ingenious. The music evolves with gameplay, giving each phase of the game its own vibe. An absolute classic.

- **🎶 Ballblazer**  
  Featuring the first procedurally generated video game music, *"Song of the Grid"* mixes jazzy phrases in real-time using clever logic and a single POKEY chip. It’s hypnotic and ahead of its time — truly one of the most iconic Atari soundtracks ever.

Other great uses of POKEY audio include *Electraglide*, *Rescue on Fractalus!*, *The Eidolon*, *Juno First*, and many modern demoscene remixes.

---

## 🎯 Project Goals and Roadmap

`libLOKEY` is currently in early development. The goal is to create a high-quality, portable POKEY audio engine suitable for:

- SDL2-based desktop tools and games
- WebAssembly builds for browser demos and testing
- Embedded RP2040-based hardware (e.g., Atari 7800 flash cartridges)
- A clean and modern **C API** with portable internals
- Modular structure with cross-platform build targets

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

### C++ API (`PokeyAdapter`, `Lokey`)
The preferred interface for working with `libLOKEY` is C++:

```cpp
#include "pokey_adapter.hpp"
#include "lokey.hpp"

PokeyAdapter pokey(sampleRate);
pokey.poke(address, value);
float sample = pokey.render();

Lokey lokey(sampleRate);
lokey.write_register(addr, value);
lokey.render_audio(buffer, frames);
```

Use `PokeyAdapter` for low-level chip emulation or `Lokey` to manage multiple POKEYs and mix output audio into a shared buffer.

---

## 🫡 Acknowledgments

`libLOKEY` uses a modified version of the **POKEY sound emulation code from the [Atari800 project](https://atari800.github.io)**.

We want to express our **deep appreciation and respect** to the original authors and maintainers of Atari800. Their outstanding work in preserving and emulating Atari’s 8-bit systems — including the **POKEY chip** — made this project possible. Without their reverse engineering efforts, `libLOKEY` would not exist.

We aim to carry that legacy forward by making their work accessible in modern contexts:

- 🧪 Testable in CI environments
- 🌐 Runnable in browsers
- 🔌 Deployable on embedded hardware

### 🧩 About Our Fork

- We have made **minimal and respectful changes** to `pokey.c` and `pokey.h` from the Atari800 source tree
- Global state and platform-specific I/O have been isolated behind **lightweight stubs**
- A clean wrapper (`lokey.c` / `lokey.h`) presents a portable C API usable across all targets

This structure allows us to track upstream changes more easily while using the core logic as-is.

---

## 📜 Licensing

The POKEY emulation code from Atari800 is licensed under the **GNU General Public License v2**.  
`libLOKEY` maintains compatibility with that license.

- Atari800 project: [http://atari800.sourceforge.net/](https://atari800.github.io)
- Full GPLv2 license text: [https://www.gnu.org/licenses/old-licenses/gpl-2.0.html](https://www.gnu.org/licenses/old-licenses/gpl-2.0.html)

See `LICENSE.txt` for more details.

---

## 🚧 Status

This project is under active development. The public API, platform support, and audio output paths are still being built. Expect frequent changes and improvements.

---

Thanks again to the Atari800 team for laying the foundation this project builds on.
