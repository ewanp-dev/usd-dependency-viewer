from PyQt6.QtWidgets import QLabel, QVBoxLayout, QWidget


class StrataObjectPage(QWidget):
    """
    The page for standalone selected USD objects
    """

    def __init__(self, parent=None, object=None) -> None:
        """
        Constructor

        :param parent: QT parent object
        :param object: Input USD object
        """
        super().__init__(parent)
        self.object = object
        self.initUI()

    def initUI(self) -> None:
        """
        UI Constructor
        """
        _lyt = QVBoxLayout(self)
        _lyt.addWidget(QLabel("Object Page"))
