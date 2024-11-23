def ibn(n):
    ibn = 0
    lst = str(n)
    kappa = []

    for l in lst:
        if l.isdigit():
            kappa.append(int(l))

    for i,j in zip(kappa, range(10 , 1, -1)):
        s = i*j
        ibn += s
        if ibn%11 == 0:
            return True
        else:
            return False
            


print(ibn(9992158107))



