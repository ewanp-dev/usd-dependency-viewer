import math
from typing import List, Optional, Text

from PyQt6.QtCore import QPointF, QRect, Qt, QTimer
from PyQt6.QtGui import (
    QBrush,
    QColor,
    QEnterEvent,
    QFont,
    QFontDatabase,
    QLinearGradient,
    QPainter,
    QPen,
)
from PyQt6.QtWidgets import (
    QLabel,
    QPushButton,
    QSizePolicy,
    QSpacerItem,
    QVBoxLayout,
    QWidget,
)

from .button import StrataAbstractButton
from .strata_globals import *
from .utils import HoverFilter


class StrataHomePage(QWidget):
    def __init__(self):
        super().__init__()
        self.offset: int = 0

        self.timer = QTimer(self)
        self.timer.timeout.connect(self.update_animation)
        self.timer.start(30)

        self.mouse_pos: QPointF = QPointF(self.width() / 2, self.height() / 2)

        self.text: str = "STRATA"
        self.font: QFont = QFont("Arial", 72, QFont.Weight.Bold)
        self.setMouseTracking(True)  # Create button

        # NOTE move the move function to another function
        self.my_button = QPushButton("Load File", self)

        self.my_button.move(
            int(
                (self.width() // 2)
                + self.width() / 2
                + ((self.mouse_pos.x() - self.width() / 2) * 0.05)
            ),
            int(
                (self.height() // 2)
                + 10
                + ((self.mouse_pos.y() - self.height() / 2) * 0.05)
            ),
        )
        # Style button
        self.my_button.setStyleSheet(
            """
            QPushButton {
                background-color: white;
                color: black;
                border-radius: 8px;
                padding: 6px 12px;
            }
            QPushButton:hover {
                background-color: lightgray;
            }
        """
        )

    def update_animation(self, speed: float = 0.002) -> None:
        # NOTE make speed into a variable
        self.offset += speed
        self.update()

    def mouseMoveEvent(self, a0) -> None:
        self.mouse_pos = a0.position()

        # button move event
        w, h = self.width(), self.height()
        dx = (self.mouse_pos.x() - w / 2) * 0.05
        dy = (self.mouse_pos.y() - h / 2) * 0.05

        base_x = self.width() // 2
        base_y = self.height() // 2

        self.my_button.move(int(base_x - 50 + dx), int(base_y + 100 + dy))  #
        self.update()

    def paintEvent(self, a0) -> None:
        painter: QPainter = QPainter(self)

        w, h = self.width(), self.height()

        bg_dx = (self.mouse_pos.x() - w / 2) * 0.01
        bg_dy = (self.mouse_pos.y() - h / 2) * 0.01

        gradient = QLinearGradient(0 + bg_dx, 0 + bg_dy, w + bg_dx, h + bg_dy)
        shift: int = int(math.sin(self.offset) * 200)

        colors: List[QColor] = [
            QColor("#1C2026"),  # deep blue-black
            QColor("#1C2026"),  # midnight blue
            QColor("#282D35"),  # rich blue
            QColor("#282D35"),  # muted purple
            QColor("#282D35"),  # neon red-pink
        ]

        stops: List[float] = [0.0, 0.25, 0.5, 0.75, 1.0]
        for stop, color in zip(stops, colors):
            gradient.setColorAt(stop, color)

        gradient.setStart((shift % w) + bg_dx, 0 + bg_dy)
        gradient.setFinalStop(((shift + w) % w) + bg_dx, h + bg_dy)

        painter.fillRect(self.rect(), QBrush(gradient))

        # text with parallax
        painter.setFont(self.font)
        painter.setRenderHint(QPainter.RenderHint.Antialiasing)

        base_x = self.width() // 2 - 150
        base_y = self.height() // 2

        dx = (self.mouse_pos.x() - w / 2) * 0.05
        dy = (self.mouse_pos.y() - h / 2) * 0.05

        pen = QPen(QColor("white"), 3)
        painter.setPen(pen)
        painter.setBrush(Qt.BrushStyle.NoBrush)
        painter.drawText(QPointF(base_x + dx, base_y - 80 + dy), self.text)
        painter.drawText(QPointF(base_x + dx, base_y + 80 + dy), self.text)

        # Filled text (middle)
        painter.setPen(pen)
        painter.setBrush(QColor("white"))
        painter.drawText(QPointF(base_x + dx, base_y + dy), self.text)
