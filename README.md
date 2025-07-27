# libLOKEY

🎧 A portable, embeddable POKEY audio engine for desktop, web, and embedded systems.  
*Also affectionately known as "lokey-pokey" by its creator.*

---

## 🕹️ What’s a POKEY?

**POKEY** stands for **POtentiometer and KEYboard** — a custom chip developed at Atari in the late 1970s by **Doug
Neubauer** (who also created *Star Raiders*). It handled:

- 4 channels of square wave audio
- Paddle/joystick input
- Keyboard scanning
- Serial I/O and timers

Though originally designed for utility and control tasks, **POKEY became a signature part of the Atari sound** —
powering everything from explosions to funky chiptunes.

You'll find POKEY in:

- **Atari 400/800** and **XL/XE** home computers
- **Atari 5200** and **7800** consoles
- Classic **arcade games**, including:
    - *Centipede*, *Millipede*, *Missile Command*, *Tempest*
    - *Food Fight*, *Cloak & Dagger*, *Liberator*, *Juno First* (quad-POKEY!)
    - *Star Wars* and *Return of the Jedi* (with vector audio)

Arcade machines often used **multiple POKEY chips** to create rich, layered audio and increase input resolution — with
up to 16 total sound channels.

---

## 🎯 What This Project Does

**libLOKEY** is a lightweight, modern C++ wrapper around the original Atari 800 POKEY sound core.

It provides:

- 🎛️ A working real-time SDL-based POKEY test harnesses for tone verification and development
- 🔊 A mix-ready audio engine (`Lokey`)
- 🎧 Support for rendering audio output with one or more POKEYs
- 🧪 C++ APIs for use in games, emulators, audio apps, or embedded platforms (like RP2040)

This project is built for clarity, modularity, and a little nostalgic joy.

---

## 🎵 Iconic POKEY Soundtracks

Despite its limitations, POKEY delivered some of the most memorable chiptunes of the early gaming era. Two games in
particular stand out as personal favorites:

- **🎶 M.U.L.E.**  
  A funky, tempo-shifting theme that’s equal parts charming and ingenious. The music evolves with gameplay, giving each
  phase of the game its own vibe. An absolute classic.

- **🎶 Ballblazer**  
  Featuring the first procedurally generated video game music, *"Song of the Grid"* mixes jazzy phrases in real-time
  using clever logic and a single POKEY chip. It’s hypnotic and ahead of its time — truly one of the most iconic Atari
  soundtracks ever.

Other great uses of POKEY audio include *Electraglide*, *Rescue on Fractalus!*, *The Eidolon*, *Juno First*, and many
modern demoscene remixes.

---

## 🎯 Project Goals and Roadmap

`libLOKEY` has reached its first working milestone. The core POKEY emulation has been integrated with SDL audio and
successfully tested in a real-time environment. The ongoing goal is to build a high-quality, portable POKEY audio engine
suitable for:

- SDL2-based desktop tools and games
- WebAssembly builds for browser demos and testing
- Embedded RP2040-based hardware (e.g., Atari 7800 flash cartridges)
- A clean and modern **C API** with portable internals
- Modular structure with cross-platform build targets

---

## 📦 Planned Platform Support

| Platform   | Planned Support Notes                        |
|------------|----------------------------------------------|
| 🛠 Linux   | First-class development with CMake + SDL     |
| 🛠 macOS   | Local testing and development                |
| 🛠 Windows | MinGW/MSVC builds planned                    |
| 🛠 WASM    | WebAssembly builds via Emscripten            |
| 🛠 RP2040  | Embedded output via PWM, DAC, or I2S planned |

---

## 🧩 Planned API Overview

### C++ API

The preferred interface for working with `libLOKEY` is C++:

```cpp
Lokey lokey;
lokey.start();                              // Start audio playback
lokey.reset();                              // Reset internal state
lokey.poke(PokeyRegister::AUDF1, 0x40);     // Write to a register
lokey.renderAndPlay();                      // Render and play one audio frame
```

---

## 🧱 Architectural Overview

libLOKEY is built using a combination of well-known design patterns to ensure modularity, portability, and testability:

🎭 Facade Pattern

The Lokey class provides a simplified interface for interacting with the entire audio pipeline, hiding lower-level
implementation details of the POKEY chip and audio output:

lokey.poke(…);
lokey.renderAndPlay();

🧩 Strategy Pattern

The core abstractions (Pokey, AudioSink) are defined as interfaces, allowing interchangeable backends like
Atari800Pokey, SDLAudioSink, and (eventually) RP2040Pokey.

🌉 Bridge Pattern

Implementation details (platform-specific audio or chip emulation) are decoupled from the public API. This lets you vary
or extend either side independently — ideal for cross-platform development.

This flexible architecture should allow libLOKEY to:

- Run on desktops, browsers, or embedded systems
- Support test harnesses without changing production code
- Cleanly separate upstream dependencies (like Atari800)

---

## 🫡 Acknowledgments

`libLOKEY` uses a version of the **POKEY sound emulation code from the [Atari800 project](https://atari800.github.io)**.

We want to express our **deep appreciation and respect** to the original authors and maintainers of Atari800. Their
outstanding work in preserving and emulating Atari’s 8-bit systems — including the **POKEY chip** — made this project
possible. Without their reverse engineering efforts, `libLOKEY` would not exist.

We aim to carry that legacy forward by making their work accessible in modern contexts:

- 🧪 Testable in CI environments
- 🌐 Runnable in browsers
- 🔌 Deployable on embedded hardware

### 🧍 About Our Integration

We really didn’t want to write another POKEY emulator — the Atari800 team already did it right. Instead, `libLOKEY` uses the original POKEY sound emulation code from the Atari800 project, with only minimal changes required to support embedded platforms like the RP2040.

#### ⚠️ Fork Notice (Embedded Use Only)

To support real-time playback on constrained hardware (like the Raspberry Pi Pico), we made a **small, isolated fork** of the Atari800 sound code — specifically based on an **older upstream commit (`ec0fecda647a210e25b6cb77def602bce7676fb3`) that still included static FIR filter infrastructure**. While we adapted it slightly to suit embedded constraints, the core logic (including filter design, poly builds, and POKEY state handling) remains almost entirely the work of the **original Atari800 developers**.

Startup performance on embedded platforms was a major reason for this fork. On the Raspberry Pi Pico, the original filter generation code took approximately **3–5 seconds** to complete at boot — unacceptable for real-time applications. By re-enabling and adapting the precomputed FIR filter path from an earlier Atari800 commit, startup is now **virtually instant**.

Key points:

- The embedded fork disables runtime FIR filter generation for instant startup
- All other behavior is preserved exactly as in upstream


## 📜 Licensing

The POKEY emulation code from Atari800 is licensed under the **GNU General Public License v2**.  
`libLOKEY` maintains compatibility with that license.

- Atari800 project: [https://github.com/atari800/atari800/](https://atari800.github.io)
- Full GPLv2 license
  text: [https://www.gnu.org/licenses/old-licenses/gpl-2.0.html](https://www.gnu.org/licenses/old-licenses/gpl-2.0.html)

See `LICENSE.txt` for more details.

---

## 🚧 Status

This project is under active development. The public API, platform support, and audio output paths are still being
built. Expect frequent changes and improvements.

---

Thanks again to the Atari800 team for laying the foundation this project builds on.
