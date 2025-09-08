from PyQt6.QtCore import Qt
from PyQt6.QtWidgets import QComboBox, QLabel, QSlider, QVBoxLayout, QWidget

"""
!!DEPRECATED!!
"""


class strata_dropdown_view_switcher(QWidget):
    """
    TODO
    * convert labels to private members
    * fix broken slider
    """

    def __init__(self):
        super().__init__()
        self.setWindowFlags(self.windowFlags() | Qt.WindowType.Popup)
        _layout_main = QVBoxLayout(self)

        # labels as vars so they can be hidden or unhidden
        self.lbl_layout = QLabel("Layout")
        self.lbl_height = QLabel("Row Height")
        self.lbl_card_size = QLabel("Card Size")

        self.view_type = QComboBox()
        self.row_height = QComboBox()
        self.card_size = QSlider()

        self.card_size.setOrientation(Qt.Orientation.Horizontal)

        self.view_type.addItems(["Table", "Cards"])
        self.row_height.addItems(["Short", "Medium", "Tall"])

        self.lbl_card_size.hide()
        self.card_size.hide()

        # SIGNALS
        self.view_type.currentTextChanged.connect(self.switch_item)

        _layout_main.addWidget(self.lbl_layout)
        _layout_main.addWidget(self.view_type)
        _layout_main.addWidget(self.lbl_card_size)
        _layout_main.addWidget(self.card_size)
        _layout_main.addWidget(self.lbl_height)
        _layout_main.addWidget(self.row_height)

    def switch_item(self):
        if self.view_type.currentText() == "Table":
            self.row_height.show()
            self.lbl_height.show()
            self.lbl_card_size.hide()
            self.card_size.hide()

        elif self.view_type.currentText() == "Cards":
            self.row_height.hide()
            self.lbl_height.hide()
            self.lbl_card_size.show()
            self.card_size.show()
