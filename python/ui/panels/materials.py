from PySide6.QtWidgets import QWidget, QVBoxLayout, QLabel


class MaterialsPanel(QWidget):
    def __init__(self, parent=None):
        super().__init__(parent)
        layout = QVBoxLayout(self)
        layout.addWidget(QLabel("Material / PBR Texture Viewer"))
        layout.addWidget(QLabel("Albedo"))
        layout.addWidget(QLabel("Normal"))
        layout.addWidget(QLabel("Roughness"))
