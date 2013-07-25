
class Node(object):

    def __init__(self, data):
        self.next = None
        self.data = data


class LinkedList(object):

    def __init__(self):
        self.head = None
        self.tail = None
        self.length = 0

    def add_node(self, data):
        new_node = Node(data)

        if self.head is None:
            self.head = new_node

        if self.tail is not None:
            self.tail.next = new_node

        self.tail = new_node

        self.length += 1

    def __str__(self):
        data_list = []
        node = self.head
        while node is not None:
            data_list.append(node.data)
            node = node.next

        return data_list.__str__()


def make_linked_list(array):
    new_list = LinkedList()

    for item in array:
        new_list.add_node(item)

    return new_list


class BinaryTreeNode(object):

    def __init__(self, data):
        self.data = data
        self.left = None
        self.right = None


class BinarySearchTree(object):

    def __init__(self):
        self.root = None

    def add_bst_node(self, root, data):
        if self.root is None:
            self.root = BinaryTreeNode(data)
            return self.root
        else:
            if root is None:
                new_node = BinaryTreeNode(data)
                return new_node
            elif data < root.data:
                root.left = self.add_bst_node(root.left, data)
            else:
                root.right = self.add_bst_node(root.right, data)

            return root

    def inorder_print(self, root):
        if root is None:
            pass
        else:
            self.inorder_print(root.left)
            print root.data
            self.inorder_print(root.right)


def make_binary_search_tree(array):
    bst = BinarySearchTree()

    for item in array:
        bst.add_bst_node(bst.root, item)

    return bst


if __name__ == "__main__":
    #is_unique_chars_test()

    #list = make_linked_list([1, 2, 3, 4, 5])
    #print list

    bst = make_binary_search_tree([6, 4, 7, 3, 8])
    bst.inorder_print(bst.root)