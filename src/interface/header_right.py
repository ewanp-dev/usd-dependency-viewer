from PyQt6.QtCore import Qt
from PyQt6.QtWidgets import QHBoxLayout, QPushButton, QWidget
from button import StrataUIButton
from strata_globals import *


class StrataUIHeaderRight(QWidget):

    def __init__(self):
        super().__init__()

        self.initUI()

    def initUI(self):
        """
        NOTE
        currently the expand button doesnt follow the dropdown menu
        we need to create two expand buttons and hide one when the dropdown
        widget is expanded

        we also need to make the main layout horizontal and have two headers split
        by a qsplitter
        """
        layout = QHBoxLayout()
        layout.setContentsMargins(0, 10, 0, 0)
        layout.setSpacing(10)

        self.expand_left = StrataUIButton(icon_name="sidebar_left.png", width=STRATA_BUTTON_WIDTH, height=STRATA_BUTTON_HEIGHT, flipped=True)
        self.expand_left.setCheckable(True)

        layout.addWidget(self.expand_left, alignment=Qt.AlignmentFlag.AlignLeft)
        self.setLayout(layout)
        self.setFixedHeight(50)
