import os

from PyQt6.QtWidgets import QPushButton
from PyQt6.QtGui import QIcon
from PyQt6.QtCore import QSize

class StrataUIButton(QPushButton):

    def __init__(self, icon_name: str=None, tooltip: str=None, width: int=10, height: int=10, parent=None):
        super().__init__(parent)

        elements_folder = os.path.join(os.path.dirname(__file__), "elements")
        icon_path = os.path.join(elements_folder, icon_name) if icon_name else None

        self.setFixedSize(width, height)

        # add in icon path checks
        if icon_path and os.path.exists(icon_path):
            self.setIcon(QIcon(icon_path))
            self.setIconSize(QSize(width - 2, height - 2))

        # tooltip
        if tooltip:
            self.setToolTip(tooltip)


        # add in stylesheets later on down the line
