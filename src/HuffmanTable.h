#pragma once

#include <utility>
#include <string>

class HuffmanTable {
    void _buildTable(const unsigned char* array, size_t num);
 public:
    enum {ALPHABET_SIZE = 255};
    typedef std::pair<unsigned char, unsigned char> Row; // <lenght in bits, rightmost 8 bit>

    explicit HuffmanTable(const unsigned char* array, size_t num);
    explicit HuffmanTable(const char binaryTable[ALPHABET_SIZE]); // reads min ALPHABET_SIZE bytes
    Row operator[](unsigned char index) const;
    std::string binaryString() const;
 protected:
    Row _table[ALPHABET_SIZE];
};
