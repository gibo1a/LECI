import string
def Le_fich(name):
    with open(name, 'r') as file:
        palavras = [i for i in file]
    return palavras

def baralha(lst):
    cipheredstr = ''
    letters = string.ascii_lowercase*2
    letterU = string.ascii_uppercase*2
    for i in range(len(lst)):
        for j in lst[i]:
            if j in letters:
                cipheredstr += letters[letters.index(j) + 3]
            elif j in letterU:
                cipheredstr += letterU[letterU.index(j) + 3]
            elif j.isalpha() == False and j in lst:
                cipheredstr += j
    return cipheredstr

def imprimeTexto(lst):
    print(baralha(lst))

def desbaralha(lst):
    cipheredstr = ''
    letters = string.ascii_lowercase*2
    letterU = string.ascii_uppercase*2
    for i in range(len(lst)):
        for j in lst[i]:
            if j in letters:
                cipheredstr += letters[letters.index(j) - 3]
            elif j in letterU:
                cipheredstr += letterU[letterU.index(j) - 3]
            elif j.isalpha() == False and j in lst:
                cipheredstr += j
    return cipheredstr

print(desbaralha(baralha(Le_fich('teste.txt'))))

    


    