
#ifndef STRBLOB_H
#define STRBLOB_H

#include <vector>
#include <string>
#include <initializer_list>
#include <memory>
#include <iostream>
#include <fstream>

class StrBlobPtr;
class ConstStrBlobPtr;

class StrBlob {
    friend class StrBlobPtr;
    friend class ConstStrBlobPtr;
    
    friend bool operator==(const StrBlob&, const StrBlob&);
    friend bool operator!=(const StrBlob&, const StrBlob&);
    
    friend bool operator<(const StrBlob&, const StrBlob&);
    friend bool operator>(const StrBlob&, const StrBlob&);
    friend bool operator<=(const StrBlob&, const StrBlob&);
    friend bool operator>=(const StrBlob&, const StrBlob&);
    
    friend std::ostream& operator<<(std::ostream&, const StrBlob&);
    friend std::istream& readStrBlob(std::istream&, StrBlob&);
    
public:
    typedef std::vector<std::string>::size_type size_type;
    
    StrBlob();
    StrBlob(std::initializer_list<std::string>&&);
    StrBlob(const StrBlob&);
    StrBlob& operator=(const StrBlob&);
    ~StrBlob() { }
    
    std::string& operator[](std::size_t&);
    const std::string& operator[](std::size_t&) const;
    
    size_type size() const { return data->size(); }
    bool empty() const { return data->empty(); }
    
    void push_back(const std::string&);
    void push_back(std::string&&);
    void pop_back();
    
    std::string& front();
    std::string& back();
    const std::string& front() const;
    const std::string& back() const;
    
    StrBlobPtr begin();
    StrBlobPtr end();
    ConstStrBlobPtr cbegin() const;
    ConstStrBlobPtr cend() const;
    
private:
    std::shared_ptr<std::vector<std::string>> data;
    
    void check(size_type i, const std::string &msg) const;
};
#endif
