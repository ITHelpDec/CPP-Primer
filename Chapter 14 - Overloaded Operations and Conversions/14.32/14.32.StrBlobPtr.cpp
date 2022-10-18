
#include "StrBlobPtr.hpp"
#include "StrBlob.hpp"

StrBlobPtr::StrBlobPtr() : curr(0) { }
StrBlobPtr::StrBlobPtr(StrBlob &a, std::size_t sz) : wptr(a.data), curr(sz) { }

std::string& StrBlobPtr::operator[](std::size_t &n) { return (*wptr.lock())[n]; }
const std::string& StrBlobPtr::operator[](std::size_t &n) const { return (*wptr.lock())[n]; }

StrBlobPtr& StrBlobPtr::operator++()
{
    check(curr, "increment past end of StrBlobPtr");
    ++curr;
    return *this;
}

StrBlobPtr& StrBlobPtr::operator--()
{
    check(curr, "decrement before begin of StrBlobPtr");
    --curr;
    return *this;
}

StrBlobPtr StrBlobPtr::operator++(int)
{
    StrBlobPtr ret = *this;
    ++*this;
    return ret;
}

StrBlobPtr StrBlobPtr::operator--(int)
{
    StrBlobPtr ret = *this;
    --*this;
    return ret;
}

StrBlobPtr& StrBlobPtr::operator+=(std::size_t &n)
{
    curr += n;
    check(curr, "increment past end of StrBlobPtr");
    return *this;
}

StrBlobPtr& StrBlobPtr::operator-=(std::size_t &n)
{
    curr -= n;
    check(curr, "increment past end of StrBlobPtr");
    return *this;
}

StrBlobPtr StrBlobPtr::operator+(std::size_t &n) const
{
    StrBlobPtr ret = *this;
    ret += n;
    return ret;
}

StrBlobPtr StrBlobPtr::operator-(std::size_t &n) const
{
    StrBlobPtr ret = *this;
    ret -= n;
    return ret;
}

std::string& StrBlobPtr::operator*() const
{
    auto p = check(curr, "dereference past end");
    return (*p)[curr];
}

std::string* StrBlobPtr::operator->() const { return &this->operator*();}

std::string& StrBlobPtr::deref() const
{
    auto p = check(curr, "dereference past end");
    return (*p)[curr];
}

StrBlobPtr& StrBlobPtr::incr()
{
    check(curr, "increment past end of StrBlobPtr");
    ++curr;
    return *this;
}

std::shared_ptr<std::vector<std::string>> StrBlobPtr::check(std::size_t i, const std::string &msg) const
{
    auto ret = wptr.lock();
    if (!ret)
        throw std::runtime_error("unbound StrBlobPtr");
    if (i >= ret->size())
        throw std::out_of_range(msg);
    return ret;
}

bool operator==(const StrBlobPtr &lhs, const StrBlobPtr &rhs)
{ return lhs.wptr.lock() == rhs.wptr.lock() && lhs.curr == rhs.curr; }

bool operator!=(const StrBlobPtr &lhs, const StrBlobPtr &rhs) { return !(lhs == rhs); }

bool operator<(const StrBlobPtr &lhs, const StrBlobPtr &rhs)
{ return lhs.wptr.lock() < rhs.wptr.lock() && lhs.curr < rhs.curr; }
bool operator>(const StrBlobPtr &lhs, const StrBlobPtr &rhs) { return rhs < lhs; }
bool operator<=(const StrBlobPtr &lhs, const StrBlobPtr &rhs) { return !(lhs > rhs); }
bool operator>=(const StrBlobPtr &lhs, const StrBlobPtr &rhs) { return !(lhs < rhs); }

void printStrBlobPter(const StrBlobPtr &sbp)
{
    int i = 0;
    std::cout << "\" ";
    try {
        for (auto sbp_it = sbp; i != sbp.deref().size(); sbp_it.incr(), ++i)
            std::cout << sbp_it.deref() << " ";
        std::cout << "\"\n" << std::endl;
    } catch (std::out_of_range err) {
        std::cerr << "\"\n" << err.what() << std::endl;
    } catch (std::exception err) {
        std::cerr << "\"\n" << err.what() << std::endl;
    }
}

