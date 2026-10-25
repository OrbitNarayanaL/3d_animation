# Project Status Tracking

## Current Milestone: Step 2 (Mesh Loading & Manipulation)

### Deliverables Checklist

#### Step 2 Tasks
- [x] **OBJ mesh import functionality** - Mesh data structure with LoadOBJ parser implemented
- [ ] Vertex, edge, and face selection system
- [ ] Basic mesh deformation framework
- [ ] Sculpting brush implementation (Smooth, Grab, Inflate)
- [ ] Mesh data structures and GPU buffer management (Enhanced)

### Previous Milestones
#### Step 1 (Window, Renderer, PySide Docking, and Bindings) - Completed
- [x] **1. CMake build (top-level)** - Builds C++ core + pybind11 module
- [x] **2. `src/core/Window`** - GLFW init, OpenGL context, resize handling
- [x] **3. `src/core/Renderer`** - VAO/VBO setup, simple shader compilation, clear/draw operations
- [x] **4. `src/bindings/pybind_module.cpp`** - pybind11 bindings exposing `Renderer` and `Window` classes
- [x] **5. `shaders/basic.*`** - Basic vertex and fragment shaders (Completed)
- [x] **6. `python/app.py`** - PySide application bootstrap and entry point
- [x] **7. `python/ui/main_window.py`** - QMainWindow with QDockWidget layout (Viewport, Sliders, Outliner, Materials)
- [x] **8. `python/ui/panels/viewport.py`** - Viewport panel embedding OpenGL via QOpenGLWidget
- [x] **9. `README.md`** - Build/run instructions and project documentation (Completed)

## Architectural Overview

### GLAD for OpenGL Function Loading
We have chosen **GLAD** over GLEW as the OpenGL loader for the following reasons:
- **Modern OpenGL Support**: GLAD is generated per-specification allowing precise control over which OpenGL versions and extensions are loaded
- **Core Profile Focus**: Better suited for modern OpenGL 3.3+ Core Profile development without legacy compatibility baggage
- **Smaller Footprint**: GLAD generates only the function pointers needed, reducing overhead
- **Active Maintenance**: GLAD's web-based generator stays current with OpenGL specifications
- **Ease of Integration**: Simple to integrate into CMake build system without complex configuration

### PySide6 for Qt Bindings
We have chosen **PySide6** (Qt6 bindings) over PySide2 for the following reasons:
- **Modern Qt Version**: Access to the latest Qt6 features, improved performance, and better high-DPI support
- **Long-term Support**: Qt6 is the current supported version with active development
- **Better API**: Improved type hints, better cross-platform consistency, and enhanced graphics integration
- **OpenGL Integration**: Superior support for QOpenGLWidget and modern graphics APIs
- **Licensing**: LGPL licensed, same as PySide2, suitable for commercial and open-source use

### QOpenGLWidget Wrapping the C++ Rendering Context
The 3D viewport is implemented using **QOpenGLWidget** which wraps and manages the C++ rendering context as follows:
- **Context Management**: QOpenGLWidget creates and manages an OpenGL context that is shared with Qt's rendering pipeline, ensuring proper synchronization
- **Integration**: It seamlessly integrates with Qt's event system (mouse, keyboard, resize events) allowing for natural interaction within the docking interface
- **C++ Bridge**: The widget's `initializeGL()`, `paintGL()`, and `resizeGL()` methods call into our C++ Renderer class (exposed via pybind11 bindings), delegating actual rendering to the high-performance C++ core
- **Thread Safety**: Qt's OpenGL widget handling ensures the context is made current on the correct thread before rendering operations
- **Resource Sharing**: Allows efficient sharing of OpenGL resources between the C++ engine and Qt's rendering infrastructure

## Upcoming Milestones

### Step 3: Parametric Slider System & Blendshapes
- [ ] Blendshape/morph target data structure
- [ ] Slider UI panel implementation with real-time updates
- [ ] Morph target interpolation and blending
- [ ] Predefined parametric controls (Height, Weight, Muscle, Face Width)
- [ ] Real-time geometry updates on slider changes

### Step 4: Rigging & Skeleton System
- [ ] Joint/bone creation and manipulation tools
- [ ] Skeleton hierarchy and parenting system
- [ ] Forward Kinematics (FK) solver
- [ ] Inverse Kinematics (IK) solver (basic implementation)
- [ ] Character posing interface
- [ ] Bone visualization

### Step 5: Material/Texture Viewer & PBR Shaders
- [ ] PBR shader implementation (Albedo, Normal, Roughness, Metalness)
- [ ] Texture loading (PNG, JPG, TGA)
- [ ] Material system and property editor
- [ ] UV mapping visualization
- [ ] Real-time material preview

### Step 6: File I/O & Polish
- [ ] FBX import/export support (using OpenFBX or Assimp)
- [ ] Enhanced OBJ support with materials (MTL)
- [ ] Scene save/load functionality
- [ ] UI polish and theming
- [ ] Performance optimizations
- [ ] Documentation and user guide
