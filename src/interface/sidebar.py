from PyQt6.QtWidgets import QPushButton, QVBoxLayout, QWidget, QSpacerItem, QSizePolicy
from PyQt6.QtCore import Qt
from button import StrataUIButton
from strata_globals import *

class StrataUISideBar(QWidget):
    """
    acts as the side bar on the left to switch between different
    window types
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
        self.win_dropdown = StrataUIButton(icon_name="list.png", width=button_width, height=button_height)
        self.win_nodegraph = StrataUIButton(icon_name="node.png", width=button_width, height=button_height)
        self.win_quick_search = StrataUIButton(icon_name="search.png", width=button_width, height=button_height)
        self.win_library = StrataUIButton(icon_name="library.png", width=button_width, height=button_height)
        self.win_command = StrataUIButton(icon_name="command.png", width=button_width, height=button_height)

        layout.addWidget(self.win_dropdown)
        layout.addWidget(self.win_nodegraph)
        layout.addWidget(self.win_quick_search)
        layout.addWidget(self.win_library)
        layout.addWidget(self.win_command)

        layout.addSpacerItem(QSpacerItem(0, 0, QSizePolicy.Policy.Minimum, QSizePolicy.Policy.Expanding))
        self.setLayout(layout)
        self.setFixedWidth(50)
