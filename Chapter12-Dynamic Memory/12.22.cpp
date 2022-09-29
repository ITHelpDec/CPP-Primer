// Exercise 12.21:
/*
 What changes would need to be made to StrBlobPtr to create a class that can be used with a const StrBlob?
 Define a class named ConstStrBlobPtr that can point to a const StrBlob.
 
 >> All amendments addressed with comments
 >> lines without comments have remained unchanged
*/

#include <vector>
#include <string>
#include <initializer_list>
#include <memory>

// announce ptr classes early to be used in StrBlob
class StrBlobPtr;
class ConstStrBlobPtr;

class StrBlob {
    friend class StrBlobPtr;
    
    // add friend class for ConstStrBlobPtr
    friend class ConstStrBlobPtr;
public:
    typedef std::vector<std::string>::size_type size_type;
    
    StrBlob();
    StrBlob(std::initializer_list<std::string> il);
    
    size_type size() const { return data->size(); }
    bool empty() const { return data->empty(); }
    
    void push_back(const std::string &t) { data->push_back(t); }
    void pop_back();
    
    std::string& front();
    std::string& back();
    
    const std::string& front() const;
    const std::string& back() const;
    
    StrBlobPtr begin();
    StrBlobPtr end();
    
    // create cbegin and cend iterators
    ConstStrBlobPtr cbegin();
    ConstStrBlobPtr cend();
    
private:
    std::shared_ptr<std::vector<std::string>> data;
    void check(size_type i, const std::string &msg) const;
};

// class StrBlobPtr {
class ConstStrBlobPtr {
public:
    // StrBlobPtr() : curr(0) { }
    ConstStrBlobPtr() : curr(0) { }
    // StrBlobPtr(StrBlob &a, std::size_t sz = 0) : wptr(a.data), curr(sz) { }
    explicit ConstStrBlobPtr(const StrBlob &a, std::size_t sz = 0) : wptr(a.data), curr(sz) { }
    // std::string& deref() const;
    const std::string& deref() const;
    
    StrBlobPtr incr();
private:
    std::shared_ptr<std::vector<std::string>> check(std::size_t, const std::string&) const;
    std::weak_ptr<std::vector<std::string>> wptr;
    std::size_t curr;
};
