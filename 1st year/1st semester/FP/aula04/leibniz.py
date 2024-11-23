def sum(m):
    soma = (((-1)**m)/((2*m)+1))
    return soma

def leibnizPi4(n = int(input("n? "))):
    for i in range(1, n + 1):
        suma = sum(i)
    return suma

def main():
    leibnizPi4()
print(leibnizPi4())
main()

    