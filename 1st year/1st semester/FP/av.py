def shorten(str):
    short = ''
    lista = []
    for i in str:
        if i.isupper():
            lista.append(i)
    return short.join(lista)


print(shorten("Universidade de Aveiro"))