def splitFich (ficheiro):
    with open(ficheiro,'r') as file:
        lista = [tuple(i[:-1]) for i in file]
    return lista


def clubesPais(pais):
    for i in lista:
        if pais in i:
            print(lista[1], end=';')
            print(lista[0], end=';')
            print(lista[3], end=';')

#def writeFich(ficheiro):
    #with open((ficheiro), 'w') as file:
        #



def clubes(lista):
    clubes = dict()
    for i in lista:
        if i[1] not in clubes.values():
            if i[2] not in clubes:
                clubes[i[2]] = i[1]
            else:
                clubes[i[2]] += i[1]
    return clubes


def maiorSubida(lista):
    ranking = sorted(lista, key = lambda x:x[4])
    return ranking[-1]


def infoClube(nome):
    for i in lista:
        if nome in i:
            print(i)
        else:
            print('Clube não existe!! ')


def rankingmedio(lista):
    rankings = dict()
    for i in lista:
        if i[1] not in rankings.values():
            if i[2] not in rankings:
                rankings[i[2]] = i[3]
            else:
                rankings[i[2]] += i[3]







