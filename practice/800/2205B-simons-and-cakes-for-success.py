t = int(input())  # read number of test cases

for _ in range(t):
    n = int(input())  # read n for this test case

    k = 1  # build the answer as product of distinct prime factors
    x = n  # work on a copy so n is preserved

    i = 2  # start trial division from the smallest prime

    while i * i <= x:  # only need to check up to sqrt(x)
        if x % i == 0:  # i is a prime factor of x
            k *= i  # include this prime once in the answer

            while x % i == 0:  # strip all occurrences of this prime
                x //= i

        i += 1  # move to the next candidate

    if x > 1:  # a remaining value greater than 1 is a prime factor
        k *= x

    print(k)  # output the minimum k for this test case
