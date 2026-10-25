from PySide6.QtWidgets import QMainWindow, QDockWidget, QWidget, QVBoxLayout, QLabel
from PySide6.QtCore import Qt
from .panels.viewport import ViewportPanel
from .panels.sliders import SlidersPanel
from .panels.outliner import OutlinerPanel
from .panels.materials import MaterialsPanel


class MainWindow(QMainWindow):
    def __init__(self):
        super().__init__()
        self.setWindowTitle("3D Character Creation Software - Dev Sandbox")
        self.resize(1280, 720)
        
        # Central Viewport Widget
        self.viewport = ViewportPanel(self)
        self.setCentralWidget(self.viewport)
        
        # Left dock - Outliner
        self.outliner_dock = QDockWidget("Outliner", self)
        self.outliner_dock.setAllowedAreas(Qt.LeftDockWidgetArea | Qt.RightDockWidgetArea)
        self.outliner_panel = OutlinerPanel()
        self.outliner_dock.setWidget(self.outliner_panel)
        self.addDockWidget(Qt.LeftDockWidgetArea, self.outliner_dock)

        # Right dock - Sliders (Parametric)
        self.sliders_dock = QDockWidget("Parametric Controls", self)
        self.sliders_dock.setAllowedAreas(Qt.LeftDockWidgetArea | Qt.RightDockWidgetArea)
        self.sliders_panel = SlidersPanel(self, viewport_panel=self.viewport)
        self.sliders_dock.setWidget(self.sliders_panel)
        self.addDockWidget(Qt.RightDockWidgetArea, self.sliders_dock)

        # Bottom dock - Materials
        self.materials_dock = QDockWidget("Material/Texture Viewer", self)
        self.materials_dock.setAllowedAreas(Qt.BottomDockWidgetArea)
        self.materials_panel = MaterialsPanel()
        self.materials_dock.setWidget(self.materials_panel)
        self.addDockWidget(Qt.BottomDockWidgetArea, self.materials_dock)
        
        # Try to populate skeleton if available
        try:
            if hasattr(self.viewport, 'cpp_renderer') and self.viewport.cpp_renderer:
                skel = self.viewport.cpp_renderer.skeleton
                self.outliner_panel.populate_skeleton(skel)
        except Exception as e:
            print(f"Outliner init error: {e}")
