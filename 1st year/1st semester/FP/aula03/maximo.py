x = int(input("x? "))
y = int(input("y? "))

def max2(x, y):
    if x < y:
        return y
    else:
        return x


def max3(max2, z):
    z = int(input("z? "))
    max2(x, y)

def main():
    z = int(input("z? "))
    max3(max2, z)
    print("Max =", max3(max2, z))

main()




