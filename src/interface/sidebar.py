"""
expanding sidebar to select nodegraph, library, or text based inspector
"""

from PyQt6.QtWidgets import QPushButton, QVBoxLayout, QWidget


class StrataSideBar(QWidget):

    def __init__(self):
        super().__init__()

        self.initUI()

    def initUI(self):
        self.setFixedWidth(50)
        layout = QVBoxLayout()
        self.test_button = QPushButton("A")
        layout.addWidget(self.test_button)
        layout.setContentsMargins(10, 0, 0, 0)

        self.setLayout(layout)
