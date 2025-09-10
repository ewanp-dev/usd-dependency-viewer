import os

from PyQt6.QtCore import QSize
from PyQt6.QtGui import QColor, QFont, QIcon, QImage, QPixmap, QTransform
from PyQt6.QtWidgets import QGraphicsDropShadowEffect, QPushButton

from .strata_globals import *


class StrataAbstractButton(QPushButton):
    """
    Bespoke abstract button class to avoid boilerplate code
    """

    def __init__(
        self,
        icon_name: str = "",
        text: str = "",
        tooltip: str = "",
        width_policy=None,
        height_policy=None,
        width: int = 10,
        height: int = 10,
        parent=None,
        flipped=False,
        inverted=STRATA_ICONS_INVERTED,
        font_size: int = 9,
    ) -> None:
        """
        Cunstructor

        :param icon_name:[Optional] Name of the icon file, full path is absolute
        :param text: [Optional] Any text to add to the button
        :param tooltip: [Optional] The button tooltip
        :param width_policy: [Optional] The buttons width policy
        :param height_policy: [Optional] The buttons height policy
        :param flipped: [Optional] Flips the icon horizontallly
        :param inverted: [Optional] Inverts the icon color
        :param font_size: [Optional] Sets the font size for the button text
        """
        super().__init__(parent)

        elements_folder = os.path.join(os.path.dirname(__file__), "elements")
        icon_path = os.path.join(elements_folder, icon_name) if icon_name else None

        self.base_width, self.base_height = width, height
        self.setFont(QFont("San Francisco", font_size))
        self.setFlat(True)

        if (width_policy) and (height_policy):
            self.setSizePolicy(width_policy, height_policy)
        else:
            self.setFixedSize(self.base_width, self.base_height)

        # setting qicon
        if icon_path:
            if os.path.exists(icon_path):
                self.img = QImage(icon_path)
                if inverted:
                    # NOTE need to find a better color method
                    self.img.invertPixels(QImage.InvertMode.InvertRgb)

                if flipped:
                    pixmap = QPixmap.fromImage(self.img)
                    flipped_pixmap = pixmap.transformed(QTransform().scale(-1, 1))
                    icon = QIcon(flipped_pixmap)
                else:
                    icon = QIcon(QPixmap.fromImage(self.img))

                self.setIcon(icon)
                self.setIconSize(QSize(self.base_width - 2, self.base_height - 2))
            else:
                # NOTE put error message here
                pass

        self.setText(text)

        if tooltip:
            self.setToolTip(tooltip)

        # self.setStyleSheet("background: transparent; border: none;")
        # self.glow_effect = QGraphicsDropShadowEffect(self)
        # self.glow_effect.setBlurRadius(0)
        # self.glow_effect.setOffset(0, 0)
        # self.glow_effect.setColor(QColor(255, 0, 0))
        # self.setGraphicsEffect(self.glow_effect)

    def setPadding(self, horizontal_padding: int, vertical_padding: int) -> None:
        """
        Sets the vertical and horizontal padding in a stylesheet
        """
        self.setStyleSheet(
            f"""
            QPushButton {{
                padding: {str(horizontal_padding)}px {str(vertical_padding)}px;
            }}
        """
        )

        # def enterEvent(self, event) -> None:
        """
        !!TMP DEPRECATED!!

        Adds a glow effect and increases the icon size when hovering

        :param event: The input event type
        """
        # NOTE default 10 but turned off for now
        # self.glow_effect.setBlurRadius(5)
        # self.setIconSize(QSize(self.base_width + 1, self.base_height + 1))
        # super().enterEvent(event)

        # def leaveEvent(self, event) -> None:
        """
        !! TMP DEPRECATED !!

        Reverts eveything to default after hover event is finished

        :param event: The input event type
        """
        # self.glow_effect.setBlurRadius(0)
        # self.setIconSize(QSize(self.base_width, self.base_height))
        # super().leaveEvent(event)
