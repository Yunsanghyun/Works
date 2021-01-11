def factorial(n):
    a = 1
    for i in range(1, n + 1):
        a *= i
        print(a)
    return a

def factorial1(n):
    if n == 1:
        return 1
    else:
        return n * factorial1(n-1)

print(factorial1(10))