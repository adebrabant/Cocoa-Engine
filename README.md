
# Project Vexxus

PixelPad is a drawing application built with C++ that follows a Test-Driven Development (TDD) approach. The application provides services to manipulate a canvas, including drawing pixels, lines, and shapes, resizing the canvas, and filling or clearing the canvas. It uses a layered architecture with well-defined services and models.

## Architecture Overview

### Layers
- **Core Layer**: Contains the base functionality, including the `Canvas` class, which represents the canvas and handles pixel manipulation.
- **Application Layer**: Implements services like `DrawService`, which interacts with the `Canvas` to execute drawing operations, such as drawing pixels or lines.
- **Infrastructure Layer**: Contains utilities and helper classes to support the core and application layers.
- **Presentation Layer**: Serves as the UI layer and main entry point of the application. It includes the main() function, initializes the rendering window, processes user input (keyboard, mouse), and renders the canvas to the screen using services and models from the Application and Core layers.

### Test-Driven Development (TDD) Approach

PixelPad follows a TDD-first mindset, meaning tests are written before code. Each method of the `DrawService` class (and others) is thoroughly tested, starting with simple unit tests and expanding to edge cases and integration tests. The tests ensure that the drawing logic behaves as expected in various scenarios.

### Setting Up the Project

#### Prerequisites
To get started, you need the following installed:
- **CMake** (version 3.20 or higher)
- **Visual Studio** (or another C++ compiler)
- **Git** (optional, for cloning the repository)

#### Setting Up the Project

1. Clone the repository (if you haven't already).
2. Run the `setup.bat` file to install dependencies and configure the project environment. This script handles the installation of `vcpkg` and the necessary dependencies defined in `vcpkg.json`.
3. Once the dependencies are installed, use the following CMake command to configure the project:

   ```bash
   cmake --preset default
   ```

   This will configure the project with the default settings.

4. To build the project, run:

   ```bash
   cmake --build --preset default
   ```
5. Open in Visual Studio: After building, you can open the generated solution in Visual Studio:

   ```bash
   start build\PixelPad.sln
   ```

## Features

- **Draw Pixel**: Draw individual pixels on the canvas with specified coordinates and colors.
- **Draw Line**: Draw lines between two points with a specified color.
- **Resize Canvas**: Dynamically resize the canvas to the desired width and height.
- **Fill Canvas**: Fill the entire canvas with a specific color.
- **Clear Canvas**: Clear the canvas and reset all pixels.
- **Get Pixel**: Retrieve the color of a specific pixel on the canvas.

## Testing

The project follows TDD, and all core functionality is thoroughly tested. Tests are written using Google Test (GTest), and they ensure that the methods behave correctly in a variety of scenarios, including edge cases.

## Project Structure

```plaintext
PixelPad/
├── Application/
│   ├── src/
│   └── include/
├── Core/
│   ├── src/
│   └── include/
├── Infrastructure/
│   ├── src/
│   └── include/
├── Presentation/
│   ├── src/
│   └── include/
├── CMakeLists.txt
├── CMakePresets.json
├── setup.bat
├── vcpkg.json
├── README.md
└── tests/
    ├── Application.Tests/
    ├── Core.Tests/
    └── Infrastructure.Tests/
```