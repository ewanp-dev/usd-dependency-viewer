import os
import sys

from PyQt6.QtCore import QPoint, QPropertyAnimation, Qt
from PyQt6.QtGui import QIcon, QImage, QPixmap, QTransform
from PyQt6.QtWidgets import (
    QWIDGETSIZE_MAX,
    QHBoxLayout,
    QMainWindow,
    QSplitter,
    QStackedWidget,
    QVBoxLayout,
    QWidget,
    QWidgetItem,
)

from .button import StrataAbstractButton
from .grid import StrataGridPage
from .home import StrataHomePage
from .inspector import StrataListPage
from .node import StrataNodePage
from .object import StrataObjectPage
from .strata_globals import *
from .utils import StrataInterfaceUtils
from .widgets.dropdown import StrataDropdown
from .widgets.header import StrataHeader
from .widgets.search import StrataFloatingSearch
from .widgets.settings import StrataSettingsPage
from .widgets.sidebar import StrataPageSwitcher

sys.path.append(
    os.path.expanduser("~/repos/local/qt-force-directed-graph-framework/src")
)
from widget import FDNodeGraphWidget


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
        self.setMouseTracking(True)
        self.dependencies = self.item.get_flattened_dependencies()

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

        central_layout = QVBoxLayout(central_widget)
        central_layout.setContentsMargins(0, 0, 0, 0)

        # ----------------------------------------------------
        # WIDGETS

        self.header = StrataHeader()
        self.sidebar = StrataPageSwitcher()
        self.dropdown_list = StrataDropdown()
        self.dropdown_list.hide()

        self.header.expand.clicked.connect(
            lambda: self.expand_dropdown(checked=self.header.expand.isChecked())
        )

        # ----------------------------------------------------
        # PAGES

        self.home_page = StrataHomePage()
        self.details_view = StrataListPage(item=self.item)
        self.grid_page = StrataGridPage()
        self.node_page = FDNodeGraphWidget()
        self.settings_page = StrataSettingsPage()
        self.object_page = StrataObjectPage()

        self.details_view.table.itemClicked.connect(self.open_item_page)

        # ----------------------------------------------------
        # TMP -- NODEGRAPH
        graph = self.node_page.view
        for i, value in enumerate(self.item.get_flattened_dependencies()):
            # SLOWWWWWWWW
            graph.createNode(node_name=str(value))

        # node_a = graph.createNode(node_name="Something")

        # ----------------------------------------------------
        # RIGHT LAYOUT

        # TODO make right properties panel
        self.pages = QStackedWidget()
        self.pages.addWidget(self.home_page)
        self.pages.addWidget(self.details_view)
        self.pages.addWidget(self.grid_page)
        self.pages.addWidget(self.node_page)
        self.pages.addWidget(self.settings_page)
        self.pages.addWidget(self.object_page)

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

        splitter.setContentsMargins(0, 0, 0, 10)
        splitter.addWidget(self.dropdown_list)
        splitter.addWidget(self.pages)
        splitter.setSizes([90, 600])

        splitter.setStyleSheet(
            f"""
        QSplitter::handle {{
            background-color: {STRATA_APPLICATION_COLORS['color3']};
            width: 10px;  /* make the handle invisible */
        }}
        """
        )

        bottom_layout = QHBoxLayout()
        bottom_layout.addWidget(self.sidebar)
        bottom_layout.addWidget(splitter)
        central_layout.addWidget(self.header)
        central_layout.addLayout(bottom_layout)

        # ----------------------------------------------------
        # FLOATING WIDGET

        self.header.search.clicked.connect(
            lambda: self.show_floating_widget(
                widget=StrataFloatingSearch(
                    self, dependencies=self.item.get_flattened_dependencies()
                )
            )
        )
        self.sidebar.settings.clicked.connect(
            lambda: self.show_floating_widget(widget=StrataSettingsPage(self))
        )

    def open_item_page(self, item: QWidgetItem) -> None:
        row: int = item.row()
        column: int = item.column()

        # do nothing if anything but the first column is selected
        if column:
            return
        file_path: str = self.details_view.table.item(row, 1).text()
        self.object_page.set_object(object=file_path)
        self.pages.setCurrentWidget(self.object_page)
        return None

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

    def expand_dropdown(self, checked: bool = False) -> None:
        """
        Expands the dropdown widget when the button is enabled
        """
        if checked:
            StrataInterfaceUtils().rotate_icon(widget=self.header.expand, angle=90)
            self.dropdown_list.show()
            self.anim = QPropertyAnimation(self.dropdown_list, b"maximumWidth")
            self.anim.setDuration(150)  # ms
            self.anim.setStartValue(0)
            self.anim.setEndValue(self.saved_width)  # target width
            self.anim.finished.connect(
                lambda: self.dropdown_list.setMaximumWidth(QWIDGETSIZE_MAX)
            )
            self.anim.start()
        else:
            StrataInterfaceUtils().rotate_icon(widget=self.header.expand, angle=0)
            start_width = self.dropdown_list.width()
            self.saved_width = start_width
            self.anim = QPropertyAnimation(self.dropdown_list, b"maximumWidth")
            self.anim.setDuration(150)
            self.anim.setStartValue(start_width)
            self.anim.setEndValue(0)

            def hide_widget():
                self.dropdown_list.hide()
                self.dropdown_list.setMaximumWidth(QWIDGETSIZE_MAX)

            self.anim.finished.connect(hide_widget)  # hide fully when collapsed
            self.anim.start()

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


def load_styles(app) -> None:
    """
    Load the qss file into the application
    """
    base_dir = os.path.dirname(__file__)
    style_path = os.path.join(base_dir, "styles", "style.qss")
    with open(style_path, "r") as f:
        qss = f.read()
        app.setStyleSheet(qss)
