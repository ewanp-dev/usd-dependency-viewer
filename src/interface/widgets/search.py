import os
from typing import List, Optional

from PyQt6.QtCore import Qt
from PyQt6.QtGui import QKeyEvent
from PyQt6.QtWidgets import QHBoxLayout, QLineEdit, QListWidget, QVBoxLayout, QWidget

from ..button import StrataAbstractButton


class StrataFloatingSearch(QWidget):
    """
    Floating search widget
    """

    def __init__(self, parent=None, dependencies: List[str] = []) -> None:
        """
        Constructor

        :param parent: QT parent object
        """
        super().__init__(parent)

        self.dependencies = dependencies
        self.setWindowFlags(Qt.WindowType.FramelessWindowHint | Qt.WindowType.Dialog)
        self.setAttribute(Qt.WidgetAttribute.WA_StyledBackground, True)
        # NOTE might not be neccesary
        # NOTE this is currently breaking outside of Linux
        # self.setAttribute(Qt.WidgetAttribute.WA_TranslucentBackground)

        self.setFocusPolicy(Qt.FocusPolicy.ClickFocus)

        # TODO make dynamic
        self.setFixedSize(500, 500)
        self.setObjectName("searchBar")

        # ----------------------------------------------------
        # WIDGETS

        self.search = QLineEdit()
        self.search.setPlaceholderText("Search for dependency...")
        self.search.setAttribute(Qt.WidgetAttribute.WA_StyledBackground, True)
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

        self.populate_default_list(list_widget=self.results)
        # ----------------------------------------------------
        # SIGNALS
        # NOTE need to match colors of both widgets
        self.setStyleSheet(
            """
            QWidget {
                border-radius: 20px;
            }
            QLineEdit {
                background-color: rgba(0, 0, 0, 0);
                background: transparent;
            }
            QLineEdit:focus {
                background-color: rgba(0, 0, 0, 0);
            }
            QListWidget {
                background-color: rgba(30, 33, 37, 0);
                color: rgb(190, 190, 190);
            }
        """
        )

    def populate_default_list(self, list_widget: QListWidget) -> None:
        """
        Populates the search list with the first ten items in dependencies

        :param list_widget: List to add items to
        """
        for i, val in enumerate(self.dependencies):
            if i > 10:
                break
            list_widget.addItem(os.path.splitext(os.path.basename(val))[0])
        return None

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
