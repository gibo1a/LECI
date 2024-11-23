with open('Lusiadas.txt', 'r') as file:
    letras = {}
    for i in file:
        for j in i:
            if j.isalpha():
                j = j.lower()
                if j not in letras:
                    letras[j] = 1
                else:
                    letras[j] += 1

    print(letras)

