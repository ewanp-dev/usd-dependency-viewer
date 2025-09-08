from typing import List

from PyQt6.QtWidgets import QHBoxLayout, QWidget

from ..strata_globals import *


class strata_widget_header(QWidget):
    """
    Merged header classes
    """

    def __init__(self, contents_margins: List[int] = [0, 0, 0, 0], **kwargs) -> None:
        """
        Cunstructor

        :param contents_margins: Set the contents margins to avoid boilerplate code
        """
        # TODO merge header classes into here
        self.contents_margins = contents_margins
        if kwargs["icon_name"]:
            self.icon_name = kwargs["icon_name"]

        _layout_main = QHBoxLayout()
        _layout_main.setContentsMargins(*contents_margins)
        _layout_main.setSpacing(10)
