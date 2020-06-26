from database_manager import DBManager
import sys
from PyQt5 import uic, QtCore
from PyQt5.QtWidgets import *
from PyQt5.QtGui import QColor

class Table(QMainWindow):
    def __init__(self):
        super().__init__()
        uic.loadUi('films.ui', self)
        self.manager = DBManager()
        self.tableWidget.setColumnCount(5)
        self.tableWidget.setHorizontalHeaderLabels(['ID', 'Название', 'Год', 'Жанр', 'Длительность'])
        self.Init()

        self.btnFind.clicked.connect(self.find)
        self.btnSave.clicked.connect(self.saveChanges)
        self.btnAdd.clicked.connect(self.showAddMenu)

    def initValues(self):
        minYear, maxYear, minDuration, maxDuration = self.manager.getInitValues()
        self.yearFrom.setRange(minYear, maxYear)
        self.yearTo.setRange(minYear, maxYear)
        self.durationFrom.setRange(minDuration, maxDuration)
        self.durationTo.setRange(minDuration, maxDuration)
        self.yearTo.setValue(maxYear)
        self.durationTo.setValue(maxDuration)

    def Init(self):
        self.addMenu = ReceiptPopout(self)
        self.genreBox.insertItem(0, '')
        for i, genre in enumerate(self.manager.getGenres()):
            self.genreBox.insertItem(i + 1, genre)
            self.addMenu.genreBox.insertItem(i, genre)

        self.initValues()

        # Init table
        self.find()
        self.tableWidget.resizeColumnsToContents()
        self.resizeEvent()
        
    def getInput(self):
        title = self.titleEdit.text()
        genre = self.genreBox.currentText()
        yearFrom = self.yearFrom.value()
        yearTo = self.yearTo.value()
        durationFrom = self.durationFrom.value()
        durationTo = self.durationTo.value()
        return (title, genre, yearFrom, yearTo, durationFrom, durationTo)

    def find(self):
        input = self.getInput()
        items = self.manager.get(*input)
        self.lastQuery = items

        self.tableWidget.setRowCount(len(items))
        for i in range(len(items)):
            for j in range(len(items[0])):
                qtItem = QTableWidgetItem(str(items[i][j]))
                if j == 0: qtItem.setFlags(QtCore.Qt.ItemIsEditable)
                self.tableWidget.setItem(i, j, qtItem)
    
    def getItemsFromTable(self):
        n, m = self.tableWidget.rowCount(), self.tableWidget.columnCount()
        items = [[self.tableWidget.item(i, j).text() for j in range(m)] for i in range(n)]
        items = [[int(r[0]), r[1], int(r[2]), r[3], int(r[4])] for r in items]
        return items

    def saveChanges(self):
        for item in self.getItemsFromTable():
            self.manager.update(*item)

    def resizeEvent(self, *args):
        columns_length = sum([self.tableWidget.columnWidth(i) for i in range(self.tableWidget.columnCount())])
        widthWithoutTitle = columns_length - self.tableWidget.columnWidth(1)
        self.tableWidget.setColumnWidth(1, self.width() - widthWithoutTitle - 20)

    def showAddMenu(self):
        self.addMenu.show()

class ReceiptPopout(QWidget):
    def __init__(self, parent):
        super().__init__()
        uic.loadUi('add.ui', self)
        self.parent = parent
        self.btnAdd.clicked.connect(self.add)

    def getInput(self):
        title = self.titleEdit.text()
        genre = self.genreBox.currentText()
        year = self.yearBox.value()
        duration = self.durationBox.value()
        return (title, year, genre, duration)

    def add(self):
        self.parent.manager.add(*self.getInput())
        self.parent.initValues()
        self.close()

if __name__ == '__main__':
    app = QApplication(sys.argv)
    table = Table()
    table.show()
    sys.exit(app.exec_())