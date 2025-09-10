from PyQt6.QtWidgets import QSizePolicy, QSpacerItem, QVBoxLayout, QWidget

from ..button import StrataAbstractButton
from ..strata_globals import *


class StrataPageSwitcher(QWidget):
    """
    Left sidebar to open pages or widgets
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

        layout = QVBoxLayout()
        layout.setSpacing(10)
        layout.setContentsMargins(10, 60, 0, 10)

        button_width, button_height = STRATA_BUTTON_WIDTH, STRATA_BUTTON_HEIGHT

        # using button widgets for each page
        self.win_database = StrataAbstractButton(
            icon_name="meal/list.png",
            width=button_width,
            height=button_height,
            tooltip="List View",
        )
        self.win_nodegraph = StrataAbstractButton(
            icon_name="meal/node.png",
            width=button_width,
            height=button_height,
            tooltip="Node View",
        )
        self.win_quick_search = StrataAbstractButton(
            icon_name="meal/search.png",
            width=button_width,
            height=button_height,
            tooltip="Search",
        )
        self.win_library = StrataAbstractButton(
            icon_name="meal/grid.png",
            width=button_width,
            height=button_height,
            tooltip="Grid Selection",
        )
        self.win_command = StrataAbstractButton(
            icon_name="meal/command.png",
            width=button_width,
            height=button_height,
            tooltip="Home Page",
        )
        self.settings = StrataAbstractButton(
            icon_name="meal/settings.png",
            width=button_width,
            height=button_height,
            tooltip="Setttings",
        )

        layout.addWidget(self.win_database)
        layout.addWidget(self.win_nodegraph)
        layout.addWidget(self.win_quick_search)
        layout.addWidget(self.win_library)
        layout.addWidget(self.win_command)

        layout.addSpacerItem(
            QSpacerItem(0, 0, QSizePolicy.Policy.Minimum, QSizePolicy.Policy.Expanding)
        )

        layout.addWidget(self.settings)

        self.setLayout(layout)
        self.setFixedWidth(50)
