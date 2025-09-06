from PyQt6.QtCore import Qt
from PyQt6.QtGui import QFont
from PyQt6.QtWidgets import QHBoxLayout, QLabel, QPushButton, QVBoxLayout, QWidget

from .button import strata_widget_button
from .strata_globals import *


class strata_widget_home(QWidget):
    """
    home screen for when the application is first opened

    TODO
    * make the home screen more interactive and have the logo be animated
    * remove spacing between the logo and the button
    * fix button width and height
    * add file browser functionality
    * add in hotkeys to the home page to open other pages (low prio)
    """

    def __init__(self, parent=None):
        super().__init__(parent)

        self.initUI()

    def initUI(self):
        main_layout = QVBoxLayout()
        main_layout.setSpacing(10)

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

        self.open = strata_widget_button(
            icon_name="meal/search.png", width=150, height=STRATA_BUTTON_HEIGHT
        )
        self.open.setText(" Select File")

        main_layout.addWidget(self.home_label, alignment=Qt.AlignmentFlag.AlignCenter)
        main_layout.addWidget(self.open, alignment=Qt.AlignmentFlag.AlignCenter)
        self.setLayout(main_layout)
