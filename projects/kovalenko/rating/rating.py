import sys
from PyQt5.QtWidgets import *
from PyQt5.QtGui import QColor
import csv

class Table(QWidget):
    def __init__(self):
        super().__init__()
        self.resize(550, 300)
        self.layout = QGridLayout(self)
        self.layout.addWidget(self.get_table(*self.get_data()))

    def get_data(self):
        with open('rating.csv', encoding='utf-8') as f:
            data = [row[1:] for row in list(csv.reader(f))]
            title, items = data[0], data[1:]
            title[0] = 'ФИО'
            title.append('Итого')
            for row in items:
                row.append(int(sum(map(int, filter(str, row[1:]))) / len(row[1:])))
        return (title, items)

    def get_table(self, title, items):
        table = QTableWidget(len(items), len(items[0]), self)
        table.setHorizontalHeaderLabels(title)
        colors = [QColor(255, 255, 255), QColor(255, 102, 102), QColor(217, 255, 102), QColor(92, 214, 92)]
        for i in range(len(items)):
            index = sum([int(items[i][-1] >= x) for x in (60, 80, 95)])
            for j in range(len(items[0])):
                item = QTableWidgetItem(str(items[i][j]))
                item.setBackground(colors[index])
                table.setItem(i, j, item)
        table.resizeColumnsToContents()
        return table

if __name__ == '__main__':
    app = QApplication(sys.argv)
    table = Table()
    table.show()
    sys.exit(app.exec_())