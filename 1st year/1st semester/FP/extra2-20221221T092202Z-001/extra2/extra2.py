def Validate(string):
    if len(string.split('+')[-1]) >= 3:
        for i in string:
            if i.isdigit() or string[0] == '+':
                continue
            else:
                return False
        return True
    else:
        return False

def registarChamada():
    chamadas = dict()
    repetir = True
    origem = input('Telefone Origem? ')
    destino = input('Telefone Destino? ')
    duracao = int(input('Duração? '))
    while repetir:
        while Validate(origem) == False:
            origem = input('Telefone Origem?')
        while Validate(destino) == False:
            destino = input('Telefone Destino? ')
        if Validate(origem) and Validate(destino):
            chamadas[origem] = destino, duracao
            repetir = False
    return chamadas

def lerFicheiro(ficheiro):
    with open(ficheiro, 'r') as file:
        for i in file:
            print('Numero Origem: ', i.split()[0])
            print('Numero Destino: ', i.split()[-2])
            print('Duração: ', i.split()[-1])

def listarClientes(dicionario):
    clientes = [ dicionario[i][0] for i in dicionario]
    return (sorted(set(list(clientes)), key = lambda x: x))

def fatura(dicionario):
    nummero = input('Cliente? ')
    if nummero in dicionario:
        print(dicionario[nummero][0])
        print(dicionario[nummero][-1])


def main():
    repetir = True
    chamadas = dict()
    print('1) Registar chamada')
    print('2) Ler ficheiro')
    print('3) Listar clientes')
    print('4) Fatura')
    print('5) Trerminar')
    while repetir:
        opçao = int(input('Opção? '))
        if opçao == 1:
            chamadas.update(registarChamada())
        elif opçao == 2:
            lerFicheiro()
        elif opçao == 3:
            listarClientes(chamadas)
        elif opçao == 4:
            fatura(chamadas)
        elif opçao == 5:
            repetir = False


main()
