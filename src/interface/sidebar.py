from PyQt6.QtCore import Qt
from PyQt6.QtWidgets import QPushButton, QSizePolicy, QSpacerItem, QVBoxLayout, QWidget

from .button import strata_widget_button
from .strata_globals import *


class strata_widget_sidebar(QWidget):
    """
    acts as the side bar on the left to switch between different
    window types

    TODO
    * start writing tooltips
    * add clicked functionality into class
    * start style sheet
    """

    def __init__(self):
        super().__init__()

        self.initUI()

    def initUI(self):

        layout = QVBoxLayout()
        layout.setSpacing(10)
        layout.setContentsMargins(10, 60, 0, 0)

        button_width, button_height = STRATA_BUTTON_WIDTH, STRATA_BUTTON_HEIGHT

        # using button widgets for each page
        self.win_database = strata_widget_button(
            icon_name="list.png", width=button_width, height=button_height
        )
        self.win_nodegraph = strata_widget_button(
            icon_name="node.png",
            width=button_width,
            height=button_height,
            tooltip="Node View",
        )
        self.win_quick_search = strata_widget_button(
            icon_name="search.png", width=button_width, height=button_height
        )
        self.win_library = strata_widget_button(
            icon_name="library.png", width=button_width, height=button_height
        )
        self.win_command = strata_widget_button(
            icon_name="command.png", width=button_width, height=button_height
        )

        layout.addWidget(self.win_database)
        layout.addWidget(self.win_nodegraph)
        layout.addWidget(self.win_quick_search)
        layout.addWidget(self.win_library)
        layout.addWidget(self.win_command)

        layout.addSpacerItem(
            QSpacerItem(0, 0, QSizePolicy.Policy.Minimum, QSizePolicy.Policy.Expanding)
        )
        self.setLayout(layout)
        self.setFixedWidth(50)
