from PyQt6.QtWidgets import QListWidget, QVBoxLayout, QWidget


class StrataDetailsView(QWidget):

    def __init__(self):
        super().__init__()

        self.initUI()

    def initUI(self):

        layout = QVBoxLayout()
        self.list = QListWidget()
        layout.setContentsMargins(0, 0, 0, 0)

        layout.addWidget(self.list)
        self.setLayout(layout)
