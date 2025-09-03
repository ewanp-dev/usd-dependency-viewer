from PyQt6.QtWidgets import QWidget, QPushButton, QComboBox, QHBoxLayout
from PyQt6.QtCore import Qt

class strata_dropdown_sort(QWidget):

    def __init__(self):
        super().__init__()
        self.setWindowFlags(self.windowFlags() | Qt.WindowType.Popup)
        self.sort_type = QComboBox()
        self.sort_rule = QComboBox()
        self.clear_sort = QPushButton("C")

        types_list = ["file name", "file path", "file size", "extension", "date created", "date modified",]
        self.sort_type.addItems(l)

        sort_rule_str = ["A->Z", "Z->A"]
        sort_rule_num = ["0->1", "1->0"]
        sort_rule_time = ["Old to new", "New to old"]

        _layout_main = QHBoxLayout(self)
        _layout_main.addWidget(self.sort_type)
        _layout_main.addWidget(self.sort_rule)
        _layout_main.addWidget(self.clear_sort)
