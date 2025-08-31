import os

from PyQt6.QtWidgets import QPushButton, QSizePolicy
from PyQt6.QtGui import QIcon, QPixmap, QTransform
from PyQt6.QtCore import QSize

class StrataUIButton(QPushButton):
    """
    abstract button class to remove boilerplate code

    TODO
    * make better checks for missing icon path, you should be able to add just text
    * add in better size policy control
    * check to see if there is any more functionality we can add to this
    * add in more checks for missing icons
    """

    def __init__(
            self, 
            icon_name: str=None, 
            tooltip: str=None,
            width_policy=None,
            height_policy=None,
            width: int=10, 
            height: int=10, 
            parent=None, 
            flipped=False
        ):
        super().__init__(parent)

        elements_folder = os.path.join(os.path.dirname(__file__), "elements")
        icon_path = os.path.join(elements_folder, icon_name) if icon_name else None

        if ( width_policy ) and ( height_policy ):
            self.setSizePolicy(width_policy, height_policy)
        else:
            self.setFixedSize(width, height)

        # setting qicon
        if ( os.path.exists(icon_path) ) and ( icon_path ):
            if ( flipped ):
                pixmap = QPixmap(icon_path)
                flipped_pixmap = pixmap.transformed(QTransform().scale(-1, 1))
                icon = QIcon(flipped_pixmap)
            else:
                icon = QIcon(icon_path)

            self.setIcon(icon)
            self.setIconSize(QSize(width - 2, height - 2))


        if ( tooltip ):
            self.setToolTip(tooltip)

        # add in stylesheets later on down the line

    def setPadding(self, horizontal_padding: int, vertical_padding: int):
        """
        sets the vertical and horizontal padding in a stylesheet
        """
        self.setStyleSheet(f"""
            QPushButton {{
                padding: {str(horizontal_padding)}px {str(vertical_padding)}px;
            }}
        """)


