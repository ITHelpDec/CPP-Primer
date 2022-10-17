
#ifndef STRBLOBPTR_H
#define STRBLOBPTR_H

#include <string>
#include <vector>
#include <memory>

class StrBlob;

class StrBlobPtr {
    friend class StrBlob;
    
    friend std::ostream& printStrBlobPtr(std::ostream&, const StrBlobPtr&);
    
    friend bool operator==(const StrBlobPtr&, const StrBlobPtr&);
    friend bool operator!=(const StrBlobPtr&, const StrBlobPtr&);
    
    friend bool operator<(const StrBlobPtr&, const StrBlobPtr&);
    friend bool operator>(const StrBlobPtr&, const StrBlobPtr&);
    friend bool operator<=(const StrBlobPtr&, const StrBlobPtr&);
    friend bool operator>=(const StrBlobPtr&, const StrBlobPtr&);
    
public:
    StrBlobPtr();
    StrBlobPtr(StrBlob&, std::size_t = 0);
    
    std::string& operator[](std::size_t &n);
    const std::string& operator[](std::size_t &n) const;
    
    StrBlobPtr& operator++();
    StrBlobPtr& operator--();
    StrBlobPtr operator++(int);
    StrBlobPtr operator--(int);
    
    StrBlobPtr& operator+=(std::size_t&);
    StrBlobPtr& operator-=(std::size_t&);
    StrBlobPtr operator+(std::size_t&) const;
    StrBlobPtr operator-(std::size_t&) const;
    
    // member access operators
    std::string& operator*() const;
    std::string* operator->() const;
    
    std::string& deref() const;
    StrBlobPtr& incr();
    
private:
    std::shared_ptr<std::vector<std::string>> check(std::size_t, const std::string&) const;
    std::weak_ptr<std::vector<std::string>> wptr;
    std::size_t curr;
};

#endif
