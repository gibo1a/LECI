class Person():
    def __init__(self, age, name):
        self.name = str(name)
        self.age = str(age)
    
    def display(self):
        print(self.name, self.age)

class Student(Person):
    def __init__(self, age, name, section):
        Person.__init__(self, age, name)
        self.section = section
    
    def displayStudent(self):
        print(self.age, self.name, self.section)


x = Student(18, 'Mike', 'Math')
x.displayStudent()