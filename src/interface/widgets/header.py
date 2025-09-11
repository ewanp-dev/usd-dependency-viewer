from typing import List

from PyQt6.QtCore import Qt
from PyQt6.QtWidgets import QHBoxLayout, QWidget

from ..button import StrataAbstractButton
from ..strata_globals import *


class StrataHeaderLeft(QWidget):
    """
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

        self.expand_left = StrataAbstractButton(
            icon_name="mansha/sidebar.png",
            width=STRATA_BUTTON_WIDTH - 15,
            height=STRATA_BUTTON_HEIGHT - 15,
        )
        self.expand_left.setCheckable(True)
        layout.addWidget(self.expand_left, alignment=Qt.AlignmentFlag.AlignRight)

        self.setLayout(layout)
        self.setFixedHeight(50)


class StrataHeaderRight(QWidget):
    """
    The right side of the application header
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
        layout.setContentsMargins(0, 10, 0, 0)
        layout.setSpacing(10)

        self.expand_left = StrataAbstractButton(
            icon_name="mansha/sidebar.png",
            width=STRATA_BUTTON_WIDTH - 15,
            height=STRATA_BUTTON_HEIGHT - 15,
            flipped=True,
        )
        self.expand_left.setCheckable(True)

        layout.addWidget(self.expand_left, alignment=Qt.AlignmentFlag.AlignLeft)
        self.setLayout(layout)
        self.setFixedHeight(50)
