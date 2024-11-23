# Complete the code to make the HiLo game...

import random

def main():
    # Pick a random number between 1 and 100, inclusive
    secret = random.randrange(1, 101);
    print("Can you guess my secret?")
    # put your code here
    count = 0
    num = (int(input("Indique um número? ")))
    while num != secret:
        if num < secret:
            print("Low")
            count += 1
            num = (int(input("Indique um número? ")))
        elif num > secret:
            print("High")
            count += 1
            num = (int(input("Indique um número? ")))
        else:
            break
    print("Foram feitas:", count, "tentativas.")





main()
