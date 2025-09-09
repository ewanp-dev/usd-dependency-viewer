from typing import Optional

from PyQt6.QtCore import Qt
from PyQt6.QtGui import QKeyEvent
from PyQt6.QtWidgets import QHBoxLayout, QVBoxLayout, QWidget

from ..button import StrataAbstractButton


class StrataSettingsPage(QWidget):
    """
    The page containing the node graph
    """

    def __init__(self, parent=None) -> None:
        """
        Constructor

        :param parent: Qt parent object
        """
        # TODO make a floating widget
        # TODO make floating exit button abstract
        super().__init__(parent)
        self.initUI()

    def initUI(self) -> None:
        """
        UI Constructor
        """
        self.setWindowFlags(Qt.WindowType.FramelessWindowHint | Qt.WindowType.Dialog)
        self.setFocusPolicy(Qt.FocusPolicy.ClickFocus)
        self.setFixedSize(600, 600)

        # ----------------------------------------------------
        # WIDGETS

        self.exit = StrataAbstractButton(text="Exit")

        _lyt = QVBoxLayout(self)
        _lyt_header = QHBoxLayout()
        _lyt_header.addWidget(self.exit)
        _lyt.addLayout(_lyt_header)

        # ----------------------------------------------------
        # SIGNALS

        self.exit.clicked.connect(lambda: self.close())

    def keyPressEvent(self, a0: Optional[QKeyEvent]) -> None:
        """
        Closes the widget when escape key is pressed

        :param a0: The key press event
        """
        if a0.key() == Qt.Key.Key_Escape:
            self.close()
        else:
            return super().keyPressEvent(a0)
