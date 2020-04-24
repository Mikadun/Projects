
class Balance:
    def __init__(self):
        self.balance = 0
    
    def add_right(self, val):
        self.balance += val
    
    def add_left(self, val):
        self.balance -= val
    
    def result(self):
        return (['L', '=', 'R'])[(self.balance > 0) - (self.balance < 0) + 1]
    
balance = Balance()

balance.add_right(7)
balance.add_left(4)
balance.add_left(1)
print(balance.result())