#include <iostream>
#include <cstring>


template<typename Tp>
Tp min(const Tp &first, const Tp &second) {
    return first < second ? first : second;
}

template<typename Tp>
void swap(Tp &first, Tp &second) {
    Tp temp {first};
    first = second;
    second = temp;
}


template<typename Tp>
class Array {
private:
    Tp *m_arr{nullptr};
    size_t m_size{0UL};
public:
    Array(void) : m_arr{nullptr}, m_size{0UL} {}
    Array(size_t size) : m_arr{calloc(size, \
            sizeof(Tp))}, m_size{size} {}
    Array(const Array<Tp> &arr) : \
        m_arr{(Tp*)memcpy(malloc(arr.m_size * \
        sizeof(Tp)), arr.m_arr, arr.m_size * sizeof(Tp))}, \
        m_size{arr.m_size} {}

    void pushBack(Tp newElement) {
        size_t oldSize{size()};
        resize(oldSize + 1UL);
        set(oldSize, newElement);
    }

    void pushTop(Tp newElement) {
        insert(0UL, newElement);
    }

    Tp back(void) const {
        return at(size() - 1UL);
    }

    Tp top(void) const {
        return at(0UL);
    }
    void insert(size_t index, const Tp newValue) {
        const size_t oldSize{size()};
        resize(oldSize + 1UL);
        index %= oldSize;
        memmove(m_arr + index + 1UL, m_arr + index, \
                (oldSize - index - 1UL) * sizeof(Tp));
        set(index, newValue);
    }

    void insert(size_t indexStart, const Tp * \
            const newValues, const size_t count) {
        const size_t originalSize{size()};
        resize(originalSize + count);
        if (originalSize) indexStart %= originalSize;

        const size_t elementsToMove{originalSize - indexStart};
        memmove(m_arr + indexStart + count,
                m_arr + indexStart,
                elementsToMove * sizeof(Tp));
        memcpy(m_arr + indexStart, newValues, \
                count * sizeof(Tp));
    }

    void erase(size_t indexStart, size_t indexStop) {
        if (indexStart < indexStop && indexStop < size()) {
            memmove(m_arr + indexStart, m_arr + indexStop, \
                    (size() - indexStop - 1UL) * sizeof(Tp));
            resize(indexStop - indexStart);
        }
    }

    Tp &operator[](size_t index) {
        return m_arr[index % size()];
    }

    Tp at(size_t index) const {
        return m_arr[index % size()];
    }

    void set(size_t index, Tp newValue) {
        m_arr[index % size()] = newValue;
    }

    void set(size_t index, const Tp * \
            const newValues, size_t count) {
        memmove(m_arr + index, newValues, \
                count * sizeof(Tp));
    }

    void clear(void) {
        if (m_arr) free(m_arr);
        m_size = 0UL;
    }

    size_t size(void) const {
        return m_size;
    }

    void resize(size_t newSize) {
        Tp * const newArr{(Tp*)realloc(m_arr, \
                newSize * sizeof(Tp))}; 
        if (newSize > m_size)
            memset(newArr + m_size, 0, \
                (newSize - m_size) * sizeof(Tp));
        m_arr = newArr;
        m_size = newSize;
    }
private:
    void resizeRaw(size_t newSize) {
        if (m_arr) free(m_arr);
        m_arr = (Tp*)calloc(newSize, sizeof(Tp));
        m_size = newSize;
    }
        
    void hPush(size_t height, size_t pos) {
        while (true) {
            if (pos - height < 0UL)
                break;
            if (m_arr[pos - height] <= m_arr[pos])
                break;
            swap(operator[](pos - height), operator[](pos));
            pos -= height;
        }
    }

    void hSort(size_t height, size_t pos) {
        while (pos < m_size) {
            hPush (height, pos);
            pos += height;
        }
    }
    void merge(size_t left, size_t mid, size_t right) {
        Array<Tp> leftArr{}, rightArr{};

        leftArr.insert(0UL, m_arr + left, mid - left + 1UL);
        rightArr.insert(0UL, m_arr + mid + 1UL, right - mid);

        size_t i{0UL}, j{0UL}, k{left};
        for (; i < leftArr.size() \
                && j < rightArr.size(); k++) {
            if (leftArr[i] <= rightArr[j])
                m_arr[k] = leftArr[i], i++;
            else
                m_arr[k] = rightArr[j], j++;
        }

        if (i < leftArr.size()) {
            const size_t remnantLeft{leftArr.size() - i};
            set(k, leftArr.m_arr + i, remnantLeft);
            k += remnantLeft;
        }
        if (j < rightArr.size()) {
            const size_t remnantRight{rightArr.size() - j};
            set(k, rightArr.m_arr + j, remnantRight);
        }
    }

    void mergeSort(const size_t left, const size_t right) {
        if (left < right && size()) {
            const size_t mid{left + ((right - left) >> 1UL)};
            mergeSort(left, mid);
            mergeSort(mid + 1UL, right);
            merge(left, mid, right);
        }
    }
public:
    void shellSort(void) {
        for (size_t height{m_size >> 1UL}; height >= 1UL; height >>= 1UL)
            for (size_t pos{height}; pos < (height << 1UL); pos++)
                hSort(height, pos);
    }

    void bubbleSort(void) {
        for (size_t i{0UL}; i < m_size - 1UL; i++)
            for (size_t j{0UL}; j < m_size - i - 1UL; j++)
                if (at(j) > at(j + 1UL))
                    swap(operator[](j), operator[](j + 1UL));
    }

    void mergeSort(void) {
        if (size())
            mergeSort(0UL, size() - 1UL);
    }
    void insertionSort(void) {
        for (size_t i{1UL}; i < size(); i++) {
            const Tp key{at(i)};
            size_t j{i - 1UL}; 
            for (; j != (size_t)-1L && at(j) > key; j--)
                set(j + 1UL, at(j));
            set(j + 1UL, key);
        }
    }

    friend std::istream& operator>>(std::istream & in, \
            Array<Tp> &arr) {
        in >> arr.m_size;
        arr.resizeRaw(arr.size());
        Tp *endPtr{arr.m_arr + arr.size()};
        for (Tp *beginPtr{arr.m_arr}; \
                beginPtr < endPtr; beginPtr++)
            in >> *beginPtr;
        return in;
    }

    friend std::ostream& operator<<(std::ostream & out, \
            const Array<Tp> &arr) {
        out << "Array = { ";
        Tp *endPtr{arr.m_arr + arr.m_size};
        for (Tp *beginPtr{arr.m_arr}; \
                beginPtr < endPtr; beginPtr++)
            out << *beginPtr << ' ';
        out << '}' << std::endl;
        return out;
    }

    ~Array(void) {
        if (m_arr) free(m_arr);
    }
};

int main () {
    Array<int> arr{};
    std::cin >> arr;
    std::cout << "Basic: " << std::endl \
        << arr << std::endl;
    {
        Array<int> shellArr{arr};
        shellArr.shellSort();
        std::cout << "shellSort: " << std::endl \
            << shellArr << std::endl;
    }
    {
        Array<int> bubbleArr{arr};
        bubbleArr.bubbleSort();
        std::cout << "bubbleSort: " << std::endl \
            << bubbleArr << std::endl;
    }
    {
        Array<int> insertionArr{arr};
        insertionArr.insertionSort();
        std::cout << "insertionSort: " << std::endl \
            << insertionArr << std::endl;
    }
    {
        Array<int> mergeArr{arr};
        mergeArr.mergeSort();
        std::cout << "mergeSort: " << std::endl \
            << mergeArr << std::endl;
    }
	return 0;
}
