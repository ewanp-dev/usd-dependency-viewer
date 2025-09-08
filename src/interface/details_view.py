import os

from PyQt6.QtCore import QSize, Qt
from PyQt6.QtGui import QFont, QFontDatabase, QStandardItem, QStandardItemModel
from PyQt6.QtWidgets import (
    QHBoxLayout,
    QListWidget,
    QPushButton,
    QSizePolicy,
    QSpacerItem,
    QTableWidget,
    QTableWidgetItem,
    QVBoxLayout,
    QWidget,
)

from .button import strata_widget_button
from .dropdowns.properties import strata_dropdown_properties
from .dropdowns.results import strata_dropdown_results
from .dropdowns.sort import strata_dropdown_sort
from .dropdowns.view_switcher import strata_dropdown_view_switcher
from .strata_globals import *


class strata_widget_details_view(QWidget):
    """
    contains a detail list view  where you can select all dependencies

    NOTE
    this will be implemented with a way to switch between a grid view and details
    view
    """

    def __init__(self, item=None):
        super().__init__()

        self.item = item
        self.item_dependencies = self.item.get_flattened_dependencies()
        self.initUI()
        # self.__populate_items()

    def initUI(self):
        """
        TODO
        * add in new icon for switcher button
        * write the ui for switching between grid and details view
        * start writing tests for the list interface
        * start writing the item to redirect on selection
        """
        BUTTON_WIDTH, BUTTON_HEIGHT = int(STRATA_BUTTON_WIDTH * 1), int(
            STRATA_BUTTON_HEIGHT * 1
        )
        DETAILS_BUTTON_WIDTH: int = 100
        DETAILS_BUTTON_HEIGHT: int = 30
        DETAILS_MARGINS = [10, 5, 10, 5]
        DETAILS_ICON_SIZE = [18, 18]

        # print(QFontDatabase.families())

        _layout_header = QHBoxLayout()
        _layout_header.setContentsMargins(*DETAILS_MARGINS)
        _layout_main = QVBoxLayout()
        _layout_main.setContentsMargins(*DETAILS_MARGINS)

        # switch to abstract strata class
        self.view_switcher = strata_widget_button(
            icon_name="meal/view.png",
            width=BUTTON_WIDTH,
            height=BUTTON_HEIGHT,
            width_policy=QSizePolicy.Policy.Preferred,
            height_policy=QSizePolicy.Policy.Fixed,
        )
        self.results_list = strata_widget_button(
            text=f"{len(self.item_dependencies)} Results",
            width_policy=QSizePolicy.Policy.Preferred,
            height_policy=QSizePolicy.Policy.Fixed,
        )
        self.sort = strata_widget_button(
            icon_name="meal/sort.png",
            width=BUTTON_WIDTH,
            height=BUTTON_HEIGHT,
            width_policy=QSizePolicy.Policy.Preferred,
            height_policy=QSizePolicy.Policy.Fixed,
        )
        self.properties = strata_widget_button(
            icon_name="meal/filter.png",
            width=BUTTON_WIDTH,
            height=BUTTON_HEIGHT,
            width_policy=QSizePolicy.Policy.Preferred,
            height_policy=QSizePolicy.Policy.Fixed,
        )

        # creating dropdown widget
        self.dropdown_view = strata_dropdown_view_switcher()
        self.dropdown_results = strata_dropdown_results()
        self.dropdown_sort = strata_dropdown_sort()
        self.dropdown_properties = strata_dropdown_properties()

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

        space = QSpacerItem(
            0, 0, QSizePolicy.Policy.Minimum, QSizePolicy.Policy.Minimum
        )

        # CONNECTIONS
        self.view_switcher.clicked.connect(
            lambda checked: self.show_dropdown(self.view_switcher, self.dropdown_view)
        )
        self.results_list.clicked.connect(
            lambda checked: self.show_dropdown(self.results_list, self.dropdown_results)
        )
        self.properties.clicked.connect(
            lambda checked: self.show_dropdown(
                self.properties, self.dropdown_properties, shift=75
            )
        )
        self.sort.clicked.connect(
            lambda checked: self.show_dropdown(self.sort, self.dropdown_sort, shift=100)
        )

        # self.dropdown_sort.sort_rule.currentIndexChanged.connect(
        # lambda: self.signal_sort_type_changed(
        # type_index=0, rule_index=self.dropdown_sort.sort_rule.currentIndex()
        # )
        # )

        _layout_header.addWidget(self.view_switcher)
        _layout_header.addWidget(self.results_list)
        _layout_header.addStretch(1)
        # _layout_header.addSpacerItem(space)
        _layout_header.addWidget(self.sort)
        _layout_header.addWidget(self.properties)

        # ---------------------------------------------------------------
        # SORTING SIGNALS

        # self.dropdown_sort.sort_rule.currentIndexChanged.connect(
        # lambda: self.switch_sort_type(
        # index=self.dropdown_sort.sort_rule.currentIndex()
        # )
        # )

        # ---------------------------------------------------------------
        # TABLE WIDGET

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
            lambda checked: self.hide_column(0, self.dropdown_properties.check_name)
        )
        self.dropdown_properties.check_path.stateChanged.connect(
            lambda checked: self.hide_column(1, self.dropdown_properties.check_path)
        )
        self.dropdown_properties.check_size.stateChanged.connect(
            lambda checked: self.hide_column(2, self.dropdown_properties.check_size)
        )
        self.dropdown_properties.check_extension.stateChanged.connect(
            lambda checked: self.hide_column(
                3, self.dropdown_properties.check_extension
            )
        )

        _layout_main.setContentsMargins(0, 0, 0, 0)
        _layout_main.addLayout(_layout_header)
        _layout_main.addWidget(self.table)
        self.setLayout(_layout_main)

    def hide_column(self, column, check):
        self.table.setColumnHidden(column, not check.isChecked())

    def show_dropdown(self, btn, dropdown, shift: int = 0):
        pos = btn.mapToGlobal(btn.rect().bottomLeft())
        if shift:
            # TODO move this to a relative option
            # make pos x the max x position of the window
            pos_x = pos.x() - shift
            pos.setX(pos_x)

        dropdown.move(pos)

        dropdown.show()

    def switch_sort_type(self, index: int) -> None:
        """
        calls the sort function based on the current index
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

    def restructure_list(self, type_index, rule_index):
        if not rule_index:
            self.item_dependencies = sorted(self.item_dependencies)
        elif rule_index == 1:
            self.item_dependencies = sorted(self.item_dependencies).reverse()

        for row, name in enumerate(self.item_dependencies):
            # restructuring the list alphabetically
            continue
