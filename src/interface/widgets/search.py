from PyQt6.QtCore import QEvent, QPoint, Qt
from PyQt6.QtWidgets import QApplication, QVBoxLayout, QWidget


class strata_widget_search(QWidget):

    def __init__(self, parent=None):
        super().__init__(parent)

        self.setWindowFlags(Qt.WindowType.FramelessWindowHint | Qt.WindowType.Dialog)

        # NOTE might not be neccesary
        self.setAttribute(Qt.WidgetAttribute.WA_TranslucentBackground)

        self.setFocusPolicy(Qt.FocusPolicy.ClickFocus)

        # TODO make dynamic
        self.setFixedSize(500, 500)

        _layout_main = QVBoxLayout(self)

    def show_centered(self):
        if self.parent():
            parent_geom = self.parent().geometry()
            x = parent_geom.x() + (parent_geom.width() - self.width()) // 2
            y = parent_geom.y() + (parent_geom.height() - self.height()) // 2
            self.move(QPoint(x, y))
        self.show()

    def eventFilter(self, obj, event):
        if event.type() == QEvent.Type.MouseButtonPress:
            if not self.geometry().contains(event.globalPosition().toPoint()):
                self.close()
                QApplication.instance().removeEventFilter(self)
        return super().eventFilter(obj, event)
