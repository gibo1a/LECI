import math
A = float(input("Qual é o valor do cateto A? "))
B = float(input("Qual é o valor do cateto B? "))
Hipotenusa = (math.pow(A,2) + math.pow(B,2))
angulo = math.degrees((1/(A/(math.sqrt(Hipotenusa)))))
print("A hipotenusa tem um comprimento de " ,math.sqrt(Hipotenusa) , "e o angulo tem um valor de " ,angulo ,"º")
