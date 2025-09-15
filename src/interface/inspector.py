import os

from PyQt6.QtCore import QSize, Qt
from PyQt6.QtGui import QBrush, QColor, QFont
from PyQt6.QtWidgets import (
    QHBoxLayout,
    QSizePolicy,
    QSpacerItem,
    QTableWidget,
    QTableWidgetItem,
    QVBoxLayout,
    QWidget,
)

from .button import StrataAbstractButton
from .dropdowns.properties import StrataDropdownProperties
from .dropdowns.results import StrataDropdownResults
from .dropdowns.sort import StrataDropdownSort
from .dropdowns.view_switcher import StrataDropdownView
from .strata_globals import *


class StrataListPage(QWidget):
    """
    Page for storing the list/grid view of all dependencies
    """

    def __init__(self, item=None) -> None:
        """
        Constructor

        :param item: Input usd class item
        """
        super().__init__()

        self.item = item
        self.item_dependencies = self.item.get_flattened_dependencies()
        self.initUI()

    def initUI(self):
        """
        UI Constructor
        """

        BUTTON_WIDTH, BUTTON_HEIGHT = int(STRATA_BUTTON_WIDTH * 1), int(
            STRATA_BUTTON_HEIGHT * 1
        )
        DETAILS_MARGINS = [10, 5, 10, 5]
        DETAILS_ICON_SIZE = [18, 18]

        _layout_header = QHBoxLayout()
        _layout_header.setContentsMargins(*DETAILS_MARGINS)
        _layout_main = QVBoxLayout()
        _layout_main.setContentsMargins(*DETAILS_MARGINS)

        self.view_switcher = StrataAbstractButton(
            icon_name="viewer.png",
            width=BUTTON_WIDTH,
            height=BUTTON_HEIGHT,
            width_policy=QSizePolicy.Policy.Preferred,
            height_policy=QSizePolicy.Policy.Fixed,
        )
        self.results_list = StrataAbstractButton(
            text=f"{len(self.item_dependencies)} Results",
            width_policy=QSizePolicy.Policy.Preferred,
            height_policy=QSizePolicy.Policy.Fixed,
        )
        self.sort = StrataAbstractButton(
            icon_name="properties.png",
            width=BUTTON_WIDTH,
            height=BUTTON_HEIGHT,
            width_policy=QSizePolicy.Policy.Preferred,
            height_policy=QSizePolicy.Policy.Fixed,
        )
        self.properties = StrataAbstractButton(
            icon_name="filter.png",
            width=BUTTON_WIDTH,
            height=BUTTON_HEIGHT,
            width_policy=QSizePolicy.Policy.Preferred,
            height_policy=QSizePolicy.Policy.Fixed,
        )

        # creating dropdown widget
        self.dropdown_view = StrataDropdownView()
        self.dropdown_results = StrataDropdownResults()
        self.dropdown_sort = StrataDropdownSort()
        self.dropdown_properties = StrataDropdownProperties()

        # self.view_switcher.setText(" Table")
        self.view_switcher.setPadding(5, 5)
        self.view_switcher.setIconSize(QSize(*DETAILS_ICON_SIZE))

        self.results_list.setPadding(5, 5)

        # self.sort.setText(" Sort")
        self.sort.setPadding(5, 5)
        self.sort.setIconSize(QSize(*DETAILS_ICON_SIZE))

        # self.properties.setText(" Properties")
        self.properties.setPadding(5, 5)
        self.properties.setIconSize(QSize(*DETAILS_ICON_SIZE))

        # CONNECTIONS
        self.view_switcher.clicked.connect(
            lambda: self.show_dropdown(self.view_switcher, self.dropdown_view)
        )
        self.results_list.clicked.connect(
            lambda: self.show_dropdown(self.results_list, self.dropdown_results)
        )
        self.properties.clicked.connect(
            lambda: self.show_dropdown(
                self.properties, self.dropdown_properties, shift=75
            )
        )
        self.sort.clicked.connect(
            lambda: self.show_dropdown(self.sort, self.dropdown_sort, shift=100)
        )

        _layout_header.addWidget(self.view_switcher)
        _layout_header.addWidget(self.results_list)
        _layout_header.addStretch(1)
        _layout_header.addWidget(self.sort)
        _layout_header.addWidget(self.properties)

        # NOTE might need to change this to a grid widget
        self.table = QTableWidget()
        self.table.resizeRowsToContents()
        self.table.verticalHeader().setVisible(False)
        self.table.setRowCount(len(self.item_dependencies))
        self.table.setColumnCount(5)
        self.table.setColumnWidth(0, 250)
        self.table.setVerticalScrollBarPolicy(Qt.ScrollBarPolicy.ScrollBarAlwaysOff)
        self.table.setHorizontalScrollBarPolicy(Qt.ScrollBarPolicy.ScrollBarAlwaysOff)
        self.table.setHorizontalHeaderLabels(
            ["file name", "file path", "file size", "extension", "date modified"]
        )

        # setting bespoke font for underline
        # TODO set a specific color for the first item only
        item_font = QFont("Sans Serif", 10)
        item_font.setUnderline(True)
        stylesheet = "QTableWidgetItem { color: red; }"
        for row, name in enumerate(self.item_dependencies):
            name_item = QTableWidgetItem(os.path.splitext(os.path.basename(name))[0])
            name_item.setForeground(QBrush(QColor(143, 131, 106)))
            name_item.setFont(item_font)
            self.table.setItem(row, 0, name_item)
            self.table.setItem(row, 1, QTableWidgetItem(name))
            self.table.setItem(
                row, 2, QTableWidgetItem(f"{os.path.getsize(name) / 1024:.3f}")
            )
            self.table.setItem(
                row, 3, QTableWidgetItem(os.path.splitext(os.path.basename(name))[-1])
            )

        # ---------------------------------------------------------------
        # COLUMN PROPERTIES FUNCTIONALITY
        self.table.setColumnWidth(0, 230)
        self.table.setColumnHidden(1, True)
        self.table.setColumnHidden(2, True)
        self.table.setColumnHidden(3, True)

        self.dropdown_properties.check_name.stateChanged.connect(
            lambda: self.hide_column(0, self.dropdown_properties.check_name)
        )
        self.dropdown_properties.check_path.stateChanged.connect(
            lambda: self.hide_column(1, self.dropdown_properties.check_path)
        )
        self.dropdown_properties.check_size.stateChanged.connect(
            lambda: self.hide_column(2, self.dropdown_properties.check_size)
        )
        self.dropdown_properties.check_extension.stateChanged.connect(
            lambda: self.hide_column(3, self.dropdown_properties.check_extension)
        )

        _layout_main.setContentsMargins(0, 0, 0, 0)
        _layout_main.addLayout(_layout_header)
        _layout_main.addWidget(self.table)
        self.setLayout(_layout_main)

    def hide_column(self, column: int, check) -> None:
        """
        Hides an input column

        :param column: The column number
        :param check: Bool to enable or disable the hide operation
        """
        self.table.setColumnHidden(column, not check.isChecked())

    def show_dropdown(self, btn, dropdown, shift: int = 0) -> None:
        """
        Shows a dropdown widget

        :param btn: The button to connect the dropdown to
        :param dropdown: The dropdown widget
        :param shift: [Optional] Amount to shift the dropdown position by
        """
        pos = btn.mapToGlobal(btn.rect().bottomLeft())
        if shift:
            # TODO move this to a relative option
            pos_x = pos.x() - shift
            pos.setX(pos_x)

        dropdown.move(pos)

        dropdown.show()

    def switch_sort_type(self, index: int) -> None:
        """
        Calls the sort function based on the current index

        :param index: The current index of the sort combo box
        """
        # NOTE this function is currently broken
        # sorting by file name
        if self.dropdown_sort.sort_type.currentText() == "file name":
            if index == 0:
                # the dependencies are returning a NoneType for some reason
                print(type(self.item_dependencies))
                self.item_dependencies = self.dropdown_sort.sort_alphabetically(
                    _list=self.item_dependencies
                )
            else:
                print(type(self.item_dependencies))
                self.item_dependencies = self.dropdown_sort.sort_reverse_alphabetically(
                    _list=self.item_dependencies
                )

    def signal_sort_type_changed(self, type_index, rule_index):
        """
        !!DEPRECATED
        """
        if type_index in [0, 1, 3]:
            # indexes for string based sorting
            self.restructure_list(type_index, rule_index)
        elif type_index == 2:
            # indexes for int based sorting
            pass
        elif type_index in [4, 5]:
            # indexes for time based sorting
            pass
        return

    def restructure_list(self, type_index, rule_index) -> None:
        """
        !!DEPRECATED!!
        """
        if not rule_index:
            self.item_dependencies = sorted(self.item_dependencies)
        elif rule_index == 1:
            self.item_dependencies = sorted(self.item_dependencies).reverse()

        for row, name in enumerate(self.item_dependencies):
            # restructuring the list alphabetically
            continue
