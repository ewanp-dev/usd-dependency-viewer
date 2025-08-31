from PyQt6.QtWidgets import QListWidget, QVBoxLayout, QHBoxLayout, QWidget, QPushButton, QSpacerItem, QSizePolicy
from PyQt6.QtCore import QSize
from button import StrataUIButton
from typing import List
from strata_globals import *

class StrataUIDetailsView(QWidget):
    """
    contains a detail list view  where you can select all dependencies

    NOTE 
    this will be implemented with a way to switch between a grid view and details 
    view
    """

    def __init__(self):
        super().__init__()

        self.initUI()

    def initUI(self):
        """
        TODO
        * add in new icon for switcher button
        * fix spacer in the middle to move everything to the left and right
        * fix button size so it fits flush around the button contents
        * start writing tests for the list interface
        * start writing the item to redirect on selection
        * write the ui for switching between grid and details view
        """
        DETAILS_BUTTON_WIDTH: int = 100
        DETAILS_BUTTON_HEIGHT: int = 30

        _layout_header = QHBoxLayout()
        _layout_header.setContentsMargins(10, 5, 10, 5)
        _layout_main = QVBoxLayout()
        _layout_main.setContentsMargins(10, 5, 10, 5)

        # switch to abstract strata class
        self.view_switcher = StrataUIButton(icon_name="table.png", width_policy=QSizePolicy.Policy.Preferred, height_policy=QSizePolicy.Policy.Fixed)
        #self.results_list = StrataUIButton(icon_name="", width=DETAILS_BUTTON_WIDTH, height=STRATA_BUTTON_HEIGHT)
        self.results_list = QPushButton()
        self.sort = StrataUIButton(icon_name="sorting.png", width_policy=QSizePolicy.Policy.Preferred, height_policy=QSizePolicy.Policy.Fixed)
        self.properties = StrataUIButton(icon_name="properties.png", width_policy=QSizePolicy.Policy.Preferred, height_policy=QSizePolicy.Policy.Fixed)
        
        self.view_switcher.setText(" Table")
        self.view_switcher.setPadding(5, 5)
        self.view_switcher.setIconSize(QSize(24, 24))

        self.results_list.setText("0 Results")
        self.results_list.setFixedSize(DETAILS_BUTTON_WIDTH, DETAILS_BUTTON_HEIGHT)
        
        self.sort.setText(" Sort")
        self.sort.setPadding(5, 5)
        self.sort.setIconSize(QSize(24, 24))

        self.properties.setText(" Properties")
        self.properties.setPadding(5, 5)
        self.properties.setIconSize(QSize(24, 24))

        space = QSpacerItem(0, 0, QSizePolicy.Policy.Minimum, QSizePolicy.Policy.Minimum)
        
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
