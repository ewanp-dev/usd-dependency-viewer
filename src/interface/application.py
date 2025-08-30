import sys
import os

from PyQt6.QtCore import Qt
from PyQt6.QtWidgets import (
    QApplication,
    QHBoxLayout,
    QVBoxLayout,
    QMainWindow,
    QPushButton,
    QSplitter,
    QWidget,
)

from details_view import StrataUIDetailsView
from dropdown import StrataUIDropdown
from sidebar import StrataUISideBar
from header_left import StrataUIHeaderLeft
from header_right import StrataUIHeaderRight


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

        central_layout = QHBoxLayout(central_widget)
        central_layout.setContentsMargins(0, 0, 0, 0)

        # WIDGETS
        self.header_left = StrataUIHeaderLeft()
        self.header_right = StrataUIHeaderRight()
        self.sidebar = StrataUISideBar()
        self.dropdown_list = StrataUIDropdown()
        self.details_view = StrataUIDetailsView()

        self.header_right.expand_left.clicked.connect(self.show_left_widget)
        self.header_left.expand_left.clicked.connect(self.hide_right_widget)

        # LEFT LAYOUT
        self.left_widget = QWidget()
        left_main_layout = QVBoxLayout(self.left_widget)
        left_main_layout.addWidget(self.header_left)
        left_main_layout.addWidget(self.dropdown_list)
        self.left_widget.hide()
        left_main_layout.setContentsMargins(0, 0, 0, 0)

        # RIGHT LAYOUT
        right_widget = QWidget()
        right_main_layout = QVBoxLayout(right_widget)
        right_main_layout.setContentsMargins(0, 0, 0, 0)

        # NOTE need to account for the right properties panel later on

        right_main_layout.addWidget(self.header_right)
        right_main_layout.addWidget(self.details_view)


        # middle section

        splitter = QSplitter(Qt.Orientation.Horizontal)

        splitter.addWidget(self.left_widget)
        splitter.addWidget(right_widget)
        splitter.setSizes([90, 600])

        splitter.setStyleSheet(
            """
        QSplitter::handle {
            background: transparent;
            border: none;
            width: 0px;  /* make the handle invisible */
        }
        """
        )

        central_layout.addWidget(self.sidebar)
        central_layout.addWidget(splitter)

    def show_left_widget(self):
        self.left_widget.show()
        self.header_right.expand_left.hide()

    def hide_right_widget(self):
        self.left_widget.hide()
        self.header_right.expand_left.show()

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
