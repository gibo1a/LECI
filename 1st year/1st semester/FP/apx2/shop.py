def loadDataBase(fname, produtos):
    """Lê dados do ficheiro fname e atualiza/acrescenta a informação num
    dicionário de produtos com o formato {código: (nome, secção, preço, iva), ...}.
    """
    with open(fname,'r') as file:
        for line in file.readlines()[1:]:
            codigo, nome, seccao, preco, iva = line.split(';')
            produtos[codigo] = (nome, seccao, float(preco), (float(iva[:-2])/100))
        return produtos

def registaCompra(produtos):
    """Lê códigos de produtos (ou códigos e quantidades),
    mostra nome, quantidade e preço final de cada um,
    e devolve dicionário com {codigo: quantidade, ...}
    """
    compra = dict()
    code = input("Code? ")
    while code != "":
        if code.split()[0] in produtos:
            if code.split()[0] not in compra:
                quantidade = 0
                if code.split()[-1] in produtos:
                    quantidade = 1
                else:
                    quantidade = int(code.split()[-1])
            elif code.split()[0] in compra and code.split()[-1] in produtos:
                quantidade += 1
            else:
                quantidade = compra[code.split()[0]][0]
                quantidade += int(code.split()[-1])
            preço_final = (quantidade * produtos[code.split()[0]][2]) + (quantidade * produtos[code.split()[0]][2] * produtos[code.split()[0]][3])
            if code.split()[-1] in produtos:
                print(f'{produtos[code.split()[0]][0]} 1 {(produtos[code.split()[0]][2] + produtos[code.split()[0]][2] * produtos[code.split()[0]][3]):.2f}')
            else:
                print(f'{produtos[code.split()[0]][0]} {int(code.split()[-1])} {int(code.split()[-1]) * (produtos[code.split()[0]][2] + produtos[code.split()[0]][2] * produtos[code.split()[0]][3]):.2f}')
            compra[code.split()[0]] = (quantidade, preço_final)
            code = input("Code? ")
        else:
            code = input("Code? ")
    return compra


def fatura(produtos, compra):
    """Imprime a fatura de uma dada compra."""
    Total_Bruto = 0
    Iva = 0
    seccoes = list()
    for i in compra:
        Total_Bruto += float(compra[i][0]*produtos[i][2])
        Iva += float(compra[i][0]*produtos[i][2]) * produtos[i][3]
        Total_Liquido = Total_Bruto + Iva
        if produtos[i][1] not in seccoes:
            seccoes.append(produtos[i][1])
            print(produtos[i][1])
            if len(str(int((produtos[i][3]*100)))) == 1:
                print(f'{compra[i][0]:>5} {produtos[i][0]} ( {int((produtos[i][3]*100)):>}%) {compra[i][1]:>.2f}')
            else:
                print(f'{compra[i][0]:>5} {produtos[i][0]} ({int((produtos[i][3]*100)):>}%) {compra[i][1]:>.2f}')
        elif produtos[i][1] in seccoes:
            if len(str(int((produtos[i][3]*100)))) == 1:
                print(f'{compra[i][0]:>5} {produtos[i][0]} ( {int((produtos[i][3]*100)):>}%) {compra[i][1]:.2f}')
            else:
                print(f'{compra[i][0]:>5} {produtos[i][0]} ({int((produtos[i][3]*100)):>}%) {compra[i][1]:.2f}')
    if i == list(compra)[-1]:
        print(f"{'Total Bruto:':>30} {Total_Bruto:>10.2f}\n{'Total IVA:':>30} {Iva:>10.2f}\n{'Total Liquido:':>30} {Total_Liquido:>10.2f}")

def main(args):
    # produtos guarda a informação da base de dados numa forma conveniente.
    produtos = {'p1': ('Ketchup.', 'Mercearia Salgado', 1.59, 0.23)}
    # Carregar base de dados principal
    loadDataBase("produtos.txt", produtos)
    # Juntar bases de dados opcionais (Não altere)
    for arg in args:
        loadDataBase(arg, produtos)
    
    
    # Use este código para mostrar o menu e ler a opção repetidamente
    MENU = "(C)ompra (F)atura (S)air ? "
    repetir = True
    compras = []
    while repetir:
        # Utilizador introduz a opção com uma letra minúscula ou maiúscula
        op = input(MENU).upper()
        # Processar opção
        if op == "C":
            # Esta opção regista os produtos de uma compra
            compra = registaCompra(produtos)
            compras.append(compra)

        elif op == "F":
            # Esta opção imprime a fatura de uma compra
            numero_compra = int(input("Numero compra? "))
            fatura(produtos, compras[(numero_compra)-1])
        elif op == "S":
            # Esta opção termina o programa
            repetir = False


    print("Obrigado!")


# Não altere este código / Do not change this code
import sys
if __name__ == "__main__":
    main(sys.argv[1:])

