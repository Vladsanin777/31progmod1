#include <iostream>
#include <cstring>

template<typename Tp>
Tp * fill_random(Tp * const arr, size_t size) {
    static Tp _Randseed{Tp(time(nullptr))};

    for (size_t i = 0; i < size; i++) {
        _Randseed = _Randseed * 1103515245 + 12345;
        arr[i] = _Randseed; 
    }
    return arr;
}

template<typename Tp>
class Array final {
private:
    Tp * const m_arr;
    const size_t m_size;
public:
    Array(size_t size) : m_arr{fill_random((Tp*)malloc( \
                size * sizeof(Tp)), size)}, m_size{size} {}

    void operator--(void) {
        const Tp buf{*m_arr};
        memmove(m_arr, m_arr + 1, (m_size - 1) * sizeof(Tp));
        m_arr[m_size - 1] = buf;
    }

    void operator++(void) {
        const Tp buf{m_arr[m_size - 1]};
        memmove(m_arr + 1, m_arr, (m_size - 1) * sizeof(Tp));
        *m_arr = buf;
    }

    void operator<<(size_t shift) {
        shift %= m_size;
        if ((m_size >> 1) < shift) {
            *this >> (m_size - shift); return;
        }
        Tp * const buf {(Tp*)malloc(shift * sizeof(Tp))};
        memcpy(buf, m_arr, shift * sizeof(Tp));
        memmove(m_arr, m_arr + shift, (m_size - shift) * sizeof(Tp));
        memcpy(m_arr + (m_size - shift), buf, shift * sizeof(Tp));
        free(buf);
    } 

    void operator>>(size_t shift) {
        shift %= m_size;
        if ((m_size >> 1) < shift) {
            *this << (m_size - shift); return;
        }
        Tp * const buf {(Tp*)malloc(shift * sizeof(Tp))};
        memcpy(buf, m_arr + (m_size - shift), shift * sizeof(Tp));
        memmove(m_arr + shift, m_arr, (m_size - shift) * sizeof(Tp));
        memcpy(m_arr, buf, shift * sizeof(Tp));
        free(buf);
    }

    friend std::ostream &operator<<(std::ostream &out, \
            const Array &arr) {
        out << "Array = { ";
        for (size_t i{0}; i < arr.m_size; i++)
            out << arr.m_arr[i] << ' ';
        out << '}' << std::endl;
        return out;
    }

    ~Array(void) {
        free(m_arr);
    }
};

int main(int argc, char **argv) {
    if (argc != 2) {
        std::cout << "Must launce: \"" << *argv \
            << " <any number>\"" << std::endl;
        return -1;
    }
    Array<int> arr{strtoul(argv[1], NULL, 10)};
    std::cout << "arr >> 1, arr << 1, arr << 3, arr >> 3, " \
        "arr << 126, arr >> 126;" << std::endl;
    std::cout << arr; ++arr; std::cout << arr;
    --arr; std::cout << arr; arr << 3; std::cout << arr;
    arr >> 3; std::cout << arr; arr << 126; 
    std::cout << arr; arr >> 126; std::cout << arr << std::endl;
    return 0;
}
