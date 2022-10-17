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
    explicit StrBlobPtr(StrBlob&, std::size_t);
    
    // "[]" operators
    std::string& operator[](std::size_t &n);
    const std::string& operator[](std::size_t &n) const;
    
    std::string& deref() const;
    StrBlobPtr& incr();
    
private:
    std::shared_ptr<std::vector<std::string>> check(std::size_t, const std::string&) const;
    std::weak_ptr<std::vector<std::string>> wptr;
    std::size_t curr;
};

#endif
