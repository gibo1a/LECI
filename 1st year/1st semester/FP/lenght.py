s = 'abcdEfg'
a = ''

for i ,j in zip(s,range(1, len(s) +1 )):
    i = i.lower()
    a += i.upper()
    a += i*j
    a += '-'
print(a)
