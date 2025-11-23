def sieve_primes(limit: int):
    sieve = [True] * (limit + 1)
    sieve[0] = sieve[1] = False

    p = 2
    while p * p <= limit:
        if sieve[p]:
            for multiple in range(p * p, limit + 1, p):
                sieve[multiple] = False
        p += 1

    return [i for i in range(limit) if sieve[i]]


def print_primes_formatted(primes, per_row=10):
    for i in range(0, len(primes), per_row):
        row = primes[i:i + per_row]
        li = ", ".join(map(str, row))
        if i + per_row < len(primes):
            li += ","
        print(li)


if __name__ == "__main__":
    primes = sieve_primes(100000)
    print_primes_formatted(primes)