n = int(input()) # Чтение размера снежинки
snow = [['.' for i in range(n)] for j in range(n)] # Создание NxN матрицы, заполненной точками
for i in range(n):
  snow[i][i] = '*' # Заполнение главной диагонали
  snow[i][n - i - 1] = '*' # Заполнение побочной диагонали
  snow[i][n // 2] = '*' # Заполнение среднего столба
  snow[n // 2][i] = '*' # Заполнение средней строки

for i in snow: # Для каждой строки в матрицы снежинки
  print(" ".join(i)) # Вставляем между элементами строки снежинки пробелы и выводим
