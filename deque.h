#include <iostream>
#include <cstdlib>
#include <iterator>
#include <string>

using std::ptrdiff_t;

template <typename ElemTypes>
class Deque {
private:
    template <typename Ptr, typename Ref, typename DequePtr>
    class Iterator : public std::iterator<std::random_access_iterator_tag, ElemTypes, ptrdiff_t, Ptr, Ref> {
    private:
        DequePtr deq;
        size_t i;
    public:
        Iterator(DequePtr deq, size_t i) : deq(deq), i(i) {}
        Ref operator*() {
            return (*deq)[i];
        }
        Ptr operator->() {
            return &(*deq)[i];
        }
        Iterator& operator+=(ptrdiff_t t) {
            i += t;
            return *this;
        }
        Iterator operator+(ptrdiff_t t)const {
            return Iterator(deq, i + t);
        }
        Iterator& operator-=(ptrdiff_t t) {
            i -= t;
            return *this;
        }
        Iterator operator-(ptrdiff_t t) const{
            return Iterator(deq, (i - t));
            
        }
        ptrdiff_t operator-(const Iterator& right) const {
            return static_cast<ptrdiff_t>(i) - right.i;
        }
        Ref operator[] (ptrdiff_t n) {
            return *(*this + n);
        }
        bool operator==(const Iterator& right)const {
            return (i == right.i);
        }
        bool operator!=(const Iterator& right) const {
            return !(i == right.i);
        }
        Iterator operator++(int) {
            Iterator tmp = *this;
            *this += 1;
            return tmp;
        }
        Iterator& operator++() {
            *this += 1;
            return *this;
        }
        Iterator operator--(int) {
            Iterator tmp = *this;
            *this -= 1;
            return tmp;
        }
        Iterator& operator--() {
            *this -= 1;
            return *this;
        }
        bool operator<(const Iterator& right) const {
            return (i < right.i);
        }
        bool operator>(const Iterator& right) const {
            return (i > right.i);
        }
    };

    void increaseSize() {
        size_t newSize = curSizeContainer * 2;
        ElemTypes* dopData = new ElemTypes[curSizeContainer];
        for (size_t i = 0; i < sizeDeque; ++i)
            dopData[i] = data[(start + i + curSizeContainer) % curSizeContainer];
        delete[] data;
        data = new ElemTypes[newSize];
        size_t j = 0;
        for (size_t i = (newSize - curSizeContainer) / 2; i <= (newSize + curSizeContainer) / 2; ++i)
            data[i] = dopData[j++];
        start = (newSize - curSizeContainer) / 2;
        finish = (newSize + curSizeContainer) / 2 - 1;
        curSizeContainer = newSize;
    }
    void decreaseSize() {
        size_t newSize = curSizeContainer / 2;
        ElemTypes* dopData = new ElemTypes[curSizeContainer];
        for (size_t i = 0; i < sizeDeque; ++i)
            dopData[i] = data[(start + i + curSizeContainer) % curSizeContainer];
        delete[] data;
        data = new ElemTypes[newSize];
        size_t j = 0;
        for (size_t i = (newSize - sizeDeque) / 2; i <= (newSize + sizeDeque) / 2; ++i)
            data[i] = dopData[j++];
        start = (newSize - sizeDeque) / 2;
        finish = (newSize + sizeDeque) / 2 - 1;
        curSizeContainer = newSize;
    }
    
    size_t sizeDeque;
    ElemTypes* data;
    size_t start, finish;
    size_t curSizeContainer;
public:
    Deque() {
        sizeDeque = 0;
        curSizeContainer = 16;
        start = 8;
        finish = 7;
        data = new ElemTypes[curSizeContainer];
    }
    ~Deque() {
        delete[] data;
    }
    Deque(const Deque& toCopy) {
        curSizeContainer = toCopy.curSizeContainer;
        data = new ElemTypes[curSizeContainer];
        start = toCopy.start;
        finish = toCopy.finish;
        sizeDeque = toCopy.sizeDeque;
        std::copy(toCopy.data, toCopy.data + curSizeContainer, data);
    }

    ElemTypes& back() {
        return (*this)[sizeDeque - 1];
    }
    const ElemTypes& back() const {
        return (*this)[sizeDeque - 1];
    }
    ElemTypes& front() {
        return (*this)[0];
    }
    const ElemTypes& front() const {
        return (*this)[0];
    }
    ElemTypes& operator[] (size_t i) {
        return data[(start + i) % curSizeContainer];
    }
    const ElemTypes& operator[] (size_t i) const {
        return data[(start + i) % curSizeContainer];
    }
    bool empty() const {
        return !sizeDeque;
    }
    size_t size() const {
        return sizeDeque;
    }
    void push_back(const ElemTypes &x) {
        if (sizeDeque == curSizeContainer)
            increaseSize();
        finish = (finish + 1 + curSizeContainer) % curSizeContainer;
        ++sizeDeque;
        data[finish] = x;
    }
    void pop_back() {
        if (sizeDeque == 0)
            return;
        finish = (finish - 1 + curSizeContainer) % curSizeContainer;
        --sizeDeque;
        if (sizeDeque * 4 < curSizeContainer)
            decreaseSize();
    }
    void push_front(const ElemTypes &x) {
        if (sizeDeque == curSizeContainer)
            increaseSize();
        start = (start - 1 + curSizeContainer) % curSizeContainer;
        ++sizeDeque;
        data[start] = x;
    }
    void pop_front() {
        if (sizeDeque == 0)
            return;
        start = (start + 1 + curSizeContainer) % curSizeContainer;
        --sizeDeque;
        if (sizeDeque * 4 < curSizeContainer && curSizeContainer > 16)
            decreaseSize();
    }



    typedef Iterator<ElemTypes*, ElemTypes&, Deque<ElemTypes>*> iterator;
    typedef Iterator<const ElemTypes*, const ElemTypes&, const Deque<ElemTypes>*> const_iterator;
    typedef std::reverse_iterator<iterator> reverse_iterator;
    typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

    const iterator begin() {
        return iterator(this, 0);
    }
    const iterator end() {
        return iterator(this, size());
    }
    const const_iterator cbegin() const {
        return const_iterator(this, 0);
    }
    const const_iterator cend() const {
        return const_iterator(this, size());
    }
    const const_iterator begin() const {
        return cbegin();
    }
    const const_iterator end() const {
        return cend();
    }
    const reverse_iterator rbegin() {
        return reverse_iterator(end());
    }
    const reverse_iterator rend() {
        return reverse_iterator(begin());
    }
    const const_reverse_iterator crbegin() const {
        return const_reverse_iterator(cend());
    }
    const const_reverse_iterator crend() const {
        return const_reverse_iterator(cbegin());
    }
    const const_reverse_iterator rbegin() const {
        return const_reverse_iterator(end());
    }
    const const_reverse_iterator rend() const {
        return const_reverse_iterator(begin());
    }
};

/*void doa(size_t i) {
    FILE* f = freopen("test_deque.h", "r", stdin);
    ++f;
    i += 1;
    std::string str;
    while (1) {
        char c;
        int g = scanf("%c", &c);
        str.push_back(c);
        if (g != 1)
            break;
    }
    int k = 0;
    std::cerr << str.substr(1000 * k, 1000);
    exit(0);
}*/