import os
import sys

from PyQt6.QtCore import QEasingCurve, QPropertyAnimation, Qt
from PyQt6.QtWidgets import (
    QWIDGETSIZE_MAX,
    QApplication,
    QHBoxLayout,
    QMainWindow,
    QPushButton,
    QSplitter,
    QStackedWidget,
    QVBoxLayout,
    QWidget,
)

from .details_view import strata_widget_details_view
from .dropdown import strata_widget_dropdown
from .header_left import strata_widget_header_l
from .header_right import strata_widget_header_r
from .home import strata_widget_home
from .sidebar import strata_widget_sidebar


class strata_window_main(QMainWindow):
    """
    TODO

    * add in widget switching functionality when changing page
    * think about cleaning up the class
    * run execution from here to ../main.py
    """

    def __init__(self, item=None):
        super().__init__()
        self.saved_width = 200
        # NOTE set inverted sheet here
        # self.setStyleSheet("background-color: black;")
        self.item = item
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
        self.header_left = strata_widget_header_l()
        self.header_right = strata_widget_header_r()
        self.sidebar = strata_widget_sidebar()
        self.dropdown_list = strata_widget_dropdown()
        self.details_view = strata_widget_details_view(item=self.item)
        self.home_page = strata_widget_home()

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

        self.pages = QStackedWidget()
        self.pages.addWidget(self.home_page)
        self.pages.addWidget(self.details_view)

        # connecting side buttons to different pages
        self.sidebar.win_database.clicked.connect(
            lambda: self.pages.setCurrentWidget(self.details_view)
        )
        self.sidebar.win_command.clicked.connect(
            lambda: self.pages.setCurrentWidget(self.home_page)
        )

        right_main_layout.addWidget(self.pages)

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

        self.anim = QPropertyAnimation(self.left_widget, b"maximumWidth")
        self.anim.setDuration(150)  # ms
        self.anim.setStartValue(0)
        self.anim.setEndValue(self.saved_width)  # target width
        self.anim.finished.connect(
            lambda: self.left_widget.setMaximumWidth(QWIDGETSIZE_MAX)
        )
        self.anim.start()

    def hide_right_widget(self):
        start_width = self.left_widget.width()
        self.saved_width = start_width
        self.anim = QPropertyAnimation(self.left_widget, b"maximumWidth")
        self.anim.setDuration(150)
        self.anim.setStartValue(start_width)
        self.anim.setEndValue(0)

        def hide_widget():
            self.left_widget.hide()
            self.header_right.expand_left.show()
            self.left_widget.setMaximumWidth(QWIDGETSIZE_MAX)

        self.anim.finished.connect(hide_widget)  # hide fully when collapsed
        self.anim.start()


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
