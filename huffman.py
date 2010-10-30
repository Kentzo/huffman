from counter import Counter
from heapq import *
import pyopencl as cl

__author__ = 'Kulakov Ilya'

class Huffman:
    def __init__(self):
        self.table = {}
        self.block_size = 1
        self.offsets = []

    def buildTree(self, string):
        tree = [(freq, sym) for (sym, freq) in Counter(string).most_common()]
        heapify(tree)
        while len(tree) > 1:
            left, right = heappop(tree), heappop(tree)
            heappush(tree, (left[0] + right[0], left, right))
        self.tree = tree

    def buildKeys(self, root, code=''):
        if len(root) == 2:
            if len(code):
                self.table.update({root[1] : code})
            else:
                self.table.update({root[1] : '0'})
        else:
            self.buildKeys(root[1], code + '0')
            self.buildKeys(root[2], code + '1')

    def buildTable(self, string):
        self.table = {}
        self.buildTree(string)
        self.buildKeys(self.tree[0])

    def encode(self, string):
        self.buildTable(string)
        result = ''.join([self.table[i] for i in string])
        codeword = ''
        offset = counter = 0
        for i in result:
            codeword += i
            counter += 1     
            offset += 1
            if self.table.has_key(codeword) and counter < self.block_size * 8:
                codeword = ''
                offset = 0
            elif not self.table.has_key(codeword) and counter == self.block_size * 8:
                codeword = ''
                self.offsets.append(offset)
                offset = 0
            if counter == self.block_size * 8:
                counter = 0
                self.offsets.append(0)
            return result


h = Huffman()
print h.encode('addddddddddddddd33333333333333444444444444fffffffffffvvvvvvvvbc')
print h.table
print h.offsets
            


