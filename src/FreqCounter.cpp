#include "FreqCounter.h"

template<>
template<>
FreqCounter<unsigned char>::FreqCounter(const unsigned char* cur, const unsigned char* end) {
    size_t freqs[255] = {0};
    while (cur != end) {
        freqs[*cur] += 1;
        ++cur;
    }
    for (size_t i=0; i<255; ++i) {
        if (freqs[i] > 0) {
            _frequencies.push_back(Freq(i, freqs[i]));
        }
    }
    std::sort(_frequencies.begin(), _frequencies.end(), _comparator_less<unsigned char>);
}
