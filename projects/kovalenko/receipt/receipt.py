import sys
from PyQt5 import uic, QtCore
from PyQt5.QtWidgets import QApplication, QWidget, QMainWindow, QCheckBox, QLabel, QSpinBox, QSizePolicy, QTextBrowser
from PyQt5.QtGui import QPixmap
from PyQt5.QtCore import Qt

ITEM_NAMES = ['Тыква', 'Хлеб', 'Кофе', 'Пудинг', 'Яйцо', 'Картофель фри', 'Мороженное', 'Пицца', 'Сок', 'Мясо', 'Ролл', 'Бурито']
ITEM_PRICES = [220, 30, 50, 60, 8, 75, 80, 69, 50, 130, 100, 90]

class Receipt(QMainWindow):
    def __init__(self):
        super().__init__()
        uic.loadUi('receipt.ui', self)

        self.items = []
        n = len(ITEM_NAMES)
        for i in range(n):
            self.items.append(self.createItem(i))
            for j in range(len(self.items[i])):
                self.layoutItems.addWidget(self.items[i][j], i + 1, j + 1)

        self.btnPush.clicked.connect(self.getReceipt)
            
    def createItem(self, i):
        size = (30, 30)
        checkbox = QCheckBox(self)
        checkbox.setSizePolicy(QSizePolicy.Fixed, QSizePolicy.Minimum)

        pixmap = QPixmap('images/item{}.png'.format(i + 1)).scaled(*size, Qt.KeepAspectRatio, Qt.FastTransformation)
        image = QLabel(self)
        image.setSizePolicy(QSizePolicy.Fixed, QSizePolicy.Fixed)
        image.setPixmap(pixmap)

        label = QLabel(ITEM_NAMES[i], self)
    
        price = QLabel('Цена {}р'.format(ITEM_PRICES[i]), self)
        price.setSizePolicy(QSizePolicy.Fixed, QSizePolicy.Minimum)

        spinbox = QSpinBox(self)
        spinbox.setRange(1, 100)
        spinbox.setMaximumWidth(50)

        return (checkbox, image, label, price, spinbox)

    def getReceipt(self):
        lines = []
        sum = 0
        for check, image, label, price, spinbox in self.items:
            if check.isChecked():
                cur_price = int(price.text()[5:-1]) * int(spinbox.value())
                lines.append(str('{} {}*{} шт = {}р'.format(label.text(), price.text()[5:], spinbox.value(), cur_price)))
                sum += cur_price
        lines.append('=' * 20)
        lines.append('Итого: {}р'.format(sum))
        self.popout = ReceiptPopout(self, lines)
        self.popout.show()


class ReceiptPopout(QWidget):
    def __init__(self, *args):
        super().__init__()
        uic.loadUi('receipt_popout.ui', self)
        self.initUI(args)

    def initUI(self, args):
        self.text.setPlainText('\n'.join(args[-1]))

if __name__ == '__main__':
    app = QApplication(sys.argv)
    receipt = Receipt()
    receipt.show()
    sys.exit(app.exec_())