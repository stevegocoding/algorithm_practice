
"""
Multiples of 2, 3, 5
Consider a series in ascending order that only consists of numbers that can be
factored by any combination of 2, 3 and 5.
e.g. 1, 2, 3, 4, 5, 6, 8, 9, 10, 12, 15 ...

For example the numbers 7 (prime), 13 (prime) or 14 (2*7, 7 is not a valid factor),
are not in the above series. They are not factorable by 2, 3, 5.
The number 1 is included by definition.
"""


def find_ugly_number(n):
    if n <= 0:
        return 0

    ugly_numbers = [1]*n
    next_ugly_idx = 1

    mul_2 = 0
    mul_3 = 0
    mul_5 = 0

    while next_ugly_idx < n:
        min_number = min(ugly_numbers[mul_2]*2, ugly_numbers[mul_3]*3, ugly_numbers[mul_5]*5)
        ugly_numbers[next_ugly_idx] = min_number

        while ugly_numbers[mul_2] * 2 <= ugly_numbers[next_ugly_idx]:
            mul_2 += 1

        while ugly_numbers[mul_3] * 3 <= ugly_numbers[next_ugly_idx]:
            mul_3 += 1

        while ugly_numbers[mul_5] * 5 <= ugly_numbers[next_ugly_idx]:
            mul_5 += 1

        next_ugly_idx += 1

    result = ugly_numbers[next_ugly_idx-1]
    return result


if __name__ == "__main__":
    print find_ugly_number(1500)