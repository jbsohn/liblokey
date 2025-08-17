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

**libLOKEY** is a lightweight, modern C++ POKEY library with a reusable audio sink layer. It’s designed for use in
games, tools, and embedded projects.

It provides:

- 🎛️ Real-time SDL test harness for tone verification
- 🔊 Audio sink abstraction (`lokey::audio`) with SDL, Pico GPIO/PWM, and Null sinks
- 🧪 Instance-based POKEY API (`lokey::pokey`) for one or more chips
- 🛠 Clean CMake targets: `lokey::audio` and `lokey::pokey`

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

An iconic app startup sound was extracted using our custom fork of the open-source JS7800 emulator, which allowed us to
log POKEY register writes and reproduce authentic sound sequences on the Pico.

Our recording-enabled JS7800 fork is available at:

https://github.com/jbsohn/js7800/tree/lokey-record

Special thanks to the JS7800 devs—modifying a JavaScript emulator to log POKEY data was way easier (and more fun) than
wrestling with native code!

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

## 🎛️ POKEY Implementations

libLOKEY supports **two** POKEY cores, selectable at build or runtime:

- **ProSystem POKEY** *(default for RP2040)*:  
  Compact, integer-based, and ideal for embedded use.

- **Atari800 POKEY** *(desktop/test)*:  
  Feature-complete, long-standing reference implementation.

---

## 🧱 Architectural Overview

- **Two targets:**
    - `lokey::audio` → SDL/Pico sinks (no chip code)
    - `lokey::pokey` → POKEY engine (depends on `lokey::audio`)

- **Strategy:** Multiple sink backends; multiple POKEY cores behind a common API.

- **Bridge:** Platform audio details decoupled from chip emulation for easy cross-platform use.

*(Higher-level orchestration lives in consumer projects like `lokey-7800`.)*

---

## 🫡 Acknowledgments

`libLOKEY` uses POKEY sound emulation code from:

- **Atari800 project** — GPLv2  
  https://github.com/atari800/atari800  
  https://www.gnu.org/licenses/old-licenses/gpl-2.0.html

- **OpenEmu ProSystem Core** — GPLv2  
  https://github.com/OpenEmu/ProSystem-Core  
  https://www.gnu.org/licenses/old-licenses/gpl-2.0.html

We express deep appreciation to the original authors and maintainers of these projects. Their reverse engineering work
makes `libLOKEY` possible.

We don’t want to make a POKEY emulator when everyone else has already made a good one.
libLOKEY’s goal is to offer a clean, portable audio engine and toolkit—not to reinvent the POKEY wheel.

---

## AI-Assisted Development

This project wouldn’t exist—at least not as a one-person, evenings-and-weekends effort—without practical help from AI
tools. ChatGPT and related assistants made it possible to tackle firmware, C++ refactors, embedded hardware, and
documentation at a solo-friendly pace.

More thoughts here:  
👉 [What AI Is Doing to Software Development](https://johnsmusicandtech.com/posts/what-ai-is-doing-to-software-development/)

---

## 🚧 Status

ProSystem and Atari 800 cores runs on RP2040 via PWM sink. Atari800 and ProSystem cores validated on desktop via SDL.

