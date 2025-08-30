import sys
import os

from PyQt6.QtCore import Qt
from PyQt6.QtWidgets import (
    QApplication,
    QHBoxLayout,
    QMainWindow,
    QPushButton,
    QSplitter,
    QVBoxLayout,
    QWidget,
)

from details_view import StrataDetailsView
from dropdown import StrataList
from sidebar import StrataSideBar
from header import StrataUITopBar


class UsdDependencyViewerWindow(QMainWindow):

    def __init__(self):
        super().__init__()

        self.initUI()

    def initUI(self):
        # temporary title
        self.setWindowTitle("Usd Dependency Viewer")
        self.setGeometry(100, 100, 1280, 720)
        central_widget = QWidget()
        central_widget.setContentsMargins(0, 0, 0, 0)
        self.setCentralWidget(central_widget)
        layout = QVBoxLayout(central_widget)
        layout.setContentsMargins(0, 0, 0, 0)

        self.top_bar = StrataUITopBar()
        self.top_bar.expand_left.clicked.connect(self.on_toggle)

        mid_layout = QHBoxLayout()

        self.sidebar = StrataSideBar()
        mid_layout.addWidget(self.sidebar)

        # middle section

        splitter = QSplitter(Qt.Orientation.Horizontal)

        self.dropdown_list = StrataList()
        self.details_view = StrataDetailsView()

        splitter.addWidget(self.dropdown_list)
        splitter.addWidget(self.details_view)
        splitter.setSizes([150, 600])

        splitter.setStyleSheet(
            """
        QSplitter::handle {
            background: transparent;
            border: none;
            width: 0px;  /* make the handle invisible */
        }
        """
        )

        mid_layout.addWidget(splitter)

        layout.addWidget(self.top_bar)
        layout.addLayout(mid_layout)

    def on_toggle(self):
        if self.top_bar.expand_left.isChecked():
            self.dropdown_list.show()
        else:
            self.dropdown_list.hide()


def load_styles(app):
    base_dir = os.path.dirname(__file__)
    style_path = os.path.join(base_dir, "styles", "style.qss")
    with open(style_path, "r") as f:
        qss = f.read()
        app.setStyleSheet(qss)


if __name__ == "__main__":
    # move this to main
    app = QApplication(sys.argv)
    load_styles(app)
    app.setStyle("Fusion")
    window = UsdDependencyViewerWindow()
    window.show()
    sys.exit(app.exec())
