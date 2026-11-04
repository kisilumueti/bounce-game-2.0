# Neon Bounce 2.0

A responsive neon arcade runner with a browser-first game client and a portable C/C++ gameplay core. The project is split into small components so the browser experience, native engine and future server-side leaderboard can evolve independently.

## Technology stack

| Layer | Technology | Responsibility |
|---|---|---|
| Browser experience | HTML5, CSS3, JavaScript ES2022 | Canvas rendering, controls, audio, UI and local score history |
| Gameplay engine | C++20 | Deterministic movement, jump physics and simulation state |
| Portable utility | C11 | Deterministic xorshift random-number generator |
| WebAssembly bridge | C++ / Emscripten | Exposes the engine through a stable C ABI |
| Score analysis | Python 3 | Validates and summarizes exported score JSON |\n| Batch audit | COBOL | Processes name,score CSV ledgers in a traditional batch workflow |
| Build and tests | CMake, CTest, GitHub Actions | Native compilation, regression checks and WASM artifact build |

## Play

Open index.html in a modern browser or publish the repository with GitHub Pages. The browser game has no server dependency.

- **Jump:** Space, Arrow Up, W, click or tap.
- **Pause / resume:** P.
- **Restart:** R or the restart control.
- Collect energy fragments, avoid barriers and chain jumps to grow your combo.
- Best score, run count, player callsign and top-five board are saved in this browser using localStorage.
- Use **Export Scores** to download your local score history as JSON.

## Native C++ engine

Requirements: CMake 3.20+ and a C11/C++20 compiler.

    cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
    cmake --build build --parallel
    ctest --test-dir build --output-on-failure
    ./build/bounce_cli

## WebAssembly build

Install and activate the Emscripten SDK, then:

    emcmake cmake -S . -B build-wasm -DCMAKE_BUILD_TYPE=Release -DBUILD_TESTING=OFF
    cmake --build build-wasm --parallel

The WebAssembly module exports a compact C interface: bounce_reset, bounce_jump, bounce_step and state accessors. The browser client remains playable without the generated module; CI builds and uploads the WASM artifact separately.

## Score data and privacy

This version does **not** upload player data. It stores a display name and game scores in the current browser profile only. Clearing browser site data removes those records. Exported JSON is user-controlled and can be audited locally:

    python tools/score_audit.py neon-bounce-scores.json

The optional COBOL utility reads a CSV with one player name and integer score per row (name,score). Compile with a COBOL compiler such as GnuCOBOL: `cobc -x -free tools/score_audit.cob -o score_audit` and run it against that CSV.\n\nA local leaderboard is not a global leaderboard. For fair cross-device competition, add an authenticated API, persistent database, server-authoritative scoring, request throttling, replay/physics validation and abuse monitoring. Never trust a raw score submitted by a browser as proof of a legitimate run.

## Repository layout

    .
    ├── index.html
    ├── styles.css
    ├── game.js
    ├── manifest.json
    ├── service-worker.js
    ├── CMakeLists.txt
    ├── engine/
    │   ├── include/bounce/
    │   ├── src/
    │   └── tests/
    ├── tools/score_audit.py
    └── .github/workflows/quality.yml

## License

MIT. See LICENSE.