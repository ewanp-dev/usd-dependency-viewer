from PyQt6.QtWidgets import QWidget, QPushButton, QComboBox, QHBoxLayout
from PyQt6.QtCore import Qt

class strata_dropdown_sort(QWidget):

    def __init__(self):
        super().__init__()
        self.setWindowFlags(self.windowFlags() | Qt.WindowType.Popup)
        self.sort_type = QComboBox()
        self.sort_rule = QComboBox()
        self.clear_sort = QPushButton("C")

        _layout_main = QHBoxLayout(self)
        _layout_main.addWidget(self.sort_type)
        _layout_main.addWidget(self.sort_rule)
        _layout_main.addWidget(self.clear_sort)
