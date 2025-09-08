from PyQt6.QtCore import Qt
from PyQt6.QtWidgets import QCheckBox, QVBoxLayout, QWidget


class StrataDropdownProperties(QWidget):
    """
    Shows the different list columns to enable/disable
    """

    def __init__(self) -> None:
        """
        Constructor
        """

        super().__init__()
        self.setWindowFlags(self.windowFlags() | Qt.WindowType.Popup)

        self.check_name = QCheckBox(text="file name")
        self.check_path = QCheckBox(text="file path")
        self.check_size = QCheckBox(text="file size")
        self.check_extension = QCheckBox(text="file extension")
        self.check_modified = QCheckBox(text="date modified")

        # set defaults
        self.check_name.setCheckState(Qt.CheckState.Checked)

        _layout_main = QVBoxLayout(self)
        _layout_main.addWidget(self.check_name)
        _layout_main.addWidget(self.check_path)
        _layout_main.addWidget(self.check_size)
        _layout_main.addWidget(self.check_extension)
        _layout_main.addWidget(self.check_modified)
