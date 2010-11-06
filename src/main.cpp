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
  ifstream file("../test5");
  file.seekg (0, ios::end);
  unsigned int len = file.tellg();
  file.seekg (0, ios::beg);
  char* buffer = new char [len];
  file.read(buffer, len);

  HuffmanTable h((const unsigned char*)buffer, len);

  Row rows[255];
  for (unsigned char i = 0; i < HuffmanTable::ALPHABET_SIZE; ++i) {
    rows[i] = h[i];
    if (rows[i].codelength != 0){
      printf("%i %i\n", rows[i].code, rows[i].codelength);
    }
  }

  // work on GPU
  Row* encoded = runEncode((unsigned char*)buffer, len, rows);

  Row* cpu_encoded = new Row[len];
  //work on CPU
  for (unsigned int i = 0; i < len; ++i) {
      cpu_encoded[i] = rows[buffer[i]];
  }

  for (int i = 0; i < len; ++i) {

    if (encoded[i].code != cpu_encoded[i].code || encoded[i].codelength != cpu_encoded[i].codelength) {
      cout << "Comparison result: " << i << " " << (int)encoded[i].code << "\t" << (int)cpu_encoded[i].code << endl;
      break;
    }
  }
  delete[] cpu_encoded;

  // for (unsigned int i = 0; i < len; ++i) {
  //   printf("%i %i\n", encoded[i].code, encoded[i].codelength);
  // }
  free(encoded);
    //    delete[] buffer;
  return 0;
}
