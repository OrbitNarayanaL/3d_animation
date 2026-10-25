from PySide6.QtWidgets import QWidget, QVBoxLayout, QLabel


class SlidersPanel(QWidget):
    def __init__(self, parent=None):
        super().__init__(parent)
        layout = QVBoxLayout(self)
        layout.addWidget(QLabel("Parametric Sliders"))
        layout.addWidget(QLabel("Height"))
        layout.addWidget(QLabel("Weight"))
        layout.addWidget(QLabel("Muscle"))
        layout.addWidget(QLabel("Face Width"))
