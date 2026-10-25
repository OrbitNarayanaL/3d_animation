from PySide6.QtOpenGLWidgets import QOpenGLWidget
from PySide6.QtCore import Qt
import sys

# Try loading our compiled native C++ binary module
try:
    import renderer
    NATIVE_AVAILABLE = True
except ImportError:
    NATIVE_AVAILABLE = False

class ViewportPanel(QOpenGLWidget):
    def __init__(self, parent=None):
        super().__init__(parent)
        self.cpp_renderer = None
        if NATIVE_AVAILABLE:
            self.cpp_renderer = renderer.Renderer()
        
    def initializeGL(self):
        if self.cpp_renderer:
            self.cpp_renderer.initialize("shaders/basic.vert", "shaders/basic.frag")
            try:
                mesh = self.cpp_renderer.GetMesh() if hasattr(self.cpp_renderer, 'GetMesh') else None
            except Exception:
                pass
            
    def paintGL(self):
        if self.cpp_renderer:
            self.cpp_renderer.clear()
            self.cpp_renderer.render_triangle()
            
    def resizeGL(self, w, h):
        pass
