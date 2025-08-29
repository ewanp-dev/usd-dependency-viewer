from PyQt6.QtCore import Qt
from PyQt6.QtWidgets import QHBoxLayout, QPushButton, QWidget


class StrataUITopBar(QWidget):

    def __init__(self):
        super().__init__()

        self.initUI()

    def initUI(self):
        layout = QHBoxLayout()
        layout.setContentsMargins(50, 10, 0, 0)
        layout.setSpacing(10)

        self.expand_button = QPushButton("E")
        self.expand_button.setCheckable(True)
        self.expand_button.setFixedHeight(40)
        self.expand_button.setFixedWidth(40)

        layout.addWidget(self.expand_button, alignment=Qt.AlignmentFlag.AlignLeft)
        self.setLayout(layout)
        self.setFixedHeight(50)
