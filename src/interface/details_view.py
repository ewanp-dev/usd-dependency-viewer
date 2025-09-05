import os
from typing import List

from PyQt6.QtCore import QSize
from PyQt6.QtGui import QStandardItem, QStandardItemModel
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
        BUTTON_WIDTH, BUTTON_HEIGHT = int(STRATA_BUTTON_WIDTH * 1), int(STRATA_BUTTON_HEIGHT * 1)
        DETAILS_BUTTON_WIDTH: int = 100
        DETAILS_BUTTON_HEIGHT: int = 30
        DETAILS_MARGINS = [10, 5, 10, 5]
        DETAILS_ICON_SIZE = [18, 18]

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
        self.dropdown_properties = strata_dropdown_properties()
        self.dropdown_results = strata_dropdown_results()
        self.dropdown_sort = strata_dropdown_sort()
        self.dropdown_view = strata_dropdown_view_switcher()

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
                self.properties, self.dropdown_properties
            )
        )
        self.sort.clicked.connect(
            lambda checked: self.show_dropdown(self.sort, self.dropdown_sort)
        )

        _layout_header.addWidget(self.view_switcher)
        _layout_header.addWidget(self.results_list)
        _layout_header.addStretch(1)
        # _layout_header.addSpacerItem(space)
        _layout_header.addWidget(self.sort)
        _layout_header.addWidget(self.properties)

        # ---------------------------------------------------------------
        # TABLE WIDGET

        # NOTE might need to change this to a grid widget
        self.table = QTableWidget()
        self.table.resizeRowsToContents()
        self.table.verticalHeader().setVisible(False)
        self.table.setRowCount(len(self.item_dependencies))
        self.table.setColumnCount(5)
        self.table.setColumnWidth(0, 250)
        self.table.setHorizontalHeaderLabels(
            ["file name", "file path", "file size", "extension", "date modified"]
        )

        for row, name in enumerate(self.item_dependencies):
            self.table.setItem(
                row, 0, QTableWidgetItem(os.path.splitext(os.path.basename(name))[0])
            )
            self.table.setItem(row, 1, QTableWidgetItem(name))
            self.table.setItem(
                row, 2, QTableWidgetItem(f"{os.path.getsize(name) / 1024:.3f}")
            )
            self.table.setItem(
                row, 3, QTableWidgetItem(os.path.splitext(os.path.basename(name))[-1])
            )

        # ---------------------------------------------------------------
        # COLUMN PROPERTIES FUNCTIONALITY
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

    def show_dropdown(self, btn, dropdown):
        pos = btn.mapToGlobal(btn.rect().bottomLeft())
        dropdown.move(pos)
        dropdown.show()
