from PyQt6.QtWidgets import QWidget, QLabel, QVBoxLayout, QHBoxLayout
from PyQt6.QtCore import Qt
from PyQt6.QtGui import QFont

class StrataUIHome(QWidget):
    """
    home screen for when the application is first opened

    NOTE
    need to add some more text and interactive features to load up pages by default

    """

    def __init__(self, parent=None):
        super().__init__(parent)

        self.initUI()

    def initUI(self):
        main_layout = QHBoxLayout()

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


        main_layout.addWidget(self.home_label, alignment=Qt.AlignmentFlag.AlignCenter)
        self.setLayout(main_layout)
