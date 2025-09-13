from PyQt6.QtWidgets import QHBoxLayout, QLineEdit, QListWidget, QVBoxLayout, QWidget

from ..button import StrataAbstractButton
from ..strata_globals import *


class StrataDropdown(QWidget):
    """
    Interactive dependencies dropdown widget
    """

    def __init__(self) -> None:
        """
        Cunstructor
        """

        super().__init__()
        self.initUI()

    def initUI(self) -> None:
        """
        UI Constructor
        """

        self.setObjectName("dropdownWidget")
        # TODO clean up layout and add stylesheet
        _layout_main = QVBoxLayout()
        _layout_header = QHBoxLayout()
        _layout_main.setContentsMargins(10, 15, 15, 0)

        self.search_bar = QLineEdit()
        self.search_bar.setPlaceholderText("Search...")
        self.search_bar.setStyleSheet(
            """
                                      background: transparent;
                                      border: none;
                                      color: rgb(190, 190, 190);
                                      """
        )

        self.filter_button = StrataAbstractButton(
            icon_name="filter.png", width=18, height=18
        )

        _layout_header.addWidget(self.search_bar)
        _layout_header.addWidget(self.filter_button)

        self.list = QListWidget()
        self.list.setStyleSheet(
            """background-color: rgb(30, 33, 37); border-style: none; """
        )

        _layout_main.addLayout(_layout_header)
        _layout_main.addWidget(self.list)

        self.setLayout(_layout_main)
        self.setMinimumWidth(45)
