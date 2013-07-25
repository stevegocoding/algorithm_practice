"""
The python implementations of the questions in chapter 1 of <<Cracking the Coding Interview>>
"""

from utils import LinkedList
from utils import make_linked_list
from utils import BinaryTreeNode
from utils import BinarySearchTree
from utils import make_binary_search_tree


def is_unique_chars(str):
    """
    Question 1.1
    """
    occurrences = [0]*256
    for ch in str:
        idx = ord(ch)
        occurrences[idx] += 1
        if occurrences[idx] > 1:
            return False
    return True


def is_unique_chars2(str):
    pass


def is_unique_chars_test():
    print is_unique_chars("aaaa")


def compress_str(str):
    """
    Question 1.5
    """
    repeat_count = 0
    i = 0
    j = 0
    compressed_str = []
    while j < len(str):
        if str[i] == str[j]:
            repeat_count += 1
            j += 1
            if j == len(str):
                compressed_str.append(str[i])
                compressed_str.append(repeat_count)
                break
        else:
            compressed_str.append(str[i])
            compressed_str.append(repeat_count)
            i = j
            repeat_count = 0

    return compressed_str


def compress_str_test():
    print compress_str("aabcccccaaa")


def rotate_mat_90(mat, n):
    """
    Question 1.6
    """
    for layer in range(0, n/2):
        first = layer
        last = n - 1 - layer
        for i in range(first, last):
            pass


def add_list(list_a, list_b):
    """
    Question 2.5
    """
    pa = list_a.head
    pb = list_b.head
    result_list = LinkedList()

    if list_a.length > list_b.length:
        pshort = list_b
    else:
        pshort = list_a

    length_diff = abs(list_b.length - list_a.length)
    for i in range(length_diff):
        pshort.add_node(0)

    carry = 0
    while pa is not None and pb is not None:
        sum = (pa.data + pb.data + carry)
        if sum >= 10:
            sum -= 10
            carry = 1
        else:
            carry = 0

        result_list.add_node(sum)
        pa = pa.next
        pb = pb.next

    return result_list


def add_list_test():

    # 28
    list_a = make_linked_list([8, 2])

    # 172
    list_b = make_linked_list([2, 7, 1])

    print add_list(list_a, list_b)


######################################################################################


def is_tree_balanced(root):
    if check_height(root) == -1:
        return False
    else:
        return True


def check_height(root):
    if root is None:
        return 0

    left_height = check_height(root.left)
    if left_height == -1:
        return -1

    right_height = check_height(root.right)
    if right_height == -1:
        return -1

    height_diff = left_height - right_height
    if abs(height_diff) > 1:
        return -1
    else:
        return max(left_height, right_height) + 1

######################################################################################


def common_ancestor(root, node_p, node_q):
    pass


def common_ancestor_helper(root, node_p, node_q):
    if root is None:
        return None

    if root == node_p or root == node_q:
        return root

    is_p_on_left = covers_node(root.left, node_p)
    is_q_on_left = covers_node(root.right, node_q)

    # find common ancestor
    if is_p_on_left != is_q_on_left:
        return root

    # otherwise they are in the same side, traverse down to this side
    if is_p_on_left:
        child = root.left
    else:
        child = root.right

    return common_ancestor_helper(child, node_p, node_q)


def covers_node(root, node_p):
    if root is None:
        return False
    if root == node_p:
        return True
    return covers_node(root.left, node_p) or covers_node(root.right, node_p)


######################################################################################

def find_sum(root, sum):
    """
    Question 4.9
    """
    d = depth(root)
    path = [0]*d
    find_sum_helper(root, path, sum, 0)


def find_sum_helper(node, path, sum, level):
    if node is None:
        return

    path[level] = node.data

    t = 0
    for n in path:
        t += n
        if t == sum:
            print path

    find_sum_helper(node.left, path, sum, level+1)
    find_sum_helper(node.right, path, sum, level+1)


def depth(root):
    if root is None:
        return 0
    else:
        return 1 + max(depth(root.left), depth(root.right))


if __name__ == "__main__":
    #is_unique_chars_test()
    #compress_str_test()
    add_list_test()