from PyQt6.QtWidgets import QWidget, QVBoxLayout, QPushButton
from PyQt6.QtCore import Qt

class strata_dropdown_properties(QWidget):

    def __init__(self):
        super().__init__()
        self.setWindowFlags(self.windowFlags() | Qt.WindowType.Popup)
        layout = QVBoxLayout(self)
        layout.addWidget(QPushButton("TEST A"))
        layout.addWidget(QPushButton("TEST B"))

