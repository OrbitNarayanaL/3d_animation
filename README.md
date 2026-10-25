# 3D Character Creation Software

A high-performance desktop-based 3D Character Creation Software application built with a hybrid C++/Python architecture. Designed for professional digital content creation with real-time mesh manipulation, parametric character customization, rigging, and PBR material previewing.

## Features

- **High-Performance Rendering**: C++ core with modern OpenGL for real-time 3D visualization
- **Intuitive UI**: Professional Qt/PySide docking-panel interface for DCC workflows
- **Scripting & Automation**: Python API for automating rigging and creating custom tools
- **Mesh Manipulation**: Vertex, edge, face selection with sculpting brushes (Smooth, Grab, Inflate)
- **Parametric Character Creation**: Real-time blendshape/morph target system driven by UI sliders
- **Rigging System**: Joint/bone creation with Forward Kinematics (FK) and Inverse Kinematics (IK)
- **PBR Materials**: Physically Based Rendering with support for Albedo, Normal, and Roughness maps
- **File I/O**: Import/export support for .OBJ and .FBX formats (mesh, UVs, bone hierarchies)

## Directory Structure

```
3d_animation/
├── CMakeLists.txt              # Top-level CMake build configuration
├── README.md                   # Project documentation
├── status.md                   # Project tracking and milestone status
├── cmake/                      # Custom CMake modules
├── deps/                       # External dependencies
│   └── glad/                   # OpenGL function loader (GLAD)
├── src/                        # C++ source code
│   ├── core/                   # Core engine components
│   │   ├── Application.cpp
│   │   ├── Application.h
│   │   ├── Window.cpp
│   │   ├── Window.h
│   │   ├── Renderer.cpp
│   │   └── Renderer.h
│   ├── bindings/               # Python bindings (pybind11)
│   │   └── pybind_module.cpp
│   └── ui_bridge/              # C++ UI integration helpers
├── python/                     # Python application layer
│   ├── app.py
│   ├── ui/
│   │   ├── main_window.py
│   │   └── panels/
│   │       ├── viewport.py
│   │       ├── sliders.py
│   │       ├── outliner.py
│   │       └── materials.py
│   └── api/
│       └── __init__.py
├── shaders/                    # GLSL shader programs
│   ├── basic.vert
│   └── basic.frag
├── thirdparty/                 # Third-party libraries
│   ├── glfw/
│   ├── glm/
│   └── pybind11/
└── tests/                      # Unit and integration tests
```

## Prerequisites

### Required Software
- Microsoft Visual Studio 2022 (or later) with MSVC v143+ and C++ Desktop Development workload
- CMake 3.20+
- Python 3.10+
- OpenGL 3.3+ compatible graphics drivers

### Required Python Packages
- PySide6
- numpy (optional)

### Required C++ Dependencies
- GLFW - Windowing and input
- GLAD - OpenGL function loader
- GLM - OpenGL Mathematics
- pybind11 - Python/C++ bindings

## Build Instructions

### 1. Clone the Repository
```bash
git clone <repository-url>
cd 3d_animation
```

### 2. Initialize Submodules
```bash
git submodule update --init --recursive
```

### 3. Set Up Python Environment
```bash
python -m venv venv
venv\Scripts\activate
pip install PySide6 numpy
```

### 4. Configure and Build with CMake
```bash
mkdir build
cd build
cmake .. -G "Visual Studio 17 2022" -A x64 -DCMAKE_BUILD_TYPE=Release
cmake --build . --config Release
```

### 5. Run the Application
```bash
venv\Scripts\activate
python python/app.py
```

## Architecture Notes

- **Rendering**: OpenGL 3.3+ Core Profile with GLAD for function loading
- **UI**: PySide6 provides the Qt6-based docking interface
- **Integration**: QOpenGLWidget manages the OpenGL context and integrates with Qt's event loop. The C++ renderer is exposed via pybind11.
- **Performance**: Core rendering/mesh operations in C++, UI/scripting in Python.
