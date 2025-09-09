from PyQt6.QtWidgets import QLabel, QVBoxLayout, QWidget


class StrataObjectThumbnail(QWidget):
    """
    Thumbnail widget for grid view
    """

    def __init__(self, parent=None, object=None) -> None:
        """
        Constructor

        :param parent: QT parent object
        :param object: Input USD item
        """
        super().__init__(parent)
        self.object = object
        self.initUI()

    def initUI(self) -> None:
        """
        UI Constructor
        """
        _lyt = QVBoxLayout(self)
        _lyt.addWidget(QLabel("Thumnail"))
