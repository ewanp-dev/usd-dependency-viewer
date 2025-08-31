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
        """
        TODO
        * add in all base widgets such as filter, search. etc
        * start writing tests for the list interface
        * start writing the item to redirect on selection
        * write the ui for switching between grid and details view
        """

        layout = QVBoxLayout()
        self.list = QListWidget()
        layout.setContentsMargins(0, 0, 0, 0)

        layout.addWidget(self.list)
        self.setLayout(layout)
