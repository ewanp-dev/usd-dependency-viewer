from PyQt6.QtCore import Qt
from PyQt6.QtWidgets import QHBoxLayout, QWidget

from ..button import StrataAbstractButton
from ..strata_globals import *

FIXED_HEIGHT: int = 40


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
        self.setStyleSheet(
            f"""
            QWidget {{
                background-color: {STRATA_APPLICATION_COLORS['color3']};
            }}
        """
        )
        self.setFixedHeight(FIXED_HEIGHT)
        self.setAttribute(Qt.WidgetAttribute.WA_StyledBackground, True)
        layout = QHBoxLayout()
        layout.setContentsMargins(50, 0, 15, 0)
        layout.setSpacing(10)

        self.expand_left = StrataAbstractButton(
            icon_name="mansha/sidebar.png",
            width=STRATA_BUTTON_WIDTH - 15,
            height=STRATA_BUTTON_HEIGHT - 15,
        )
        self.expand_left.setCheckable(True)
        layout.addWidget(self.expand_left, alignment=Qt.AlignmentFlag.AlignRight)

        self.setLayout(layout)


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
        self.setStyleSheet(
            f"""
            QWidget {{
                background-color: {STRATA_APPLICATION_COLORS['color3']};
            }}
        """
        )
        self.setAttribute(Qt.WidgetAttribute.WA_StyledBackground, True)
        self.setFixedHeight(FIXED_HEIGHT)
        layout = QHBoxLayout()
        layout.setContentsMargins(15, 0, 0, 0)
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
