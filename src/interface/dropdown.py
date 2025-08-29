"""
This will be a shotgrid like text dropdown where you can manually select or filter through all dependencies
"""

from PyQt6.QtWidgets import QListWidget, QVBoxLayout, QWidget


class StrataList(QWidget):

    def __init__(self):
        super().__init__()
        self.initUI()

    def initUI(self):
        layout = QVBoxLayout()
        layout.setContentsMargins(0, 0, 0, 0)

        self.list = QListWidget()

        layout.addWidget(self.list)

        self.setLayout(layout)
        self.setStyleSheet("background-color: white;")
        self.setMinimumWidth(150)
        self.hide()
