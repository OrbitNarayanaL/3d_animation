# 3D Character Creation Software

A high-performance desktop-based 3D Character Creation Software application built with a hybrid C++/Python architecture. Designed for professional digital content creation with real-time mesh manipulation, parametric character customization, rigging, and PBR material previewing.

## Features

- **High-Performance Rendering**: C++ core with modern OpenGL for real-time 3D visualization using indexed element drawing arrays (`glDrawElements`).
- **3D Selection Engine**: Implements the Möller-Trumbull Ray-Triangle Intersection algorithm for precise vertex/component selection.
- **Dynamic Mesh Sculpting**: Native sculpt brushes with soft falloff - **Inflate**, **Smooth**, and **Grab**. Optimized GPU updates via `glBufferSubData`.
- **Parametric Character Creation**: Blendshape/morph target system with real-time slider controls for Height, Weight, Muscle, Face Width.
- **Rigging & Skeleton System**: Joint/bone hierarchy with Forward Kinematics (FK), skinning vertex attributes, bone visualization, and Python-exposed skeleton API.
- **PBR Materials**: Simplified Cook-Torrance shader with Albedo, Roughness, Metalness controls and UV layout debug visualization.
- **File I/O**: Save/load scene (.scene), export mesh to .OBJ with positions, UVs, normals.
- **Intuitive UI**: PySide6 docking interface with Viewport, Outliner (skeleton tree), Parametric Sliders, Material Editor, and File menu.
- **Scripting & Automation**: Python API via pybind11 exposing mesh, renderer, skeleton, and scene I/O.

## Directory Structure

```
3d_animation/
├── CMakeLists.txt
├── README.md
├── status.md
├── setup_and_run.ps1        # Automated build and run
├── deps/glad/               # OpenGL loader
├── shaders/
│   ├── basic.vert
│   └── basic.frag
├── src/
│   ├── core/                # C++ engine (Window, Renderer, Mesh, Selection, Rigging, SceneIO)
│   └── bindings/            # pybind11 module
├── python/
│   ├── app.py
│   ├── api/                 # Built renderer.pyd goes here
│   └── ui/                  # PySide6 UI (main_window, panels)
└── thirdparty/              # Dependencies (fetched via CMake)
```

## Prerequisites

- **Microsoft Visual Studio 2022** with Desktop C++ workload
- **CMake 3.20+**
- **Python 3.10+**
- **PySide6, numpy** (installed automatically by setup script)
- **OpenGL 3.3+ Core Profile** compatible GPU

## Quick Start

### Automated (Recommended)
```powershell
.\setup_and_run.ps1
```
This will create venv, install deps, configure/build with CMake (VS 2022 x64 Release), and launch the app.

### Manual
```powershell
# Setup environment
python -m venv venv
.\venv\Scripts\activate
pip install PySide6 numpy

# Build
mkdir build; cd build
cmake .. -G "Visual Studio 17 2022" -A x64 -DCMAKE_BUILD_TYPE=Release
cmake --build . --config Release
cd ..

# Run
python python/app.py
```

## Usage

- **Viewport**: 3D view with triangle fallback or loaded mesh
- **Outliner**: View skeleton hierarchy
- **Parametric Controls**: Adjust morph targets (Height/Weight/Muscle/Face Width)
- **Material/Texture Viewer**: Tweak Albedo/Roughness/Metalness, toggle UV debug view
- **File Menu**: Save/Load scene (.scene), Export mesh to .OBJ
- **Sculpting/Selection**: C++ API exposed for selection and brush operations

## Architecture

- **Rendering**: OpenGL 3.3 Core with GLAD, indexed drawing, PBR shader
- **UI**: PySide6/QDockWidget with QOpenGLWidget viewport
- **Bindings**: pybind11 exposes C++ classes (Window, Renderer, Mesh, Skeleton, SceneIO)
- **Data Flow**: Python UI → pybind11 → C++ core → OpenGL
