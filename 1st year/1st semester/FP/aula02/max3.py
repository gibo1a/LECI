x1 = float(input("number? "))
x2 = float(input("number? "))
x3 = float(input("number? "))

if x1 < x2 and x3 < x2:
    print("Maximum:", x2)
elif x2 < x3 and x1 < x3:
    print("Maximum:", x3)
else:
    print("Maximum", x1)