from PySide6.QtWidgets import QWidget, QVBoxLayout, QFormLayout, QLabel, QSlider, QPushButton
from PySide6.QtCore import Qt
from PySide6.QtGui import QColor


class MaterialsPanel(QWidget):
    def __init__(self, parent=None, viewport_panel=None):
        super().__init__(parent)
        self.viewport_panel = viewport_panel
        self.layout = QVBoxLayout(self)
        self.layout.addWidget(QLabel("Material / PBR Texture Viewer"))
        
        form_layout = QFormLayout()
        
        # Albedo Color
        self.color_btn = QPushButton("Albedo Color")
        self.color_btn.clicked.connect(self.change_albedo_color)
        form_layout.addRow(QLabel("Albedo"), self.color_btn)
        
        # Roughness
        self.roughness_slider = QSlider(Qt.Horizontal)
        self.roughness_slider.setRange(0, 100)
        self.roughness_slider.setValue(50)
        self.roughness_slider.valueChanged.connect(self.on_roughness_changed)
        form_layout.addRow(QLabel("Roughness"), self.roughness_slider)
        
        # Metalness
        self.metalness_slider = QSlider(Qt.Horizontal)
        self.metalness_slider.setRange(0, 100)
        self.metalness_slider.setValue(0)
        self.metalness_slider.valueChanged.connect(self.on_metalness_changed)
        form_layout.addRow(QLabel("Metalness"), self.metalness_slider)
        
        self.layout.addLayout(form_layout)
        
    def change_albedo_color(self):
        if self.viewport_panel and hasattr(self.viewport_panel, 'cpp_renderer') and self.viewport_panel.cpp_renderer:
            try:
                self.viewport_panel.cpp_renderer.set_albedo_color([0.8, 0.3, 0.1])
                self.viewport_panel.update()
            except Exception as e:
                print(f"Error: {e}")
        
    def on_roughness_changed(self, value):
        roughness = value / 100.0
        if self.viewport_panel and hasattr(self.viewport_panel, 'cpp_renderer') and self.viewport_panel.cpp_renderer:
            try:
                self.viewport_panel.cpp_renderer.set_roughness(roughness)
                self.viewport_panel.update()
            except Exception as e:
                print(f"Error: {e}")
        
    def on_metalness_changed(self, value):
        metalness = value / 100.0
        if self.viewport_panel and hasattr(self.viewport_panel, 'cpp_renderer') and self.viewport_panel.cpp_renderer:
            try:
                self.viewport_panel.cpp_renderer.set_metalness(metalness)
                self.viewport_panel.update()
            except Exception as e:
                print(f"Error: {e}")
