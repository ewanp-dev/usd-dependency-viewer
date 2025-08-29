import sys

from PyQt6.QtWidgets import (
    QApplication,
    QHBoxLayout,
    QMainWindow,
    QPushButton,
    QVBoxLayout,
    QWidget,
)

from details_view import StrataDetailsView
from sidebar import StrataSideBar


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

        mid_layout = QHBoxLayout()
        self.sidebar = StrataSideBar()
        mid_layout.addWidget(self.sidebar)
        self.details_view = StrataDetailsView()
        mid_layout.addWidget(self.details_view)

        layout.addLayout(mid_layout)


if __name__ == "__main__":
    app = QApplication(sys.argv)
    window = UsdDependencyViewerWindow()
    window.show()
    sys.exit(app.exec())
