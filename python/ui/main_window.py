from PySide6.QtWidgets import QMainWindow, QDockWidget, QTextEdit, QWidget, QVBoxLayout, QLabel
from PySide6.QtCore import Qt
from .panels.viewport import ViewportPanel

class MainWindow(QMainWindow):
    def __init__(self):
        super().__init__()
        self.setWindowTitle("3D Character Creation Software - Dev Sandbox")
        self.resize(1280, 720)
        
        # Central Viewport Widget
        self.viewport = ViewportPanel(self)
        self.setCentralWidget(self.viewport)
        
        # Setup Docking Panels
        self.create_dock("Parametric Sliders", Qt.LeftDockWidgetArea)
        self.create_dock("Outliner / Skeleton Hierarchy", Qt.RightDockWidgetArea)
        self.create_dock("Material & Texture Viewer", Qt.BottomDockWidgetArea)
        
    def create_dock(self, title, area):
        dock = QDockWidget(title, self)
        dock.setAllowedAreas(Qt.LeftDockWidgetArea | Qt.RightDockWidgetArea | Qt.BottomDockWidgetArea)
        
        # Placeholder Inner Widget
        content = QWidget()
        layout = QVBoxLayout(content)
        layout.addWidget(QLabel(f"{title} Control Space Panel"))
        
        dock.setWidget(content)
        self.addDockWidget(area, dock)
