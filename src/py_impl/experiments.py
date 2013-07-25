__author__ = 'magkbdev'


def all_substr(str, start, output):

    if start > len(str):
        return

    print output

    for i in range(start, len(str)):
        a = str[start:i+1]
        output.append(a)
        all_substr(str, i+1, output)
        output.pop()


def all_substr_test():
    all_substr("abcde", 0, [])


################################################################################################


def shift_down(a, start, end):

    root = start

    while (2 * root + 1) <= end:
        child = 2 * root + 1
        swap = root
        if a[child] < a[swap]:
            swap = child
        if child + 1 <= end and a[child+1] < a[swap]:
            swap = child + 1
        if swap != root:
            a[root], a[swap] = a[swap], a[root]
        else:
            return


def shift_up(a, start, end):

    child = end
    while child > start:
        parent = (child - 1) / 2
        if a[child] < a[parent]:
            a[parent], a[child] = a[child], a[parent]
            child = parent
        else:
            return


def heapify(a, count):
    end = 1
    while end < count:
        shift_up(a, 0, end)
        end += 1


import heapq


def heapify_test():
    a = [9, 8, 7, 10, 12, 5, 13]
    b = [9, 10, 8, 12, 1, 20]
    heapify(a, len(a))
    print a

    heapq.heapify(b)
    print b



if __name__ == "__main__":
    #all_substr_test()
    heapify_test()