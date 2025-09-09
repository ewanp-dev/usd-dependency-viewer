from PyQt6.QtWidgets import QLabel, QVBoxLayout, QWidget


class StrataNodePage(QWidget):
    """
    The page containing the node graph
    """

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
        lbl = QLabel("Node Page")
        _lyt.addWidget(lbl)
