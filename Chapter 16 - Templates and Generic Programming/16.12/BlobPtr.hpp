
#ifndef BlobPtr_hpp
#define BlobPtr_hpp

#include <iostream>
#include <memory>
#include <vector>
#include <string>

template <typename> class Blob;

template <typename T> class BlobPtr {
public:
    BlobPtr() : curr(0) { }
    BlobPtr(Blob<T> &a, std::size_t sz = 0) : wptr(a.data), curr(sz) { }
    
    T& operator*()
    {
        auto p = check(curr, "dereference past end");
        return (*p)[curr];
    }
    
    const T& operator*() const;
    
    BlobPtr& operator++();
    BlobPtr& operator--();
private:
    std::shared_ptr<std::vector<T>> check(std::size_t, const std::string&) const;
    std::weak_ptr<std::vector<T>> wptr;
    std::size_t curr;
};

template <typename T>
// BlobPtr<T> BlobPtr<T>::operator++() ("&" missing in page 664)
BlobPtr<T>& BlobPtr<T>::operator++()
{
    BlobPtr ret = *this;
    ++*this;
    return ret;
}

template <typename T>
BlobPtr<T>& BlobPtr<T>::operator--()
{
    BlobPtr ret = *this;
    --*this;
    return ret;
}

template <typename T>
const T& BlobPtr<T>::operator*() const
{ return BlobPtr::operator*(); }

#endif /* BlobPtr_hpp */
