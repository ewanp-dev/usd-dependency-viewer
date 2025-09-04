from PyQt6.QtWidgets import QWidget, QLineEdit, QVBoxLayout, QSizePolicy
from PyQt6.QtCore import Qt

from ..button import strata_widget_button

class strata_dropdown_results(QWidget):

    def __init__(self):
        super().__init__()
        self.setWindowFlags(self.windowFlags() | Qt.WindowType.Popup)

        _layout_main = QVBoxLayout(self)
        self.limit = QLineEdit()
        self.reset = strata_widget_button(
            icon_name="sorting.png",
            width_policy=QSizePolicy.Policy.Preferred,
            height_policy=QSizePolicy.Policy.Fixed,
        )
        self.copy = strata_widget_button()

        _layout_main.addWidget(self.limit)
        _layout_main.addWidget(self.reset)
        _layout_main.addWidget(self.copy)


