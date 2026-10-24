# Cocoa Engine

Cocoa is a work-in-progress game engine I'm building from scratch in modern C++, with a custom renderer at its core.

The project started as a way to explore graphics programming and better understand what goes into building a game engine. Rather than relying on an existing engine, I wanted to build the underlying systems myself, learn how they work, and make my own architectural decisions along the way.

Cocoa is currently focused on 2D rendering, with plans to expand into 3D graphics in the future.

## Current Features

The engine is being developed incrementally. Some of the functionality implemented so far includes:

- Custom OpenGL 2D renderer with batched drawing
- Texture, shader, sprite, and material management
- Entity Component System (ECS)
- Scene cameras and orthographic projection
- Sprite layering, sorting, and blending
- Asset loading and resource management
- Graphics device abstraction
- Unit testing with GoogleTest
- Benchmark testing with GoogleBenchmark

The repository also includes a Sandbox application for experimenting with and validating engine features as they're developed.

## Technology

Cocoa is written in modern C++ and uses:

- **OpenGL** — Graphics rendering
- **GLFW / GLEW** — Windowing, OpenGL context, and extension loading
- **CMake / vcpkg** — Build system and dependency management
- **GoogleTest** — Automated testing
- **GoogleBenchmark** — Benchmark testing

The engine is organized into independent subsystems, keeping rendering, assets, scenes, and other functionality separated.

## Building Cocoa

Cocoa currently supports development on Windows and Linux.

**Prerequisites**

- CMake 3.20+
- A C++ compiler
- Git
- OpenGL development support

**Windows**

Run the setup script to install dependencies:

`setup.bat`

Configure and build:

```bash
cmake --preset windows
cmake --build --preset windows
```

**Linux (Ubuntu-based distributions)**

Run the setup script:

```bash
./setup.sh
```

Configure and build:

```bash
cmake --preset linux-debug
cmake --build --preset linux-debug
```

## Learning Resources

Much of Cocoa's development is guided by studying graphics programming, rendering techniques, and game engine architecture.

Some of the resources I'm using include:

- **LearnOpenGL** — Joey de Vries
- **Real-Time Rendering** — Tomas Akenine-Möller, Eric Haines, Naty Hoffman, and others
- **Foundations of Game Engine Development, Volume 2: Rendering** — Eric Lengyel

These resources provide the theory and techniques that I explore and implement within Cocoa.

---

Cocoa is a personal project and is still in active development. The goal isn't to rush toward a feature-complete engine, but to build something useful while continuing to improve my understanding of graphics programming and engine development.
