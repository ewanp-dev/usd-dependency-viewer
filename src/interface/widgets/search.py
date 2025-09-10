from typing import List, Optional

from PyQt6.QtCore import Qt
from PyQt6.QtGui import QKeyEvent
from PyQt6.QtWidgets import QHBoxLayout, QLineEdit, QListWidget, QVBoxLayout, QWidget

from ..button import StrataAbstractButton


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

        # ----------------------------------------------------
        # WIDGETS

        self.search = QLineEdit()
        self.search.setPlaceholderText("Search for dependency...")
        self.exit = StrataAbstractButton(text="Exit")
        self.results = QListWidget()

        _lyt = QVBoxLayout(self)
        _lyt_top = QHBoxLayout()

        _lyt_top.addWidget(self.search)
        _lyt_top.addWidget(self.exit)

        _lyt.addLayout(_lyt_top)
        _lyt.addWidget(self.results)

        # ----------------------------------------------------
        # SIGNALS

        # NOTE might need to create a exit function if more control is needed
        self.exit.clicked.connect(lambda: self.close())

        # ----------------------------------------------------
        # SIGNALS
        # NOTE need to match colors of both widgets
        self.setStyleSheet(
            """
            QWidget {
            background-color: rgb(40, 40, 40);
            }

            QLineEdit {
            color: rgb(190, 190, 190);
            border: 0px solid gray;
            padding: 5px 5px;
            border-radius: 0px;
            background-color: rgba(25, 25, 25, 0);
            }

            QListWidget {
            background-color: rgba(25, 25, 25, 0);
            color: rgb(190, 190, 190);
            }
        """
        )

    def filter_list(self, query: str) -> List[str] | None:
        """
        Returns a filtered list based on search query

        :param query: Text from the QLineEdit
        """
        return None

    def keyPressEvent(self, a0: Optional[QKeyEvent]) -> None:
        """
        Closes the widget when escape key is pressed

        :param a0: The key press event
        """
        if a0.key() == Qt.Key.Key_Escape:
            self.close()
        else:
            return super().keyPressEvent(a0)
