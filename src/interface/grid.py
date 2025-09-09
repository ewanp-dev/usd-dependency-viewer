from PyQt6.QtWidgets import QLabel, QVBoxLayout, QWidget


class StrataGridPage(QWidget):

    def __init__(self, parent=None) -> None:
        """
        Constructor

        :param parent: Qt parent object
        """
        super().__init__(parent)
        self.initUI()

    def initUI(self) -> None:
        """
        UI Constructor
        """

        _lyt = QVBoxLayout(self)
        lbl = QLabel("Grid Page")
        _lyt.addWidget(lbl)
