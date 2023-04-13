import matplotlib.pyplot as plt
import csv

# Читаем данные из файла output.csv
with open('output.csv') as csvfile:
    data = list(csv.reader(csvfile))

# Преобразуем данные из строк в числа
data = [[float(val) for val in row] for row in data]

# Строим график
plt.imshow(data, cmap='hot', aspect='auto', origin='lower')
plt.xlabel('x')
plt.ylabel('t')
plt.colorbar()
plt.show()

