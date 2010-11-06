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
  ifstream file("../test");
  file.seekg (0, ios::end);
  unsigned int len = file.tellg();
  file.seekg (0, ios::beg);
  char* buffer = new char [len];
  file.read(buffer, len);

  HuffmanTable h((const unsigned char*)buffer, len);

  Row rows[255];
  for (unsigned char i = 0; i < HuffmanTable::ALPHABET_SIZE; ++i) {
    rows[i] = h[i];
    printf("%i %i\n", rows[i].code, rows[i].codelength);
  }

  // work on GPU
  Row* encoded = runEncode((unsigned char*)buffer, len, rows);

  Row* cpu_encoded = new Row[len];
  //work on CPU
  for (unsigned int i = 0; i < len; ++i) {
      cpu_encoded[i] = rows[buffer[i]];
  }

  cout << memcmp(encoded, cpu_encoded, len) << endl;
  delete[] cpu_encoded;

  // for (unsigned int i = 0; i < len; ++i) {
  //   printf("%i %i\n", encoded[i].code, encoded[i].codelength);
  // }
  free(encoded);
    //    delete[] buffer;
  return 0;
}
