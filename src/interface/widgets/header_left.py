from PyQt6.QtCore import Qt
from PyQt6.QtWidgets import QHBoxLayout, QWidget

from ..button import strata_widget_button
from ..strata_globals import *


class strata_widget_header_l(QWidget):
    """
    !!DEPRECATED!!

    Left side of the application header
    """

    def __init__(self) -> None:
        """
        Constructor
        """
        super().__init__()

        self.initUI()

    def initUI(self) -> None:
        """
        UI Constructor
        """
        layout = QHBoxLayout()
        layout.setContentsMargins(50, 10, 0, 0)
        layout.setSpacing(10)

        self.expand_left = strata_widget_button(
            icon_name="meal/sidebar.png",
            width=STRATA_BUTTON_WIDTH,
            height=STRATA_BUTTON_HEIGHT,
        )
        self.expand_left.setCheckable(True)

        layout.addWidget(self.expand_left, alignment=Qt.AlignmentFlag.AlignRight)
        self.setLayout(layout)
        self.setFixedHeight(50)
