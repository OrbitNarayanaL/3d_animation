from PySide6.QtWidgets import QWidget, QVBoxLayout, QFormLayout, QLabel, QSlider
from PySide6.QtCore import Qt


class SlidersPanel(QWidget):
    def __init__(self, parent=None, viewport_panel=None):
        super().__init__(parent)
        self.viewport_panel = viewport_panel
        self.layout = QVBoxLayout(self)
        self.layout.addWidget(QLabel("Parametric Morph Targets"))
        
        form_layout = QFormLayout()
        
        # Define parametric sliders
        self.sliders = {}
        params = ["Height", "Weight", "Muscle", "Face Width"]
        
        for param in params:
            slider = QSlider(Qt.Horizontal)
            slider.setRange(0, 100)
            slider.setValue(0)
            slider.valueChanged.connect(lambda val, p=param: self.on_slider_changed(p, val))
            form_layout.addRow(QLabel(param), slider)
            self.sliders[param] = slider
        
        self.layout.addLayout(form_layout)
        
    def on_slider_changed(self, param, value):
        # Convert to 0.0 - 1.0 range and pass to C++ bindings
        weight = value / 100.0
        print(f"{param}: {weight}")
        if self.viewport_panel and hasattr(self.viewport_panel, 'cpp_renderer') and self.viewport_panel.cpp_renderer:
            try:
                # Try to access mesh if available through renderer
                pass
            except Exception as e:
                pass
