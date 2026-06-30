# Cocoa Engine

**Cocoa Engine** is a C++ ECS-based 2D game engine focused on rendering architecture, asset management, reusable engine systems, and clear separation between simulation, rendering, and gameplay-facing logic.

The goal of this project is to build a small but real engine from the ground up while developing the systems that sit underneath a 2D game or editor workflow.

## Project Overview

Cocoa Engine is not a game-specific codebase. The engine is designed as a reusable C++ framework with a sandbox application used to test and validate engine features as they are developed.

```plaintext
Cocoa Engine = full repository / engine project
Cocoa        = reusable engine library
Sandbox      = testbed application for exercising the engine
```

The sandbox exists to prove that engine systems work together without coupling the engine directly to one game.

## Project Goals

- Build a custom C++ 2D game engine
- Use OpenGL for rendering
- Keep reusable engine code separate from sandbox/application code
- Build reusable systems for rendering, input, assets, scenes, and ECS
- Use handles and managers for resource ownership
- Support testable engine systems where practical
- Grow the engine incrementally without over-engineering early systems

## Technical Stack

- C++
- CMake
- OpenGL
- GLFW
- GLEW
- GoogleTest
- JSON-based asset metadata
- Custom ECS, rendering, asset, and resource systems

## Current Focus

The current focus is building the foundation of the engine:

- Application lifecycle
- Window creation
- OpenGL context setup
- Graphics device abstraction
- Basic renderer commands
- Renderer2D architecture
- Texture, shader, and material managers
- Asset metadata and resource loading
- Input handling
- Scene and entity structure
- ECS-driven rendering direction

## Engine Architecture

Cocoa Engine is organized around reusable engine systems that can be composed by a sandbox or future game/editor layer.

```plaintext
Sandbox Application
   ↓
Scene / ECS
   ↓
Renderer2D
   ↓
Material / Shader / Texture Managers
   ↓
GraphicsDevice
   ↓
OpenGL Backend
```

The engine is being built around clear ownership boundaries:

- Scene and ECS systems describe what exists
- Render systems decide what should be drawn
- Renderer2D converts draw requests into commands
- Managers own reusable resources like textures, shaders, and materials
- GraphicsDevice hides the low-level graphics backend

## Asset Pipeline

The asset pipeline is designed around stable resource IDs and metadata instead of passing raw file paths throughout the engine.

Target flow:

```plaintext
Resource ID
   ↓
AssetDatabase metadata lookup
   ↓
AssetSource reads bytes
   ↓
AssetManager loads image/shader source
   ↓
TextureManager / ShaderManager create GPU resources
   ↓
MaterialManager combines shader + texture + material data
   ↓
Renderer2D draws using MaterialHandle
```

This keeps asset lookup, file loading, GPU resource creation, and rendering responsibilities separated.

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
start build\CocoaEngine.sln
```

## Project Structure

```plaintext
Cocoa-Engine/
├── Cocoa/
│   ├── include/
│   └── src/
│       ├── Assets/
│       ├── Chronos/
│       ├── Core/
│       ├── ECS/
│       ├── Graphics/
│       │   └── OpenGL/
│       ├── Inputs/
│       ├── Platforms/
│       └── Scenes/
├── Sandbox/
│   ├── include/
│   ├── src/
│   └── Assets/
├── Cocoa.Tests/
├── CMakeLists.txt
├── CMakePresets.json
├── setup.bat
├── vcpkg.json
└── README.md
```

## Current Status

Cocoa Engine is in active development.

The main goal right now is to build a solid 2D engine foundation with C++, OpenGL, ECS, asset management, Renderer2D, and clear separation between reusable engine code and sandbox/application code.

The project is intentionally being developed incrementally, with each system added as the engine needs it rather than trying to design the entire engine upfront.
