import sys
from PyQt6.QtWidgets import *
from functools import partial


class CalcWindow(QMainWindow):
    # The main window of the application
    def __init__(self):
        super().__init__()
        self.setWindowTitle("calc")
        self.generalLayout = QGridLayout()
        centralWidget = QWidget(self)
        centralWidget.setLayout(self.generalLayout)
        self.setCentralWidget(centralWidget)
        self._create_buttons()
        self._create_display()
        self.value = 0

    def handle_button(self, button):
        if button.palette().button().color().getRgb() == (255, 0, 0, 255):
            button.setStyleSheet("background-color:#00ff00;")
            self.value -= int(button.text())
        else:
            button.setStyleSheet("background-color:#ff0000;")
            self.value += int(button.text())
        self.display.setText(str(self.value))

    def _create_buttons(self):
        for vertical in range(0, 4):
            for horizontal in range(0, 4):
                value = 2 ** ((3 - horizontal) + vertical * 4)
                button = QPushButton(str(value))
                button.setStyleSheet("background-color:#00ff00;")
                button.clicked.connect(partial(self.handle_button, button))
                self.generalLayout.addWidget(button, vertical, horizontal)

    def _create_display(self):
        self.display = QLineEdit()
        self.display.setFixedHeight(35)
        self.display.setReadOnly(True)
        self.generalLayout.addWidget(self.display, 5, 0, 1, 4)


if __name__ == "__main__":
    pycalcApp = QApplication([])
    pycalcWindow = CalcWindow()
    pycalcWindow.show()
    sys.exit(pycalcApp.exec())
