// Exercise 18.07:
/*
 Define your Blob and BlobPtr classes from Chapter 16 to use function try blocks for their constructors.
*/

#ifndef BlobPtr_hpp
#define BlobPtr_hpp

#include <iostream>
#include <memory>
#include <vector>
#include <string>

// added
#include <stdexcept>

template <typename> class Blob;
template <typename> class BlobPtr;

template <typename T> bool operator==(const BlobPtr<T>&, const BlobPtr<T>&);
template <typename T> bool operator!=(const BlobPtr<T>&, const BlobPtr<T>&);

template <typename T> bool operator< (const BlobPtr<T>&, const BlobPtr<T>&);
template <typename T> bool operator>(const BlobPtr<T>&, const BlobPtr<T>&);
template <typename T> bool operator<=(const BlobPtr<T>&, const BlobPtr<T>&);
template <typename T> bool operator>=(const BlobPtr<T>&, const BlobPtr<T>&);

template <typename T> class BlobPtr {
    friend bool operator==<T>(const BlobPtr<T>&, const BlobPtr<T>&);
    friend bool operator!=<T>(const BlobPtr<T>&, const BlobPtr<T>&);
    
    friend bool operator< <T>(const BlobPtr<T>&, const BlobPtr<T>&);
    friend bool operator> <T>(const BlobPtr<T>&, const BlobPtr<T>&);
    friend bool operator<=<T>(const BlobPtr<T>&, const BlobPtr<T>&);
    friend bool operator>=<T>(const BlobPtr<T>&, const BlobPtr<T>&);
public:
    // here
    BlobPtr() try : curr(0)
    { } catch (const std::bad_alloc &e) {
        std::cerr << "Unable to create pointer" << std::endl;
    }
    
    // ...and here
    BlobPtr(Blob<T> &a, std::size_t sz = 0) try : wptr(a.data), curr(sz)
    { } catch (const std::bad_alloc &e) {
        std::cerr << "Unable to create pointer" << std::endl;
    }
    
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

template <typename T> const T& BlobPtr<T>::operator*() const
{
    return BlobPtr::operator*();
}

template <typename T>
std::shared_ptr<std::vector<T>> BlobPtr<T>::check(std::size_t pos, const std::string &msg) const
{
    std::shared_ptr<std::vector<T>> ret = wptr.lock();
    if (!ret) { throw std::runtime_error("unbound BlobPtr"); }
    else if (pos > (*ret).size()) { throw std::out_of_range(msg); }
    return ret;
}

template <typename T> bool operator==(const BlobPtr<T> &lhs, const BlobPtr<T> &rhs)
{
    if (lhs.wptr.lock() != rhs.wptr.lock()) {
        throw std::runtime_error("Pointers to different Blobs!");
    } return lhs.curr == rhs.curr;
}

template <typename T> bool operator!=(const BlobPtr<T> &lhs, const BlobPtr<T> &rhs)
{
    return !(lhs == rhs);
}

template <typename T> bool operator<(const BlobPtr<T> &lhs, const BlobPtr<T> &rhs)
{
    if (lhs.wptr.lock() != rhs.wptr.lock()) {
        throw std::runtime_error("Pointers to different Blobs!");
    } return lhs.curr < rhs.curr;
}

template <typename T> bool operator>(const BlobPtr<T> &lhs, const BlobPtr<T> &rhs)
{
    return rhs < lhs;
}

template <typename T> bool operator<=(const BlobPtr<T> &lhs, const BlobPtr<T> &rhs)
{
    return !(lhs > rhs);
}

template <typename T> bool operator>=(const BlobPtr<T> &lhs, const BlobPtr<T> &rhs)
{
    return !(lhs < rhs);
}

#endif /* BlobPtr_hpp */
