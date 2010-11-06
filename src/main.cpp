#include <iostream>
#include <fstream>
#include <string>
#include <cassert>
#include "HuffmanTable.h"
#include "FreqCounter.h"
#include "Row.h"
#include <stdio.h>


using namespace std;

extern "C" Row* runEncode(unsigned char* a_data, size_t len, Row a_table[255]);

int main() {
    // ifstream file("./test");
    // file.seekg (0, ios::end);
    // size_t length = file.tellg();
    // file.seekg (0, ios::beg);
    // char* buffer = new char [length];
    // file.read(buffer, length);

  unsigned char str[] = "abcddee";
  unsigned int len = sizeof(str) - 1;
  HuffmanTable h((const unsigned char*)str, len);

  Row rows[255];
  for (unsigned char i = 0; i < HuffmanTable::ALPHABET_SIZE; ++i) {
    rows[i] = h[i];
  }
  Row* encoded = runEncode(str, len, rows);
  for (unsigned int i = 0; i < len; ++i) {
    printf("%i %i\n", encoded[i].code, encoded[i].codelength);
  }
  free(encoded);
    //    delete[] buffer;
  return 0;
}
