class BankAccount():
    def __init__(self, accountNumber, name, balance):
        self.accountNumber = accountNumber
        self.name = name
        self.balance = balance
    def Deposit(self, money):
        self.balance = self.balance + money
        return dp
    def Withdrawal(self, money):
        self.balance = self.balance - money
        return wt
    
    def bankFees(self):
        self.balance = 0.95*self.balance
        return bk
    def display(self):
        print('Name:', self.name)
        print('AccountNumber:', self.accountNumber)
        print('Balance:', self.balance)
