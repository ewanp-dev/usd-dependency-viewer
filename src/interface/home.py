from typing import List, Optional, Text

from PyQt6.QtCore import QRect, Qt
from PyQt6.QtGui import QEnterEvent, QFont, QFontDatabase
from PyQt6.QtWidgets import QLabel, QSizePolicy, QSpacerItem, QVBoxLayout, QWidget

from .button import StrataAbstractButton
from .strata_globals import *
from .utils import HoverFilter


class StrataHomePage(QWidget):
    """
    The home button/startup page
    """

    def __init__(self, parent=None) -> None:
        """
        Constructor

        :param parent: QT parent object
        """
        super().__init__(parent)

        self.initUI()

    def initUI(self) -> None:
        """
        UI Constructor
        """
        db = QFontDatabase
        print(db.families())
        main_layout = QVBoxLayout()
        main_layout.setSpacing(10)

        # TODO change splash text to logo
        # TODO remove spacing between logo and search
        splash_text: str = """  
███████╗████████╗██████╗  █████╗ ████████╗ █████╗ 
██╔════╝╚══██╔══╝██╔══██╗██╔══██╗╚══██╔══╝██╔══██╗
███████╗   ██║   ██████╔╝███████║   ██║   ███████║
╚════██║   ██║   ██╔══██╗██╔══██║   ██║   ██╔══██║
███████║   ██║   ██║  ██║██║  ██║   ██║   ██║  ██║
╚══════╝   ╚═╝   ╚═╝  ╚═╝╚═╝  ╚═╝   ╚═╝   ╚═╝  ╚═╝                                                 
        """

        text = "STRATA"
        label_a, label_b, label_c = QLabel(text), QLabel(text), QLabel(text)
        # self.home_label = QLabel(splash_text.strip())
        # self.home_label.setAlignment(Qt.AlignmentFlag.AlignCenter)
        font = QFont("MesloLGL Nerd Font", 15)
        label_a.setFont(font)
        # self.home_label.setFont(font)
        # self.home_label.setWordWrap(False)
        self.open = StrataAbstractButton(
            icon_name="search.png",
            width=150,
            height=STRATA_BUTTON_HEIGHT - 20,
            default_stylesheet=False,
        )

        self.setStyleSheet(
            """
            QPushButton {
                font: 10pt 'Sans Serif';
                color: rgb(28, 32, 38);
                background-color: rgb(190, 190, 190);
                border-radius: 15px;
            }
            QPushButton:hover {
                background-color: rgb(50, 50, 50);
                color: rgb(190, 190, 190);
            }
                           """
        )
        hover_filter = HoverFilter(widget=self.open)
        self.open.installEventFilter(hover_filter)
        self.open.setText(" Select File")
        self.open.setFixedHeight(30)
        self.open.setFixedWidth(100)

        main_layout.addWidget(label_a, alignment=Qt.AlignmentFlag.AlignCenter)
        main_layout.addWidget(label_b, alignment=Qt.AlignmentFlag.AlignCenter)
        main_layout.addWidget(label_c, alignment=Qt.AlignmentFlag.AlignCenter)
        main_layout.addWidget(self.open, alignment=Qt.AlignmentFlag.AlignCenter)
        self.setLayout(main_layout)
        main_layout.setSpacing(10)

    def enterEvent(self, event: Optional[QEnterEvent]) -> None:
        print("This is an enter event")
        return super().enterEvent(event)
