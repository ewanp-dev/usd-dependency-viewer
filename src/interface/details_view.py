from PyQt6.QtWidgets import QListWidget, QVBoxLayout, QWidget


class StrataUIDetailsView(QWidget):
    """
    contains a detail list view  where you can select all dependencies

    NOTE 
    this will be implemented with a way to switch between a grid view and details 
    view
    """

    def __init__(self):
        super().__init__()

        self.initUI()

    def initUI(self):

        layout = QVBoxLayout()
        self.list = QListWidget()
        layout.setContentsMargins(0, 0, 0, 0)

        layout.addWidget(self.list)
        self.setLayout(layout)
