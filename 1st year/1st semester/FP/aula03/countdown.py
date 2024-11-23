def countdown(N):
    if N > 0:
        print(N)
    else:
        print("Enter an positive number! ")
    while N > 0:
        N = N - 1
        print(N)


countdown(10)


