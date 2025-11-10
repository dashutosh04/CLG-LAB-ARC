import random

natural_numbers = list(range(1, 100000))

for number in natural_numbers:
    print(random.choice(natural_numbers), end=" ")
