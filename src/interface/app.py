import os

from PyQt6.QtCore import QPropertyAnimation, Qt
from PyQt6.QtWidgets import (
    QWIDGETSIZE_MAX,
    QHBoxLayout,
    QMainWindow,
    QSplitter,
    QStackedWidget,
    QVBoxLayout,
    QWidget,
)

from .home import StrataHomePage
from .inspector import StrataListPage
from .widgets.dropdown import StrataDropdown
from .widgets.header_left import StrataHeaderLeft
from .widgets.header_right import StrataHeaderRight
from .widgets.search import StrataFloatingSearch
from .widgets.sidebar import StrataPageSwitcher


class StrataApplication(QMainWindow):
    """
    Main application window the package draws from
    """

    def __init__(self, item=None):
        """
        Cunstructor

        :param item: Input USD path object
        """
        super().__init__()
        self.saved_width = 200
        self.item = item
        self.initUI()

    def initUI(self):
        """
        UI Cunstructor
        """

        # temporary title
        self.setWindowTitle("Usd Dependency Viewer")
        self.setGeometry(100, 100, 1280, 720)

        central_widget = QWidget()
        central_widget.setContentsMargins(0, 0, 0, 0)
        self.setCentralWidget(central_widget)

        central_layout = QHBoxLayout(central_widget)
        central_layout.setContentsMargins(0, 0, 0, 0)

        # WIDGETS
        self.header_left = StrataHeaderLeft()
        self.header_right = StrataHeaderRight()
        self.sidebar = StrataPageSwitcher()
        self.dropdown_list = StrataDropdown()
        self.details_view = StrataListPage(item=self.item)
        self.home_page = StrataHomePage()

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
            border: 1px rgb(190, 190, 190);
            width: 0px;  /* make the handle invisible */
        }
        """
        )

        central_layout.addWidget(self.sidebar)
        central_layout.addWidget(splitter)

        # ----------------------------------------------------
        # FLOATING WIDGET
        self.sidebar.win_quick_search.clicked.connect(self.show_floating_search)

    def show_floating_search(self) -> None:
        """
        Show the floating searching widget upon button press
        """
        self.floating_search = StrataFloatingSearch(self)
        self.floating_search.show_centered()

    def show_left_widget(self) -> None:
        """
        Expand the dropdown widget upon button press
        """
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

    def hide_right_widget(self) -> None:
        """
        Hide the dropdown widget upon button press
        """
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


def load_styles(app) -> None:
    """
    Load the qss file into the application
    """
    base_dir = os.path.dirname(__file__)
    style_path = os.path.join(base_dir, "styles", "style.qss")
    with open(style_path, "r") as f:
        qss = f.read()
        app.setStyleSheet(qss)
