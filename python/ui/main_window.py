from PySide6.QtWidgets import QMainWindow, QDockWidget, QMenuBar, QFileDialog
from PySide6.QtCore import Qt
from .panels.viewport import ViewportPanel
from .panels.sliders import SlidersPanel
from .panels.outliner import OutlinerPanel
from .panels.materials import MaterialsPanel
import sys
import os

try:
    sys.path.append(os.path.join(os.path.dirname(__file__), '..', 'api'))
    import renderer
    NATIVE_AVAILABLE = True
except Exception:
    NATIVE_AVAILABLE = False


class MainWindow(QMainWindow):
    def __init__(self):
        super().__init__()
        self.setWindowTitle("3D Character Creation Software - Dev Sandbox")
        self.resize(1280, 720)
        
        # Central Viewport Widget
        self.viewport = ViewportPanel(self)
        self.setCentralWidget(self.viewport)
        
        # Menu Bar
        self.create_menu_bar()
        
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
        self.materials_panel = MaterialsPanel(self, viewport_panel=self.viewport)
        self.materials_dock.setWidget(self.materials_panel)
        self.addDockWidget(Qt.BottomDockWidgetArea, self.materials_dock)
        
        try:
            if hasattr(self.viewport, 'cpp_renderer') and self.viewport.cpp_renderer:
                skel = self.viewport.cpp_renderer.skeleton
                self.outliner_panel.populate_skeleton(skel)
        except Exception as e:
            print(f"Outliner init error: {e}")
    
    def create_menu_bar(self):
        menu_bar = self.menuBar()
        file_menu = menu_bar.addMenu("File")
        
        save_action = file_menu.addAction("Save Project Sandbox Scene")
        save_action.triggered.connect(self.save_scene)
        
        load_action = file_menu.addAction("Load Project Sandbox Scene")
        load_action.triggered.connect(self.load_scene)
        
        export_action = file_menu.addAction("Export Current Mesh to .OBJ File")
        export_action.triggered.connect(self.export_mesh)
    
    def save_scene(self):
        if not NATIVE_AVAILABLE:
            return
        file_path, _ = QFileDialog.getSaveFileName(self, "Save Scene", "", "Scene Files (*.scene)")
        if file_path:
            try:
                albedo = [0.8, 0.5, 0.2]
                renderer.save_scene(file_path, 0.5, 0.0, albedo)
            except Exception as e:
                print(f"Error saving: {e}")
    
    def load_scene(self):
        if not NATIVE_AVAILABLE:
            return
        file_path, _ = QFileDialog.getOpenFileName(self, "Load Scene", "", "Scene Files (*.scene)")
        if file_path:
            try:
                albedo = [0.0, 0.0, 0.0]
                rough = 0.5
                metal = 0.0
                renderer.load_scene(file_path, rough, metal, albedo)
                if hasattr(self.viewport, 'cpp_renderer') and self.viewport.cpp_renderer:
                    self.viewport.cpp_renderer.set_roughness(rough)
                    self.viewport.cpp_renderer.set_metalness(metal)
                    self.viewport.cpp_renderer.set_albedo_color(albedo)
                    self.viewport.update()
            except Exception as e:
                print(f"Error loading: {e}")
    
    def export_mesh(self):
        if not NATIVE_AVAILABLE:
            return
        file_path, _ = QFileDialog.getSaveFileName(self, "Export Mesh", "", "OBJ Files (*.obj)")
        if file_path:
            try:
                if hasattr(self.viewport, 'cpp_renderer') and self.viewport.cpp_renderer:
                    mesh = self.viewport.cpp_renderer.mesh
                    renderer.export_mesh_to_obj(file_path, mesh)
            except Exception as e:
                print(f"Error exporting: {e}")
