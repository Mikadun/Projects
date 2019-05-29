m = [
    [ 2, 3, 0,  0],
    [-1, 4, 1,  0],
    [ 0, 1, 2, -1],
    [ 0, 0, 1,  1]
]

n = 4

b = [-1, -3, 5, 0]

alpha = [0, -m[0][1] / m[0][0]]
for i in range(1, n - 1):
    alpha.append( -m[i][i+1]/( m[i][i] + m[i][i-1] * alpha[i] ) )
    
beta = [0, b[0]/m[0][0]]
for i in range(1, n - 1):
    beta.append(  (-m[i][i-1] * beta[i] + b[i])/( m[i][i] + m[i][i-1] * alpha[i] ) )    
    
x = [0 for i in range(n)]
x[n - 1] = (-m[n - 1][n - 2] * beta[n - 1] + b[n - 1]) / (m[n - 1][n - 1] + m[n - 1][n - 2]*alpha[n - 1]) 

for i in range(n - 1):
    j = n - i - 2
    x[j] = alpha[j + 1]*x[j + 1] + beta[j + 1]
    
print(alpha)
print(beta)
print(x)
print(m[1][2])
    
    
