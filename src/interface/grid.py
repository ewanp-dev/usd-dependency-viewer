from PyQt6.QtWidgets import QLabel, QVBoxLayout, QWidget

from .widgets.thumbnail import StrataObjectThumbnail


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
        self.thumbnail = StrataObjectThumbnail()
        lbl = QLabel("Grid Page")
        _lyt.addWidget(lbl)
