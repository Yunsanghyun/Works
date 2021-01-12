def 제곱(number):
    return number * number

a = list(range(100))
print(list(map(lambda number: number * number,a)))
