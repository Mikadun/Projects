import sys
from PyQt5 import uic, QtCore
from PyQt5.QtWidgets import QApplication, QWidget, QMainWindow

 
class Calculator(QMainWindow):
    def __init__(self):
        super().__init__()
        uic.loadUi('calculator.ui', self)

        self.btn_0.clicked.connect(self.add)
        self.btn_1.clicked.connect(self.add)
        self.btn_2.clicked.connect(self.add)
        self.btn_3.clicked.connect(self.add)
        self.btn_4.clicked.connect(self.add)
        self.btn_5.clicked.connect(self.add)
        self.btn_6.clicked.connect(self.add)
        self.btn_7.clicked.connect(self.add)
        self.btn_8.clicked.connect(self.add)
        self.btn_9.clicked.connect(self.add)

        self.btn_plus.clicked.connect(self.add)
        self.btn_minus.clicked.connect(self.add)
        self.btn_mult.clicked.connect(self.add)
        self.btn_div.clicked.connect(self.add)

        self.btn_left_bracket.clicked.connect(self.add)
        self.btn_right_bracket.clicked.connect(self.add)

        self.btn_dot.clicked.connect(self.add_dot)
        self.btn_clear.clicked.connect(self.clear_all)
        self.btn_backspace.clicked.connect(self.delete_last)
        self.btn_result.clicked.connect(self.get_result)

        self.fsm = {'number': {'(': 'return'}, 
                    'operator': {'operator': self.delete_last, ')': 'return'},
                    '(': {'operator': 'return', ')': 'return'},
                    ')': {'number': 'return', '(': 'return'}
        }

    def add(self, param = None):
        sender = self.sender().text()
        try:
            if self.check_state(self.get_state(sender)):
                value = param or sender
                self.insert_output(value)
        except Exception as e:
            print(e)

    def delete_last(self):
        value = self.get_output()
        self.set_output(value[:-1])
    
    def clear_all(self):
        self.set_output(0)

    def add_dot(self):
        if self.check_state('number'):
            value = self.sender().text()
            output = self.get_output()
            i = len(output) - 1
            while i >= 0 and output[i].isdigit(): i -= 1
            if i < 0 or output[i] != value:
                self.insert_output(value)

    def get_result(self):
        try: self.set_output(str(eval(self.get_output())))
        except: self.set_output('Error')

    def set_output(self, value):
        if len(str(value)) == 0: value = 0
        self.text_output.setText(str(value))

    def insert_output(self, value):
        current = self.get_output()
        if len(current) == 1 and current[0] == '0' and value.isdigit() or current == 'Error':
            current = ''
        self.set_output(current + str(value))

    def get_output(self):
        return self.text_output.text()

    def get_state(self, symbol = None):
        if symbol == None: symbol = self.get_output()[-1]
        if symbol.isdigit() or symbol == '.': return 'number'
        if symbol in '+-*/': return 'operator'
        return symbol

    def check_state(self, next):
        prev = self.get_state()
        if next in self.fsm[prev].keys():
            if self.fsm[prev][next] == 'return':
                return False
            self.fsm[prev][next]()
        return True

if __name__ == '__main__':
    app = QApplication(sys.argv)
    calc = Calculator()
    calc.show()
    sys.exit(app.exec_())