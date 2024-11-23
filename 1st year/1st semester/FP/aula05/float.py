def inputFloatList():
    lst = []
    n = 0
    while n != "":
        n = input("Digite um valor ")
        if n == "":
            break
        else:
            lst.append(int(n))

    return lst

def countLower(lst, v):
    count = 0
    for i in range(len(lst)):
        if lst[i] < v:
            count += 1
    return count


def minmax(lst):
    lst.sort()
    maximo = lst[-1]
    minimo = lst[0]

    return (maximo, minimo)

def final(lst):
    vm = (sum(minmax(lst))/2)
    countLower(lst, vm)








