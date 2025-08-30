"""
This will be a shotgrid like text dropdown where you can manually select or filter through all dependencies
"""

from PyQt6.QtWidgets import QListWidget, QVBoxLayout, QWidget


class StrataUIDropdown(QWidget):
    """
    list widget with dropdown functionality to see tree view of all
    dependencies
    """

    def __init__(self):
        super().__init__()
        self.initUI()

    def initUI(self):
        layout = QVBoxLayout()
        layout.setContentsMargins(0, 0, 0, 0)

        self.list = QListWidget()

        layout.addWidget(self.list)

        self.setLayout(layout)
        self.setStyleSheet("background-color: rgb(50, 50, 50);")
        self.setMinimumWidth(45)
