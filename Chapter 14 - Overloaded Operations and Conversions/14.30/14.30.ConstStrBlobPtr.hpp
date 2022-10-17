
#ifndef CONSTSTRBLOBPTR_H
#define CONSTSTRBLOBPTR_H

#include <string>
#include <vector>
#include <memory>

class StrBlob;

class ConstStrBlobPtr {
    friend class StrBlob;
    friend std::ostream& printConstStrBlobPtr(std::ostream&, const ConstStrBlobPtr&);
    
    friend bool operator==(const ConstStrBlobPtr&, const ConstStrBlobPtr&);
    friend bool operator!=(const ConstStrBlobPtr&, const ConstStrBlobPtr&);
    
    friend bool operator<(const ConstStrBlobPtr&, const ConstStrBlobPtr&);
    friend bool operator>(const ConstStrBlobPtr&, const ConstStrBlobPtr&);
    friend bool operator<=(const ConstStrBlobPtr&, const ConstStrBlobPtr&);
    friend bool operator>=(const ConstStrBlobPtr&, const ConstStrBlobPtr&);
    
public:
    ConstStrBlobPtr();
    ConstStrBlobPtr(const StrBlob&, std::size_t = 0);
    
    const std::string& operator[](std::size_t &n) const;
    
    // member access functions
    const std::string& operator*() const;
    const std::string* operator->() const;
    
    std::string& deref() const;
    ConstStrBlobPtr& incr();
    
private:
    std::shared_ptr<std::vector<std::string>> check(std::size_t, const std::string&) const;
    std::weak_ptr<std::vector<std::string>> wptr;
    std::size_t curr;
};

#endif

