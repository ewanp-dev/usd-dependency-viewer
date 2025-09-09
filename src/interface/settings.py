from PyQt6.QtWidgets import QLabel, QVBoxLayout, QWidget


class StrataSettingsPage(QWidget):
    """
    The page containing the node graph
    """

    def __init__(self, parent=None) -> None:
        """
        Constructor

        :param parent: Qt parent object
        """
        # TODO make a floating widget
        # TODO make floating exit button abstract
        super().__init__(parent)
        self.initUI()

    def initUI(self) -> None:
        """
        UI Constructor
        """

        _lyt = QVBoxLayout(self)
        lbl = QLabel("Settings Page")
        _lyt.addWidget(lbl)
