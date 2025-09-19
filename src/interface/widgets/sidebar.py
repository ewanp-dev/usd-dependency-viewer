from PyQt6.QtCore import QSize, Qt
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

        self.setAttribute(Qt.WidgetAttribute.WA_StyledBackground, True)
        layout = QVBoxLayout()
        layout.setSpacing(10)
        layout.setContentsMargins(10, 10, 10, 10)

        self.setStyleSheet(
            """
                           background-color: red;
                           border-radius: 20px;"""
        )
        button_width, button_height = (
            STRATA_BUTTON_WIDTH - 15,
            STRATA_BUTTON_HEIGHT - 15,
        )

        # using button widgets for each page
        self.win_database = StrataAbstractButton(
            icon_name="list.png",
            width=button_width,
            height=button_height,
            tooltip="List View",
        )
        self.win_nodegraph = StrataAbstractButton(
            icon_name="node.png",
            width=button_width,
            height=button_height,
            tooltip="Node View",
        )
        self.win_quick_search = StrataAbstractButton(
            icon_name="search.png",
            width=button_width,
            height=button_height,
            tooltip="Search",
        )
        self.win_library = StrataAbstractButton(
            icon_name="grid.png",
            width=button_width,
            height=button_height,
            tooltip="Grid Selection",
        )
        self.win_command = StrataAbstractButton(
            icon_name="home.png",
            width=button_width,
            height=button_height,
            tooltip="Home Page",
        )
        self.settings = StrataAbstractButton(
            icon_name="settings.png",
            width=button_width,
            height=button_height,
            tooltip="Setttings",
        )

        layout.addWidget(self.win_database)
        layout.addWidget(self.win_nodegraph)
        # layout.addWidget(self.win_quick_search)
        layout.addWidget(self.win_library)
        layout.addWidget(self.win_command)

        layout.addSpacerItem(
            QSpacerItem(0, 0, QSizePolicy.Policy.Minimum, QSizePolicy.Policy.Expanding)
        )

        layout.addWidget(self.settings)

        self.setLayout(layout)
        # self.setFixedWidth(40)

        # self.setStyleSheet(
        # f"""
        # QWidget {{
        # background-color: {STRATA_APPLICATION_COLORS['color2']};
        # }}
        # """
        # )
