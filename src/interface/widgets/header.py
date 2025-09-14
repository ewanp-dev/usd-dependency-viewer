from PyQt6.QtCore import Qt
from PyQt6.QtWidgets import QHBoxLayout, QWidget

from ..button import StrataAbstractButton
from ..strata_globals import *

FIXED_HEIGHT: int = 40


class StrataHeader(QWidget):
    """
    Merged widget class
    """

    def __init__(self, parent=None):
        """
        Constructor
        """
        super().__init__(parent)
        self.initUI()

    def initUI(self):
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
        _lyt = QHBoxLayout(self)
        _lyt.setContentsMargins(10, 0, 10, 0)
        _lyt.setSpacing(10)
        self.expand = StrataAbstractButton(
            icon_name="sidebar.png",
            width=STRATA_BUTTON_WIDTH - 15,
            height=STRATA_BUTTON_HEIGHT - 15,
            flipped=True,
        )
        self.expand.setCheckable(True)
        _lyt.addWidget(self.expand, alignment=Qt.AlignmentFlag.AlignLeft)
