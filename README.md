# 3D Character Creation Software

A high-performance desktop-based 3D Character Creation Software application built with a hybrid C++/Python architecture. Designed for professional digital content creation with real-time mesh manipulation, parametric character customization, rigging, and PBR material previewing.

## Features

- **High-Performance Rendering**: C++ core with modern OpenGL for real-time 3D visualization using indexed element drawing arrays (`glDrawElements`).
- **3D Selection Engine**: Implements the high-speed Möller-Trumbull Ray-Triangle Intersection algorithm for precise vertex component selection from screen space.
- **Dynamic Mesh Sculpting**: Native 3D sculpt brush systems with customizable soft falloff tracking for three distinct editing states:
  * **Inflate**: Volumetric extrusion pushing vertices outward directly along accumulated local surface normals.
  * **Smooth**: Multi-neighbor vertex spatial filtering to flatten or reduce geometric sharp noise artifacts.
  * **Grab**: Linear and quadratic soft-selection screen drag translation matching mouse pointer velocity deltas.
- **Dynamic GPU Streaming**: High-efficiency VBO updates leveraging optimized sub-resource data writing blocks (`glBufferSubData`) and fully multi-threaded automatic surface normal recalculation engines.
- **Intuitive UI Layout**: Professional Qt/PySide docking-panel interface for Digital Content Creation (DCC) workspaces.
- **Scripting & Automation Layer**: Embedded Python API via optimized pybind11 translation structures exposing vertex layouts and rendering parameters.
- **Parametric Character Customization**: *[In Progress]* Blendshape/morph target interpolation architectures.
- **Rigging & Skeletons**: *[Upcoming]* Joint hierarchical graphs incorporating Forward/Inverse Kinematics (FK/IK) solvers.

## Directory Structure

```
3d_animation/
├── CMakeLists.txt              # Top-level CMake build configuration
├── README.md                   # Project documentation
├── status.md                   # Project tracking and milestone status
├── cmake/                      # Custom CMake modules
├── deps/                       # External dependencies
│   └── glad/                   # Custom generated core profile OpenGL function loader
├── src/                        # C++ source engine codebase
│   ├── core/                   # Subsystem modules
│   │   ├── Application.cpp/.h  # App state controller
│   │   ├── Window.cpp/.h       # GLFW context manager
│   │   ├── Renderer.cpp/.h     # Element buffer rendering calls
│   │   ├── Mesh.cpp/.h         # OBJ parser, brush operations, and vertex attributes
│   │   └── Selection.cpp/.h    # Ray-casting intersection calculations
│   └── bindings/               # Python translation modules
│       └── pybind_module.cpp   # pybind11 module bindings mapping core types
└── python/                     # Frontend and runtime script application paths
    ├── app.py                  # PySide Application entry loop
    └── ui/                     # Layout definitions
        ├── main_window.py      # QMainWindow dock layouts
        └── panels/             # Panel modules
```

## Prerequisites

### Required Software
- Microsoft Visual Studio 2022 with Desktop C++ workloads
- CMake 3.20+
- Python 3.10+ (with PySide6 and numpy)
- OpenGL 3.3+ Core Profile graphics drivers

## Build and Run Instructions

### 1. Set Up Python Environment
```bash
python -m venv venv
venv\Scripts\activate
pip install PySide6 numpy
```

### 2. Configure and Build the Core C++ Binary (.pyd)
```bash
mkdir build
cd build
cmake .. -G "Visual Studio 17 2022" -A x64 -DCMAKE_BUILD_TYPE=Release
cmake --build . --config Release
```

### 3. Start the Interactive Sandbox Workspace
```bash
cd ..
venv\Scripts\activate
python python/app.py
```
