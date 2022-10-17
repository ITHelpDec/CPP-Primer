#include "ConstStrBlobPtr.hpp"
#include "StrBlob.hpp"

ConstStrBlobPtr::ConstStrBlobPtr() : curr(0) { }
ConstStrBlobPtr::ConstStrBlobPtr(const StrBlob &a, std::size_t sz = 0) : wptr(a.data), curr(sz) { }

// "[]" operators
const std::string& ConstStrBlobPtr::operator[](std::size_t &n) const { return (*wptr.lock())[n]; }

std::string& ConstStrBlobPtr::deref() const
{
    auto p = check(curr, "dereference past end");
    return (*p)[curr];
}

ConstStrBlobPtr& ConstStrBlobPtr::incr()
{
    check(curr, "increment past end of StrBlobPtr");
    ++curr;
    return *this;
}

std::shared_ptr<std::vector<std::string>> ConstStrBlobPtr::check(std::size_t i, const std::string &msg) const
{
    auto ret = wptr.lock();
    if (!ret)
        throw std::runtime_error("unbound StrBlobPtr");
    if (i >= ret->size())
        throw std::out_of_range(msg);
    return ret;
}

bool operator==(const ConstStrBlobPtr &lhs, const ConstStrBlobPtr &rhs)
{
    // check they're the same and the current elements are the same
    return lhs.wptr.lock() == rhs.wptr.lock() && lhs.curr == rhs.curr;
}
bool operator!=(const ConstStrBlobPtr &lhs, const ConstStrBlobPtr &rhs) { return !(lhs == rhs); }

bool operator<(const ConstStrBlobPtr &lhs, const ConstStrBlobPtr &rhs)
{
    return lhs.wptr.lock() < rhs.wptr.lock() && lhs.curr < rhs.curr;
}
bool operator>(const ConstStrBlobPtr &lhs, const ConstStrBlobPtr &rhs) { return rhs < lhs; }
bool operator<=(const ConstStrBlobPtr &lhs, const ConstStrBlobPtr &rhs) { return !(lhs > rhs); }
bool operator>=(const ConstStrBlobPtr &lhs, const ConstStrBlobPtr &rhs) { return !(lhs < rhs); }

void printConstStrBlobPter(const ConstStrBlobPtr &sbp)
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
