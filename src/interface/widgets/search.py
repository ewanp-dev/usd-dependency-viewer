from PyQt6.QtCore import Qt
from PyQt6.QtWidgets import QVBoxLayout, QWidget


class StrataFloatingSearch(QWidget):
    """
    Floating search widget
    """

    def __init__(self, parent=None) -> None:
        """
        Constructor

        :param parent: QT parent object
        """
        super().__init__(parent)

        self.setWindowFlags(Qt.WindowType.FramelessWindowHint | Qt.WindowType.Dialog)

        # NOTE might not be neccesary
        # NOTE this is currently breaking outside of Linux
        # self.setAttribute(Qt.WidgetAttribute.WA_TranslucentBackground)

        self.setFocusPolicy(Qt.FocusPolicy.ClickFocus)

        # TODO make dynamic
        self.setFixedSize(500, 500)

        _layout_main = QVBoxLayout(self)
