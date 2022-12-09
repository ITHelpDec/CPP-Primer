// Exercise 16.24:
/*
 Add a constructor that takes two iterators to your Blob template.
 
 >> Could also do it in two files and #include "Blob.hpp"
 >> constructor highlighted in comments
*/

#include <vector>
#include <initializer_list>
#include <utility>
#include <memory>
#include <string>
#include <iostream>

template <typename> class BlobPtr;
template <typename> class ConstBlobPtr;
template <typename> class Blob;

template <typename T> bool operator==(const Blob<T>&, const Blob<T>&);

template <typename T> class Blob {
    friend class BlobPtr<T>;
    
    friend bool operator==<T>(const Blob<T>&, const Blob<T>&);
public:
    typedef T value_type;
    typedef typename std::vector<T>::size_type size_type;
    
    Blob();
    Blob(std::initializer_list<T> il);
    
    // constructor using iteraotrs – defined outside of class
    template <typename It> Blob(It b, It e);
    
    size_type size() const { return data->size(); }
    bool empty() const { return data->empty(); }
    
    void push_back(const T &t) { data->push_back(t); }
    void push_back(T &&t) { data->push_back(std::move(t)); }
    void pop_back();
    
    T& front();
    T& back();
    
    const T& front() const;
    const T& back() const;

    T& operator[] (size_type i);
    const T& operator[] (size_type i) const;
    
private:
    std::shared_ptr<std::vector<T>> data;
    
    void check(size_type i, const std::string &msg) const;
};

template <typename T>
inline Blob<T>::Blob() : data(std::make_shared<std::vector<T>>()) { }

template <typename T>
inline Blob<T>::Blob(std::initializer_list<T> il) : data(std::make_shared<std::vector<T>>(il)) { }

// constructor defined below
template< typename T>
template <typename It>
inline Blob<T>::Blob(It b, It e) : data(std::make_shared<std::vector<T>>(b, e)) { }

template <typename T>
inline void Blob<T>::check(size_type i, const std::string &msg) const
{
    if (i >= data->size()) { throw std::out_of_range(msg); }
}

template <typename T> inline void Blob<T>::pop_back()
{
    check(0, "pop_back on empty Blob");
    data->pop_back();
}

template <typename T> inline T& Blob<T>::front()
{
    check(0, "front on empty Blub");
    return data->front();
}

template <typename T> inline const T& Blob<T>::front() const
{ return Blob::front(); }

template <typename T> inline T& Blob<T>::back()
{
    check(0, "back on empty Blob");
    return data->back();
}

template <typename T> inline const T& Blob<T>::back() const
{ return Blob::back(); }

template <typename T> inline T& Blob<T>::operator[] (size_type i)
{
    check(i, "subscript out of range");
    return (*data)[i];
}

template <typename T> inline const T& Blob<T>::operator[] (size_type i) const
{ return Blob::operator[](i); }

template <typename T> inline bool operator==(const Blob<T> &lhs, const Blob<T> &rhs)
{ return *lhs.data == *rhs.data; }

int main()
{
    std::vector<int> ivec = { 0, 1, 2, 3 };
    
    Blob<int> iblob(ivec.begin(), ivec.end());
    
    for (int i = 0; i != iblob.size(); ++i) {
        std::cout << iblob[i] << " ";
    } std::cout << std::endl;
    
    return 0;
}
