#include <iostream>
#include <fstream>
#include <string>
#include <cassert>
#include "HuffmanTable.h"
#include "FreqCounter.h"


using namespace std;

// void print(const vector<FreqCounter<char>::Freq>& freq) {
//     cout << freq.size() << endl;
//     for (size_t i=0; i<freq.size(); ++i) {
//         cout << freq[i].first << " : " << freq[i].second << ", ";
//     }
//     cout << endl;
// }

int main() {
    ifstream file("/Users/kent90/Movies/YouTube - CMake-CPack-CTest-CDash Open Source Tools to Build Test and Deploy C++ Software.mp4");
    file.seekg (0, ios::end);
    size_t length = file.tellg();
    file.seekg (0, ios::beg);
    char* buffer = new char [length];
    file.read(buffer, length);

    char str[] = "abcddee";
    HuffmanTable h((const unsigned char*)buffer, length - 1);
    //FreqCounter<unsigned char> test((const unsigned char*)buffer, (const unsigned char*)buffer + length);
    
    // string tableString = h.binaryString();

    // HuffmanTable h2(tableString);

    // assert(h2.binaryString() == tableString);

    // cout << h2.binaryString() << endl;
    
    delete[] buffer;
    return 0;
}
