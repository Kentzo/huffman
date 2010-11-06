#pragma once

#include <vector>
#include <utility>
#include <algorithm>
#include <map>


template<typename ELEMENT_TYPE>
class FreqCounter {
public:
    typedef std::pair<ELEMENT_TYPE, size_t> Freq;
    typedef std::vector<Freq> Frequencies;
    template<typename InputIterator>
    explicit FreqCounter(InputIterator cur, InputIterator end);
    Frequencies mostCommon(size_t count = -1);

protected:
    Frequencies _frequencies;
};

template<typename ELEMENT_TYPE>
bool _comparator_less(const typename FreqCounter<ELEMENT_TYPE>::Freq& left, const typename FreqCounter<ELEMENT_TYPE>::Freq& right) {
    return left.second < right.second;
}

template<typename ELEMENT_TYPE>
template<typename InputIterator>
FreqCounter<ELEMENT_TYPE>::FreqCounter(InputIterator cur, InputIterator end) {
    std::map<ELEMENT_TYPE, size_t> freqs;
    while (cur != end) {
        freqs[*cur] += 1;
        ++cur;
    }
    typename std::map<ELEMENT_TYPE, size_t>::const_iterator cur_freq = freqs.begin(), end_freq = freqs.end();
    while (cur_freq != end_freq) {
        _frequencies.push_back(Freq(cur_freq->first, cur_freq->second));
        ++cur_freq;
    }
    std::sort(_frequencies.begin(), _frequencies.end(), _comparator_less<ELEMENT_TYPE>);
}

template<typename ELEMENT_TYPE>
std::vector<typename FreqCounter<ELEMENT_TYPE>::Freq> FreqCounter<ELEMENT_TYPE>::mostCommon(size_t count/* = -1*/) {
    size_t size = min(count, _frequencies.size());
    typename FreqCounter<ELEMENT_TYPE>::Frequencies most_common(size);
    std::copy(_frequencies.begin(), _frequencies.begin() + size, most_common.begin());
    return most_common;
}

template<>
template<typename InputIterator>
FreqCounter<unsigned char>::FreqCounter(InputIterator cur, InputIterator end) {
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
