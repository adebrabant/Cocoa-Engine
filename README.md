# Vexxus

**Vexxus** is a 2D game project built in C++ on top of **Cocoa**, a custom reusable game engine/framework.

The goal of this project is to build a real 2D game while developing the engine systems behind it, including rendering, input, scene management, asset management, and core gameplay infrastructure.

## Cocoa Engine

**Cocoa** is the reusable engine layer used by Vexxus.

Cocoa is being designed as a reusable 2D engine/framework, not something tightly coupled to Vexxus. This keeps the engine reusable for future projects while allowing Vexxus to focus on game-specific logic, assets, scenes, and gameplay systems.

```plaintext
Cocoa = engine/framework
Vexxus = game
```

## Project Goals

- Build a custom C++ 2D game engine
- Use OpenGL for rendering
- Keep engine code separate from game code
- Build reusable systems for rendering, input, assets, and scenes
- Use clean architecture principles where they make sense
- Validate the engine by building Vexxus on top of Cocoa

## Current Focus

The current focus is building the foundation of Cocoa:

- Application lifecycle
- Window creation
- OpenGL context setup
- Renderer abstraction
- Basic rendering commands
- Input handling
- Early 2D rendering systems
- Scene and entity structure

## Setting Up the Project

### Prerequisites

- CMake 3.20 or higher
- Visual Studio or another C++ compiler
- Git
- vcpkg dependencies installed through the setup script

### Setup

Run the setup script:

```bash
setup.bat
```

Configure the project:

```bash
cmake --preset default
```

Build the project:

```bash
cmake --build --preset default
```

Open the generated Visual Studio solution:

```bash
start build\Vexxus.sln
```

## Project Structure

```plaintext
Vexxus/
├── Cocoa/
│   ├── Core/
│   ├── Graphics/
│   │   └── OpenGL/
│   ├── Input/
│   ├── Scene/
│   │   └── ECS/
│   └── Math/
├── Vexxus/
│   ├── src/
│   ├── include/
│   └── Assets/
├── tests/
├── CMakeLists.txt
├── CMakePresets.json
├── setup.bat
├── vcpkg.json
└── README.md
```

## Current Status

This project is in active development. The main goal right now is to build a solid 2D engine foundation with C++, OpenGL, and clean separation between the reusable engine code and the Vexxus game code.