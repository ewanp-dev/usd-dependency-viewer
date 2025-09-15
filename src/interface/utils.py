from PyQt6.QtGui import QIcon, QImage, QPixmap, QTransform

from .button import StrataAbstractButton
from .strata_globals import *


class StrataInterfaceUtils:
    """
    Contains all the util functions for the interface
    """

    def rotate_icon(
        self,
        widget: StrataAbstractButton,
        angle: int = 0,
        invert: bool = STRATA_ICONS_INVERTED,
    ) -> None:
        """
            Rotates the icon of the given button widget

        :param widget: The button widget with the icon to rotate
        :param angle: The angle at which to rotate
        """

        # TODO expand this outside of the StrataAbstractButton class
        # NOTE this breaks the buttons color being inverted
        path: str | None = widget.icon_path
        img = QImage(path)

        # NOTE this needs to be removed later on down the line
        if invert:
            img.invertPixels(QImage.InvertMode.InvertRgb)

        pixmap = QPixmap.fromImage(img)
        widget.setIcon(QIcon(pixmap.transformed(QTransform().rotate(angle))))
        return None
