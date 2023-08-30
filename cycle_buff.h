#ifndef LAB_7_CYCLE_BUFF_H
#define LAB_7_CYCLE_BUFF_H

#define size_t unsigned long long

#include <iostream>
#include <iterator>

template <class T>
class CBuff {
private:
    size_t b_s;
    size_t f, l;
    T *arr;

public:
    class iterator : public std::iterator<std::random_access_iterator_tag, T> {
    private:
        T *ptr;

    public:
        iterator() {
            ptr = nullptr;
        }

        explicit iterator(T *_ptr) {
            ptr = _ptr;
        }

        explicit iterator(T &_ptr) {
            ptr = _ptr;
        }

        T& operator*() const {
            return *ptr;
        }

        T* operator->() {
            return ptr;
        }

        template<typename Iter>
        T& operator[](Iter diff) {
            return ptr[diff];
        }

        bool operator==(iterator t) {
            return ptr == t.ptr;
        }

        bool operator!=(iterator t) {
            return ptr != t.ptr;
        }

        iterator operator+(int diff) {
            return iterator(ptr+diff);
        }

        iterator operator++() {
            ptr++;
            return (*this);
        }

        iterator operator++(int) {
            const iterator t = *this;
            ptr++;
            return t;
        }

        iterator operator-(int diff) {
            return iterator(ptr-diff);
        }

        iterator operator--() {
            ptr--;
            return (*this);
        }

        iterator operator--(int) {
            const iterator t = *this;
            ptr--;
            return t;
        }

        int operator-(iterator diff) {
            return ptr - diff.ptr;
        }

        bool operator<(iterator diff) {
            return *ptr < *diff.ptr;
        }
    };

    CBuff() {
        b_s = 0;
        f = 0;
        l = 0;
        arr = nullptr;
    }

    explicit CBuff(const size_t size) {
        b_s = size;
        arr = new T[b_s];
        f = 0;
        l = 0;

        for(int i = 0; i < b_s; i++)
            arr[i] = 0;
    }

    CBuff(const size_t size, const T val) {
        b_s = size;
        arr = new T[b_s];
        f = 0;
        l = b_s-1;

        for(int i = 0; i < b_s; i++)
            arr[i] = val;
    }

    ~CBuff() {
        delete[] arr;
    }

    iterator begin() {
        return iterator(arr);
    }

    iterator end() {
        return iterator(arr+l+1);
    }

    T& operator[](size_t N) {
        if(N >= b_s)
            throw std::invalid_argument("out of range");

        return arr[N];
    }

    void resize(size_t new_size) {
        int new_l = l % new_size;
        T *new_arr = new T[new_size];

        for(int i = 0; i <= l; i++)
            new_arr[i%new_size] = arr[i];

        delete[] arr;

        b_s = new_size;
        l = new_l;
        f = (l+1)%b_s;
        arr = new_arr;

        while(f != 0) {
            T tmp = arr[b_s-1];
            arr[b_s-1] = arr[0];
            for(int i = b_s-1; i > 0; i--) {
                arr[i] = arr[i-1];
            }
            arr[0] = tmp;

            f = (f+1)%b_s;
            l++;
        }
    }

    size_t size() {
        return b_s;
    }

    T& front() {
        return arr[f];
    }

    void delete_first() {
        l--;
        for(int i = 0; i < l; i++) {
            arr[i] = arr[i+1];
        }
    }

    T& last() {
        return arr[l];
    }

    void delete_last() {
        l--;
    }

    void push(const T t) {
        if(l < b_s-1) {
            T tmp = *end();
            auto i = end();
            while (i != begin()) {
                *i = *(i-1);
                i--;
            }
            *begin() = tmp;
            l++;
        } else {
            *(begin()+1) = t;
            T tmp = *(begin());
            auto i = begin();
            while(i+1 != end()) {
                *i = *(i+1);
                i++;
            }

            *(end()-1) = tmp;
        }
    }

    void push_end(const T t) {
        if(l < b_s-1)
            l++;

        arr[l] = t;
    }

    void put(iterator it, const T val) {
        *(it) = val;
    }

    void eraze(iterator first, iterator last) {
        int len = last - first;
        last--;

        while(last != end()) {
            *(first) = *(last+1);
            first++;
            last++;
        }

        l = l - len;
        if(l < 0)
            l = 0;
    }
};

#endif
