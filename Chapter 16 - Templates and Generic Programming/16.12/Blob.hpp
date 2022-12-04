
#ifndef Blob_hpp
#define Blob_hpp

#include <vector>
#include <initializer_list>
#include <utility>
#include <memory>
#include <string>

template <typename> class BlobPtr;
template <typename> class ConstBlobPtr;
template <typename> class Blob;

template <typename T> bool operator==(const Blob<T>&, const Blob<T>&);

template <typename T> class Blob {
    friend class BlobPtr<T>;
    friend class ConstBlobPtr<T>;
    
    friend bool operator==<T>(const Blob<T>&, const Blob<T>&);
public:
    typedef T value_type;
    typedef typename std::vector<T>::size_type size_type;
    
    Blob();
    Blob(std::initializer_list<T> il);
    
    size_type size() const { return data->size(); }
    bool empty() const { return data->empty(); }
    
    void push_back(const T &t) { data->push_back(t); }
    void push_back(T &&t) { data->push_back(std::move(t)); }
    void pop_back();
    
    T& front();
    T& back();
    
    // constexpr suggested on cpppreference since C++20?
    // constexpr T& front() const;
    // constexpr T& back() const;
    
    // changed back to const (thank you, robert)
    const T& front() const;
    const T& back() const;
    
    // const "[]" operator added (thank you, robert)
    T& operator[] (size_type i);
    const T& operator[] (size_type i) const;
private:
    std::shared_ptr<std::vector<T>> data;
    
    void check(size_type i, const std::string &msg) const;
};

template <typename T>
Blob<T>::Blob() : data(std::make_shared<std::vector<T>>()) { }

template <typename T>
Blob<T>::Blob(std::initializer_list<T> il) : data(std::make_shared<std::vector<T>>(il)) { }

template <typename T>
void Blob<T>::check(size_type i, const std::string &msg) const
{
    if (i >= data->size()) { throw std::out_of_range(msg); }
}

template <typename T> void Blob<T>::pop_back()
{
    check(0, "pop_back on empty Blob");
    data->pop_back();
}

template <typename T> T& Blob<T>::front()
{
    check(0, "front on empty Blub");
    return data->front();
}

template <typename T> const T& Blob<T>::front() const
{ return Blob::front(); }

template <typename T> T& Blob<T>::back()
{
    check(0, "back on empty Blob");
    return data->back();
}

template <typename T> const T& Blob<T>::back() const
{ return Blob::back(); }

template <typename T> T& Blob<T>::operator[] (size_type i)
{
    check(i, "subscript out of range");
    return (*data)[i];
}

template <typename T> const T& Blob<T>::operator[] (size_type i) const
{ return Blob::operator[](i); }

template <typename T>
bool operator==(const Blob<T> &lhs, const Blob<T> &rhs)
{ return lhs->data == rhs->data; }

#endif /* Blob_hpp */
