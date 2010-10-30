from collections import Counter
from heapq import *
import pyopencl as cl

__author__ = 'Kulakov Ilya'

class Huffman:
    def __init__(self):
        self.table = {}

    def buildTree(self, string):
        tree = [(freq, sym) for (sym, freq) in Counter(string).most_common()]
        heapify(tree)
        while len(tree) > 1:
            left, right = heappop(tree), heappop(tree)
            heappush(tree, (left[0] + right[0], left, right))
        self.tree = tree

    def buildKeys(self, root, code=''):
        if len(root) == 2:
            self.table.update({root[1] : code})
        else:
            self.buildKeys(root[1], code + '0')
            self.buildKeys(root[2], code + '1')

    def buildTable(self, string):
        self.table = {}
        self.buildTree(string)
        self.buildKeys(self.tree[0])


