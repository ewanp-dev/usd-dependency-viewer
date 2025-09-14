from PyQt6.QtWidgets import QLabel, QVBoxLayout, QWidget


class StrataObjectPage(QWidget):
    """
    The page for standalone selected USD objects
    """

    def __init__(self, parent=None, object: str = "") -> None:
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
        self.label = QLabel(self.object)
        _lyt.addWidget(self.label)

    def set_object(self, object: str = "") -> None:
        """
        Sets the core object

        :param object: TMP the path to the usd object
        """
        self.object = object
        self.label.setText(self.object)

    def get_object(self) -> str:
        """
        Gets the path of the current object

        :returns str: The object path
        """
        return self.object
