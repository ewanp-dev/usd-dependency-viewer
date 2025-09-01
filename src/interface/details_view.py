from typing import List

from PyQt6.QtCore import QSize
from PyQt6.QtWidgets import (
    QHBoxLayout,
    QListWidget,
    QPushButton,
    QSizePolicy,
    QSpacerItem,
    QVBoxLayout,
    QWidget,
)

from .button import strata_widget_button
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
        self.initUI()
        self.__populate_items()

    def initUI(self):
        """
        TODO
        * add in new icon for switcher button
        * write the ui for switching between grid and details view
        * start writing tests for the list interface
        * start writing the item to redirect on selection
        """
        DETAILS_BUTTON_WIDTH: int = 100
        DETAILS_BUTTON_HEIGHT: int = 30
        DETAILS_MARGINS = [10, 5, 10, 5]
        DETAILS_ICON_SIZE = [14, 14]

        _layout_header = QHBoxLayout()
        _layout_header.setContentsMargins(*DETAILS_MARGINS)
        _layout_main = QVBoxLayout()
        _layout_main.setContentsMargins(*DETAILS_MARGINS)

        # switch to abstract strata class
        self.view_switcher = strata_widget_button(
            icon_name="table.png",
            width_policy=QSizePolicy.Policy.Preferred,
            height_policy=QSizePolicy.Policy.Fixed,
        )
        self.results_list = strata_widget_button(
            text="0 Results",
            width_policy=QSizePolicy.Policy.Preferred,
            height_policy=QSizePolicy.Policy.Fixed,
        )
        self.sort = strata_widget_button(
            icon_name="sorting.png",
            width_policy=QSizePolicy.Policy.Preferred,
            height_policy=QSizePolicy.Policy.Fixed,
        )
        self.properties = strata_widget_button(
            icon_name="properties.png",
            width_policy=QSizePolicy.Policy.Preferred,
            height_policy=QSizePolicy.Policy.Fixed,
        )

        self.view_switcher.setText(" Table")
        self.view_switcher.setPadding(5, 5)
        self.view_switcher.setIconSize(QSize(*DETAILS_ICON_SIZE))

        self.results_list.setPadding(5, 5)

        self.sort.setText(" Sort")
        self.sort.setPadding(5, 5)
        self.sort.setIconSize(QSize(*DETAILS_ICON_SIZE))

        self.properties.setText(" Properties")
        self.properties.setPadding(5, 5)
        self.properties.setIconSize(QSize(*DETAILS_ICON_SIZE))

        space = QSpacerItem(
            0, 0, QSizePolicy.Policy.Minimum, QSizePolicy.Policy.Minimum
        )

        _layout_header.addWidget(self.view_switcher)
        _layout_header.addWidget(self.results_list)
        _layout_header.addStretch(1)
        # _layout_header.addSpacerItem(space)
        _layout_header.addWidget(self.sort)
        _layout_header.addWidget(self.properties)

        # NOTE might need to change this to a grid widget
        self.list = QListWidget()
        _layout_main.setContentsMargins(0, 0, 0, 0)

        _layout_main.addLayout(_layout_header)
        _layout_main.addWidget(self.list)
        self.setLayout(_layout_main)

    def __populate_items(self):
        self.list.addItems(self.item.layers_path)
