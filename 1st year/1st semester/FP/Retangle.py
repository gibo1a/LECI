class Retangle():
    def __init__(self, lenght, width):
        self.lenght = lenght
        self.width = width
    
    def Perimeter(self):
        pm = 2*self.lenght + 2*self.width
        return pm
    def Area(self):
        ar = self.lenght*self.width
        return ar
    def display(self):
        print(self.lenght, self.width, self.Perimeter(), self.Area())

class Parallelepipede(Retangle):
    def __init__(self, width, lenght, height):
        Retangle.__init__(self, width, lenght)
        self.height = height
    
    def Volume(self):
        vl = self.Area() * self.height
        return vl

myRectangle = Retangle(7 , 5)
myRectangle.display()
print("----------------------------------")
myParallelepipede = Parallelepipede(7 , 5 , 2)
print("the volume of myParallelepipede is: " , myParallelepipede.Volume())


