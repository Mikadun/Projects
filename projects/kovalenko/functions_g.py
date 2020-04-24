def check_pin(code):
    prime, pal, degree = map(int, code.split('-'))

    for i in range(2, int(prime ** 0.5) + 1):
        if prime % i == 0:
            return 'Incorrect'
    
    pal = str(pal)
    for i in range(len(pal) // 2):
        if pal[i] != pal[len(pal) - i - 1]:
            return 'Incorrect'

    while degree > 1:
        if degree % 2 != 0:
            return 'Incorrect'
        
        degree >>= 1

    return 'Correct'

print(check_pin('131-1221-32'))