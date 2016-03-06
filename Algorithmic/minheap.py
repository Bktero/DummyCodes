"""A module that only provide a min heap to store integers."""

import math
import random

__author__ = 'pgradot'


class MinHeap:
    """A min heap data structure to store integers.

    A heap is made of an array of data that represent a complete binary tree.

    See:
        - https://en.wikipedia.org/wiki/Heap_(data_structure)
        - https://en.wikipedia.org/wiki/Binary_tree#complete
        - http://www.dgp.toronto.edu/people/JamesStewart/378notes/07heaps/
    """

    def __init__(self, capacity=32):
        """Create a new instance.

        Create a new empty heap. It contains no data.
        :param capacity: maximum amount of data in the heap
        :type capacity: int
        """
        self.count = 0
        self.capacity = capacity
        self.array = [None] * capacity

    def __str__(self):
        string = "MinHeap {} / {} (depth={}) --> ".format(self.count, self.capacity, self.depth())
        string += ', '.join(str(value) for value in self.array)
        return string

    def depth(self):
        """Compute the depth of the binary tree.

        The depth of a complete binary is the same as the depth of a perfect binary tree
        with the same number of levels. The formula for perfect trees is here
        (even if called "complete"):
        http://www.dgp.toronto.edu/people/JamesStewart/378notes/07heaps/

        To compute the depth of the tree, we first need to compute the number of
        elements that would be needed to fill the last level.

        :return: the depth of the tree
        :rtype: int
        """
        if self.count == 0:
            return 0

        total = 1
        level = 1
        while total < self.count:
            level *= 2
            total += level
        return int(math.log(total + 1, 2))

    def pretty_print(self):
        """Print the content of the heap as a pretty heap."""
        if self.count == 0:
            print("(empty)")
            return

        # Number of printed elements
        n_printed = 0

        for level in range(0, self.depth()):
            # Max number of elements at this level
            number_max = int(math.pow(2, level))

            # Actual number of elements at this level
            number = min(number_max, self.count - n_printed)

            # Spacing between elements
            spacing = int(pow(2, self.depth() - level))

            # Print elements
            print("\t" * (spacing // 2 - 1), end="")

            for i in range(0, number):
                print("{}".format(self.array[n_printed + i]), end="\t" * spacing)

            # End of line
            print("")

            # Update number of printed elements
            n_printed += number

    def push(self, number):
        """Push a new value in the heap.

        The value is added at the end of the tree and then the tree is re-balanced.

        :param number: the value to push in the heap
        :type number: int
        """
        if self.count == self.capacity:
            raise Exception("Heap is full!")

        if self.count == 0:
            # First element!
            self.array[0] = number
            self.count = 1
            return

        # Insert new element at the end of the array
        self.array[self.count] = number

        # Shift up new element as much as needed
        index = self.count
        parent_index = (index - 1) // 2

        # print("number", index, '==>', number)
        # print("parent", parent_index, '==>', self.array[parent_index])

        while index > 0 and self.array[parent_index] > self.array[index]:
            # Swap elements, shifting up element to its parent's location
            parent = self.array[parent_index]
            self.array[parent_index] = self.array[index]
            self.array[index] = parent

            # Update indexes for next iteration
            index = parent_index
            parent_index = (index - 1) // 2
            # print("i", index, '==>', self.array[index])
            # print("p", parent_index, '==>', self.array[parent_index])

        # Increase element count
        self.count += 1

    def pop(self):
        """Pop the root value of the tree.

        :return : the value at the root of the tree (that is, the min value because this is a min heap)
        :rtype : int
        """
        if self.count == 0:
            # Heap is already empty
            return None

        # Extract root
        root = self.array[0]

        # Decrease element count
        self.count -= 1

        # Place last element at the root
        self.array[0] = self.array[self.count]
        self.array[self.count] = None

        # Shift down the new root as much as needed
        index = 0
        left_child_index = 2 * index + 1
        right_child_index = 2 * index + 2

        while True:

            if left_child_index >= self.count or self.array[left_child_index] is None:
                # End of tree
                break

            if self.array[right_child_index] is None:
                # There is only the left child
                if self.array[left_child_index] < self.array[index]:
                    # The element can be swapped down
                    child_index = left_child_index
                else:
                    # Don't swap, end of tree
                    break
            else:
                # There are two children
                if self.array[left_child_index] >= self.array[index] \
                        and self.array[right_child_index] >= self.array[index]:
                    # Both children are greater than the element
                    # The element is correctly place, stop swapping
                    break
                else:
                    # Swap with the lowest child
                    if self.array[left_child_index] < self.array[right_child_index]:
                        child_index = left_child_index
                    else:
                        child_index = right_child_index

            # Swap elements
            child = self.array[child_index]
            self.array[child_index] = self.array[index]
            self.array[index] = child

            # Update indexes for next iteration
            index = child_index
            left_child_index = 2 * index + 1
            right_child_index = 2 * index + 2

        # Return extracted root
        return root


def test_basic():
    """Run a basic test for the MinHeap class."""
    # Push some data
    heap = MinHeap()
    heap.push(0)
    heap.push(11)
    heap.push(18)
    heap.push(13)
    heap.push(15)
    heap.push(20)

    assert heap.count == 6, "Count is invalid"

    # Check additions
    expected = [0, 11, 18, 13, 15, 20]
    for i in range(0, heap.count):
        assert heap.array[i] == expected[i], "Invalid data at index {}".format(i)

    # Remove elements
    assert heap.pop() == 0, "Bad pop"
    assert heap.pop() == 11, "Bad pop"
    assert heap.pop() == 13, "Bad pop"
    assert heap.pop() == 15, "Bad pop"
    assert heap.pop() == 18, "Bad pop"
    assert heap.pop() == 20, "Bad pop"

    # Push and check again
    heap.push(3)

    expected = [3, 13, 11, 20, 15, 18]
    for i in range(0, heap.count):
        assert heap.array[i] == expected[i], "Invalid data at index {}".format(i)


def advanced_test():
    """Run an advanced test for the MinHeap class."""
    max_elements = 128000
    added = []
    heap = MinHeap(max_elements)

    # Generate data, save same and push them to the heap
    for _ in range(0, max_elements):
        number = random.randint(-1024, 1024)
        added.append(number)
        heap.push(number)

    assert heap.count == max_elements, "Count is invalid"
    assert len(added) == max_elements, "Added's length is invalid"

    # Pop them all
    popped = []

    for _ in range(0, max_elements):
        number = heap.pop()
        popped.append(number)

    assert heap.count == 0, "Count is invalid, heap should be empty"

    # Check pop data
    added.sort()
    assert added == popped

    # Nothing left to pop
    assert heap.pop() is None, "Heap should not be pop-able"

    # So far, so good
    print("Test end with success")


test_basic()
advanced_test()
# http://www.dgp.toronto.edu/people/JamesStewart/378notes/07heaps/
