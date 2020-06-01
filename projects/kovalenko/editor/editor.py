import sys
from PyQt5 import uic, QtCore
from PyQt5.QtWidgets import QApplication, QWidget, QMainWindow

 
class Editor(QMainWindow):
    def __init__(self):
        super().__init__()
        uic.loadUi('editor.ui', self)

        self.textEdit.textChanged.connect(self.textChanged)

    def textChanged(self):
        self.textView.setHtml(self.textEdit.toPlainText())


if __name__ == '__main__':
    app = QApplication(sys.argv)
    editor = Editor()
    editor.show()
    sys.exit(app.exec_())