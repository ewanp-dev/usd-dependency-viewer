from PyQt6.QtCore import QRect, Qt
from PyQt6.QtGui import QFont
from PyQt6.QtWidgets import QLabel, QSizePolicy, QSpacerItem, QVBoxLayout, QWidget

from .button import StrataAbstractButton
from .strata_globals import *


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

        self.home_label = QLabel(splash_text.strip())
        self.home_label.setAlignment(Qt.AlignmentFlag.AlignCenter)
        font = QFont("Luxi Mono", 15)
        self.home_label.setFont(font)
        self.home_label.setWordWrap(False)
        self.open = StrataAbstractButton(
            icon_name="search.png", width=150, height=STRATA_BUTTON_HEIGHT - 20
        )
        self.open.setText(" Select File")

        main_layout.addWidget(self.home_label, alignment=Qt.AlignmentFlag.AlignCenter)
        main_layout.addWidget(self.open, alignment=Qt.AlignmentFlag.AlignCenter)
        self.setLayout(main_layout)
        main_layout.setSpacing(10)
