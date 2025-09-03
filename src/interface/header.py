from typing import List

from button import strata_widget_button
from PyQt6.QtWidgets import QHBoxLayout, Qt, QWidget
from strata_globals import *


class strata_widget_header(QWidget):

    def __init__(self, contents_margins: List[int] = [0, 0, 0, 0], **kwargs):
        """
        TODO
        * finish off this class
        * merge both header classes into this one
        * add in dynamic button creation for left and right sides
        * finish writing the base class
        * run tests
        """
        self.contents_margins = contents_margins
        if kwargs["icon_name"]:
            self.icon_name = kwargs["icon_name"]

        _layout_main = QHBoxLayout()
        _layout_main.setContentsMargins(*contents_margins)
        _layout_main.setSpacing(10)
