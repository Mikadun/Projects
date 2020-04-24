
def password_level(password):
    if (len(password) < 6):
        return 'Invalid password'

    types = [0, 0, 0]
    for c in password:
        if (c.isdigit()):
            types[0] = 1
        elif 'A' < c < 'Z':
            types[1] = 1
        elif 'a' < c < 'z':
            types[2] = 1

    return (['Insecure password', 'Weak password', 'Strong password'])[types.count(1) - 1]

print(password_level('qwerty'))