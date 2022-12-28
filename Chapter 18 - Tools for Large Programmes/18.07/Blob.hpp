// Exercise 18.07:
/*
 Define your Blob and BlobPtr classes from Chapter 16 to use function try blocks for their constructors.
*/

#ifndef Blob_hpp
#define Blob_hpp

#include "BlobPtr.hpp"

#include <initializer_list>
#include <utility>

template <typename> class BlobPtr;
template <typename> class Blob;

template <typename T> bool operator==(const Blob<T>&, const Blob<T>&);
template <typename T> bool operator!=(const Blob<T>&, const Blob<T>&);

template <typename T> bool operator<(const Blob<T>&, const Blob<T>&);
template <typename T> bool operator>(const Blob<T>&, const Blob<T>&);
template <typename T> bool operator<=(const Blob<T>&, const Blob<T>&);
template <typename T> bool operator>=(const Blob<T>&, const Blob<T>&);

template <typename T> class Blob {
    friend class BlobPtr<T>;
    
    friend bool operator==<T>(const Blob<T>&, const Blob<T>&);
    friend bool operator!=<T>(const Blob<T>&, const Blob<T>&);
    
    friend bool operator< <T>(const Blob<T>&, const Blob<T>&);
    friend bool operator> <T>(const Blob<T>&, const Blob<T>&);
    friend bool operator<=<T>(const Blob<T>&, const Blob<T>&);
    friend bool operator>=<T>(const Blob<T>&, const Blob<T>&);
public:
    typedef T value_type;
    typedef typename std::vector<T>::size_type size_type;
    
    // contructors
    Blob();
    Blob(std::initializer_list<T> il);
    
    // constructor using iteraotrs – defined outside of class
    template <typename It> Blob(It b, It e);
    
    // copy and copy assignment
    // Blob(const Blob&);
    // Blob& operator=(const Blob&);
    
    // move and move assignment
    // Blob(Blob&&);
    //Blob& operator=(Blob&&);
    
    // destructor
    // ~Blob() { }
    
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
    
     typename std::vector<T>::iterator begin() { return data->begin(); }
     typename std::vector<T>::iterator end() { return data->end(); }
    // typename std::vector<T>::iterator end() { return data + data->size(); }
    
private:
    std::shared_ptr<std::vector<T>> data;
    
    void check(size_type i, const std::string &msg) const;
};

// here
template <typename T>
inline Blob<T>::Blob() try : data(std::make_shared<std::vector<T>>()) {
} catch (const std::bad_alloc &e) {
    std::cerr << "error: " << e.what() << "\n>>> ran out of memory!" << std::endl;
}

// here
template <typename T>
inline Blob<T>::Blob(std::initializer_list<T> il) try : data(std::make_shared<std::vector<T>>(il)) {
} catch (const std::bad_alloc &e) {
    std::cerr << "error: " << e.what() << "\n>>> ran out of memory!" << std::endl;
}

// ...and here
template< typename T>
template <typename It>
inline Blob<T>::Blob(It b, It e) try : data(std::make_shared<std::vector<T>>(b, e)) {
} catch (const std::length_error &le) {
    std::cerr << "error: " << le.what() << "\n>>> use iterators instead pointers" << std::endl;
}

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
{
    return Blob::front();
}

template <typename T> inline T& Blob<T>::back()
{
    check(0, "back on empty Blob");
    return data->back();
}

template <typename T> inline const T& Blob<T>::back() const
{
    return Blob::back();
}

template <typename T> inline T& Blob<T>::operator[] (size_type i)
{
    check(i, "subscript out of range");
    return (*data)[i];
}

template <typename T> inline const T& Blob<T>::operator[] (size_type i) const
{
    return Blob::operator[](i);
}

template <typename T> inline bool operator==(const Blob<T> &lhs, const Blob<T> &rhs)
{
    return *lhs.data == *rhs.data;
}

template <typename T> inline bool operator!=(const Blob<T> &lhs, const Blob<T> &rhs)
{
    return !(lhs == rhs);
}

template <typename T> inline bool operator<(const Blob<T> &lhs, const Blob<T> &rhs)
{
    return lhs.size() < rhs.size();
}

template <typename T> inline bool operator>(const Blob<T> &lhs, const Blob<T> &rhs)
{
    return rhs < lhs;
}

template <typename T> inline bool operator<=(const Blob<T> &lhs, const Blob<T> &rhs)
{
    return !(lhs > rhs);
}

template <typename T> inline bool operator>=(const Blob<T> &lhs, const Blob<T> &rhs)
{
    return !(lhs < rhs);
}

#endif /* Blob_hpp */
