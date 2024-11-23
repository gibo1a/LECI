def countDigits(str):
    count = 0
    for i in str:
        if i.isdigit():
            count += 1
    return count

print('result:' , countDigits('23 mil 456'))
