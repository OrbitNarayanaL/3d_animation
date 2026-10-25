import sys
import os
from PySide6.QtWidgets import QApplication
from ui.main_window import MainWindow

def main():
    # Append the api folder path to help Python discover the built compiled module (.pyd)
    sys.path.append(os.path.join(os.path.dirname(__file__), 'api'))
    
    app = QApplication(sys.argv)
    window = MainWindow()
    window.show()
    sys.exit(app.exec())

if __name__ == "__main__":
    main()
