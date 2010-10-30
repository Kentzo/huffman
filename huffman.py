from counter import Counter
from heapq import *
import pyopencl as cl

__author__ = 'Kulakov Ilya'

class Huffman:
    def __init__(self):
        self.table = {}
        self.rev_table = {}
        self.block_size = 32
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
        self.rev_table = {}
        for key, value in self.table.items():
            self.rev_table.update({value : key})
        codeword = ''
        offset = counter = 0
        for i in result:
            codeword += i
            counter += 1     
            offset += 1
            if self.rev_table.has_key(codeword) and counter <= self.block_size * 8:
                codeword = ''
                offset = 0
                if counter == self.block_size * 8:
                    self.offsets.append(0)
                    counter = 0
            elif not self.rev_table.has_key(codeword) and counter == self.block_size * 8:
                self.offsets.append(offset)
                offset = 0
                counter = 0
        return result

    def decodeBlock(self, string, block, i):
        offset = 0
        if i != 0:
            offset = self.offsets[i-1]
        start = i * self.block_size * 8 - offset
        end = i * self.block_size * 8
        block = string[start:end] + block
        result = codeword = ''
        for j in block:
            codeword += j
            if self.rev_table.has_key(codeword):
                result += self.rev_table[codeword]
                codeword = ''
        return result               
            

    def decode(self, string):        
        result = ''
        for i in range(0, len(string), self.block_size * 8):
            result += self.decodeBlock(string, string[i:i + self.block_size*8], i / (self.block_size * 8))
        return result

h = Huffman()
text_to_encode = open('./test2').read()
print len(text_to_encode)
encoded = h.encode(text_to_encode)
keys = h.rev_table.keys()
keys.sort()
print keys
print h.table
for key in keys:
    print key
print h.offsets
print encoded
decoded = h.decode(encoded)
print decoded
print text_to_encode == decoded 


            


