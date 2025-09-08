from PyQt6.QtCore import Qt
from PyQt6.QtWidgets import QLineEdit, QSizePolicy, QVBoxLayout, QWidget

from ..button import StrataAbstractButton


class StrataDropdownResults(QWidget):
    """
    Dropdown to control the amount of results returned
    """

    def __init__(self) -> None:
        """
        Constructor
        """

        super().__init__()
        self.setWindowFlags(self.windowFlags() | Qt.WindowType.Popup)

        _layout_main = QVBoxLayout(self)
        self.limit = QLineEdit()
        self.reset = StrataAbstractButton(
            icon_name="sorting.png",
            width_policy=QSizePolicy.Policy.Preferred,
            height_policy=QSizePolicy.Policy.Fixed,
        )
        self.copy = StrataAbstractButton()

        _layout_main.addWidget(self.limit)
        _layout_main.addWidget(self.reset)
        _layout_main.addWidget(self.copy)
