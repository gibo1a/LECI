tempo = int(input("Tempo da chamada "))
tempo2 = tempo - 60
custo = (0.12 + (tempo2 * 0.002))
if tempo <= 60:
    print("Custo da chamada = 0.12$")
else:
    print("Custo da chamada = ", custo)
      
