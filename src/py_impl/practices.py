
from utils import LinkedList
from utils import make_linked_list
from utils import BinaryTreeNode


def find_min_rotated(array):
    """
    Find the minimum value in a sorted array's rotation
    [3, 4, 5, 1, 2] is a rotation of [1, 2, 3, 4, 5]
    """
    low = 0
    high = len(array) - 1
    mid = low
    while array[low] >= array[high]:
        if (high - low) == 1:
            mid = high
            break

        mid = (low + high) / 2

        if array[low] <= array[mid]:
            low = mid
        elif array[mid] <= array[high]:
            high = mid

    return array[mid]


def find_min_rotated_test():
    array = [3, 4, 5, 1, 2]
    min = find_min_rotated(array)
    print min


################################################################################################

def power(base, exp):
    """
    Implement power function
    """
    if equal(base, 0.0) and exp < 0:
        raise Exception("Invalid Input")

    exp_abs = abs(exp)

    result = power_helper(base, exp_abs)

    if exp < 0:
        result = 1.0 / result

    return result


def power_helper(base, exp):

    if exp == 0:
        return 1
    if exp == 1:
        return base

    result = power_helper(base, exp/2)
    result *= result

    if (exp - (exp / 2) * 2) == 1:
        result *= base

    return result


def power_test():
    result = power(2, 5)
    print result


def equal(a, b):
    return abs(a - b) < 0.00000001

################################################################################################


def print_1_to_ndigits_numbers(n):

    number = ['0']*n
    digit_idx = n - 1

    while digit_idx >= 0:

        if (ord(number[digit_idx]) - ord('0')) == 9:
            number[digit_idx] = '0'
            digit_idx -= 1
        else:
            number[digit_idx] = chr(ord(number[digit_idx])+1)

        v = ['0']*n
        for i in range(0, n):
            v[i] = number[i]

        print v


def print_1_to_ndigits_numbers_test():
    print_1_to_ndigits_numbers(1)


################################################################################################


def search_sorted_2d_array(mat, num_rows, num_cols, k):
    """
    An 2D array, each row and column is sorted in ascending order, find a given number
    in this 2D array
    """
    col = num_cols - 1
    row = 0

    while col >= 0 and row < num_rows:
        if k == mat[row][col]:
            return True
        elif k < mat[row][col]:
            col -= 1
        elif k > mat[row][col]:
            row += 1

    return False


def search_sorted_2d_array_test():

    mat = [[1, 2, 8, 9], [2, 4, 9, 12], [4, 7, 10, 13], [6, 8, 11, 15]]
    print search_sorted_2d_array(mat, len(mat), len(mat[0]), 7)


################################################################################################

def reverse_print_list(head_node):
    """
    Print a linked list in reversed order
    """
    if head_node is None:
        return

    reverse_print_list(head_node.next)

    print head_node.data


def reverse_print_list_test():
    list = make_linked_list([1, 2, 3, 4, 5])
    reverse_print_list(list.head)


################################################################################################


def build_binary_tree(preorder_seq, inorder_seq):
    """
    Reconstruct a binary tree given the pre-order and inorder sequence
    """
    if len(preorder_seq) != len(inorder_seq):
        raise Exception("Invalid input!")

    build_helper(preorder_seq, inorder_seq, 0, len(preorder_seq)-1, 0, len(inorder_seq)-1)


def build_helper(preorder_seq, inorder_seq, start_preorder, end_preorder, start_inorder, end_inorder):

    root_val = preorder_seq[start_preorder]
    root = BinaryTreeNode(root_val)

    if start_preorder == end_preorder and \
        start_inorder == end_inorder and \
            preorder_seq[start_preorder] == inorder_seq[start_inorder]:
        return root

    root_inorder = 0
    while root_inorder <= end_inorder and root_val != inorder_seq[root_inorder]:
        root_inorder += 1

    left_length = root_inorder - start_inorder

    if left_length > 0:
        root.left = build_helper(preorder_seq,
                                 inorder_seq,
                                 start_preorder+1, start_preorder+left_length,
                                 start_inorder, root_inorder-1)

    if left_length < end_preorder - start_preorder:
        root.right = build_helper(preorder_seq,
                                  inorder_seq,
                                  start_preorder+left_length+1, end_preorder,
                                  root_inorder+1, end_inorder)

    return root

if __name__ == "__main__":
    #find_min_rotated_test()
    #power_test()
    #print_1_to_ndigits_numbers_test()
    #search_sorted_2d_array_test()
    reverse_print_list_test()