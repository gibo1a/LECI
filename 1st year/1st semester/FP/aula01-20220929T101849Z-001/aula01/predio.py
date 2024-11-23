andares = int(input("Qual é o número de andares? "))
moradores = int(input("Qual é o número de moradores por piso? "))
distancia_percorrida = (((andares*moradores)*2)*3)
tempo_funcionamento = distancia_percorrida/1
print("O elevador percorre" , distancia_percorrida ,"metros" ,"e funciona" ,tempo_funcionamento ,"horas.")
