from PyQt6.QtCore import Qt
from PyQt6.QtGui import QFont
from PyQt6.QtWidgets import QHBoxLayout, QLabel, QPushButton, QVBoxLayout, QWidget

from .button import strata_widget_button
from .strata_globals import *


class strata_widget_home(QWidget):
    """
    home screen for when the application is first opened

    NOTE
    need to add some more text and interactive features to load up pages by default

    """

    def __init__(self, parent=None):
        super().__init__(parent)

        self.initUI()

    def initUI(self):
        """
        TODO
        * fix spacing between label and button
        * fix button width and height
        * increase button icon and text size
        * add button functionality to create file browser
        """
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
        font = QFont("Courier New", 20)
        self.home_label.setFont(font)
        self.home_label.setWordWrap(False)

        self.open = strata_widget_button(
            icon_name="search.png", width=150, height=STRATA_BUTTON_HEIGHT
        )
        self.open.setText("Select File")

        main_layout.addWidget(self.home_label, alignment=Qt.AlignmentFlag.AlignCenter)
        main_layout.addWidget(self.open, alignment=Qt.AlignmentFlag.AlignCenter)
        self.setLayout(main_layout)
