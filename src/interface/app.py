import os

from PyQt6.QtCore import QPoint, QPropertyAnimation, Qt
from PyQt6.QtWidgets import (
    QWIDGETSIZE_MAX,
    QHBoxLayout,
    QMainWindow,
    QSplitter,
    QStackedWidget,
    QVBoxLayout,
    QWidget,
)

from .grid import StrataGridPage
from .home import StrataHomePage
from .inspector import StrataListPage
from .node import StrataNodePage
from .object import StrataObjectPage
from .widgets.dropdown import StrataDropdown
from .widgets.header import StrataHeaderLeft, StrataHeaderRight
from .widgets.search import StrataFloatingSearch
from .widgets.settings import StrataSettingsPage
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

        self.setWindowTitle("Strata")

        # TODO make geometry dynamic
        self.setGeometry(100, 100, 1280, 720)

        central_widget = QWidget()
        central_widget.setContentsMargins(0, 0, 0, 0)
        self.setCentralWidget(central_widget)

        central_layout = QHBoxLayout(central_widget)
        central_layout.setContentsMargins(0, 0, 0, 0)

        # ----------------------------------------------------
        # WIDGETS

        self.header_left = StrataHeaderLeft()
        self.header_right = StrataHeaderRight()
        self.sidebar = StrataPageSwitcher()
        self.dropdown_list = StrataDropdown()
        self.details_view = StrataListPage(item=self.item)

        # ----------------------------------------------------
        # PAGES

        self.home_page = StrataHomePage()
        self.grid_page = StrataGridPage()
        self.node_page = StrataNodePage()
        self.settings_page = StrataSettingsPage()
        self.object_page = StrataObjectPage()

        self.header_right.expand_left.clicked.connect(self.show_left_widget)
        self.header_left.expand_left.clicked.connect(self.hide_right_widget)

        # ----------------------------------------------------
        # LEFT LAYOUT

        self.left_widget = QWidget()
        left_main_layout = QVBoxLayout(self.left_widget)
        left_main_layout.addWidget(self.header_left)
        left_main_layout.addWidget(self.dropdown_list)
        self.left_widget.hide()
        left_main_layout.setContentsMargins(0, 0, 0, 0)

        # ----------------------------------------------------
        # RIGHT LAYOUT

        # TODO make right properties panel
        right_widget = QWidget()
        right_main_layout = QVBoxLayout(right_widget)
        right_main_layout.setContentsMargins(0, 0, 0, 0)
        right_main_layout.addWidget(self.header_right)

        self.pages = QStackedWidget()
        self.pages.addWidget(self.home_page)
        self.pages.addWidget(self.details_view)
        self.pages.addWidget(self.grid_page)
        self.pages.addWidget(self.node_page)
        self.pages.addWidget(self.settings_page)
        right_main_layout.addWidget(self.pages)

        # ----------------------------------------------------
        # SIDEBAR BUTTON SIGNALS

        self.sidebar.win_database.clicked.connect(
            lambda: self.pages.setCurrentWidget(self.details_view)
        )
        self.sidebar.win_command.clicked.connect(
            lambda: self.pages.setCurrentWidget(self.home_page)
        )
        self.sidebar.win_library.clicked.connect(
            lambda: self.pages.setCurrentWidget(self.grid_page)
        )
        self.sidebar.win_nodegraph.clicked.connect(
            lambda: self.pages.setCurrentWidget(self.node_page)
        )

        # ----------------------------------------------------
        # SPLITTER

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

        self.sidebar.win_quick_search.clicked.connect(
            lambda: self.show_floating_widget(widget=StrataFloatingSearch(self))
        )
        self.sidebar.settings.clicked.connect(
            lambda: self.show_floating_widget(widget=StrataSettingsPage(self))
        )

    def show_floating_widget(self, widget) -> None:
        """
        Show the floating searching widget upon button press
        """
        if widget.parent():
            parent_geom = widget.parent().geometry()
            x = parent_geom.x() + (parent_geom.width() - widget.width()) // 2
            y = parent_geom.y() + (parent_geom.height() - widget.height()) // 2
            widget.move(QPoint(x, y))
        widget.show()

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
