"""
This will be a shotgrid like text dropdown where you can manually select or filter through all dependencies
"""

from PyQt6.QtWidgets import (
    QHBoxLayout,
    QLineEdit,
    QListWidget,
    QPushButton,
    QVBoxLayout,
    QWidget,
)

from .button import strata_widget_button
from .strata_globals import *


class strata_widget_dropdown(QWidget):
    """
    list widget with dropdown functionality to see tree view of all
    dependencies
    """

    def __init__(self):
        super().__init__()
        self.initUI()

    def initUI(self):
        """
        TODO
        * start adding basic widgets to this layout to build upon
        * create stylesheet
        * run unit tests on dependency checker
        * run unit tests on loading speeds
        """

        _layout_main = QVBoxLayout()
        _layout_header = QHBoxLayout()
        _layout_main.setContentsMargins(0, 0, 0, 0)

        self.search_bar = QLineEdit()
        self.filter_button = strata_widget_button(
            icon_name="filter.png", width=24, height=24
        )

        _layout_header.addWidget(self.search_bar)
        _layout_header.addWidget(self.filter_button)

        self.list = QListWidget()

        _layout_main.addLayout(_layout_header)
        _layout_main.addWidget(self.list)

        self.setLayout(_layout_main)
        # self.setStyleSheet("background-color: rgb(50, 50, 50);")
        self.setMinimumWidth(45)
