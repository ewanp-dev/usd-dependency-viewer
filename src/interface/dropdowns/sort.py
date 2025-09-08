from typing import List

from PyQt6.QtCore import Qt
from PyQt6.QtWidgets import QComboBox, QHBoxLayout, QPushButton, QWidget


class strata_dropdown_sort(QWidget):
    """
    Dropdown to sort the dependencies list
    """

    def __init__(self) -> None:
        """
        Constructor
        """

        super().__init__()
        self.setWindowFlags(self.windowFlags() | Qt.WindowType.Popup)
        self.sort_type = QComboBox()
        self.sort_rule = QComboBox()
        self.clear_sort = QPushButton("C")

        self.types_list = [
            "file name",
            "file path",
            "file size",
            "extension",
            "date created",
            "date modified",
        ]
        self.sort_type.addItems(self.types_list)
        self.sort_rule.addItems(["A->Z", "Z->A"])
        self.sort_type.setPlaceholderText("Text")

        _layout_main = QHBoxLayout(self)
        _layout_main.addWidget(self.sort_type)
        _layout_main.addWidget(self.sort_rule)
        _layout_main.addWidget(self.clear_sort)

        self.sort_type.currentIndexChanged.connect(self.switch_rule)
        self.clear_sort.clicked.connect(self.clear_boxes)

    def clear_boxes(self) -> None:
        """
        Clears all the combo boxes
        """
        self.sort_type.clear()
        self.sort_rule.clear()
        self.sort_type.addItems(self.types_list)

    def switch_rule(self) -> None:
        """
        Change the rule type based on the type index
        """
        self.sort_rule.clear()
        sort_rule_str = ["A->Z", "Z->A"]
        sort_rule_num = ["0->1", "1->0"]
        sort_rule_time = ["Old to new", "New to old"]

        text = self.sort_type.currentText()
        if text in ["file name", "file path", "extension"]:
            self.sort_rule.addItems(sort_rule_str)

        elif text in ["date created", "date modified"]:
            self.sort_rule.addItems(sort_rule_time)

        else:
            self.sort_rule.addItems(sort_rule_num)

    def sort_alphabetically(self, _list: List[str]) -> List[str]:
        """
        Sorts the input list aphabetically

        :param _list: The input list to sort
        """
        return sorted(_list)

    def sort_reverse_alphabetically(self, _list: List[str]) -> List[str]:
        """
        Sorts the input list reverse alphabetically

        :param _list: The input list to sort
        """
        return sorted(_list).reverse()
