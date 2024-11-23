import random

Modo_de_jogo = int(input("Selecione o modo de jogo! \n Pressione 1 para modo de jogo 1! \n Pressione 2 para modo de jogo 2!\n"))

if Modo_de_jogo == 1:
    Numero_adivinhado= 0
    Numero_a_adivinhar = random.randint(0,100)
    Tentativas = 0
    while Numero_a_adivinhar != Numero_adivinhado:
        Numero_adivinhado = int(input("Tente adivinhar o número!\n"))
        Tentativas += 1
        if Numero_adivinhado < Numero_a_adivinhar:
            print("Muito baixo")
        elif Numero_adivinhado > Numero_a_adivinhar:
            print("Muito alto")
    print(Tentativas)
elif Modo_de_jogo == 2:
    Tentativas = 0
    Numero_a_adivinhar = int(input("Introduza o número a adivinhar!\n"))
    Numero_adivinhado = 0
    while Numero_adivinhado != Numero_a_adivinhar:
        Numero_adivinhado = random.randint(0,100)
        Tentativas += 1
    print(Tentativas)

