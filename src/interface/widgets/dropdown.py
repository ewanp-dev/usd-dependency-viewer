from PyQt6.QtWidgets import QHBoxLayout, QLineEdit, QListWidget, QVBoxLayout, QWidget

from ..button import strata_widget_button
from ..strata_globals import *


class strata_widget_dropdown(QWidget):
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

        # TODO clean up layout and add stylesheet
        _layout_main = QVBoxLayout()
        _layout_header = QHBoxLayout()
        _layout_main.setContentsMargins(0, 0, 0, 0)

        self.search_bar = QLineEdit()
        self.filter_button = strata_widget_button(
            icon_name="meal/sort.png", width=24, height=24
        )

        _layout_header.addWidget(self.search_bar)
        _layout_header.addWidget(self.filter_button)

        self.list = QListWidget()

        _layout_main.addLayout(_layout_header)
        _layout_main.addWidget(self.list)

        self.setLayout(_layout_main)
        self.setMinimumWidth(45)
