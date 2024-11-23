def maiuscula(str):
    final = ''
    for n in str:
        if n.isupper():
            n = n.lower()
            final += n
        elif n.islower():
            n = n.upper()
            final += n
        else:
            final += n
    return final
print(maiuscula('UniVERsidade de AVeiro'))


